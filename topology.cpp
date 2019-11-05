#include "topology.h"

Energy::Energy(TransportType type){
	type_ = type;
	img = Mat(600,600,CV_8UC3,Scalar(255,255,255));
	Test= true;
	sink=Node(0,0);
	alpha = 0.00002;
	TopLayer=0;
	ENERGY=100;
	NetThresEnergy=75;
	for(int i=0;i<LayerNum;i++){
		Mark[i]=0;
		ThresEnergy[i]=75;
	}
}

int Energy::InitNode(int width, int heigth,  int NodeNum)
{
	if(NodeNum > width * heigth)
		return 0;


	srand((int)time(0));
	for (int i= 0; i< NodeNum; i++) 
	{ 
		int row = rand() % width;
		int col = rand() % heigth;

		node[i]=Node(col,row,i,ENERGY,Scalar(255,0,0));
		drawCrossNode(img,node[i],Scalar(255,0,0));

		imshow("network",img);
		if(true==Test) waitKey(30);
	}
	imshow("network", img);
	if(true==Test) waitKey();
	return 1;
}

void Energy::ClassifyNode()
{
	for(int i=0;i<NODENUM;i++)
	{
		if(0==node[i].layer())
			layer[0].push_back(node[i]);
		else if(1==node[i].layer())
			layer[1].push_back(node[i]);
		else if(2==node[i].layer())
			layer[2].push_back(node[i]);
		else if(3==node[i].layer())
			layer[3].push_back(node[i]);
		else if(4==node[i].layer())
			layer[4].push_back(node[i]);
	}
}

void Energy::DrawLayer()
{
	circle(img,Point(0,0),1,Scalar(255,0,255));
	imshow("network",img);
	if(true==Test) waitKey(200);

	circle(img,Point(0,0),303,Scalar(255,0,255));
	imshow("network",img);
	if(true==Test) waitKey(200);

	circle(img,Point(0,0),428,Scalar(255,0,255));
	imshow("network",img);
	if(true==Test) waitKey(200);

	circle(img,Point(0,0),524,Scalar(255,0,255));
	imshow("network",img);
	if(true==Test) waitKey(200);

	circle(img,Point(0,0),608,Scalar(255,0,255));
	imshow("network",img);
	if(true==Test) waitKey();
}

void Energy::FindLayerFirstLinkNode()
{
	vector<Node>::iterator it;

	for(int i=0;i<LayerNum;i++)
	{
		Node FirstLinkNode(600);
		for(it=layer[i].begin();it!=layer[i].end();it++)
		{
			if(it->x<FirstLinkNode.x)
				FirstLinkNode=*it;
		}
		circle(img,Point(FirstLinkNode.x,FirstLinkNode.y),4,Scalar(0,255,0),2,8,0);
		imshow("WSN",img);
		LayerFirstLinkNode[i]=FirstLinkNode;
		if(true==Test) waitKey(200);
	}
	if(true==Test) waitKey();
}

void Energy::LinkNodeEachLayer()
{
	vector<Node> temp1;

	for(int i=0;i<LayerNum;i++)
	{
		temp1=layer[i];
		int temp1cap=temp1.size();
		LayerLeaderSeq[i].clear();
		LayerLeaderSeq[i].push_back(LayerFirstLinkNode[i]);
		vector<Node>::iterator it;

		while( LayerLeaderSeq[i].size()<unsigned int(temp1cap+1))

		{
			Node NextNode=*(temp1.begin());
			vector<Node>::iterator p;

			for(it=temp1.begin();it!=temp1.end();it++)
			{
				if( DistanceBetweenNodes(*(LayerLeaderSeq[i].end()-1) ,*it) <= 
					DistanceBetweenNodes(*(LayerLeaderSeq[i].end()-1),NextNode)  )
				{
					NextNode=*it;	
					p=it;
				}
			}

			LayerLeaderSeq[i].push_back(NextNode);
			temp1.erase(p);
		}

		LayerLeaderSeq[i].erase(LayerLeaderSeq[i].begin());

		for(it=LayerLeaderSeq[i].begin();it!=LayerLeaderSeq[i].end()-1;it++)
		{
			line(img, Point(it->x,it->y), Point((it+1)->x,(it+1)->y), Scalar(155,155,155),1,8,0);  
			imshow("network",img);
			if(true==Test) waitKey(30);
		}
		if(true==Test) waitKey(200);
	}
	if(true==Test) waitKey();
}

