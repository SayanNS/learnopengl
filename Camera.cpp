#include "Camera.h"

Camera::Camera()
{
	horDirection = 0;
	verDirection = 0;

	yaw = 90;
	pitch = 0;

	eye = new glm::vec3(0, 0, -500);
	direction = new glm::vec3(0, 0, 1);

	viewMatrix = new float[16];

	viewMatrix[3] = 0;
	viewMatrix[7] = 0;
	viewMatrix[11] = 0;
	viewMatrix[15] = 1;
}

Camera::~Camera()
{
	delete eye;
	delete direction;
	delete viewMatrix;
}

float* Camera::GetViewMatrix()
{
	glm::vec3 k = *direction;
	glm::vec3 i = glm::normalize(glm::cross(glm::vec3(0, 1, 0), k));
	glm::vec3 j = glm::normalize(glm::cross(k, i));

	glm::vec3 t(glm::dot(-i, *eye), glm::dot(-j, *eye), glm::dot(-k, *eye));

	viewMatrix[0] = i[0];
	viewMatrix[4] = i[1];
	viewMatrix[8] = i[2];

	viewMatrix[1] = j[0];
	viewMatrix[5] = j[1];
	viewMatrix[9] = j[2];

	viewMatrix[2] = k[0];
	viewMatrix[6] = k[1];
	viewMatrix[10] = k[2];

	viewMatrix[12] = t[0];
	viewMatrix[13] = t[1];
	viewMatrix[14] = t[2];

	return viewMatrix;
}

void Camera::ProcessKeyboardInput(const Uint8* state)
{
	horDirection = state[SDL_SCANCODE_D] - state[SDL_SCANCODE_A];
	verDirection = state[SDL_SCANCODE_W] - state[SDL_SCANCODE_S];
}

void Camera::ProcessMouseInput(int x, int y)
{
	this->yaw -= x;
	this->pitch -= y;
	
	direction->x = cos(glm::radians((float)this->yaw)) * cos(glm::radians((float)this->pitch));
	direction->y = sin(glm::radians((float)this->pitch));
	direction->z = sin(glm::radians((float)this->yaw)) * cos(glm::radians((float)this->pitch));
}
  
void Camera::UpdateViewMatrix(Uint32 ticks)
{
	glm::vec3 k = *direction;
	glm::vec3 i = glm::normalize(glm::cross(glm::vec3(0, 1, 0), k));

	for (int index = 0; index < 3; index++)
	{
		float temp = (k[index] * verDirection * VER_SPEED + i[index] * horDirection * HOR_SPEED) * ticks;
		(*eye)[index] += temp;
	}
} 
