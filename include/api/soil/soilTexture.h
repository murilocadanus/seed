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

#ifndef __SOIL_TEXTURE_H__
#define __SOIL_TEXTURE_H__

#include "Defines.h"

#if defined(USE_API_SOIL)

#include "File.h"
#include "interface/ITexture.h"

namespace Seed { namespace SOIL {

IResource *TextureResourceLoader(const String &filename, ResourceManager *res = pResourceManager);

/// SOIL Texture
class SEED_CORE_API Texture : public ITexture
{
	friend IResource *TextureResourceLoader(const String &filename, ResourceManager *res);

	public:
		Texture();
		virtual ~Texture();

		// ITexture
		virtual const void *GetData() const;
		virtual void PutPixel(u32 x, u32 y, const Color &px);
		virtual Color GetPixel(u32 x, u32 y) const;
		virtual u8 GetPixelAlpha(u32 x, u32 y) const;

		virtual u32 GetBytesPerPixel() const;

		virtual void Update(Color *buffer);
		virtual void Reset();
		virtual bool Load(const String &desc, u32 width, u32 height, Color *buffer = NULL, u32 atlasWidth = 0, u32 atlasHeight = 0, bool copy = false); // O que acontece no Reload?
		virtual void Close();

		virtual u32 GetAtlasWidth() const;
		virtual u32 GetAtlasHeight() const;

		// IResource
		virtual bool Load(const String &filename, ResourceManager *res = pResourceManager);
		virtual bool Unload();
		virtual u32 GetUsedMemory() const;

	protected:
		void UnloadTexture();

	private:
		SEED_DISABLE_COPY(Texture);

	private:
		u8 *pData;

		u32 iBytesPerPixel;
		u32 iPitch;

		u32 iAtlasWidth;
		u32 iAtlasHeight;

		bool bCopy;
};

}} // namespace

#else // USE_API_SOIL
	#error "Include 'Texture.h' instead 'api/soil/soilTexture.h' directly."
#endif // USE_API_SOIL
#endif // __SOIL_TEXTURE__
