#pragma once
#include "pch.h"
#include "Renderer.h"

using namespace DirectX::SimpleMath;
class Bird
{
private:
	Vector2 screenPos;
	float yVelocity;
	int screenHeight;

	const float gravity = 1;
	const float lift = 5; 

	float rotation;

	bool dead;

public:
	Bird();
	~Bird();

	void Flap();
	void Update(float elapsedTime, bool active);
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

