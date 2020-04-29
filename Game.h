#include <SDL.h>
#include <GL/glew.h>
#include "Texture.h"
#include "Camera.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include <math.h>
#include "Actor.h"
#include <iostream>
#include "Renderer.h"

#define WINDOW_X 100
#define WINDOW_Y 100
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 500
#define WINDOW_NAME "Game window"

#define NEAR 0.1f
#define FAR 2000.f

#define FOV 45.f

class Game
{
public:
	Game();
	
	bool Initialize();

	void RunLoop();

	void Shutdown();

private:
	void ProcessInput();

	void UpdateGame();

	void GenerateOutput();

	SDL_Window* mWindow;

	SDL_GLContext mContext;

	bool mIsLeftButtonDown;
	bool mIsRunning;
	Uint32 mTicksCount;
	Camera* mCamera;
	Renderer* mRenderer;
};