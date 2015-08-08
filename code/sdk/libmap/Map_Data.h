#ifndef Map_Data_h_
#define Map_Data_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <vector>
#include <list>
#include <iostream>
using namespace std;


/*该类前端和后端通用，，所以未使用cocos中的相关类*/


enum TileValue
{
	changtongwuzu = 0,	//畅通无阻
	youzhedang,			//有遮挡，角色走在了大树下面
	bunengxingzou		//不能行走
};

class EventArea
{
public:
	EventArea()
	{
		beginTileX = 0;
		beginTileY = 0;
		endTileX = 0;
		endTileY = 0;
	}
	int beginTileX;
	int beginTileY;
	int endTileX;
	int endTileY;
};
class Map_Data
{
public:
	Map_Data();
	~Map_Data();

public:
	/*cocos2dx客户端或者服务器端可以调用的函数*/

	int getMapID(){ return this->mapID; }
	void initData();
	int LoadMapData(int mapID, char * allpath);//Success return 0,else return < 0
	int getTileValue(int x, int y);
	int getXTileNum();//x方向上的格子数量
	int getYTileNum();//y方向上的格子数量

	//坐标转换,节点坐标和地图坐标互相转换
	bool mapPointToTilePoint(int in_x, int in_y, int * out_x, int * out_y);
	bool tilePointToMapPoint(int in_x, int in_y, int * out_x, int * out_y);

	void setBlockWidth(int blockWidth){ this->blockWidth = blockWidth; }
	void setBlockHeight(int blockHeight){ this->blockHeight = blockHeight; }
	int getWidth(){ return this->width; }
	int getHeight(){ return this->height; }
	int getTileWidth(){ return this->tileWidth; }
	int getTileHeight(){ return this->tileHeight; }
	int getBlockWidth(){ return this->blockWidth; }
	int getBlockHeight(){ return this->blockHeight; }

	//操作事件区域
	const map<int, vector<EventArea>> & getEventAreaData() const{ return this->map_EventArea; }
	void addEventArea(int type,int beginTileX,int beginTileY,int endTileX, int endTileY);
	void deleteEventArea(int type, int tileX,int tileY);
	void deleteAllEventArea(){ this->map_EventArea.clear(); }
	const EventArea * getEventArea(int tileX, int tileY, int * out_eventType);

	/////////////new event area



public:
	/*仅仅允许地图编辑器调用的函数*/
	int WriteMapData(char * allpath);
	void newMapData(int mapID,int width, int heigth, int tileWidth, int tileHeight);
	void setTileValue(int x, int y, int value);//不存在则不赋值
private:

	void Password(char * buf, int buflen);//加解密,key在静态库中定义
	void setTileValue_Forced(int x, int y, int value);//强制，不存在新建
private:
	int mapID;
	map<int, map<int, int>> map_TileData;	//地图阻挡数据
	map<int, vector<EventArea>> map_EventArea;		//地图事件区域
	map<int, list<vector<EventArea>>> eventAreaData;
	//TODO...								//地图路点数据
	int width;
	int height;
	int tileWidth;
	int tileHeight;
	int blockWidth;
	int blockHeight;
};

#endif