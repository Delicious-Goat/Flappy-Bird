#pragma once
#include "pch.h"
#include <Eigen/Dense>
#include <Eigen/Core>
using namespace Eigen;

class NeuralNetwork
{
private:

    static double sigmoid(int x)
    {
        return 1 / (1 + exp(-x));
    }

public:
    MatrixXd weightsIH;
    MatrixXd weightsHO;
    MatrixXd biasesIH;
    MatrixXd biasesHO;

public:
	NeuralNetwork(int in, int hid, int out)
	{
        weightsIH = MatrixXd::Random(hid,in);

        weightsHO = MatrixXd::Random(out,hid);

        biasesIH = MatrixXd::Random(hid,1);
        biasesHO = MatrixXd::Random(out,1);  
	}

    //Copy Constructors
    NeuralNetwork(NeuralNetwork& net)
    {
        weightsIH = net.weightsIH;
        weightsHO = net.weightsHO;

        biasesIH = net.biasesIH;
        biasesHO = net.biasesHO;
    }
    NeuralNetwork(std::shared_ptr<NeuralNetwork> net)
    {
        weightsIH = net->weightsIH;
        weightsHO = net->weightsHO;

        biasesIH = net->biasesIH;
        biasesHO = net->biasesHO;
    }

    
    int feedForward(MatrixXd input)
    {     
        MatrixXd hiddenOutputs = (weightsIH * input) + biasesIH;
        hiddenOutputs.unaryExpr([&](double x) {return sigmoid(x); });

        MatrixXd finalOutputs = (weightsHO * hiddenOutputs) + biasesHO;
        finalOutputs.unaryExpr([&](double x) {return sigmoid(x); });

        
        if (finalOutputs(0) > finalOutputs(1))
            return 1;
        return 0; 
    }

    void mutate(double rate)
    {
       srand((unsigned)time(NULL));
       weightsIH.unaryExpr([&](double x) {
           if (rand()%1 < rate)
           {

               return ((double)rand() / (double)RAND_MAX);
           }
           else
           {
               return x;
           }
       });
    }

};