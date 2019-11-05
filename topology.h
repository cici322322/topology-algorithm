#include <ctime>
#include <vector>

#include <opencv2\opencv.hpp>
#include "node.h"

using namespace std;
using namespace cv;

class WSNTopologyBasedEnergy
{
public:
	enum TransportType
	{
		ConstPowertoLeader = 0,
		VarPowertoLeaderAndSinkShift = 1,
	};

public:
	WSNTopologyBasedEnergy(TransportType type = ConstPowertoLeader);
	int InitNode(int width, int heigth,  int NodeNum);
	void ClassifyNode();
	void DrawWSNLayer();
	void FindLayerFirstLinkNode();
	void LinkNodeEachLayer();
	int WSNLifeTime();

private:
	void drawCrossNode(Mat &img, WSNNode node, Scalar color);
	double DistanceBetweenNodes(WSNNode node1,WSNNode node2);
	double SDistanceBetweenNodes(WSNNode node1,WSNNode node2);
	vector<int> SelectServalNode();
	void SelectLeaderID();
	void TopLayer0SentSink();
	void TopLayer1SentSink();
	void TopLayer2SentSink();
	void TopLayer3SentSink();
	void TopLayer4SentSink();

	int MinMark();
	void NodeSentSignalVarPower();
	void NodeSentSignalSamePower();

private:
	Mat img;
	bool Test
	char type
	WSNNode sink;
	double alpha;
	int TopLayer;
	static const int NODENUM = 100;
	static const int LayerNum = 5;
	double ENERGY;
	double NetThresEnergy;
	int Mark[LayerNum];
	double ThresEnergy[LayerNum];
	WSNNode node[NODENUM];
	WSNNode LayerFirstLinkNode[LayerNum];
	vector<WSNNode> layer[LayerNum]; 
	vector<WSNNode> LayerLeaderSeq[LayerNum];
	WSNNode LayerLeaderNode[LayerNum];
};
