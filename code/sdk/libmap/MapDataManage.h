#ifndef MapDataManage_h_
#define MapDataManage_h_

#include <map>
#include <iostream>
#include "Map_Data.h"

class MapDataManage
{
private:
	MapDataManage();
	~MapDataManage();

public:
	static MapDataManage * getObject()
	{
		static MapDataManage manage;
		return &manage;
	}

	int LoadMapData(int mapID, char * allpath);

	Map_Data * getMapData(int mapID);
	Map_Data * getMapData(){
		return getMapData(this->currentMapID);
	}
	inline void setCurrentMapID(int curMapID) { this->currentMapID = curMapID; }
	inline int getCurrentMapID() { return this->currentMapID; }

	int getMapNum(){ return data.size(); }
	Map_Data * getMapData_Index(int index);
	int deleteMapData_Index(int index);

	int deleteMapData(int mapID);
	void deleteAllMapData();

	//editor functions
	int NewMapData(int mapID, int width,int height, int tileWidth, int tileHeight);

private:
	int currentMapID;
	std::map<int, Map_Data> data;

};

#endif
