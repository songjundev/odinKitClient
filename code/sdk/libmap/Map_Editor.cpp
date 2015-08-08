#include "Map_Editor.h"
#include "MapDataManage.h"
#include "Map_Director.h"

Map_Editor::Map_Editor()
{
	draw = NULL;
	drawArea = NULL;
	canDragMap = true;
	tmpDraw = NULL;
}


Map_Editor::~Map_Editor()
{
	map_TileData.clear();
}

bool Map_Editor::init()
{
	Layer::init();

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Map_Editor::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Map_Editor::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Map_Editor::onTouchEnded, this);
	listener->setSwallowTouches(false);

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void Map_Editor::onEnter()
{
	Layer::onEnter();
	drawGridLine();
}

void Map_Editor::onExit()
{
	Layer::onExit();
}

void Map_Editor::editStopData(int tile_x, int tile_y, int data)
{
	int value = MapDataManage::getObject()->getMapData()->getTileValue(tile_x, tile_y);
	if (value < 0 || data < 0)
		return;

	int map_x = 0;
	int map_y = 0;
	MapDataManage::getObject()->getMapData()->tilePointToMapPoint(tile_x, tile_y, &map_x, &map_y);
	
	
	map<int, map<int, Sprite *>>::iterator it = map_TileData.find(tile_x);
	if (it != map_TileData.end())
	{
		map<int, Sprite *> * _map = &(map_TileData[tile_x]);
		map<int, Sprite *>::iterator _it = _map->find(tile_y);
		if (_it != _map->end())
		{
			if (_it->second)
			{
				if (!data)
				{
					_it->second->removeFromParent();
					_map->erase(_it);
				}
				else
				{
					return;
				}
			}
		}
	}

	MapDataManage::getObject()->getMapData()->setTileValue(tile_x, tile_y, data);

	if (!data)
		return;

	Sprite * sprite = NULL;
	if (data == 1)
		sprite = Sprite::create("../CocosEditor/Resources/editor/gantan.png");
	else
	if (data == 2)
		sprite = Sprite::create("../CocosEditor/Resources/editor/cuowu.png");

	this->addChild(sprite);
	sprite->setScale(0.2f);
	sprite->setPosition(map_x, map_y);

	map_TileData[tile_x][tile_y] = sprite;
}

void Map_Editor::drawGridLine()
{
	this->draw = DrawNode::create();
	addChild(draw);
	//draw point,参数依次为位置、Size、填充颜色
	//draw->drawLine(Vec2(0, 0), Vec2(s.width, s.height), Color4F(1.0, 0.0, 0.0, 0.5));

	Color4F color = Color4F(1.0, 0.0, 0.0, 1);

	int tileWidth = MapDataManage::getObject()->getMapData()->getTileWidth();
	int tileHeight = MapDataManage::getObject()->getMapData()->getTileHeight();

	int width = MapDataManage::getObject()->getMapData()->getWidth();
	int height = MapDataManage::getObject()->getMapData()->getHeight();

	Vec2 p1 = { (float)0, (float)(tileHeight / 2) };
	Vec2 p2 = { (float)(tileWidth / 2), 0 };


	//转换
	bool zhuanhuan1 = false;
	bool zhuanhuan2 = false;
	//向右画斜线
	while (1)
	{
		//draw->drawLine(p1, p2, color);
		draw->drawSegment(p1, p2, 1, color);
		p1.y = p1.y + tileHeight;

		if (p1.y >= height)
		{
			p1.y = height;
			if (!zhuanhuan1)
			{
				p1.x = tileWidth / 2;
				zhuanhuan1 = true;
			}
			else
			{
				if (p1.x < width)
					p1.x = p1.x + tileWidth;
				else
					p1.x = width;
			}
		}

		p2.x = p2.x + tileWidth;
		if (p2.x >= width)
		{
			p2.x = width;
			if (!zhuanhuan2)
			{
				p2.y = tileHeight / 2;
				zhuanhuan2 = true;
			}
			else
			{
				if (p2.y < height)
					p2.y = p2.y + tileHeight;
				else
					p2.y = height;
			}
		}

		if (p1 == p2)
			break;
	}

	p1 = { (float)0, (float)(height - tileHeight / 2) };
	p2 = { (float)(tileWidth / 2), (float)height };

	zhuanhuan1 = false;
	zhuanhuan2 = false;

	//向左画斜线
	while (1)
	{
		//draw->drawLine(p1, p2, color);
		draw->drawSegment(p1, p2, 1, color);

		p1.y = p1.y - tileHeight;
		if (p1.y <= 0)
		{
			p1.y = 0;
			if (!zhuanhuan1)
			{
				p1.x = tileWidth / 2;
				zhuanhuan1 = true;
			}
			else
			{
				if (p1.x < width)
					p1.x = p1.x + tileWidth;
				else
					p1.x = width;
			}
		}

		p2.x = p2.x + tileWidth;
		if (p2.x >= width)
		{
			p2.x = width;
			if (!zhuanhuan2)
			{
				p2.y = height - tileHeight / 2;
				zhuanhuan2 = true;
			}
			else
			{
				if (p2.y > 0)
					p2.y = p2.y - tileHeight;
				else
					p2.y = 0;
			}
		}

		if (p1 == p2)
			break;
	}
}

