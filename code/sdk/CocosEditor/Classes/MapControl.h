#ifndef MapControl_h_
#define MapControl_h_

#include "cocos2d.h"
using namespace cocos2d;

#include "message.h"


enum caozuo
{
	enum_caozuo_dragMap = 0,		//拖动地图
	enum_caozuo_editStopData,	//编辑阻挡数据
	enum_caozuo_editEventArea,	//编辑事件区域
	enum_caozuo_deleteEventArea,	//删除事件区
	enum_caozuo_selectedEventArea,	//查询事件区
};

class Map_Director;
class Map_Layer;
class MapControl : public Layer, public LocalMessage
{
public:
	MapControl();
	~MapControl();

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	CREATE_FUNC(MapControl);

	//重写消息接收函数
	virtual void ReceiveMessage(int messageType, MessageData * data);

	void touchBegan(int tile_x, int tile_y);
	void touchMove(int tile_x, int tile_y);
	void touchEnd(int tile_x, int tile_y);

	void handleDrag(MessageData * data);
	void handleStopEdit(MessageData * data);
	void handleEventArea(MessageData * data);
	void handleDeleteEventArea(MessageData * data);
	void handleSelectedEventArea(MessageData * data);
private:
	void update(float dt);
private:
	Vec2 beginTilePoint;
	int editStopData;	//编辑阻挡数据,-1不编辑
	int eventAreaType;  //事件区域类型
	caozuo caoz;
	Map_Director * mapDirector;
};

#endif