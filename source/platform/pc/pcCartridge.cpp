/******************************************************************************
 ** Copyright (c) 2010 Seed Developers
 ** All rights reserved
 ** Contact: licensing@seedframework.org
 ** Website: http://www.seedframework.org

 ** This file is part of the Seed Framework.

 ** Commercial Usage
 ** Seed Framework is available under proprietary license for those who cannot,
 ** or choose not to, use LGPL and GPL code in their projects (eg. iPhone,
 ** Nintendo Wii and others).

 ** GNU Lesser General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU Lesser
 ** General Public License version 2.1 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.LGPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU Lesser General Public License version 2.1 requirements
 ** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 **
 ** In addition, as a special exception, Seed developers gives you certain
 ** additional rights. These rights are described in the Seed Framework LGPL
 ** Exception version 1.1, included in the file LGPL_EXCEPTION.txt in this
 ** package.
 **
 ** If you have questions regarding the use of this file, please contact
 ** Seed developers at licensing@seedframework.org.
 **
 *****************************************************************************/

/*! \file pcCartridge.cpp
	\author	Danny Angelo Carminati Grein
	\brief Cartridge PC Implementation
*/

#include "Cartridge.h"
#include "LeakReport.h"

#if defined(BUILD_PC)

#include "Log.h"
#include "FileSystem.h"

#include <stdio.h>

#define TAG "[Cartridge] "