void Map_Editor::drawEventAreaTemp(const Vec2 & beginTilePoint, const Vec2 & endTilePoint)
{
	if (abs(beginTilePoint.x - endTilePoint.x) < 1 || abs(beginTilePoint.y - endTilePoint.y) < 1)
		return;
	if (!tmpDraw)
	{
		tmpDraw = DrawNode::create();
		this->addChild(tmpDraw);
		//tmpDraw->setOpacity(100);
	}

	this->drawEventArea(tmpDraw, beginTilePoint, endTilePoint);
}
void Map_Editor::deleteEventArea(int type, const Vec2 & tilePoint)
{
	MapDataManage::getObject()->getMapData()->deleteEventArea(type, tilePoint.x, tilePoint.y);
	this->updateEventArea();
}
void Map_Editor::updateEventArea()
{
	drawArea->clear();
	const map<int, vector<EventArea>> * _map = &(MapDataManage::getObject()->getMapData()->getEventAreaData());

	for (map<int, vector<EventArea>>::const_iterator it = _map->begin(); it != _map->end(); it++)
	{
		for (vector<EventArea>::const_iterator _it = it->second.begin(); _it != it->second.end(); _it++)
		{
			this->drawEventArea(drawArea, Vec2((*_it).beginTileX, (*_it).beginTileY), Vec2((*_it).endTileX, (*_it).endTileY));
		}
	}
}

void Map_Editor::drawEventAreaOK(const Vec2 & beginTilePoint, const Vec2 & endTilePoint, int type)
{
	if (abs(beginTilePoint.x - endTilePoint.x) < 1 || abs(beginTilePoint.y - endTilePoint.y) < 1)
		return;
	MapDataManage::getObject()->getMapData()->addEventArea(type, beginTilePoint.x, beginTilePoint.y, endTilePoint.x, endTilePoint.y);

	if (!drawArea)
	{
		drawArea = DrawNode::create();
		this->addChild(drawArea);
	}

	this->drawEventArea(drawArea, beginTilePoint, endTilePoint);
}


void Map_Editor::drawEventArea(DrawNode * draw, const Vec2 & beginTilePoint, const Vec2 & endTilePoint)
{
	int beginMapX;
	int beginMapY;
	int endMapX;
	int endMapY;

	Color4F color = Color4F(0.0, 1.0, 0.0, 0.5);

	MapDataManage::getObject()->getMapData()->tilePointToMapPoint(beginTilePoint.x, beginTilePoint.y, &beginMapX, &beginMapY);
	MapDataManage::getObject()->getMapData()->tilePointToMapPoint(endTilePoint.x, endTilePoint.y, &endMapX, &endMapY);

	Vec2 vec[4] = {
		Vec2(beginMapX, beginMapY),
		Vec2(endMapX, beginMapY),
		Vec2(endMapX, endMapY),
		Vec2(beginMapX, endMapY),
	};

	tmpDraw->clear();
	draw->drawPolygon(vec, 4, color, 1, color);
}

bool Map_Editor::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}
void Map_Editor::onTouchMoved(Touch *touch, Event *unused_event)
{
	if (!canDragMap)
		return;

	Map_Director * mapDirector = (Map_Director *)(this->getParent());
	Vec2 vec = mapDirector->getPosition() + touch->getDelta();
	mapDirector->LocationMap(vec);
}
void Map_Editor::onTouchEnded(Touch *touch, Event *unused_event)
{

}