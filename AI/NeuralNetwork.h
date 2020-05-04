#pragma once
#include "pch.h"
#include <Eigen/Dense>
#include <Eigen/Core>
using namespace Eigen;

class NeuralNetwork
{
private:

    static double sigmoid(double x)
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
            return 0;
        return 1; 
    }

    double mutateFunc()
    {
        if ((double)rand() / RAND_MAX)
        {
            return (double)rand() / RAND_MAX;
        }
    }

    void mutate(double rate)
    {
        for (int i = 0; i < weightsIH.rows(); i++)
        {
            for (int j = 0; j < weightsIH.cols(); j++)
            {
                if((double)rand() / RAND_MAX < rate)
                    weightsIH(i, j) = mutateFunc();
            }
        }
        for (int i = 0; i < weightsHO.rows(); i++)
        {
            for (int j = 0; j < weightsHO.cols(); j++)
            {
                if ((double)rand() / RAND_MAX < rate)
                    weightsHO(i, j) = mutateFunc();
            }
        }
        for (int i = 0; i < biasesIH.rows(); i++)
        {
            for (int j = 0; j < biasesIH.cols(); j++)
            {
                if ((double)rand() / RAND_MAX < rate)
                    biasesIH(i, j) = mutateFunc();
            }
        }
        for (int i = 0; i < biasesHO.rows(); i++)
        {
            for (int j = 0; j < biasesHO.cols(); j++)
            {
                if ((double)rand() / RAND_MAX < rate)
                    biasesHO(i, j) = mutateFunc();
            }
        }


    }

};