namespace Seed { namespace PC {

SEED_SINGLETON_DEFINE(Cartridge)

Cartridge::Cartridge()
	: iType(0)
	, iCurrentSlot(-1)
	, pData(NULL)
{
}

Cartridge::~Cartridge()
{
}

bool Cartridge::Initialize()
{
	Log(TAG "Initializing...");
	this->Reset();
	Log(TAG "Initialization completed.");

	return true;
}

bool Cartridge::Reset()
{
	Free(this->pData);

	iType = 0;
	iSize = 0;
	MEMSET(strPath, '\0', PC_MAX_PATH);

	return true;
}

bool Cartridge::Shutdown()
{
	this->Reset();
	Log(TAG "Terminating...");
	Log(TAG "Terminated.");
	return true;
}

bool Cartridge::Prepare(eCartridgeSize size)
{
	iType = size;
	iSize = this->GetCardType(size);

	const FilePath *p = pFileSystem->GetWriteableDirectory();
	ASSERT_MSG(p!=NULL, "You must set a WriteableDirectory!");

	MEMSET(strPath, '\0', sizeof(strPath));

	PATHCOPY(strPath, p, PC_MAX_PATH);
	PATHCAT(strPath, PATH_SEPARATOR, PC_MAX_PATH - 1);
	PATHCAT(strPath, CARTRIDGE_FILENAME, PC_MAX_PATH - PATHLEN(strPath) - 1);

	this->pData = static_cast<u8 *>(Alloc(iSize));
	MEMSET(this->pData, 0, iSize);

	if (!this->Verify(strPath, iSize))
	{
		if (!this->CreateSaveFile())
		{
			Log(TAG "ERROR: trying to create save file!");
			return false;
		}
	}

	return true;
}

bool Cartridge::Read(u32 src, void *dest, u32 len)
{
	if (src >= iSize)
	{
		Log(TAG "%s:%d: source address error.", __FILE__, __LINE__);
		return false;
	}

	if (len > iSize)
	{
		Log(TAG "%s:%d: length error.", __FILE__, __LINE__);
		return false;
	}

	if (src + len > iSize)
	{
		Log(TAG "%s:%d: source address error.", __FILE__, __LINE__);
		return false;
	}

	s32 iResult = 0;
	FILE *pFp = FOPEN(strPath, "rb");
	if (!pFp)
	{
		Info(TAG "fopen %s failed", strPath);
		this->eLastError = Seed::ErrorAccessDenied;
		return false;
	}

	iResult = fseek(pFp, 0, SEEK_SET);
	if (iResult)
	{
		Log(TAG "fseek failed: %d", iResult);
		fclose(pFp);
		this->eLastError = Seed::ErrorAccessDenied;
		return false;
	}

	u32 iAmountRead = (u32)fread(this->pData, 1, iSize, pFp);
	if (iAmountRead != iSize)
	{
		Log(TAG "fread: could not load save data!");
		fclose(pFp);
		this->eLastError = Seed::ErrorDeviceFull;
		return false;
	}

	iResult = fseek(pFp, static_cast<s32>(src), SEEK_SET);
	if (iResult)
	{
		Log(TAG "fseek failed: %d", iResult);
		fclose(pFp);
		this->eLastError = Seed::ErrorAccessDenied;
		return false;
	}

	iAmountRead = (u32)fread(dest, 1, len, pFp);
	fclose(pFp);

	if (iAmountRead != len)
	{
		Log(TAG "fread: Could not read all the data requested: AmountRead = %d Requested = %d\n", iAmountRead, len);
		this->eLastError = Seed::ErrorDeviceFull;
		return false;
	}

	return true;
}

bool Cartridge::Write(u32 dest, const void *src, u32 len)
{
	if (dest >= iSize)
	{
		Log(TAG "%s:%d: dest address error.", __FILE__, __LINE__);
		return false;
	}

	if (len > iSize)
	{
		Log(TAG "%s:%d: length error.", __FILE__, __LINE__);
		return false;
	}

	if (dest + len > iSize)
	{
		Log(TAG "%s:%d: dest address error.", __FILE__, __LINE__);
		return false;
	}

	s32 iResult = 0;

	u8 *ptr = &this->pData[dest];
	memcpy(ptr, src, len);

	FILE *pFp = FOPEN(strPath, "wb+");
	if (!pFp)
	{
		Info(TAG "fopen: Could not open '%s' for writing", strPath);
		this->eLastError = Seed::ErrorAccessDenied;
		return false;
	}

	iResult = fseek(pFp, 0, SEEK_SET); //fseek(pFp, static_cast<s32>(dest), SEEK_SET);
	if (iResult)
	{
		Log(TAG "fseek failed: %d", iResult);
		this->eLastError = Seed::ErrorAccessDenied;
		fclose(pFp);
		return false;
	}

	u32 iAmountWritten = (u32)fwrite(this->pData, 1, iSize, pFp); //fwrite(src, 1, len, pFp);
	fclose(pFp);

	if (iAmountWritten != iSize) //len)
	{
		Log(TAG "fwrite: Could not write all the data requested: AmountWritten = %d, Requested = %d\n", iAmountWritten, iSize); //len);
		this->eLastError = Seed::ErrorDeviceFull;
		return false;
	}

	return true;
}

u32 Cartridge::GetCardType(eCartridgeSize size)
{
	u32 i = 0;
	switch (size)
	{
		case Seed::Cartridge512b:
			i = 512;
		break;

		case Seed::Cartridge8192b:
			i = 8192;
		break;

		case Seed::Cartridge32768b:
			i = 32768;
		break;

		case Seed::Cartridge65536b:
			i = 65536;
		break;

		case Seed::Cartridge262144b:
			i = 262144;
		break;

		case Seed::CartridgeUnlimited:
			i = 1048576;
		break;

		default:
			Log(TAG "Cartridge size invalid.");
		break;
	}

	return i;
}

bool Cartridge::Verify(const FilePath *filename, u32 filesize)
{
	u32 len = 0;
	bool ret = false;

	if (this->GetFileSize(filename, &len))
	{
		if (len == filesize)
		{
			ret = true;
		}
	}

	return ret;
}

bool Cartridge::GetFileSize(const FilePath *filename, u32 *length)
{
	FILE *fp = FOPEN(filename, "rb");
	if (!fp)
	{
		this->eLastError = Seed::ErrorAccessDenied;
		return false;
	}

	s32 ret = fseek(fp, 0, SEEK_END);
	*length = static_cast<u32>(ftell(fp));
	if (ret != 0)
	{
		fclose(fp);
		this->eLastError = Seed::ErrorAccessDenied;
		return false;
	}

	ret = fclose(fp);
	if (ret != 0)
   {
		this->eLastError = Seed::ErrorAccessDenied;
		return false;
   }

	this->eLastError = Seed::ErrorNone;
	return true;
}

bool Cartridge::CreateSaveFile()
{
	Log(TAG "Creating save data...");

	FILE *fp = FOPEN(strPath, "wb+");
	if (fp)
	{
		void *pBlankData = Alloc(iSize);
		memset(pBlankData, 0, iSize);
		bool result = this->Write(0, pBlankData, iSize);
		Free(pBlankData);

		if (!result)
		{
			Log(TAG "Could not write into the newly created file.");
			this->eLastError = Seed::ErrorDeviceFull;
			return false;
		}
	}
	else
	{
		Log(TAG "could not create file.");
		this->eLastError = Seed::ErrorAccessDenied;
		return false;
	}

	Log(TAG "Save data created.");

	this->eLastError = Seed::ErrorNone;
	return true;
}

const char *Cartridge::GetObjectName() const
{
	return "Cartridge";
}

}} // namespace

#endif // BUILD_PC