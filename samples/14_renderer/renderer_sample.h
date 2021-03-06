#ifndef _RENDERERSAMPLE_H_
#define _RENDERERSAMPLE_H_

#include <Seed.h>
using namespace Seed;

extern SceneNode *gScene;

class RendererSample : public IGameApp,
					public IEventSystemListener,
					public IEventInputKeyboardListener,
					public IEventInputPointerListener
{
	SEED_DISABLE_COPY(RendererSample)

	public:
		RendererSample();
		virtual ~RendererSample();

		virtual bool Initialize();
		virtual bool Update(Seconds dt);
		virtual bool Shutdown();

		// IEventSystemListener
		virtual void OnSystemShutdown(const EventSystem *ev) override;

		// IEventInputKeyboardListener
		virtual bool OnInputKeyboardRelease(const EventInputKeyboard *ev) override;

		// IEventInputPointerListener
		virtual void OnInputPointerRelease(const EventInputPointer *ev) override;

	protected:
		ISceneObject *pObject;
		Camera		*pCamera;

		SceneNode	cScene;
		Viewport	cViewport;
		Renderer	cRenderer;

		vec3	vFrom;
		vec3	vCurrent;
		vec3	vTo;

		f32		fElapsed;
		f32		fDir;
		bool	bRotate : 1;
};

#endif // _RENDERERSAMPLE_H_
