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
	currentFrame = 0;
}


void Bird::Flap()
{
	yVelocity -= lift;
}

void Bird::Update(int frameCount, bool active)
{
	//Only apply gravity during active game
	if(active)
		yVelocity += gravity;

	//Cap velocity
	if (yVelocity < -15)
		yVelocity = -15;

	screenPos.y += yVelocity*.9;

	//Don't fall out of the screen
	if (screenPos.y > screenHeight - 300)
	{
		dead = true;
		screenPos.y = screenHeight - 300;
		yVelocity = 0;
	}

	//Animation
	if (frameCount % 4 == 0)
	{
		currentFrame++;
		if (currentFrame > 3)
			currentFrame = 0;
	}

	//Only flap wings if going up
	if (yVelocity >= 0)
		currentFrame = 0;

}

void Bird::Draw(Renderer& renderer)
{
	//Set rotation in relation to velocity
	rotation = yVelocity * 5;

	if (yVelocity > 2)
	{
		rotation = pow(2, .8*yVelocity);
		if (rotation > 90)
			rotation = 90;
	}
	else
		rotation = normalize(rotation);
	// normalize rotation between -40 and 40 then convert from degrees to radians
	rotation = rotation * (3.14 / 180);

	renderer.DrawBird(screenPos, rotation, currentFrame);
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
