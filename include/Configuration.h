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

#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include "Defines.h"
#include "interface/IObject.h"
#include "Enum.h"

namespace Seed {

class SEED_CORE_API Configuration : public IObject
{
	public:
		Configuration();
		virtual ~Configuration();

		void SetVideoMode(eVideoMode videoMode);
		eVideoMode GetVideoMode() const;

		//void SetResolution(u32 width, u32 height);
		u32 GetResolutionWidth() const;
		u32 GetResolutionHeight() const;

		void SetWorkingDirectory(const char *path);
		const char *GetWorkingDirectory() const;

		//! Sets the desired frame rate.
		/*!
			Sets the desired frame rate for running the entire system.
			\param frameRate Frame rate of the system
		 */
		void SetFrameRate(eSystemFrameRate frameRate);

		//! Gets the desired frame rate.
		/*!
			Returns the selected frame rate.
			\returns a ISystem::eFrameRate enumeration;
		 */
		eSystemFrameRate GetFrameRate() const;

		//! Sets the application title.
		/*!
			Sets the application title, mainly used for savegame data.
			\param title Title of the application;
		 */
		void SetApplicationTitle(const char *title);

		//! Returns the application title.
		/*!
			Returns the application title.
			\returns a const char * string;
		 */
		const char *GetApplicationTitle() const;

		//! Sets the application description.
		/*!
			Sets the application description, mainly used for savegame data.
			\param descr Description of the application ;
		 */
		void SetApplicationDescription(const char *desc);

		//! Returns the application description.
		/*!
			Returns the application description.
			\returns a const char * string;
		 */
		const char *GetApplicationDescription() const;

		//! Sets the application publisher name.
		/*!
			Sets the application publisher name, mainly used for savegame data.
			\param descr Publisher of the application ;
		 */
		void SetPublisherName(const char *desc);

		//! Returns the application publisher name.
		/*!
			Returns the application publisher name.
			\returns a const char * string;
		 */
		const char *GetPublisherName() const;

		//! Set the maximum radius for distance based widget collision
		/*!
			Set the maximum radius from widget center to consider
			a widget collision when no collision happens by pixel or rect.
			Useful for touch devices with finger based input.
		 */
		void SetInputDistanceRadius(f32 dist);

		//! Get the maximum radius for distance based widget collision
		/*!
			Returns the maximum radius from widget center to consider
			a widget collision when no collision happens by pixel or rect.
			Useful for touch devices with finger based input.
		 */
		f32 GetInputDistanceRadius() const;

		void SetCanHaveMultipleInstances(bool enable);
		bool GetCanHaveMultipleInstances() const;

		void SetWarningMultipleInstances(bool warnUser);
		bool GetWarningMultipleInstances() const;

		void SetRendererDeviceType(eRendererDeviceType deviceType);
		eRendererDeviceType GetRendererDeviceType() const;

		void SetReaderType(eReaderType readerType);
		eReaderType GetReaderType() const;

		// IObject
		virtual const char *GetObjectName() const;
		virtual int GetObjectType() const;

		bool bDebugSprite;

	private:
		SEED_DISABLE_COPY(Configuration);

		const char *pcWorkingDirectory;
		const char *pcTitle;
		const char *pcDescription;
		const char *pcPublisherName;

		f32 fInputRadius;

		eRendererDeviceType iRendererDeviceType;
		eReaderType iReaderType;
		eVideoMode nVideoMode;
		eSystemFrameRate iFrameRate;

		u32 iResolutionWidth;
		u32 iResolutionHeight;

		bool bMultipleInstances;
		bool bWarningMultipleInstances;
};

} // namespace

#endif // __CONFIGURATION_H__
