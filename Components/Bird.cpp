#include "pch.h"
#include "Bird.h"


using namespace DirectX::SimpleMath;
Bird::Bird()
{
	screenPos.y = 500;
	screenPos.x = 100;
	screenHeight = 0;
	yVelocity = 0;
	rotation = 0;
	dead = false;
}

Bird::~Bird()
{
}

void Bird::Flap()
{
	yVelocity -= lift;
}

void Bird::Update(float elapseTime, bool active)
{
	if(active)
		yVelocity += gravity;

	//cap velocity
	if (yVelocity < -15)
		yVelocity = -15;

	screenPos.y += yVelocity*.9;

	//don't fall out of the screen
	if (screenPos.y > screenHeight - 300)
	{
		dead = true;
		screenPos.y = screenHeight - 300;
		yVelocity = 0;
	}

}

void Bird::Draw(Renderer& renderer)
{
	//Set rotation in relation to velocity
	rotation = yVelocity * 5;


	//limit rotation
	//TODO: normalize between -40 and 40
	if (rotation > 40)
		rotation = 40;
	if (rotation < -40)
		rotation = -40;


	//convert from degrees to radians
	rotation = rotation * (3.14 / 180);


	
	renderer.DrawBird(screenPos, rotation);
}

void Bird::setScreenPos(Vector2 newPos)
{
	if (screenPos.y < 0)
		screenPos = newPos;
}

void Bird::setScreenHeight(int height)
{
	screenHeight = height;
	screenPos.y = (height - 250) / 2;
}
