#pragma once
#include "pch.h"
#include "Bird.h"

using namespace DirectX::SimpleMath;
Bird::Bird() :
	w(50),
	h(35),
	dead(false),
	currentFrame(0),
	rotation(0),
	yVelocity(0),
	screenHeight(0),
	score(0)
{
	screenPos.y = 500;
	screenPos.x = 100;

	yPosInit = 500;
}

Bird::~Bird()
{
}

Vector2* Bird::getPipePoints(Vector2* points, int index, int top)
{
	Pipe* pipe = pipes[index];

	//upper pipe
	if (top == 0)
	{
		points[0] = Vector2(pipe->getX(), 0);
		points[1] = Vector2(pipe->getX() + pipe->getW(), 0);
		points[2] = Vector2(pipe->getX() + pipe->getW(), pipe->getGapH() - pipe->getGapSize() / 2);
		points[3] = Vector2(pipe->getX(), pipe->getGapH() - pipe->getGapSize() / 2);
	}
	else if (top == 1)
	{
		points[0] = Vector2(pipe->getX(), pipe->getGapH() + pipe->getGapSize() / 2);
		points[1] = Vector2(pipe->getX() + pipe->getW(), pipe->getGapH() + pipe->getGapSize() / 2);
		points[2] = Vector2(pipe->getX() + pipe->getW(), screenHeight);
		points[3] = Vector2(pipe->getX(), screenHeight);
	}

	return points;
}


Vector2* Bird::getBirdPoints(Vector2* points)
{
	points[0] = screenPos + Vector2(36, 0) - Vector2(50, 35);
	points[1] = screenPos + Vector2(68, 0) - Vector2(50, 35);
	points[2] = screenPos + Vector2(100, 44) - Vector2(50, 35);
	points[3] = screenPos + Vector2(57, 70) - Vector2(50, 35);
	points[4] = screenPos + Vector2(19, 62) - Vector2(50, 35);
	points[5] = screenPos + Vector2(0, 32) - Vector2(50, 35);
	

	return points;
}

bool Bird::collisionDetection(Vector2* birdPoints, Vector2* pipePoints)
{
	//bird
	SimpleMath::Rectangle birdRect(screenPos.x,screenPos.y,(birdPoints[2].x-screenPos.x )*2,( birdPoints[3].y - screenPos.y)*2);

	//pipe
	SimpleMath::Rectangle pipeRect(pipePoints[0].x, pipePoints[0].y, pipePoints[1].x-pipePoints[0].x,pipePoints[3].y-pipePoints[0].y);

	if (birdRect.Intersects(pipeRect))
	{

		for (int i = 0; i < 6; i++)
		{
			if (pipeRect.Contains(birdPoints[i]))
			{
				return true;
			}	
	
		}

	}
	return false;
}

void Bird::Flap()
{
	if (dead)
		return;

	yVelocity -= lift;	
	
}


void Bird::Update(int frameCount, bool active)
{
	/*
	if (dead)
	{
		rotation += 10;
		if (rotation > 90)
			rotation = 90;

		yVelocity += gravity;
		screenPos.y += yVelocity;

		if (screenPos.y > screenHeight - 230)
		{
			screenPos.y = screenHeight - 230;
			yVelocity = 0;
		}

		return;
	}
	*/

	/*CHECK COLLISION HERE*/

	Vector2 birdPointsArr[6];
	Vector2* birdPoints = getBirdPoints(birdPointsArr);
	//check each pipe
	for (int i = 0; i < 6; i++)
	{
		//only check pipes with viable x coords
		if (pipes[i]->getX() < birdPoints[2].x + 20 && pipes[i]->getX() + pipes[i]->getW() > birdPoints[4].x - 20)
		{
			//check both upper and lower pipe	
			for (int j = 0; j < 2; j++)
			{
				Vector2 pipePointsArr[4];
				Vector2* pipePoints = getPipePoints(pipePointsArr, i, j);

				//only check pipes with viable y coords
				if (j == 0 && birdPoints[0].y > pipePoints[2].y + 20)
				{
					continue;
				}

				if (j == 1 && birdPoints[3].y < pipePoints[0].y - 20)
				{
					continue;
				}
				
				//if x and y coords are viable, check collision
				if (collisionDetection(birdPoints, pipePoints)) {
					dead = true;
				}

			}
		}
	}


	//Only apply gravity during active game
	if (active)
	{
		yVelocity += gravity;
	}
		

	//Cap up velocity
	if (yVelocity < -15)
		yVelocity = -15;

	screenPos.y += yVelocity * .9;

	//Don't fall out of the screen
	if (screenPos.y > screenHeight - 230)
	{
		dead = true;
		screenPos.y = screenHeight - 230;
		yVelocity = 0;
	}

	if (screenPos.y < -50)
		dead = true;

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
	

	//Set rotation in relation to velocity
	
	if (yVelocity < 15) {
		rotation = -10;                    // going up, point up
	}
	else if (rotation < 90) {                   // max downward tilt is 70 degrees 
		rotation += 4;      // going down, point more and more down
	}
	
	//only rotation if active
	if (!active)
		rotation = 0;

}

void Bird::Draw(Renderer& renderer)
{	
	// convert rotation from degrees to radians then draw
	renderer.DrawBird(screenPos, rotation * (3.14 / 180), currentFrame);
}

void Bird::Reset()
{
	dead = false;
	screenPos.y = yPosInit;
	yVelocity = 0;
	score = 0;
}

void Bird::setScreenPos(Vector2 newPos)
{
	if (screenPos.y < 0)
		screenPos = newPos;
}

void Bird::setScreenHeight(int height)
{
	screenHeight = height;
	screenPos.y = (height - 260) / 2;
	yPosInit = (height - 260) / 2;
}
