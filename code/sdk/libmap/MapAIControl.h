#ifndef MapAIControl_h_
#define MapAIControl_h_

#include <iostream>
#include <deque>
#include "cocos2d.h"
using namespace std;
using namespace cocos2d;

class MapAIData
{
public :
	MapAIData(){
		complete = false;
	}
	~MapAIData(){}

	//��ʼ��ͽ�����
	Vec2 begin_tile_Point;
	Vec2 end_tile_Point;
	bool complete;

	//�����������
	vector<Vec2> tile_Point;
};

class AiNode
{
public:
	AiNode(){
		g = 0;
		h = 0;
	}
	~AiNode(){}
	//f = g + h
	int g;
	int h;

	Vec2 tilePoint;
	AiNode * parentP;//ָ�򸸽ڵ�
};

class MapAIControl
{
private:

private:
	MapAIControl();
	~MapAIControl();
public:
	static MapAIControl * getObject()
	{
		static MapAIControl control;
		return &control;
	}

	//���һ�����񣬽����߳�
	int addAITask(MapAIData * aiData);

private:
	void beginThread();
	static DWORD WINAPI run(LPVOID);
	bool lineRun1(MapAIData * aiData);
	bool lineRun2(MapAIData * aiData);
	void axing(MapAIData * aiData);

	AiNode * inCose(int tile_x, int tile_y);
	AiNode * inOpen(int tile_x, int tile_y);
	void addOpen(MapAIData *, AiNode *);
	void _addOpen(MapAIData *, AiNode *, int tile_x, int tile_y);
	AiNode * getOpenNode();
	void deleteAllArray();
private:
	bool isRun;
	deque<MapAIData *> deque_data;
	list<AiNode *> open;
	list<AiNode *> close;
};

#endif