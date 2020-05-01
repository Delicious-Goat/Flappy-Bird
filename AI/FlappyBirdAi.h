#pragma once
#include "bird.h"
#include "NeuralNetwork.h"

#define popSize 100

class FlappyBirdAi
{
private:
	Bird* birds[popSize];

	NeuralNetwork* brains[popSize];

public:
	FlappyBirdAi(Pipe** pipes)
	{
		for (int i = 0; i < popSize; i++)
		{
			birds[i] = new Bird;
			birds[i]->initPipes(pipes);

			brains[i] = new NeuralNetwork(14, 20, 2);
		}
	}
	~FlappyBirdAi()
	{
		for (int i = popSize; i > 0; i--)
		{
			delete birds[i];

			delete brains[i];
		}
	}
	void Draw(Renderer& renderer)
	{
		for (int i = 0; i < popSize; i++)
		{
			birds[i]->Draw(renderer);
		}
	}
	void Update(int frameCount, bool active)
	{
		for (int i = 0; i < popSize; i++)
		{
			birds[i]->Update(frameCount, active);
			
			auto pipes = birds[i]->getPipes();

			MatrixXd input(14,1);
			input << birds[i]->getYVelocity(),birds[i]->getY(),
					pipes[0]->getX(), pipes[0]->getGapH(),
					pipes[1]->getX(), pipes[1]->getGapH(),
					pipes[2]->getX(), pipes[2]->getGapH(),
					pipes[3]->getX(), pipes[3]->getGapH(),
					pipes[4]->getX(), pipes[4]->getGapH(),
					pipes[5]->getX(), pipes[5]->getGapH();


			int result = brains[i]->feedForward(input);

			if (result == 1)
			{
				birds[i]->Flap();
			}
			
			

		}
	}
	void setX(int x)
	{
		for (int i = 0; i < popSize; i++)
		{
			birds[i]->setX(x);
		}
	}
	void setScreenHeight(int h)
	{
		for (int i = 0; i < popSize; i++)
		{
			birds[i]->setScreenHeight(h);
		}
	}
};
