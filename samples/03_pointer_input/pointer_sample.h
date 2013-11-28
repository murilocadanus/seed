#ifndef _POINTERSAMPLE_H_
#define _POINTERSAMPLE_H_

#include <Seed.h>
using namespace Seed;

class PointerSample : public IGameApp,
					public IEventSystemListener,
					public IEventInputKeyboardListener,
					public IEventInputPointerListener
{
	SEED_DISABLE_COPY(PointerSample)

	public:
		PointerSample();
		virtual ~PointerSample();

		virtual bool Initialize();
		virtual bool Update(Seconds dt);
		virtual bool Shutdown();

		// IEventSystemListener
		virtual void OnSystemShutdown(const EventSystem *ev);

		// IEventInputKeyboardListener
		virtual void OnInputKeyboardRelease(const EventInputKeyboard *ev);

		// IEventInputPointerListener
		virtual void OnInputPointerRelease(const EventInputPointer *ev);

	protected:
		Presentation cPres;
		ISceneObject *pObject;
		Camera		*pCamera;

		Vector3f	vFrom;
		Vector3f	vCurrent;
		Vector3f	vTo;

		f32			fElapsed;
		f32			fDir;
		bool		bRotate : 1;
};

#endif // _POINTERSAMPLE_H_
