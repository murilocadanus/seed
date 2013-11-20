#ifndef _RENDERERSAMPLE_H_
#define _RENDERERSAMPLE_H_

#include <Seed.h>
using namespace Seed;

extern SceneNode *gScene;

class RendererSample : public IGameApp,
					public IEventSystemListener,
					public IEventInputKeyboardListener,
					public IEventInputPointerListener,
					public IEventJobListener
{
	SEED_DISABLE_COPY(RendererSample)

	public:
		RendererSample();
		virtual ~RendererSample();

		virtual bool Initialize();
		virtual bool Update(f32 dt);
		virtual bool Shutdown();

		// IEventSystemListener
		virtual void OnSystemShutdown(const EventSystem *ev);

		// IEventInputKeyboardListener
		virtual void OnInputKeyboardRelease(const EventInputKeyboard *ev);

		// IEventInputPointerListener
		virtual void OnInputPointerRelease(const EventInputPointer *ev);

		// IEventJobListener
		virtual void OnJobCompleted(const EventJob *ev);
		virtual void OnJobAborted(const EventJob *ev);

	protected:
		ISceneObject *pImage;
		Camera		*pCamera;

		SceneNode	cScene;
		Viewport	cViewport;
		Renderer	cRenderer;

		Vector3f	vFrom;
		Vector3f	vCurrent;
		Vector3f	vTo;

		f32			fElapsed;
		f32			fDir;
		bool		bRotate : 1;
};

#endif // _RENDERERSAMPLE_H_
