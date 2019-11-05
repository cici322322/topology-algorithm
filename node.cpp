#include "node.h"

Node::Node(){}

Node::Node(int _x):x(_x){}

Node::Node(int _x,int _y):x(_x),y(_y){}

Node::Node(int _x,int _y,int _id,double _energy=double(100)):x(_x),y(_y),id(_id),energy(_energy){}

Node::Node(int _x,int _y,int _id,double _energy,Scalar _color):
	x(_x),y(_y),id(_id),energy(_energy),color(_color){}

Node::~Node(void){}


Scalar  Node::NodeColor(){
		if(energy>75)
		{color=Scalar(255,0,0);}  
		else if(energy>56)
		{color=Scalar(0,255,255);}
		else if(energy>42)
		{color=Scalar(0,128,255);}
		else if(energy>31)
		{color=Scalar(0,0,255);} 
		else if(energy>23)
		{color=Scalar(140,140,140);}
		else
		{color=Scalar(0,0,0);}
		return color;
	}

int Node:: layer (){
		if (distance()<303)
		return 0;
		else if(distance()<428)
			return 1;
		else if(distance()<524)
			return 2;
		else if(distance()<608)
			return 3;
		else
			return 4;
	}


int Node::GetNodeID()const
{return id;}

Scalar Node::GetNodeColor()const
{return color;}
