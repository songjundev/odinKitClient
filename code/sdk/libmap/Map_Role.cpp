#include "Map_Role.h"
#include "MapDataManage.h"

Map_Role::Map_Role()
{
}


Map_Role::~Map_Role()
{
	this->map_Role.clear();
}

bool Map_Role::init()
{
	Layer::init();

	
	auto sprite = Sprite3D::create("../CocosEditor/Resources/model/knight/knight.c3b");
	sprite->setRotation3D(Vec3(0, 180, 0));
	addChild(sprite);
	sprite->setScale(20.f);
	sprite->setPosition(Vec2(100, 100));
	sprite->setGlobalZOrder(1);
	//
	auto animation = Animation3D::create("../CocosEditor/Resources/model/knight/knight.c3b");
	auto animate = Animate3D::create(animation, 0.f, animation->getDuration());
	sprite->runAction(RepeatForever::create(animate));
	int x = animate->getReferenceCount();


	return true;
}
void Map_Role::onEnter()
{
	Layer::onEnter();

}
void Map_Role::onExit()
{
	Layer::onExit();
}

void Map_Role::addChildToWorld(Node * child, int id, int index, int tile_x, int tile_y)
{

	map<int, map<int, Node *>>::iterator it = this->map_Role.find(id);
	if (it != map_Role.end())
	{
		map<int, Node *> * _map = &(map_Role[id]);
		map<int, Node*>::iterator _it = _map->find(index);
		if (_it != _map->end())
		{
			//存在这个角色
			return;
		}
	}

	this->addChild(child);
	int mapX = 0;
	int mapY = 0;
	MapDataManage::getObject()->getMapData()->tilePointToMapPoint(tile_x, tile_y, &mapX, &mapY);
	child->setPosition(mapX, mapY);

	map_Role[id][index] = child;
}

void Map_Role::removeChild(int id, int index)
{
	map<int, map<int, Node *>>::iterator it = this->map_Role.find(id);
	if (it != map_Role.end())
	{
		map<int, Node *> * _map = &(map_Role[id]);
		map<int, Node*>::iterator _it = _map->find(index);
		if (_it != _map->end())
		{
			//存在这个角色
			this->removeChild(_it->second);
			_map->erase(_it);
		}
	}
}

Node* Map_Role::getRole(int id, int index)
{
	map<int, map<int, Node *>>::iterator it = this->map_Role.find(id);
	if (it != map_Role.end())
	{
		map<int, Node *> * _map = &(map_Role[id]);
		map<int, Node*>::iterator _it = _map->find(index);
		if (_it != _map->end())
		{
			//存在这个角色
			return _it->second;
		}
	}

	return NULL;
}


void Map_Role::setRolePosition(int id, int index, int tile_x, int tile_y)
{
	Node * node =  getRole(id, index);
	if (!node)
		return;
	MapDataManage::getObject()->getMapData()->tilePointToMapPoint(tile_x, tile_y, &tile_x, &tile_y);
	node->setPosition(tile_x, tile_y);
}
void Map_Role::setRolePosition(Node * node, int tile_x, int tile_y)
{
	if (!node)
		return;
	MapDataManage::getObject()->getMapData()->tilePointToMapPoint(tile_x, tile_y, &tile_x, &tile_y);
	node->setPosition(tile_x, tile_y);
}