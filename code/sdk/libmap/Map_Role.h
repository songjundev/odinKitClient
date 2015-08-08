#ifndef Map_Role_h_
#define Map_Role_h_

#include <map>
#include <iostream>
#include"cocos2d.h"
using namespace cocos2d;
using namespace std;
/*
	��ͼ��ɫ��
*/

class Map_Role : public Layer
{
public:
	Map_Role();
	~Map_Role();

	CREATE_FUNC(Map_Role);
	////////////////
	void addChildToWorld(Node * child,int id, int index, int tile_x, int tile_y);
	void removeChild(int id, int index);
	Node* getRole(int id, int index);
	void setRolePosition(int id, int index, int tile_x, int tile_y);
	void setRolePosition(Node *, int tile_x, int tile_y);

	//ע����ײ��⺯�� TODO...
	//���²㼶 TODO...
private:
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	///////////˽�л������һЩ����/////////////
	virtual void addChild(Node * child){
		Layer::addChild(child);
	}
	virtual void addChild(Node * child, int localZOrder){
		Layer::addChild(child, localZOrder);
	}
	virtual void addChild(Node* child, int localZOrder, int tag){
		Layer::addChild(child, localZOrder, tag);
	}
	virtual void addChild(Node* child, int localZOrder, const std::string &name){
		Layer::addChild(child, localZOrder, name);
	}

	//����ֱ����������õ�ͼ������
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

	//��ֹɾ������
	virtual void removeChild(Node* child, bool cleanup = true){
		Layer::removeChild(child, cleanup);
	}
	virtual void removeChildByTag(int tag, bool cleanup = true){
		Layer::removeChildByTag(tag, cleanup);
	}
	virtual void removeChildByName(const std::string &name, bool cleanup = true){
		Layer::removeChildByName(name, cleanup);
	}
	virtual void removeAllChildren(){
		Layer::removeAllChildren();
	}
	virtual void removeAllChildrenWithCleanup(bool cleanup)
	{
		Layer::removeAllChildrenWithCleanup(cleanup);
	}

	//
private:

	//�����б�id�� index�� Node *
	map < int, map<int, Node *>> map_Role;
};

#endif