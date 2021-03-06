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

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "interface/ISceneObject.h"
#include "Vertex.h"
#include "Rect.h"

namespace Seed {

class ITexture;

ISceneObject *FactoryCamera();

/// Camera
/*!
Orthogonal or Perspective Camera with support to render to texture.
*/
class SEED_CORE_API Camera : public ISceneObject
{
	SEED_DISABLE_COPY(Camera)
	SEED_DECLARE_RTTI(Camera, ISceneObject)

	public:
		Camera();
		virtual ~Camera();

		virtual void SetProjection(eProjection type);
		virtual eProjection GetProjection() const;

		virtual bool Contains(ITransformable *obj, mat4 &worldMatrix);
		virtual void SetView(const Rect4f &rect);

		/// Set a texture as render target, must be a valid and initialized texture.
		/**
		Will try to set a valid initialized texture as a render target.
		Check result to be sure that it was succeded.
		*/
		virtual bool SetTexture(ITexture *target);
		virtual ITexture *GetTexture() const;

		// ISceneObject
		virtual void Update(Seconds dt) override;
		virtual void Render(const mat4 &worldTransform) override;

		// IDataObject
		virtual bool Write(Writer &writer) override;
		virtual bool Unload() override;
		virtual Camera *Clone() const override;
		virtual void Set(Reader &reader) override;

	protected:
		virtual bool IsInView(ITransformable *obj, mat4 &worldTransform);
		virtual bool IsInFrustum(ITransformable *obj, mat4 &worldTransform);

	protected:
		ITexture	*pTexture;
		sVertex		aMesh[4];
		eProjection nProjection;
		Rect4f		rViewArea; // Used to check input area
		Rect4f		rBoundingBox; // Used to check boundaries in world
		mat4	mInverse;
};

} // namespace

#endif // CAMERA_H
