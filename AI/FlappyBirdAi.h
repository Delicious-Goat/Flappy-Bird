#pragma once
#include "pch.h"
#include "bird.h"
#include "NeuralNetwork.h"

#define popSize 250

class FlappyBirdAi
{
private:


	std::vector<Bird*> birds;
	std::vector<Bird*> deadBirds;
	std::vector<std::shared_ptr<NeuralNetwork>> brains;

	double fitnesses[popSize];

public:
	FlappyBirdAi(Pipe** pipes)
	{
		
		for (int i = 0; i < popSize; i++)
		{
			birds.emplace_back(new Bird);

			birds[i]->initPipes(pipes);
			
			brains.push_back(std::make_shared<NeuralNetwork>(4, 10, 2));
		}
		
	}
	~FlappyBirdAi()
	{
		for (int i = birds.size()-1; i >= 0; i--)
		{
			delete birds[i];
		}
		for (int i = deadBirds.size()-1; i >= 0; i--)
		{
			delete deadBirds[i];
		}

		birds.clear();
		deadBirds.clear();
		brains.clear();
	}
	void Draw(Renderer& renderer)
	{
		for (int i = 0; i < birds.size(); i++)
		{
		
			birds[i]->Draw(renderer);
		}		
	}
	void calculateFitness()
	{
		//calculate sum
		double sum = 0;

		for (int i = 0; i < popSize; i++)
		{
			sum += (deadBirds[i]->fitness - 200)/100;
		}

		//normalize fitness
		for (int i = 0; i < popSize; i++)
		{
			fitnesses[i] = ((deadBirds[i]->fitness - 200) / 100) / sum;
		}

	}

	int pickOne()
	{
		int* indices = new int[10000];
		int counter = 0;
		for (int i = 0; i < popSize; i++)
		{
			int num = fitnesses[i] * 10000;
			for (int j = 0; j < num; j++)
			{
				indices[counter] = i;
				counter++;
			}
		}

		int r = rand() % 10000;

		int picked = indices[r];

		delete[] indices;

		return picked;

		/*
		std::wstringstream wss(L"");
		double sum = 0;
		for (int i = 0; i < popSize; i++)
		{
			wss << fitnesses[i] << " ";
			sum += fitnesses[i];
		}
		wss << std::endl << sum<<std::endl;
		OutputDebugString(wss.str().c_str());
		*/

	}
	void nextGen(Pipe** pipes)
	{
		//pick a brain based on fitnesses
		calculateFitness();
		int picked = pickOne();

		//create the parent
		std::shared_ptr<NeuralNetwork> parent = brains[picked];

		//clear brains vector
		brains.clear();

		//generate new brains
		for(int i = 0; i<popSize; i ++)
		{
			brains.emplace_back(std::make_shared<NeuralNetwork>(parent));
		}
		
		
		//mutate every brain
		for (int i = 0; i < popSize; i++)
		{
			brains[i]->mutate(.05);
		}
		
		/*
		for (int i = 0; i < popSize; i++)
		{
			std::wstringstream wss(L"");
			for (int j = 0; j < 5; j++)
			{
				wss << brains[i]->weightsIH(j) << " ";
			}
			OutputDebugString(wss.str().c_str());
			OutputDebugStringA("\n");
		}
		
		std::wstringstream wss(L"");
		wss << brains[0]->weightsIH(3) << " ";
		OutputDebugString(wss.str().c_str());
		*/


		//Reset pipes
		for (int i = 0; i < 6; i++)
		{
			pipes[i]->Reset();
		}

		//create new birds
		for (int i = deadBirds.size()-1; i >= 0; i--)
		{
			deadBirds[i]->Reset();
			birds.emplace_back(std::move(deadBirds[i]));
		}
		deadBirds.clear();

	}

	static int nearestPipe(Pipe** pipes, int birdX) 
	{
		int nearestDistance = 0;
		int index = 0; 
		for (int i = 0; i < 6; i++)
		{
			if (pipes[i]->getX() < nearestDistance && pipes[i]->getX() > birdX)
			{
				nearestDistance = pipes[i]->getX() - birdX;
				index = i;
			}
		}

		return index;
	}

	void Update(int frameCount)
	{
		auto pipes = birds[0]->getPipes();
		int nearestIndex = nearestPipe(pipes, birds[0]->getX());
		Pipe* nearestPipe = pipes[nearestIndex];
		for (int i = 0; i < birds.size(); i++)
		{
			birds[i]->Update(frameCount);

			MatrixXd input(4,1);
			input << birds[i]->getYVelocity(), birds[i]->getY(),
					 nearestPipe->getX(), nearestPipe->getGapH();


			int result = brains[i]->feedForward(input);

			if (result == 1)
			{
				birds[i]->Flap();
			}
			
			
			if (birds[i]->isDead())
			{
				deadBirds.emplace_back(std::move(birds[i]));
				birds.erase(birds.begin() + i);

				//all birds are dead
				if (birds.empty())
				{
					nextGen(pipes);

					return;
				}
			}
			else {
				birds[i]->fitness++;
			}


		}
	}

	void setX(int x)
	{
		
		for (int i = 0; i < birds.size(); i++)
		{
			birds[i]->setX(x);
		}
		
	}

	void setScreenHeight(int h)
	{
		
		for (int i = 0; i < birds.size(); i++)
		{
			birds[i]->setScreenHeight(h);
		}
		
	}
};
