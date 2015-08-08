#ifndef Map_Director_h
#define Map_Director_h_

#include "Map_Define.h"
#include "cocos2d.h"
using namespace cocos2d;

class Map_Layer;
class Map_Editor;
class Map_Role;
class Map_Director : public Layer
{
public:
	static Map_Director * createMap(char * imageDir, bool isEditMode = false);

	//////////////
	bool MoveMap(Direction direction, float dt);
	//地图相对于屏幕左下角的坐标
	void LocationMap(Vec2 & point);
	void setSpeed(float speed);
	float getSpeed() { return this->speed; }
	//

	//
	Map_Layer * getMapLayer(){ return this->mapLayer; }
	Map_Editor * getMapEditor(){ return this->mapEditor; }
	Map_Role * getMapRole(){ return this->mapRole; }
private:
	Map_Director();
	~Map_Director();
	CREATE_FUNC(Map_Director);
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	///////////////////////////////

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
	//
	bool canMove(Direction direction, float dt);
private:
	//obj
	Map_Layer * mapLayer;
	Map_Editor * mapEditor;
	Map_Role * mapRole;
	//
	float speed;
};

#endif