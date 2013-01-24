#include "gameflow.h"
#include "game.h"

#include <Rocket/Debugger.h>
#include <Rocket/Controls.h>

GameFlow *gFlow = NULL;

GameFlow::GameFlow()
	: pScene(NULL)
	, pRocket(NULL)
	, pContext(NULL)
	, pDoc(NULL)
{
	gFlow = this;
}

GameFlow::~GameFlow()
{
	gFlow = NULL;
}

bool GameFlow::Initialize()
{
	bool init = cPres.Load("game.config", this);

	// Create the transitions
	cMenuToGame.Initialize(&cMenu, &cOnGame, &cGame);
	cMenuToOptions.Initialize(&cMenu, &cOnOptions, &cOptions);
	cMenuToCredits.Initialize(&cMenu, &cOnCredits, &cCredits);
	cOptionsToMenu.Initialize(&cOptions, &cOnMenu, &cMenu);
	cCreditsToMenu.Initialize(&cCredits, &cOnMenu, &cMenu);
	cGameToMenu.Initialize(&cGame, &cOnMenu, &cMenu);

	// Create the State Machine.
	cFlow.RegisterTransition(&cMenuToGame);
	cFlow.RegisterTransition(&cMenuToOptions);
	cFlow.RegisterTransition(&cMenuToCredits);
	cFlow.RegisterTransition(&cOptionsToMenu);
	cFlow.RegisterTransition(&cCreditsToMenu);
	cFlow.RegisterTransition(&cGameToMenu);

	IGameApp::Initialize();

	return init;
}

bool GameFlow::Update(f32 dt)
{
	cFlow.Update(dt);
	cGame.LateStop();
	return true;
}

bool GameFlow::Shutdown()
{
	if (cFlow.GetCurrentState() == &cGame)
	{
		cGame.OnStop(NULL);
	}

	pInput->RemoveKeyboardListener(this);
	pSystem->RemoveListener(this);

	this->ReleaseGUI();
	cPres.Unload();

	return IGameApp::Shutdown();
}

void GameFlow::OnSystemShutdown(const EventSystem *ev)
{
	UNUSED(ev)
	pSystem->Shutdown();
}

void GameFlow::OnInputKeyboardRelease(const EventInputKeyboard *ev)
{
	Key k = ev->GetKey();

	if (k == Seed::KeyEscape)
		pSystem->Shutdown();
	else if (k == Seed::KeyF1)
		pResourceManager->Print();
	else if (k == Seed::KeyF2)
		pResourceManager->GarbageCollect();
	else if (k == Seed::KeyF5)
		this->ReloadGUI();
	else if (k == Seed::KeyF10)
		Rocket::Debugger::SetVisible(!Rocket::Debugger::IsVisible());
}

void GameFlow::OnPresentationLoaded(const EventPresentation *ev)
{
	UNUSED(ev)

	pSystem->AddListener(this);
	pInput->AddKeyboardListener(this);

	pScene = cPres.GetRendererByName("MainRenderer")->GetScene();

	this->InitializeGUI();
	cFlow.Initialize(&cMenu);
}


bool GameFlow::UnloadGUI()
{
	Log("Unloading GUI Document");
	if (pDoc)
	{
		pDoc->Hide();
		pContext->UnloadDocument(pDoc);
		pDoc->RemoveReference();
		pDoc = NULL;
	}

	return true;
}

bool GameFlow::ReloadGUI()
{
	return this->LoadGUI(sDocument);
}

bool GameFlow::LoadGUI(const String &doc)
{
	if (this->UnloadGUI())
	{
		Log("Loading GUI Document");
		pDoc = pContext->LoadDocument(doc.c_str());
		if (pDoc != NULL)
		{
			Rocket::Core::Element *title = pDoc->GetElementById("title");
			if (title != NULL)
				title->SetInnerRML(pDoc->GetTitle());

			pDoc->Focus();
			pDoc->Show();
		}

		sDocument = doc;
	}

	return true;
}

