#pragma once
#include "pch.h"
#include "pipe.h"
#include "Renderer.h"


using namespace DirectX::SimpleMath;
class Bird
{
private:
	Vector2 screenPos;
	float yVelocity;
	int screenHeight;

	const float gravity = 1;
	const float lift = 40; 

	int currentFrame;
	float rotation;
	static float normalize(float x) { return 40 / (1 + exp(-.1 * x)) - 20; }
	
	bool dead;

	Pipe** pipes;

	int w, h;


	bool collisionDetection(Vector2* birdPoints, Vector2* pipePoints);

public:
	Bird(Pipe* pipesInit[6]);
	~Bird();

	//Move private
	Vector2* getBirdPoints(Vector2* points);
	Vector2* getPipePoints(Vector2* points, int index, int top);

	void Flap();
	void Update(int frameCount, bool active);
	void Draw(Renderer& renderer);


	void setScreenPos(Vector2 newPos);
	void setScreenHeight(int height);

	inline Vector2 Bird::getScreenPos() { return screenPos; }
	inline void setX(int newX) { screenPos.x = newX; }
	inline void setY(int newY) { screenPos.y = newY; }
	inline int getYVelocity() { return yVelocity; }
	inline void setYVelocity(int newYVelocity) { yVelocity = newYVelocity; }
	inline bool isDead() { return dead; }
	inline void kill() { dead = true; }
	inline int getRotation() { return rotation; }
};

