#include "Map_Layer.h"
#include "MapDataManage.h"
#include "Map_Editor.h"
#include "Map_Role.h"

Map_Layer::Map_Layer()
{
	touchBeganObj = NULL;
	touchMoveObj = NULL;
	touchEndObj = NULL;

	touchBeganFunc = NULL;
	touchMoveFunc = NULL;
	touchEndFunc = NULL;
	//
	beyondSize.width = 0; beyondSize.height = 0;
	speed = 0;
	memset(imageDir, 0, sizeof(imageDir));
}


Map_Layer::~Map_Layer()
{
	Director::getInstance()->purgeCachedData();
}

bool Map_Layer::init()
{
	Layer::init();
	
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Map_Layer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Map_Layer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Map_Layer::onTouchEnded, this);
	listener->setSwallowTouches(true);//不向下传递触摸
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void Map_Layer::onEnter()
{
	Layer::onEnter();
}

void Map_Layer::onExit()
{
	Layer::onExit();
}

bool Map_Layer::initMapData()
{
	//计算block的大小
	char buf[20] = { "/0_0.jpg" };
	string dir = imageDir;
	string path = dir + buf;
	Texture2D * texture = Director::getInstance()->getTextureCache()->addImage(path);
	if (!texture)
		return false;

	Sprite * sprite = Sprite::createWithTexture(texture);
	MapDataManage::getObject()->getMapData()->setBlockWidth(sprite->getContentSize().width);
	MapDataManage::getObject()->getMapData()->setBlockHeight(sprite->getContentSize().height);

	//地图的左上角和屏幕的左上角保持一致
	Size winSize = Director::getInstance()->getWinSize();
	this->setContentSize(Size(MapDataManage::getObject()->getMapData()->getWidth(), MapDataManage::getObject()->getMapData()->getHeight()));

	return true;
}
Map_Layer * Map_Layer::createMapLayer(char * imageDir)
{
	Map_Layer * map = Map_Layer::create();
	strcpy(map->imageDir, imageDir);
	map->initMapData();

	return map;
}

void Map_Layer::registerTouchBegan(Ref * obj, TouchBegan_Function func)
{
	this->touchBeganObj = obj;
	this->touchBeganFunc = func;
}
void Map_Layer::registerTouchMove(Ref * obj, TouchMove_Function func)
{
	this->touchMoveObj = obj;
	this->touchMoveFunc = func;
}
void Map_Layer::registerTouchEnd(Ref * obj, TouchEnd_Function func)
{
	this->touchEndObj = obj;
	this->touchEndFunc = func;
}

bool Map_Layer::onTouchBegan(Touch *touch, Event *unused_event)
{
	int x = touch->getLocation().x;
	int y = touch->getLocation().y;

	int tileX = 0;
	int tileY = 0;

	Vec2 vec;
	vec = this->convertToNodeSpace(Vec2(x , y));

	MapDataManage::getObject()->getMapData()->mapPointToTilePoint(vec.x, vec.y, &tileX, &tileY);

	if (touchBeganObj && touchBeganFunc)
		(touchBeganObj->*touchBeganFunc)(tileX, tileY);

	//////////////////////////////////////

	return true;
}

void Map_Layer::onTouchMoved(Touch *touch, Event *unused_event)
{
	int x = touch->getLocation().x;
	int y = touch->getLocation().y;

	int tileX = 0;
	int tileY = 0;

	Vec2 vec;
	vec = this->convertToNodeSpace(Vec2(x, y));

	MapDataManage::getObject()->getMapData()->mapPointToTilePoint(vec.x, vec.y, &tileX, &tileY);

	if (touchMoveObj && touchMoveFunc)
		(touchMoveObj->*touchMoveFunc)(tileX, tileY);

	///////////////////////////
}

