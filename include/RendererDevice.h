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

#ifndef __RENDERER_DEVICE_H__
#define __RENDERER_DEVICE_H__

#if defined(BUILD_IOS)
	#include "platform/pc/pcRendererDevice.h"

	#if defined(SEED_ENABLE_OGLES2)
	#include "api/ogl/oglES2RendererDevice.h"
	#else
	#include "api/ogl/oglES1RendererDevice.h"
	#endif

#elif defined(BUILD_SDL) || defined(BUILD_GLFW) || defined(BUILD_SDL2)
	#include "platform/pc/pcRendererDevice.h"

	#if defined(SEED_ENABLE_OGLES2)
	#include "api/ogl/oglES2RendererDevice.h"
	#else
	#include "api/ogl/oglES1RendererDevice.h"
	#endif

	#if defined(SEED_ENABLE_OGL20)
	#include "api/ogl/ogl20RendererDevice.h"
	#endif

	#if defined(SEED_ENABLE_OGL30)
	#include "api/ogl/ogl30RendererDevice.h"
	#endif

	#if defined(SEED_ENABLE_OGL40)
	#include "api/ogl/ogl40RendererDevice.h"
	#endif

	#if defined(SEED_ENABLE_D3D8)
	#include "api/directx/D3D8RendererDevice.h"
	#endif

	#if defined(SEED_ENABLE_D3D9)
	#include "api/directx/D3D9RendererDevice.h"
	#endif

	#if defined(SEED_ENABLE_D3D10)
	#include "api/directx/D3D10RendererDevice.h"
	#endif

	#if defined(SEED_ENABLE_D3D11)
	#include "api/directx/D3D11RendererDevice.h"
	#endif

	using namespace Seed::PC;
#elif defined(BUILD_QT)
//	#include "platform/qt/qtRendererDevice.h"
	#include "platform/pc/pcRendererDevice.h"
	#include "api/ogl/oglES1RendererDevice.h"
#endif

#include "interface/IHardwareBuffer.h"

#endif // __RENDERER_DEVICE_H__