int Energy::LifeTime()
{
	int i=-1;
	int SentCount=0;
	bool   BREAK=false;
	while(SentCount+1)
	{

		if(type_==ConstTXtoLeader)
			NodeSentSignalConstTX();
		else if(type_==VarTXtoLeader)
			NodeSentSignalVarTX();



		for( i=0;i<NODENUM;i++)
		{
			if(node[i].energy<=0)
			{
				BREAK=true;
				circle(img,Point(node[i].x,node[i].y),5,Scalar(0,0,0),3,8,0);
				imshow("network",img);
				break;
			}
		}

		if(BREAK)
			break;	

		SentCount++;
	}
	cout<<"sent"<<SentCount<<"times"<<endl;

	return i;
}

void Energy::drawCrossNode(Mat &img, Node node, Scalar color)
{
	int col = node.x > 2 ? node.x : 2;
	int row = node.y> 2 ? node.y : 2;

	line(img, Point(col -2, row - 2), Point(col + 2, row + 2), color,2,8,0);  
	line(img, Point(col + 2, row - 2), Point(col - 2, row + 2), color,2,8,0);  
}

double Energy::DistanceBetweenNodes(Node node1,Node node2)
{
	return sqrt(   (node1.x-node2.x)*(node1.x-node2.x) + (node1.y-node2.y)*(node1.y-node2.y)   );
}

double Energy::SDistanceBetweenNodes(Node node1,Node node2)
{
	return ( (node1.x-node2.x)*(node1.x-node2.x) + (node1.y-node2.y)*(node1.y-node2.y) )  ;
}