void Map_Layer::onTouchEnded(Touch *touch, Event *unused_event)
{
	int x = touch->getLocation().x;
	int y = touch->getLocation().y;

	int tileX = 0;
	int tileY = 0;

	Vec2 vec;
	vec = this->convertToNodeSpace(Vec2(x, y));

	MapDataManage::getObject()->getMapData()->mapPointToTilePoint(vec.x, vec.y, &tileX, &tileY);

	if (touchEndObj && touchEndFunc)
		(touchEndObj->*touchEndFunc)(tileX, tileY);

	/////////////////////////////
}

void Map_Layer::updateBlock(Vec2 & point, float dt)
{
	Size winSize = Director::getInstance()->getWinSize();
	int width = MapDataManage::getObject()->getMapData()->getWidth();
	int height = MapDataManage::getObject()->getMapData()->getHeight();
	int blockWidth = MapDataManage::getObject()->getMapData()->getBlockWidth();
	int blockHeight = MapDataManage::getObject()->getMapData()->getBlockHeight();

	this->beyondSize.width = blockWidth;
	this->beyondSize.height = blockHeight;

	while (dt * this->speed > beyondSize.width)
	{
		this->beyondSize.width += blockWidth;
		this->beyondSize.height += blockHeight;
	}

	Vec2 minPoint = Vec2(point.x - this->beyondSize.width, point.y - this->beyondSize.height);
	
	if (minPoint.x < 0)
		minPoint.x = 0;
	if (minPoint.y < 0)
		minPoint.y = 0;

	int minx = minPoint.x / blockWidth;
	int miny = minPoint.y / blockHeight;

	Vec2 maxPoint = Vec2(point.x + winSize.width + beyondSize.width, point.y + winSize.height + beyondSize.height);

	if (maxPoint.x > width)
		maxPoint.x = width;
	if (maxPoint.y > height)
		maxPoint.y = height;

	int maxx = maxPoint.x / blockWidth;
	int maxy = maxPoint.y / blockHeight;

	/* ---------需要移除的精灵-----------*/
	for (map<int, map<int, Sprite *>>::iterator it1 = map_blockSprite.begin(); it1 != map_blockSprite.end(); it1++)
	{
		map<int, Sprite *> * _map = &(it1->second);

		for (map<int, Sprite *>::iterator it2 = (*_map).begin(); it2 != (*_map).end(); )
		{
			if (it1->first < minx || it1->first > maxx || it2->first < miny || it2->first > maxy)
			{
				if (!it2->second)
				{
					it2++;
					continue;
				}
				this->deque_removeBlockSprite.push_back(it2->second);
				(*_map).erase(it2++);

				continue;
			}
			it2++;
		}
	}

	/*---------------构建图块-------------*/
	for (int j = miny; j <= maxy; j++)
	for (int i = minx; i <= maxx; i++)
	{
		//创建图块，重复利用
		Sprite * sprite = this->map_blockSprite[i][j];
		if (!sprite)
		{
			if (!deque_removeBlockSprite.empty())
			{
				sprite = deque_removeBlockSprite.front();
				deque_removeBlockSprite.pop_front();
				if (!updateBlockSpriteFrame(i, j, sprite))
					continue;
			}
			else
			{
				sprite = Sprite::create();
				sprite->setAnchorPoint(Vec2(0,0));
				if (!updateBlockSpriteFrame(i, j, sprite))
					continue;
				this->addChild(sprite);
			}
			this->map_blockSprite[i][j] = sprite;
			sprite->setPosition(i * blockWidth, j * blockHeight);
		}
	}
}

bool Map_Layer::updateBlockSpriteFrame(int x, int y, Sprite * sprite)
{
	char buf[20] = { 0 };
	sprintf(buf, "/%d_%d.jpg",x,y);

	string dir = imageDir;
	string path = dir + buf;

	Texture2D * texture = Director::getInstance()->getTextureCache()->addImage(path);
	if (!texture)
		return false;
	SpriteFrame * frame = SpriteFrame::createWithTexture(texture, Rect(0,0,texture->getContentSize().width, texture->getContentSize().height));
	sprite->setSpriteFrame(frame);
	return true;
}