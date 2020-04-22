#pragma once
#include "Renderer.h"
using namespace DirectX::SimpleMath;
class Pipe
{
private:
	Vector2 screenPos;
	int gapY;
	int index;
	const int gapSize = 50;
public:
	Pipe(int initX);
	~Pipe() = default;

	void Update(float deltaX);
	void Draw(Renderer& renderer);
};

