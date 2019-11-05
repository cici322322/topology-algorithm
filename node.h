#pragma once
#include <math.h>

#include "opencv2/opencv.hpp"

using namespace cv;

class Node
{
public:
	Node();
	Node(int );
	Node(int ,int );
	Node(int _x,int _y,int _number,double _energy);
	Node(int _x,int _y,int _number,double _energy,Scalar _color);
	~Node(void);
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

