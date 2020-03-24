#pragma once
#include <glm.hpp>
#include "glm/gtx/transform.hpp"
#include <SDL_scancode.h>

#define VER_SPEED 0.2f
#define HOR_SPEED 0.2f

class Camera
{
public:
	Camera();

	~Camera();

	float* GetViewMatrix();

	void ProcessKeyboardInput(const Uint8* state);

	void ProcessMouseInput(int x, int y);

	void UpdateViewMatrix(Uint32 ticks);

private:
	short horDirection;
	short verDirection;

	glm::vec3* eye;
	glm::vec3* direction;

	int yaw;
	int pitch;

	float* viewMatrix;
};

