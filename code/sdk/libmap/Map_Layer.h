#ifndef Map_Layer_h_
#define Map_Layer_h_

#include <iostream>
#include <map>
#include <deque>
#include "Map_Define.h"
#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

class Map_Editor;
class Map_Role;
class Map_Layer : public Layer
{
public:
	static Map_Layer * createMapLayer(char * imageDir);

	void registerTouchBegan(Ref * obj, TouchBegan_Function func);
	void registerTouchMove(Ref * obj, TouchMove_Function func);
	void registerTouchEnd(Ref * obj, TouchEnd_Function func);
	void destroyTouchBegan(){ this->touchBeganObj = NULL; this->touchBeganFunc = NULL; }
	void destroyTouchMove(){ this->touchMoveObj = NULL; this->touchMoveFunc = NULL; }
	void destroyTouchEnd(){ this->touchEndObj = NULL; this->touchEndFunc = NULL; }

	///////
	void updateBlock(Vec2 & point, float dt);
	void setSpeed(float speed){ this->speed = speed; };
private:
	Map_Layer();
	~Map_Layer();

	CREATE_FUNC(Map_Layer);
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

	////////////// 私有继承的方法 /////////////////

	//不能直接让外界设置地图的坐标
	virtual void setPosition(const Vec2 &position){
		Layer::setPosition(position);
	}
	virtual void setPosition(float x, float y){
		Layer::setPosition(x, y);
	}
	virtual void setPositionX(float x){
		Layer::setPositionX(x);
	}
	virtual void setPositionY(float y){
		Layer::setPositionY(y);
	}

	///////////////////////////
	bool initMapData();
	bool updateBlockSpriteFrame(int x, int y, Sprite *);
private:
	//
	Ref * touchBeganObj;
	Ref * touchMoveObj;
	Ref * touchEndObj;
	TouchBegan_Function touchBeganFunc;
	TouchMove_Function touchMoveFunc;
	TouchEnd_Function	touchEndFunc;
	//
	char imageDir[512];
	Size beyondSize; //绘制地图块的时候允许超越的长
	float speed;	//地图的移动速度
	map<int, map<int, Sprite *>> map_blockSprite;
	deque<Sprite *> deque_removeBlockSprite;
};

#endif