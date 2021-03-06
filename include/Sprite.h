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

#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Defines.h"
#include "Reader.h"
#include "Vertex.h"
#include "Container.h"
#include "interface/ISceneObject.h"
#include "RendererDevice.h"

namespace Seed {

class ITexture;
class ParticleEmitter;
class Animation;
class Frame;

ISceneObject *FactorySprite();

/// Sprite 2D
/*!
Animated Sprite
*/
class SEED_CORE_API Sprite : public ISceneObject
{
	SEED_DECLARE_CONTAINER(Vector, Animation)
	SEED_DECLARE_CONTAINER(Vector, Frame)
	SEED_DECLARE_RTTI(Sprite, ISceneObject)

	friend class ParticleEmitter;
	public:
		friend class ResourceLoader;

	public:
		Sprite();
		Sprite(const Sprite &other);
		virtual ~Sprite();

		Sprite &operator=(const Sprite &other);

		virtual ITexture *GetTexture() const;
		virtual const void *GetData() const;

		virtual Color GetPixel(u32 x, u32 y) const;
		virtual u8 GetPixelAlpha(u32 x, u32 y) const;

		virtual void SetLoop(bool loop);
		virtual bool SetAnimation(u32 index);
		virtual bool SetAnimation(String name);
		virtual void SetCurrentFrame(u32 frame);
		virtual void GotoAndStop(u32 frame);
		virtual void GotoAndPlay(u32 frame);
		virtual void Stop();
		virtual void Play();
		virtual bool IsFinished() const;
		virtual void NextFrame();
		virtual void PreviousFrame();
		virtual u32  GetCurrentAnimation() const;
		virtual const String GetCurrentAnimationName() const;
		virtual u32 GetAnimationCount() const;
		virtual u32  GetFrameCount() const;
		virtual u32  GetCurrentFrame() const;
		virtual bool IsLoop() const;
		virtual bool IsAnimated() const;

		void operator+=(Animation *anim);
		void operator-=(Animation *anim);

		virtual void Reset();
//		virtual void Initialize();

		// ISceneObject
		virtual void Update(Seconds dt) override;
		virtual void Render(const mat4 &worldTransform) override;

		// IDataObject
		virtual bool Write(Writer &writer) override;
		virtual bool Unload() override;
		virtual Sprite *Clone() const override;
		virtual void Set(Reader &reader) override;

	protected:
		virtual void ReconfigureAnimation();
		virtual void ReconfigureFrame();

	protected:
		FrameVector *pvFrames;
		Animation	*pAnimation;
		Frame		*pFrame;
		ITexture	*pFrameTexture;

		AnimationVector vAnimations;

		u32 iCurrentAnimation;
		u32 iCurrentFrame;
		u32 iFrames;
		f32 fFrameTime;

		sVertex cVertex[4];
		VertexBuffer cVertexBuffer;

		bool bInitialized : 1;
		bool bChanged : 1;
		bool bAnimation : 1;
		bool bLoop : 1;
		bool bPlaying : 1;
		bool bFinished : 1;
		bool bIsCopy : 1;
};

} // namespace

#endif // __SPRITE_H__
