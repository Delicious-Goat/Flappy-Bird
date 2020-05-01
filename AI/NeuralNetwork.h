#pragma once
#include "pch.h"
#include <Eigen/Dense>
#include <Eigen/Core>
using namespace Eigen;

class NeuralNetwork
{
private:
    double sigmoid(int x)
    {
        return 1 / (1 + exp(-x));
    }

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
    

};