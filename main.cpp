#include <opencv2\opencv.hpp>

#include "topology.h"
#include "node.h"

using namespace std;
using namespace cv;

void  help(){
	cout    <<"start to simulate wsn"<<endl
		<<"random 1-10 nodes send signal"<<endl
		<<"the color of nodes represents ResEnergy"<<endl
		<<"interval of two flashingrepresents one unit timeT"<<endl
		<<"bule means 100% >= ResEnergy > 75%" <<endl
		<<"yellow means 75% >= ResEnergy > 56%"<<endl
		<<"orange means 56% >= ResEnergy > 42%"<<endl
		<<"red means 42% > =ResEnergy > 31%"<<endl
		<<"grey means 31% >= ResEnergy > 23%"<<endl
		<<"black means 23% > =ResEnergy >  0 "<<endl
		<<"1 represents constant TX to leader nodes"<<endl
		<<"2 represents variable TX to leader nodes"<<endl
		<<"select corresponedent number";
}

void main()
{
	help();
	Energy toplogy;
	char c = getchar();
	switch (c)
	{
	case '1':
		toplogy = Energy(Energy::ConstTXtoLeader);
		break;
	case '2':
		toplogy = Energy(Energy::VarTXtoLeader);
		break;
	default:
		cout<<"constant TX"<<endl;
		break;
	}
	cout<<"continue"<<endl;
	toplogy.InitNode(600,600,100);
	toplogy.ClassifyNode();
	oplogy.DrawLayer();
	toplogy.FindLayerFirstLinkNode(); 	
	toplogy.LinkNodeEachLayer();
	toplogy.WSNTime();

	waitKey();
} 
