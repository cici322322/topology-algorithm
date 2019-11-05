#include <ctime>
#include <vector>

#include <opencv2\opencv.hpp>
#include "node.h"

using namespace std;
using namespace cv;

class Energy
{
private:
	void drawCrossNode(Mat &img, Node node, Scalar color);
	double DistanceBetweenNodes(Node node1,Node node2);
	double SDistanceBetweenNodes(Node node1,Node node2);
	vector<int> SelectServalNode();
	void SelectLeaderID();
	void TopLayer0Sink();
	void TopLayer1Sink();
	void TopLayer2Sink();
	void TopLayer3Sink();
	void TopLayer4Sink();

	int MinMark();
	void NodeSentSignalVarTX();
	void NodeSentSignalConstTX();

private:
	Mat img;
	bool Test
	char type
	Node sink;
	double alpha;
	int TopLayer;
	static const int NODENUM = 100;
	static const int LayerNum = 5;
	double ENERGY;
	double NetThresEnergy;
	int Mark[LayerNum];
	double ThresEnergy[LayerNum];
	Node node[NODENUM];
	Node LayerFirstLinkNode[LayerNum];
	vector<Node> layer[LayerNum]; 
	vector<Node> LayerLeaderSeq[LayerNum];
	Node LayerLeaderNode[LayerNum];
	
public:
	enum TransportType
	{
		ConstTX = 0,
		VarTX = 1,
	};

public:
        Energy(TransportType type = ConstTX);
	int InitNode(int width, int heigth,  int NodeNum);
	void ClassifyNode();
	void DrawLayer();
	void FindFirstLinkNode();
	void LinkNodeEachLayer();
	int LifeTime();


};
