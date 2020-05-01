#pragma once
#include "pch.h"
#include "bird.h"
#include "NeuralNetwork.h"

#define popSize 100

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
			
			brains.push_back(std::make_shared<NeuralNetwork>(14, 20, 2));
		}
		
	}
	~FlappyBirdAi()
	{
		for (int i = birds.size(); i >= 0; i--)
		{
			delete birds[i];
		}
		for (int i = deadBirds.size(); i >= 0; i--)
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
			sum += deadBirds[i]->fitness;
		}

		//normalize fitness
		for (int i = 0; i < popSize; i++)
		{
			fitnesses[i] = deadBirds[i]->fitness / sum;
		}
	}

	int pickOne()
	{
		return rand() % popSize;
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
			brains[i]->mutate(1);
		}

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

	void Update(int frameCount)
	{
		auto pipes = birds[0]->getPipes();

		for (int i = 0; i < birds.size(); i++)
		{
			birds[i]->Update(frameCount);

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