vector<int> Energy::SelectSeveralNode()
{
	vector<int> SelectNodeSeq;
	vector<int>::iterator it;

	srand((int)time(0));
	int SelectNodeNum=rand()%9+1;
	for(int i=0;i<SelectNodeNum;i++)
	{
		SelectNodeSeq.push_back(rand()%99);
	}
	for(int i=0;i<LayerNum;i++)
	{
		for(it=SelectNodeSeq.begin();it!=SelectNodeSeq.end();it++)
		{
			drawCrossNode(img,node[*it],Scalar(255,255,255));
		}
		cv::imshow("network",img);
		if(true==Test) waitKey(70);
		for(it=SelectNodeSeq.begin();it!=SelectNodeSeq.end();it++)
		{
			drawCrossNode(img,node[*it],node[*it].NodeColor());	
		}
		cv::imshow("network",img);
		if(true==Test) waitKey(70);
	}
	return SelectNodeSeq;
}
void Energy::SelectLeaderID()
{
	vector<Node>::iterator it;
	int i=0;
	while(i<LayerNum)
	{
		int j=0;
		bool   BREAK=false;
		for(it=LayerLeaderSeq[i].begin();it!=LayerLeaderSeq[i].end();it++)
		{
			if(node[it->GetNodeID()].energy>=ThresEnergy[i])
			{
				LayerLeaderNode[i]=*it;
				drawCrossNode(img,node[LayerLeaderNode[i].GetNodeID()],node[LayerLeaderNode[i].GetNodeID()].NodeColor());
				imshow("WSN",img);
				i++;
				BREAK=true;
				break;
			}
			j++;
		}
		if(BREAK) continue;
		if(j==LayerLeaderSeq[i].size())
		{
			ThresEnergy[i]=3*ThresEnergy[i]/4;
			Mark[i]++;
		}

	}
}
void Energy::TopLayer0Sink()
{
	vector<int>::iterator it;
	vector<int> _array=SelectSeveralNode();
	for(it=_array.begin();it!=_array.end();it++)
	{
		Mat tempimg=img.clone();
		SelectLeaderID();
		line(tempimg,Point(0,0),Point(LayerLeaderNode[0].x,LayerLeaderNode[0].y),Scalar(45,150,45),1,8,0);
		for(int i=0;i<LayerNum-1;i++)
		{
			line(tempimg,Point(LayerLeaderNode[i].x,LayerLeaderNode[i].y),Point(LayerLeaderNode[i+1].x,LayerLeaderNode[i+1].y),Scalar(0,255,0));
			imshow("network",tempimg);
		}
		if(true==Test) waitKey(100);
		if(0==node[*it].layer())
		{
			node[LayerLeaderNode[0].GetNodeID()].energy-=1+alpha * SDistanceBetweenNodes(LayerLeaderNode[0],sink);
			node[*it].energy-=0.5+alpha * SDistanceBetweenNodes(node[*it],LayerLeaderNode[0]);
		}
		else if(1==node[*it].layer())
		{
			node[LayerLeaderNode[1].GetNodeID()].energy-=1+alpha * SDistanceBetweenNodes(LayerLeaderNode[1],LayerLeaderNode[0]);
			node[*it].energy-=0.5+alpha * SDistanceBetweenNodes(node[*it],LayerLeaderNode[1]);
			node[LayerLeaderNode[0].GetNodeID()].energy-=1;
		}
		else if(2==node[*it].layer())
		{
			node[LayerLeaderNode[2].GetNodeID()].energy-=1+alpha * SDistanceBetweenNodes(LayerLeaderNode[2],LayerLeaderNode[1]);
			node[*it].energy-=0.5+alpha * SDistanceBetweenNodes(node[*it],LayerLeaderNode[2]);
			node[LayerLeaderNode[0].GetNodeID()].energy-=1;
			node[LayerLeaderNode[1].GetNodeID()].energy-=1;

		}

		else if(3==node[*it].layer())
		{
			node[LayerLeaderNode[3].GetNodeID()].energy-=1+alpha * SDistanceBetweenNodes(LayerLeaderNode[3],LayerLeaderNode[2]);
			node[*it].energy-=0.5+alpha * SDistanceBetweenNodes(node[*it],LayerLeaderNode[3]);
			node[LayerLeaderNode[0].GetNodeID()].energy-=1;
			node[LayerLeaderNode[1].GetNodeID()].energy-=1;
			node[LayerLeaderNode[2].GetNodeID()].energy-=1;
		}
		else 
		{
			node[LayerLeaderNode[4].GetNodeID()].energy-=1+alpha * SDistanceBetweenNodes(LayerLeaderNode[4],LayerLeaderNode[3]);
			node[*it].energy-=0.5+alpha * SDistanceBetweenNodes(node[*it],LayerLeaderNode[4]);
			node[LayerLeaderNode[0].GetNodeID()].energy-=1;
			node[LayerLeaderNode[1].GetNodeID()].energy-=1;
			node[LayerLeaderNode[2].GetNodeID()].energy-=1;
			node[LayerLeaderNode[3].GetNodeID()].energy-=1;
		}

		drawCrossNode(img,node[*it],node[*it].NodeColor());
		imshow("network",img);	

	for(int i=0;i<NODENUM;i++)
	{
		drawCrossNode(img,node[i],node[i].NodeColor());
		imshow("network",img);
	}
	if(true==Test) waitKey(400); 
}

void Energy::TopLayer1Sink()
{
	vector<int>::iterator it;
	vector<int> _array=SelectSeveralNode();
	for(it=_array.begin();it!=_array.end();it++)
	{
		Mat tempimg=img.clone();

		SelectLeaderID();

		line(tempimg,Point(0,0),Point(LayerLeaderNode[1].x,LayerLeaderNode[1].y),Scalar(45,150,45),1,8,0);
		for(int i=0;i<LayerNum-1;i++)
		{
			line(tempimg,Point(LayerLeaderNode[i].x,LayerLeaderNode[i].y),Point(LayerLeaderNode[i+1].x,LayerLeaderNode[i+1].y),Scalar(0,255,0));
			imshow("network",tempimg);
		}
		if(true==Test) waitKey(100);
		if(0==node[*it].layer())
		{
			node[LayerLeaderNode[0].GetNodeID()].energy-=1+alpha * SDistanceBetweenNodes(LayerLeaderNode[0],LayerLeaderNode[1]);
			node[*it].energy-=0.5+alpha * SDistanceBetweenNodes(node[*it],LayerLeaderNode[0]);
			node[LayerLeaderNode[1].GetNodeID()].energy-=1;
		}
		else if(1==node[*it].layer())
		{
			node[LayerLeaderNode[1].GetNodeID()].energy-=1+alpha * SDistanceBetweenNodes(LayerLeaderNode[1],sink);
			node[*it].energy-=0.5+alpha * SDistanceBetweenNodes(node[*it],LayerLeaderNode[1]);
		}
		else if(2==node[*it].layer())
		{
			node[LayerLeaderNode[2].GetNodeID()].energy-=1+alpha * SDistanceBetweenNodes(LayerLeaderNode[2],LayerLeaderNode[1]);
			node[*it].energy-=0.5+alpha * SDistanceBetweenNodes(node[*it],LayerLeaderNode[2]);
			node[LayerLeaderNode[1].GetNodeID()].energy-=1;

		}

		else if(3==node[*it].layer())
		{
			node[LayerLeaderNode[3].GetNodeID()].energy-=1+alpha * SDistanceBetweenNodes(LayerLeaderNode[3],LayerLeaderNode[2]);
			node[*it].energy-=0.5+alpha * SDistanceBetweenNodes(node[*it],LayerLeaderNode[3]);
			node[LayerLeaderNode[1].GetNodeID()].energy-=1;
			node[LayerLeaderNode[2].GetNodeID()].energy-=1;
		}
		else 
		{
			node[LayerLeaderNode[4].GetNodeID()].energy-=1+alpha * SDistanceBetweenNodes(LayerLeaderNode[4],LayerLeaderNode[3]);
			node[*it].energy-=0.5+alpha * SDistanceBetweenNodes(node[*it],LayerLeaderNode[4]);
			node[LayerLeaderNode[1].GetNodeID()].energy-=1;
			node[LayerLeaderNode[2].GetNodeID()].energy-=1;
			node[LayerLeaderNode[3].GetNodeID()].energy-=1;
		}

		drawCrossNode(img,node[*it],node[*it].NodeColor());
		imshow("network",img);	
	}

	for(int i=0;i<NODENUM;i++)
	{
		drawCrossNode(img,node[i],node[i].NodeColor());
		imshow("network",img);
	}
	if(true==Test) waitKey(400);
}

void Energy::TopLayer2Sink()
{
	vector<int>::iterator it;
	vector<int> _array=SelectSeveralNode();
	for(it=_array.begin();it!=_array.end();it++)
	{
		Mat tempimg=img.clone();
		SelectLeaderID();
		line(tempimg,Point(0,0),Point(LayerLeaderNode[2].x,LayerLeaderNode[2].y),Scalar(45,150,45),1,8,0);
		for(int i=0;i<LayerNum-1;i++)
		{
			line(tempimg,Point(LayerLeaderNode[i].x,LayerLeaderNode[i].y),Point(LayerLeaderNode[i+1].x,LayerLeaderNode[i+1].y),Scalar(0,255,0));
			imshow("network",tempimg);
		}
		if(true==Test) waitKey(100);
		if(0==node[*it].layer())
		{
			node[LayerLeaderNode[0].GetNodeID()].energy-=1+alpha * SDistanceBetweenNodes(LayerLeaderNode[0],LayerLeaderNode[1]);
			node[*it].energy-=0.5+alpha * SDistanceBetweenNodes(node[*it],LayerLeaderNode[0]);
			node[LayerLeaderNode[1].GetNodeID()].energy-=1;
			node[LayerLeaderNode[2].GetNodeID()].energy-=1;
		}
		else if(1==node[*it].layer())
		{
			node[LayerLeaderNode[1].GetNodeID()].energy-=1+alpha * SDistanceBetweenNodes(LayerLeaderNode[1],LayerLeaderNode[2]);
			node[*it].energy-=0.5+alpha * SDistanceBetweenNodes(node[*it],LayerLeaderNode[1]);
			node[LayerLeaderNode[2].GetNodeID()].energy-=1;
		}
		else if(2==node[*it].layer())
		{
			node[LayerLeaderNode[2].GetNodeID()].energy-=1+alpha * SDistanceBetweenNodes(LayerLeaderNode[2],sink);
			node[*it].energy-=0.5+alpha * SDistanceBetweenNodes(node[*it],LayerLeaderNode[2]);
		}

		else if(3==node[*it].layer())
		{
			node[LayerLeaderNode[3].GetNodeID()].energy-=1+alpha * SDistanceBetweenNodes(LayerLeaderNode[3],LayerLeaderNode[2]);
			node[*it].energy-=0.5+alpha * SDistanceBetweenNodes(node[*it],LayerLeaderNode[3]);
			node[LayerLeaderNode[2].GetNodeID()].energy-=1;
		}
		else 
		{
			node[LayerLeaderNode[4].GetNodeID()].energy-=1+alpha * SDistanceBetweenNodes(LayerLeaderNode[4],LayerLeaderNode[3]);
			node[*it].energy-=0.5+alpha * SDistanceBetweenNodes(node[*it],LayerLeaderNode[4]);
			node[LayerLeaderNode[2].GetNodeID()].energy-=1;
			node[LayerLeaderNode[3].GetNodeID()].energy-=1;
		}
		drawCrossNode(img,node[*it],node[*it].NodeColor());
		imshow("network",img);	
	}
	for(int i=0;i<NODENUM;i++)
	{
		drawCrossNode(img,node[i],node[i].NodeColor());
		imshow("network",img);
	}
	if(true==Test) waitKey(400);
}

void Energy::TopLayer3Sink()
{
	vector<int>::iterator it;
	vector<int> _array=SelectSeveralNode();
	for(it=_array.begin();it!=_array.end();it++)
	{
		Mat tempimg=img.clone();

		SelectLeaderID();

		line(tempimg,Point(0,0),Point(LayerLeaderNode[3].x,LayerLeaderNode[3].y),Scalar(45,150,45),1,8,0);
		for(int i=0;i<LayerNum-1;i++)
		{
			line(tempimg,Point(LayerLeaderNode[i].x,LayerLeaderNode[i].y),Point(LayerLeaderNode[i+1].x,LayerLeaderNode[i+1].y),Scalar(0,255,0));
			imshow("network",tempimg);
		}
		if(true==Test) waitKey(100);
		if(0==node[*it].layer())
		{
			node[LayerLeaderNode[0].GetNodeID()].energy-=1+alpha * SDistanceBetweenNodes(LayerLeaderNode[0],LayerLeaderNode[1]);
			node[*it].energy-=0.5+alpha * SDistanceBetweenNodes(node[*it],LayerLeaderNode[0]);
			node[LayerLeaderNode[1].GetNodeID()].energy-=1;
			node[LayerLeaderNode[2].GetNodeID()].energy-=1;
			node[LayerLeaderNode[3].GetNodeID()].energy-=1;
		}
		else if(1==node[*it].layer())
		{
			node[LayerLeaderNode[1].GetNodeID()].energy-=1+alpha * SDistanceBetweenNodes(LayerLeaderNode[1],LayerLeaderNode[2]);
			node[*it].energy-=0.5+alpha * SDistanceBetweenNodes(node[*it],LayerLeaderNode[1]);
			node[LayerLeaderNode[2].GetNodeID()].energy-=1;
			node[LayerLeaderNode[3].GetNodeID()].energy-=1;
		}
		else if(2==node[*it].layer())
		{
			node[LayerLeaderNode[2].GetNodeID()].energy-=1+alpha * SDistanceBetweenNodes(LayerLeaderNode[2],LayerLeaderNode[3]);
			node[*it].energy-=0.5+alpha * SDistanceBetweenNodes(node[*it],LayerLeaderNode[2]);
			node[LayerLeaderNode[3].GetNodeID()].energy-=1;
		}

		else if(3==node[*it].layer())
		{
			node[LayerLeaderNode[3].GetNodeID()].energy-=1+alpha * SDistanceBetweenNodes(LayerLeaderNode[3],sink);
			node[*it].energy-=0.5+alpha * SDistanceBetweenNodes(node[*it],LayerLeaderNode[3]);
		}
		else 
		{
			node[LayerLeaderNode[4].GetNodeID()].energy-=1+alpha * SDistanceBetweenNodes(LayerLeaderNode[4],LayerLeaderNode[3]);
			node[*it].energy-=0.5+alpha * SDistanceBetweenNodes(node[*it],LayerLeaderNode[4]);
			node[LayerLeaderNode[3].GetNodeID()].energy-=1;
		}

		drawCrossNode(img,node[*it],node[*it].NodeColor());
		imshow("network",img);	
	}

	for(int i=0;i<NODENUM;i++)
	{
		drawCrossNode(img,node[i],node[i].NodeColor());
		imshow("network",img);
	}
	if(true==Test) waitKey(400); 
}

void Energy::TopLayer4Sink()
{
	vector<int>::iterator it;
	vector<int> _array=SelectServalNode();
	for(it=_array.begin();it!=_array.end();it++)
	{
		Mat tempimg=img.clone();

		SelectLeaderID();

		line(tempimg,Point(0,0),Point(LayerLeaderNode[4].x,LayerLeaderNode[4].y),Scalar(45,150,45),1,8,0);
		for(int i=0;i<LayerNum-1;i++)
		{
			line(tempimg,Point(LayerLeaderNode[i].x,LayerLeaderNode[i].y),Point(LayerLeaderNode[i+1].x,LayerLeaderNode[i+1].y),Scalar(0,255,0));
			imshow("network",tempimg);
		}
		if(true==Test) waitKey(100);

		if(0==node[*it].layer())
		{
			node[LayerLeaderNode[0].GetNodeID()].energy-=1+alpha * SDistanceBetweenNodes(LayerLeaderNode[0],LayerLeaderNode[1]);
			node[*it].energy-=0.5+alpha * SDistanceBetweenNodes(node[*it],LayerLeaderNode[0]);
			node[LayerLeaderNode[1].GetNodeID()].energy-=1;
			node[LayerLeaderNode[2].GetNodeID()].energy-=1;
			node[LayerLeaderNode[3].GetNodeID()].energy-=1;
			node[LayerLeaderNode[4].GetNodeID()].energy-=1;
		}
		else if(1==node[*it].layer())
		{
			node[LayerLeaderNode[1].GetNodeID()].energy-=1+alpha * SDistanceBetweenNodes(LayerLeaderNode[1],LayerLeaderNode[2]);
			node[*it].energy-=0.5+alpha * SDistanceBetweenNodes(node[*it],LayerLeaderNode[1]);
			node[LayerLeaderNode[2].GetNodeID()].energy-=1;
			node[LayerLeaderNode[3].GetNodeID()].energy-=1;
			node[LayerLeaderNode[4].GetNodeID()].energy-=1;
		}
		else if(2==node[*it].layer())
		{
			node[LayerLeaderNode[2].GetNodeID()].energy-=1+alpha * SDistanceBetweenNodes(LayerLeaderNode[2],LayerLeaderNode[3]);
			node[*it].energy-=0.5+alpha * SDistanceBetweenNodes(node[*it],LayerLeaderNode[2]);
			node[LayerLeaderNode[3].GetNodeID()].energy-=1;
			node[LayerLeaderNode[4].GetNodeID()].energy-=1;
		}

		else if(3==node[*it].layer())
		{
			node[LayerLeaderNode[3].GetNodeID()].energy-=1+alpha * SDistanceBetweenNodes(LayerLeaderNode[3],LayerLeaderNode[3]);
			node[*it].energy-=0.5+alpha * SDistanceBetweenNodes(node[*it],LayerLeaderNode[3]);
			node[LayerLeaderNode[4].GetNodeID()].energy-=1;
		}
		else 
		{
			node[LayerLeaderNode[4].GetNodeID()].energy-=1+alpha * SDistanceBetweenNodes(LayerLeaderNode[4],sink);
			node[*it].energy-=0.5+alpha * SDistanceBetweenNodes(node[*it],LayerLeaderNode[4]);
		}

		drawCrossNode(img,node[*it],node[*it].NodeColor());
		imshow("network",img);	
	}
	
	for(int i=0;i<NODENUM;i++)
	{
		drawCrossNode(img,node[i],node[i].NodeColor());
		imshow("network",img);
	}
	if(true==Test) waitKey(400);
}


int Energy::MinMark()
{
	int min=Mark[0];
	int j=0;
	for(int i=0;i<LayerNum;i++)
	{
		if(Mark[i]<min)
		{
			min=Mark[i];
			j=i;
		}
	}
	return j;
}

void Energy::NodeSentSignalVarTX()
{
	if(0==MinMark())
		TopLayer0Sink();
	else if(1==MinMark())
		TopLayer1Sink();
	else if(2==MinMark())
		TopLayer2Sink();
	else if(3==MinMark())
		TopLayer3Sink();
	else 
		TopLayer4Sink();

}

void Energy::NodeSentSignalConstTX()
{
	vector<int>::iterator it;
	vector<int> _array=SelectSeveralNode();
	for(it=_array.begin();it!=_array.end();it++)
	{
		SelectLeaderID();

		if(0==node[*it].layer())
		{
			node[LayerLeaderNode[0].GetNodeID()].energy-=10;
			node[*it].energy-=7;
		}
		else if(1==node[*it].layer())
		{

			node[LayerLeaderNode[1].GetNodeID()].energy-=10;
			node[*it].energy-=7;
		}
		else if(2==node[*it].layer())
		{
			node[LayerLeaderNode[2].GetNodeID()].energy-=10;
			node[*it].energy-=7;
		}

		else if(3==node[*it].layer())
		{
			node[LayerLeaderNode[3].GetNodeID()].energy-=10;
			node[*it].energy-=7;
		}
		else 
		{
			node[LayerLeaderNode[4].GetNodeID()].energy-=10;
			node[*it].energy-=7;
		}

		drawCrossNode(img,node[*it],node[*it].NodeColor());
		imshow("network",img);	
	}
	for(int i=0;i<LayerNum;i++)
	{
		drawCrossNode(img,node[LayerLeaderNode[i].GetNodeID()],node[LayerLeaderNode[i].GetNodeID()].NodeColor());
		imshow("network",img);
	}
	if(true==Test) waitKey(400);
}
