#ifndef MoveModel_h_
#define MoveModel_h_

#include "Map_Define.h"
#include "cocos2d.h"
#include <iostream>
#include <deque>
using namespace cocos2d;
using namespace std;

class MoveModel : public Node
{
public:
	MoveModel();
	~MoveModel();

	CREATE_FUNC(MoveModel);

	//绑定运动体
	void setRunObject(Node * node){
		this->runObject = node;
		point = node->getPosition();
	}
	Node * getRunObject(){
		return this->runObject;
	}

	//添加一组坐标，自动移动
	void addPointArray(vector<Vec2> * vect_tile);

	void setSpeed(float speed){ this->speed = speed; }
	float getSpeed(){ return this->speed; }
	void setPoint(Vec2 & vec2){ point.x = vec2.x; point.y = vec2.y; }
	Vec2 & getPoint(){ return point; }

private:
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	void update(float dt);
	void update2(float dt);
	void Analysis();

	void bindingRunObject();
private:
	Node * runObject;

	cocos2d::Point end;	//去的一个点
	cocos2d::Point begin;//起始点
	bool run;
	float angle;//当前的角度
	float speed;
	Vec2 point;//地图坐标
	deque<Vec2> deque_point;
};

#endif