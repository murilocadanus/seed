/*
* Copyright (c) 2012, Seed Developers
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
* 4. A credit line is required in the game credits, as the following line:
*    Powered by Seed Framework
* 5. A Seed Framework logo should be displayed within a splash screen, or in
*    the case where the game haven't or cannot have a splash, a logo should be
*    displayed somewhere in the game (eg. menu, credits, other place).
*
* THIS SOFTWARE IS PROVIDED BY SEED DEVELOPERS ''AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL SEED DEVELOPERS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#if defined(BUILD_QT)

#include "Defines.h"
#include "System.h"
#include "Log.h"
#include "Timer.h"
#include "physfs/physfs.h"
#include "platform/pc/platform.h"

#define TAG "[System] "

#define MAX_FRAMESKIP_THRESHOLD 10

namespace Seed { namespace QT {

SEED_SINGLETON_DEFINE(System)

System::System()
	: fLastFrameTime(0.0f)
	, fFpsTime(0.0f)
	, fElapsedTime(0.0f)
	, iRetraceCount(0)
	, iFrameRate(0)
	, iRetraceIndex(0)
	, arRetraceCount()
	, bShutdown(false)
	, bSleeping(false)
{
	memset(arRetraceCount, '\0', sizeof(arRetraceCount));
}

System::~System()
{
}

bool System::Reset()
{
	IManager::Reset();
	return true;
}

bool System::Initialize()
{
	Log(TAG "Initializing...");
	IManager::Initialize();
	Log(TAG "Initialization completed.");

	return true;
}

bool System::Shutdown()
{
	this->bShutdown = true;
	IManager::Shutdown();
	Log(TAG "Terminating...");

	return true;
}

bool System::Update(Seconds dt)
{
	UNUSED(dt);
	this->WaitForRetrace();
	return true;
}

void System::Sleep()
{
}

bool System::IsSleeping() const
{
	return false;
}

bool System::IsShuttingDown() const
{
	return this->bShutdown;
}

bool System::IsResetting() const
{
	return false;
}

void System::WaitForRetrace()
{
	++iRetraceCount;

	if (!fLastFrameTime)
		fLastFrameTime = f32(pTimer->GetMilliseconds());

	f32 frameMaxTime = 1000.0f / iFrameRate;

	do
	{
		//hold fps
		f32 time		= f32(pTimer->GetMilliseconds());
		f32 frameTime	= time - fLastFrameTime;
		fFpsTime		+= frameTime;
		fElapsedTime	+= frameTime;
		fLastFrameTime	= time;
	} while (fElapsedTime < frameMaxTime);

	fElapsedTime -= frameMaxTime;

	//Raptor: test fix for when WM_PAINT stops comming for a long time due to the
	//user moving the window, for instance. Tries to avoid the retrace trying to
	//catch up with the lost frame time
	if ((fElapsedTime / frameMaxTime) > MAX_FRAMESKIP_THRESHOLD)
		fElapsedTime = 0;

	if (fFpsTime > 1000)
	{
		//Dbg("FPS: %d", iRetraceCount);

		arRetraceCount[iRetraceIndex++] = iRetraceCount;
		if (iRetraceIndex >= SYSTEM_RETRACE_HISTORY_MAX)
			iRetraceIndex = 0;

		fFpsTime -= 1000;
		iRetraceCount = 0;
	}
}

const char *System::GetUsername() const
{
	return get_user_name();
}

const char *System::GetHomeFolder() const
{
	return PHYSFS_getUserDir();
}

const char *System::GetApplicationDataFolder() const
{
	return PHYSFS_getBaseDir();
}

const char *System::GetSaveGameFolder() const
{
	return PHYSFS_getUserDir();
}

void System::GoToMenu()
{
}

void System::OnHomeCalled()
{
}

void System::GoToDataManager()
{
}

void System::HangUp()
{
}

bool System::IsHomeEnabled() const
{
	return false;
}

bool System::IsHomeRunning() const
{
	return false;
}

bool System::InitializeHome()
{
	return true;
}

void System::EnableHome()
{
}

void System::DisableHome()
{
}

void System::SetWidget(QWidget *widget)
{
	pWidget = widget;
}

}} // namespace

#endif // BUILD_QT
