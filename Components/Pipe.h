#pragma once
#include "Renderer.h"
using namespace DirectX::SimpleMath;
class Pipe
{
private:
	Vector2 screenPos;
	int index;
	const int w = 160;
	int gapSize = 200;
public:
	Pipe(int initX);
	~Pipe() = default;

	void Update(float deltaX);
	void Draw(Renderer& renderer);
	void Reset();

	inline int getX() { return screenPos.x; }
	inline int getW() { return w; }
	inline int getGapH() { return screenPos.y; }
	inline int getGapSize() { return gapSize; }
};

