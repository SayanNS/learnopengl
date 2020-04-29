#include "Game.h"

Game::Game()
{
	mWindow = nullptr;
	mIsRunning = true;
	mTicksCount = 0;
	mIsLeftButtonDown = false;
	mCamera = new Camera();
}

bool Game::Initialize()
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	if (sdlResult != 0)
	{
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mWindow = SDL_CreateWindow(
		WINDOW_NAME,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_OPENGL
	);

	if (!mWindow)
	{
		return false;
	}

	mContext = SDL_GL_CreateContext(mWindow);

	if (mContext == 0)
	{
		return false;
	}

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		return false;
	}

	glGetError();

	mRenderer = new Renderer();

	float yScale = 1 / tan(glm::radians(FOV / 2));
	float xScale = yScale * WINDOW_HEIGHT / WINDOW_WIDTH;

	float projection[] = {
		xScale, 0, 0, 0,
		0, yScale, 0, 0,
		0, 0, FAR / (FAR - NEAR), 1,
		0, 0, -NEAR * FAR / (FAR - NEAR), 0
	};

	//std::cout <<  << std::endl;
	//float* projection = (float*)&glm::perspective(glm::radians(FOV), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, NEAR, FAR);

	//for (int i = 0; i < 4; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//	{
	//		std::cout << projection[i * 4 + j] << " ";
	//	}
	//	std::cout << std::endl;
	//}

	if (mRenderer->Initialize("json/Cube.json"))
	{
		mRenderer->SetShaderActive();
		mRenderer->SetShaderUniform("uProjection", projection);
	}
	else
	{
		return false;
	}

	return true;
}

void Game::Shutdown() 
{
	SDL_DestroyWindow(mWindow);

	SDL_GL_DeleteContext(mContext);

	SDL_Quit();
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();

		UpdateGame(); 

		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
		{
			SDL_MouseButtonEvent* mouseMotionEvent = (SDL_MouseButtonEvent*) & event;

			if (mouseMotionEvent->button == SDL_BUTTON_LEFT)
			{
				mIsLeftButtonDown = true;
			}

			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			SDL_MouseButtonEvent* mouseMotionEvent = (SDL_MouseButtonEvent*) & event;

			if (mouseMotionEvent->button == SDL_BUTTON_LEFT)
			{
				mIsLeftButtonDown = false;
			}

			break;
		}
		case SDL_MOUSEMOTION:
		{
			SDL_MouseMotionEvent* mouseMotionEvent = (SDL_MouseMotionEvent*) & event;
		
			if (mIsLeftButtonDown)
			{
				mCamera->ProcessMouseInput(mouseMotionEvent->xrel, mouseMotionEvent->yrel);
			}

			break;
		}
		case SDL_QUIT:

			mIsRunning = false;

			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);

	mCamera->ProcessKeyboardInput(state);

}

void Game::UpdateGame()
{
	Uint32 ticks = SDL_GetTicks();

	if (mCamera->IsCameraStateChanged())
	{
		mCamera->UpdateViewMatrix(ticks - mTicksCount);
	}

	mTicksCount = ticks;
}

void Game::GenerateOutput()
{
	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	//glBlendFunc(
	//	GL_SRC_ALPHA,
	//	GL_ONE_MINUS_SRC_ALPHA
	//);

	mRenderer->SetShaderActive();
	mRenderer->SetVertexActive();

	if (mCamera->IsCameraStateChanged())
	{
		mRenderer->SetShaderUniform1("uViewPos", mCamera->GetViewPosition());
		mRenderer->SetShaderUniform("uView", mCamera->GetViewMatrix());
	}

	mRenderer->Draw();

	SDL_GL_SwapWindow(mWindow);
}