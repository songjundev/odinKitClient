#include "MapControl.h"
#include "Map_Layer.h"
#include "MapDataManage.h"
#include "Map_Editor.h"
#include "Map_Role.h"
#include "Map_Director.h"

MapControl::MapControl()
{

	editStopData = -1;
	eventAreaType = 0;

	caoz = enum_caozuo_dragMap;

	LocalMessageManage::getObject()->registerMessage(this, enum_MessageType_DragMode);
	LocalMessageManage::getObject()->registerMessage(this, enum_MessageType_EditStopData);
	LocalMessageManage::getObject()->registerMessage(this, enum_MessageType_EditEventArea);
	LocalMessageManage::getObject()->registerMessage(this, enum_MessageType_DeleteEventArea);
	LocalMessageManage::getObject()->registerMessage(this, enum_MessageType_SelectedEventArea);
}


MapControl::~MapControl()
{
	LocalMessageManage::getObject()->deleteMessage(this, enum_MessageType_DragMode);
	LocalMessageManage::getObject()->deleteMessage(this, enum_MessageType_EditStopData);
	LocalMessageManage::getObject()->deleteMessage(this, enum_MessageType_EditEventArea);
	LocalMessageManage::getObject()->deleteMessage(this, enum_MessageType_DeleteEventArea);
	LocalMessageManage::getObject()->deleteMessage(this, enum_MessageType_SelectedEventArea);
}

bool MapControl::init()
{
	Layer::init();

	this->scheduleUpdate();
	return true;
}

void MapControl::onEnter()
{
	Layer::onEnter();

	//加载地图

	//MapDataManage::getObject()->setCurrentMapID();
	this->mapDirector = Map_Director::createMap("../CocosEditor/Resources/map", true);
	this->addChild(mapDirector);
	mapDirector->setSpeed(200);
	mapDirector->getMapLayer()->registerTouchBegan(this, MAP_TOUCH_BEGIN(MapControl::touchBegan));
	mapDirector->getMapLayer()->registerTouchMove(this, MAP_TOUCH_MOVE(MapControl::touchMove));
	mapDirector->getMapLayer()->registerTouchEnd(this, MAP_TOUCH_END(MapControl::touchEnd));


	//添加运动的精灵
	/*Sprite * sprite = Sprite::create("../CocosEditor/Resources/CloseNormal.png");
	mapDirector->getMapRole()->addChildToWorld(sprite, 110, 0, 0, 0);*/
}

void MapControl::onExit()
{
	Layer::onExit();
}


void MapControl::touchBegan(int tile_x, int tile_y)
{
	beginTilePoint.x = tile_x;
	beginTilePoint.y = tile_y;

	if (caoz == enum_caozuo_selectedEventArea)
	{
		char buf[120] = { 0 };
		int type = 0;
		if (MapDataManage::getObject()->getMapData()->getEventArea(tile_x, tile_y, &type))
		{
			sprintf(buf,"事件类型：%d",type);
			MessageData data;
			data.push<char *>(buf);
			LocalMessageManage::getObject()->sendMessage(enum_MessageType_ShowQMessageBox, &data);
		}
	}
	if (editStopData < 0)
		return;
}
void MapControl::touchMove(int tile_x, int tile_y)
{
	if (caoz == enum_caozuo_editStopData)
		mapDirector->getMapEditor()->editStopData(tile_x, tile_y, editStopData);
	if (caoz == enum_caozuo_editEventArea)
		mapDirector->getMapEditor()->drawEventAreaTemp(beginTilePoint, Vec2(tile_x, tile_y));
}
void MapControl::touchEnd(int tile_x, int tile_y)
{
	if (caoz == enum_caozuo_editStopData)
		mapDirector->getMapEditor()->editStopData(tile_x, tile_y, editStopData);
	if (caoz == enum_caozuo_editEventArea)
		mapDirector->getMapEditor()->drawEventAreaOK(beginTilePoint, Vec2(tile_x, tile_y), eventAreaType);
	if (caoz == enum_caozuo_deleteEventArea)
		mapDirector->getMapEditor()->deleteEventArea(eventAreaType, Vec2(tile_x, tile_y));
}



void MapControl::update(float dt)
{

}


void MapControl::ReceiveMessage(int messageType, MessageData * data)
{
	switch (messageType)
	{
	case enum_MessageType_DragMode:
		handleDrag(data);
		break;
	case enum_MessageType_EditStopData:
		handleStopEdit(data);
		break;
	case enum_MessageType_EditEventArea:
		handleEventArea(data);
		break;
	case enum_MessageType_DeleteEventArea:
		handleDeleteEventArea(data);
		break;
	case enum_MessageType_SelectedEventArea:
		handleSelectedEventArea(data);
		break;
	default:
		break;
	}

}


void MapControl::handleDrag(MessageData * data)
{
	mapDirector->getMapEditor()->setCanDragMap(true);
	this->editStopData = -1;
	caoz = enum_caozuo_dragMap;
}
void MapControl::handleStopEdit(MessageData * data)
{
	mapDirector->getMapEditor()->setCanDragMap(false);
	this->editStopData = data->pop<int>();
	caoz = enum_caozuo_editStopData;
}
void MapControl::handleEventArea(MessageData * data)
{
	mapDirector->getMapEditor()->setCanDragMap(false);
	eventAreaType = data->pop<int>();
	caoz = enum_caozuo_editEventArea;
}
void MapControl::handleDeleteEventArea(MessageData * data)
{
	mapDirector->getMapEditor()->setCanDragMap(false);
	eventAreaType = data->pop<int>();
	caoz = enum_caozuo_deleteEventArea;
}
void MapControl::handleSelectedEventArea(MessageData * data)
{
	caoz = enum_caozuo_selectedEventArea;
}