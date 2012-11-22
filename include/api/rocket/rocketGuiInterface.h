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

#ifndef __ROCKET_GUI_INTERFACE_H__
#define __ROCKET_GUI_INTERFACE_H__

#include "Defines.h"

#if SEED_USE_ROCKET_GUI == 1

#include "File.h"
#include <Rocket/Core/RenderInterface.h>
#include <Rocket/Core/FileInterface.h>
#include <Rocket/Core/SystemInterface.h>

namespace Seed { namespace RocketGui {

struct FilePtr
{
	File *pFile;
	long iOffset;
};

class SEED_CORE_API GuiInterface : public Rocket::Core::RenderInterface, public Rocket::Core::FileInterface, public Rocket::Core::SystemInterface
{
	public:
		GuiInterface();
		virtual ~GuiInterface();

		// Rocket::Core::RenderInterface
		virtual void RenderGeometry(Rocket::Core::Vertex *vertices, int num_vertices, int *indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f &translation);
		virtual Rocket::Core::CompiledGeometryHandle CompileGeometry(Rocket::Core::Vertex *vertices, int num_vertices, int *indices, int num_indices, Rocket::Core::TextureHandle texture);
		virtual void RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f &translation);
		virtual void ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry);
		virtual void EnableScissorRegion(bool enable);
		virtual void SetScissorRegion(int x, int y, int width, int height);
		virtual bool LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i &texture_dimensions, const Rocket::Core::String &source);
		virtual bool GenerateTexture(Rocket::Core::TextureHandle &texture_handle, const Rocket::Core::byte *source, const Rocket::Core::Vector2i &source_dimensions);
		virtual void ReleaseTexture(Rocket::Core::TextureHandle texture_handle);
		virtual float GetHorizontalTexelOffset();
		virtual float GetVerticalTexelOffset();

		// Rocket::Core::FileInterface
		virtual Rocket::Core::FileHandle Open(const Rocket::Core::String &path);
		virtual void Close(Rocket::Core::FileHandle file);
		virtual size_t Read(void *buffer, size_t size, Rocket::Core::FileHandle file);
		virtual bool Seek(Rocket::Core::FileHandle file, long offset, int origin);
		virtual size_t Tell(Rocket::Core::FileHandle file);

		// Rocket::Core::SystemInterface
		virtual float GetElapsedTime();

	private:
		SEED_DISABLE_COPY(GuiInterface);
};

}} // namespace

#else // SEED_USE_ROCKET_GUI
	#error "Include 'GuiManager.h' instead 'api/rocket/rocketGuiInterface.h' directly."
#endif // SEED_USE_ROCKET_GUI
#endif // __ROCKET_GUI_INTERFACE_H__
