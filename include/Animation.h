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

/*! \file Animation.h
	\author	Danny Angelo Carminati Grein
	\brief Sequence of sprite frames
*/

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "Defines.h"
#include "interface/IObject.h"

namespace Seed {

class Frame;

class SEED_CORE_API Animation : public IObject
{
	public:
		Animation();
		virtual ~Animation();

		bool Load(const void *data);
		bool Unload();

		Frame **GetFrames() const;
		u32 GetFrameCount() const;

		// IObject
		virtual const char *GetObjectName() const;
		virtual int GetObjectType() const;

//	private:
		Frame		**ppFrames;
		const char	*pName;
		u32			iIndex;
		u32			iFrames;
		u32			iFlags;
		u32			iAnimationId;
};

} // namespace

#endif // __ANIMATION_H__