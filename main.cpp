#include <opencv2\opencv.hpp>

#include "topology.h"
#include "node.h"

using namespace std;
using namespace cv;

void  help(){
	cout<<"    ///////////////////////////////////////////////////////"<<endl
		<<"start to simulate wsn"<<endl
		<<"random 1-10 nodes send signal"<<endl
		<<"the color of nodes represents ResEnergy"<<endl
		<<"interval of two flashingrepresents one unit timeT"<<endl
		<<"bule means 100% >= ResEnergy > 75%" <<endl
		<<"yellow means 75% >= ResEnergy > 56%"<<endl
		<<"orange means 56% >= ResEnergy > 42%"<<endl
		<<"red means 42% > =ResEnergy > 31%"<<endl
		<<"grey means 31% >= ResEnergy > 235%"<<endl
		<<"black means 23% > =ResEnergy >  0 "<<endl
		<<"1 represents constant TX to leader nodes"<<endl
		<<"2 represents variable TX to leader nodes"<<endl
		<<"--"<<endl
		<<"select corresponedent number";
}

void main()
{
	help();
	WSNTopologyBasedEnergy wsntoplogy;
	char c = getchar();
	switch (c)
	{
	case '1':
		wsntoplogy = WSNTopologyBasedEnergy(WSNTopologyBasedEnergy::ConstPowertoLeader);
		break;
	case '2':
		wsntoplogy = WSNTopologyBasedEnergy(WSNTopologyBasedEnergy::VarPowertoLeaderAndSinkShift);
		break;
	default:
		cout<<"constant TX"<<endl;
		break;
	}
	cout<<"continue"<<endl;
	wsntoplogy.InitNode(600,600,100);
	wsntoplogy.ClassifyNode();
	wsntoplogy.DrawWSNLayer();
	wsntoplogy.FindLayerFirstLinkNode(); 	
	wsntoplogy.LinkNodeEachLayer();
	wsntoplogy.WSNLifeTime();

	waitKey();
} 
