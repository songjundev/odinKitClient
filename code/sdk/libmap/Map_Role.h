#ifndef Map_Role_h_
#define Map_Role_h_

#include <map>
#include <iostream>
#include"cocos2d.h"
using namespace cocos2d;
using namespace std;
/*
	地图角色层
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

	//注册碰撞检测函数 TODO...
	//更新层级 TODO...
private:
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	///////////私有化父类的一些函数/////////////
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

	//禁止删除操作
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

	//参数列表：id、 index、 Node *
	map < int, map<int, Node *>> map_Role;
};

#endif