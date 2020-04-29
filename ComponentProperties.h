#pragma once

class UpdatableComponent
{
public:

	virtual void Update();
};

class DrawableComponent
{
public:

	virtual void Draw();
	virtual void UpdateViewMatrix();
};

class InputableComponent
{
public:

	virtual void Input();
};