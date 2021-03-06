#include "pres_sample.h"

PresentationSample::PresentationSample()
	: cPres()
{
}

PresentationSample::~PresentationSample()
{
}

bool PresentationSample::Initialize()
{
	return cPres.Load("pres2.config", [&](Presentation *, Viewport *aborted) {
		if (!aborted)
		{
			pSystem->AddListener(this);
			pInput->AddKeyboardListener(this);
			pInput->AddPointerListener(this);
		}
	});
}

bool PresentationSample::Update(Seconds dt)
{
	UNUSED(dt)
	return true;
}

bool PresentationSample::Shutdown()
{
	cPres.Unload();

	pInput->RemovePointerListener(this);
	pInput->RemoveKeyboardListener(this);
	pSystem->RemoveListener(this);

	return IGameApp::Shutdown();
}

void PresentationSample::OnSystemShutdown(const EventSystem *ev)
{
	UNUSED(ev)
	pSystem->Shutdown();
}

bool PresentationSample::OnInputKeyboardRelease(const EventInputKeyboard *ev)
{
	auto k = ev->GetKey();

	if (k == eKey::Escape)
		pSystem->Shutdown();
	else if (k == eKey::F1)
		pResourceManager->Print();
	else if (k == eKey::F2)
		pResourceManager->GarbageCollect();

	return true;
}

void PresentationSample::OnInputPointerRelease(const EventInputPointer *ev)
{
	if (ev->GetReleased() == eInputButton::MouseLeft)
	{
		auto vp = pViewManager->GetViewportAt(ev->GetX(), ev->GetY());
		Log("Click at viewport %s", vp->sName.c_str());
		Log("Click position %d,%d position inside viewport is at %d,%d", ev->GetX(), ev->GetY(), ev->GetX() - vp->GetX(), ev->GetY() - vp->GetY());
	}
}
