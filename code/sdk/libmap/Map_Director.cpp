#include "Map_Director.h"
#include "Map_Layer.h"
#include "Map_Editor.h"
#include "Map_Role.h"
#include "MapDataManage.h"

Map_Director::Map_Director()
{
	this->mapLayer = NULL;
	this->mapEditor = NULL;
	this->mapRole = NULL;
}


Map_Director::~Map_Director()
{
}


bool Map_Director::init()
{
	Layer::init();
	return true;
}
void Map_Director::onEnter()
{
	Layer::onEnter();
}
void Map_Director::onExit()
{
	Layer::onExit();
}

Map_Director * Map_Director::createMap(char * imageDir, bool isEditMode)
{
	Map_Director * mapDirector = Map_Director::create();
	mapDirector->setGlobalZOrder(enum_map_director);

	Size winSize = Director::getInstance()->getWinSize();
	mapDirector->mapLayer = Map_Layer::createMapLayer(imageDir);
	mapDirector->addChild(mapDirector->mapLayer);
	Vec2 point(0, winSize.height - mapDirector->mapLayer->getContentSize().height);
	mapDirector->LocationMap(point);
	mapDirector->mapLayer->setGlobalZOrder(enum_map_layer);
	//±à¼­²ã
	if (isEditMode)
	{
		mapDirector->mapEditor = Map_Editor::create();
		mapDirector->addChild(mapDirector->mapEditor, enum_map_editor);
		mapDirector->mapEditor->setContentSize(Size(MapDataManage::getObject()->getMapData()->getWidth(), MapDataManage::getObject()->getMapData()->getHeight()));
		mapDirector->mapEditor->setGlobalZOrder(enum_map_editor);
	}
	//½ÇÉ«²ã
	mapDirector->mapRole = Map_Role::create();
	mapDirector->addChild(mapDirector->mapRole);
	mapDirector->mapRole->setContentSize(Size(MapDataManage::getObject()->getMapData()->getWidth(), MapDataManage::getObject()->getMapData()->getHeight()));
	mapDirector->mapRole->setGlobalZOrder(enum_map_role);
	return mapDirector;
}

bool Map_Director::canMove(Direction direction, float dt)
{
	Size winSize = Director::getInstance()->getWinSize();
	int width = MapDataManage::getObject()->getMapData()->getWidth();
	int height = MapDataManage::getObject()->getMapData()->getHeight();
	float juli = dt * this->speed;

	if (direction == enum_up)
	{
		if (abs(this->getPositionY()) + juli > abs(height - winSize.height))
		{
			this->setPositionY(-abs(height - winSize.height));
			return false;
		}
		else
		{
			this->setPositionY(this->getPositionY() + juli);
		}

	}
	else
	if (direction == enum_down)
	{
		if (this->getPositionY() - dt * speed <= winSize.height - height)
		{
			this->setPositionY(winSize.height - height);
			return false;
		}
		else
		{
			this->setPositionY(this->getPositionY() - juli);
		}
	}
	else
	if (direction == enum_left)
	{
		if (this->getPositionX() - dt * speed <= winSize.width - width)
		{
			this->setPositionX(winSize.width - width);
			return false;
		}
		else
		{
			this->setPositionX(this->getPositionX() - juli);
		}
	}
	else
	if (direction == enum_right)
	{
		if (abs(this->getPositionX()) + juli > abs(width - winSize.width))
		{
			this->setPositionX(-abs(width - winSize.width));
			return false;
		}
		else
		{
			this->setPositionX(this->getPositionX() + juli);
		}
	}

	return true;

}
void Map_Director::LocationMap(Vec2 & point)
{
	Size winSize = Director::getInstance()->getWinSize();
	int width = MapDataManage::getObject()->getMapData()->getWidth();
	int height = MapDataManage::getObject()->getMapData()->getHeight();

	if (point.x > 0)
		point.x = 0;
	if (point.y > 0)
		point.y = 0;
	if (point.x < winSize.width - width)
		point.x = winSize.width - width;
	if (point.y < winSize.height - height)
		point.y = winSize.height - height;

	this->setPosition(point);

	point.x = abs(point.x);
	point.y = abs(point.y);

	this->mapLayer->updateBlock(point, 0);
}


bool Map_Director::MoveMap(Direction direction, float dt)
{
	bool ok = canMove(direction, dt);
	Vec2 vec(abs(this->getPositionX()), abs(this->getPositionY()));
	this->mapLayer->updateBlock(vec, dt);
	return ok;
}

void Map_Director::setSpeed(float speed)
{
	this->speed = speed;
	mapLayer->setSpeed(speed);
}