bool GameFlow::InitializeGUI()
{
	pRocket = New(RocketInterface());
	pRocket->sName = "GUI";
	Rocket::Core::SetRenderInterface(pRocket);
	Rocket::Core::SetFileInterface(pRocket);
	Rocket::Core::SetSystemInterface(pRocket);
	Rocket::Core::Initialise();
	Rocket::Controls::Initialise();

	pContext = Rocket::Core::CreateContext("main", Rocket::Core::Vector2i(pScreen->GetWidth(), pScreen->GetHeight()));
	if (pContext == NULL)
	{
		Rocket::Core::Shutdown();
		return false;
	}

	Rocket::Core::String fonts[4];
	fonts[0] = "Delicious-Roman.otf";
	fonts[1] = "Delicious-Italic.otf";
	fonts[2] = "Delicious-Bold.otf";
	fonts[3] = "Delicious-BoldItalic.otf";

	for (unsigned int i = 0; i < sizeof(fonts) / sizeof(Rocket::Core::String); i++)
		Rocket::Core::FontDatabase::LoadFontFace(fonts[i]);

	Rocket::Debugger::Initialise(pContext);
	pRocket->SetCurrentContext(pContext);
	pInput->AddKeyboardListener(pRocket);
	pInput->AddPointerListener(pRocket);
	pRocket->SetZ(-1000.0f);
	pScene->Add(pRocket);

	pContext->AddEventListener("load", this);
	pContext->AddEventListener("click", this);

	return true;
}

void GameFlow::ReleaseGUI()
{
	pContext->RemoveEventListener("load", this);
	pContext->RemoveEventListener("click", this);

	pInput->RemovePointerListener(pRocket);
	pInput->RemoveKeyboardListener(pRocket);

	pContext->UnloadAllDocuments();

	if (pDoc)
	{
		pDoc->RemoveReference();
		pDoc = NULL;
	}

	pContext->RemoveReference();

	Rocket::Core::Shutdown();

	pScene->Remove(pRocket);
	Delete(pRocket);
}

void GameFlow::ProcessEvent(Rocket::Core::Event &ev)
{
	if (ev.GetType() == "load")
	{

	}
	else if (ev.GetType() == "click")
	{
		Rocket::Core::String eid = ev.GetTargetElement()->GetId().ToLower();
		if (eid.Empty())
			return;

		if (eid == "exit")
			pSystem->Shutdown();
		else if (eid == "credits")
			cFlow.OnEvent(&cOnCredits);
		else if (eid == "menu")
			cFlow.OnEvent(&cOnMenu);
		else if (eid == "options")
			cFlow.OnEvent(&cOnOptions);
		else if (eid == "game")
			cFlow.OnEvent(&cOnGame);
	}
}

void GameFlow::AddScene(SceneNode *node)
{
	pScene->Add(node);
}

void GameFlow::RemoveScene(SceneNode *node)
{
	pScene->Remove(node);
}

// MainMenu
MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::OnStart(IObject *data)
{
	UNUSED(data)
	Log("Entering MainMenu State");

	gFlow->LoadGUI("mainmenu.rml");
}

void MainMenu::OnUpdate(f32 dt)
{
	UNUSED(dt)
}

void MainMenu::OnStop(IObject *data)
{
	UNUSED(data)
	Log("Exiting MainMenu State");
}

// Options
Options::Options()
{
}

Options::~Options()
{
}

void Options::OnStart(IObject *data)
{
	UNUSED(data)
	Log("Entering Options State");

	gFlow->LoadGUI("options.rml");
}

void Options::OnUpdate(f32 dt)
{
	UNUSED(dt)
}

void Options::OnStop(IObject *data)
{
	UNUSED(data)
	Log("Exiting Options State");
}


// GameState
GameState::GameState()
	: cScene()
	, pGame(NULL)
	, bDoStop(false)
{
}

GameState::~GameState()
{
}

void GameState::OnStart(IObject *data)
{
	UNUSED(data)
	Log("Entering Game State");
	bDoStop = false;

	gFlow->LoadGUI("game.rml");
	pGame = New(Game(&cScene));
	pGame->Initialize();
	cScene.SetVisible(true);
}

void GameState::OnUpdate(f32 dt)
{
	pGame->Update(dt);
}

void GameState::OnStop(IObject *data)
{
	UNUSED(data)
	Log("Exiting Game State");
	bDoStop = true;
	cScene.SetVisible(false);
}

/*
We need this because we will mess with the SceneGraph from an unexpected event (ie. user input)
and the Renderer may be traversing the graph, so we need be sure that the destruction will happen
inside an update.
*/
void GameState::LateStop()
{
	if (bDoStop && pGame)
	{
		pGame->Shutdown();
		Delete(pGame);
	}
}

// Credits
Credits::Credits()
{
}

Credits::~Credits()
{
}

void Credits::OnStart(IObject *data)
{
	UNUSED(data)
	Log("Entering Credits State");

	gFlow->LoadGUI("credits.rml");
}

void Credits::OnUpdate(f32 dt)
{
	UNUSED(dt)
}

void Credits::OnStop(IObject *data)
{
	UNUSED(data)
	Log("Exiting Credits State");
}
