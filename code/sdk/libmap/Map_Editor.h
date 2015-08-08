#ifndef _Map_Editor_h_
#define _Map_Editor_h_

#include <map>
#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

class Map_Editor : public Layer
{
public:
	Map_Editor();
	~Map_Editor();
	CREATE_FUNC(Map_Editor);

	void editStopData(int tile_x, int tile_y, int data);//�༭�赲����
	//�������Ƶ���ʱ������
	void drawEventAreaTemp(const Vec2 & beginTilePoint, const Vec2 & endTilePoint);
	//��ɻ��ƹ���
	void drawEventAreaOK(const Vec2 & beginTilePoint, const Vec2 & endTilePoint, int type);
	void drawEventArea(DrawNode * draw,const Vec2 & beginTilePoint, const Vec2 & endTilePoint);
	void deleteEventArea(int type,const Vec2 & tilePoint);
	void updateEventArea();

	void setCanDragMap(bool canDragMap) { this->canDragMap = canDragMap; }
	bool getCanDragMap(){ return this->canDragMap; }
private:
	////////////////
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	////////////////
	void drawGridLine();
private:
	bool canDragMap;//������קmap
	DrawNode * draw;
	DrawNode * drawArea;
	DrawNode * tmpDraw;//��ʱ����
	map<int, map<int , Sprite *>> map_TileData;
};

#endif