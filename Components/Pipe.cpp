#include "pch.h"
#include "Pipe.h"

Pipe::Pipe(int initPlace)
{
	index = initPlace;

	screenPos.x = 1700 + index*(1600/4);

	screenPos.y = rand()%400 + 200;

}

void Pipe::Draw(Renderer& renderer)
{
	renderer.DrawPipe(screenPos);
}

void Pipe::Reset()
{
	screenPos.x = 1700 + index * (1600 / 4);

	screenPos.y = rand() % 400 + 200;
}

void Pipe::Update(float deltaX)
{
	screenPos.x -= deltaX;
	if (screenPos.x + 40 <= -400)
	{
		screenPos.x = 2000 - 40;
		screenPos.y = rand() % 400 + 200;
	}
}


