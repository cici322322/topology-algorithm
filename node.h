#pragma once
#include <math.h>

#include "opencv2/opencv.hpp"

using namespace cv;

class WSNNode
{
public:
	WSNNode();
	WSNNode(int );
	WSNNode(int ,int );
	WSNNode(int _x,int _y,int _number,double _energy);
	WSNNode(int _x,int _y,int _number,double _energy,Scalar _color);
	~WSNNode(void);
	float distance()const{return sqrt(float(x*x+y*y));}
	int layer ();
	Scalar NodeColor();
	int GetNodeID()const;
	Scalar GetNodeColor()const;

public:
	int x,y;
	double energy;

private:
	int leaderID;
	int id;
	Scalar color;
};

