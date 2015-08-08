#include "MapDataManage.h"

using namespace std;

MapDataManage::MapDataManage()
{
	currentMapID = -1;
}

MapDataManage::~MapDataManage()
{
	this->deleteAllMapData();
}

int MapDataManage::LoadMapData(int mapID, char * allpath)
{
	map<int, Map_Data >::iterator it = data.find(mapID);
	if (it != data.end())
		return -1;

	//不存在新建对象
	Map_Data * mapData = &data[mapID];
	int re = mapData->LoadMapData(mapID, allpath);
	if (re < 0)
	{
		data.erase(it);
		return re;
	}

	return 0;
}

int MapDataManage::deleteMapData(int mapID)
{
	map<int, Map_Data>::iterator it = data.find(mapID);
	if (it == data.end())
		return -1;

	if (currentMapID == it->second.getMapID())
		currentMapID = -1;

	data.erase(it);
	return 0;
}

void MapDataManage::deleteAllMapData()
{
	currentMapID = -1;
	data.clear();
}

Map_Data * MapDataManage::getMapData(int mapID)
{
	if (mapID < 0)
		return NULL;
	map<int, Map_Data>::iterator it = data.find(mapID);
	if (it == data.end())
		return NULL;
	else
		return &(it->second);
}

int MapDataManage::NewMapData(int mapID, int width, int height, int tileWidth, int tileHeight)
{
	this->currentMapID = mapID;

	map<int, Map_Data>::iterator it = data.find(mapID);
	if (it != data.end())
	{
		it->second.initData();
		it->second.newMapData(mapID, width, height, tileWidth, tileHeight);
		return -1;
	}
	Map_Data d;
	data.insert(map<int, Map_Data>::value_type(mapID,d));
	(&(data[mapID]))->newMapData(mapID, width, height, tileWidth, tileHeight);

	return 0;
}

Map_Data * MapDataManage::getMapData_Index(int index)
{
	int i = 0;
	for (map<int, Map_Data>::iterator it = data.begin(); it != data.end(); it++, i++)
	{
		if (index == i)
			return (&it->second);
	}

	return NULL;
}

int MapDataManage::deleteMapData_Index(int index)
{
	int i = 0;
	for (map<int, Map_Data>::iterator it = data.begin(); it != data.end(); it++, i++)
	{
		if (index == i)
		{
			data.erase(it);
			return 0;
		}
	}

	return -1;
}