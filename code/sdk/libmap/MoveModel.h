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

	//���˶���
	void setRunObject(Node * node){
		this->runObject = node;
		point = node->getPosition();
	}
	Node * getRunObject(){
		return this->runObject;
	}

	//���һ�����꣬�Զ��ƶ�
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

	cocos2d::Point end;	//ȥ��һ����
	cocos2d::Point begin;//��ʼ��
	bool run;
	float angle;//��ǰ�ĽǶ�
	float speed;
	Vec2 point;//��ͼ����
	deque<Vec2> deque_point;
};

#endif