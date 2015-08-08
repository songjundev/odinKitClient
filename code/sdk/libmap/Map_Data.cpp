#include "Map_Data.h"

#define KEY "nihaowohaodajiahao"

Map_Data::Map_Data()
{
	//只初始化一次
	mapID = -1;
	//允许多次初始化
	this->initData();
}

Map_Data::~Map_Data()
{
	this->map_TileData.clear();
}

void Map_Data::initData()
{
	width = 0;
	height = 0;
	tileWidth = 0;
	tileHeight = 0;
	blockWidth = 0;
	blockHeight = 0;

	this->map_TileData.clear();
}

void Map_Data::Password(char * buf, int buflen)
{
	char * p = buf;
	char * pKey = KEY;

	unsigned int bufLen = buflen;
	unsigned int keyLen = strlen(pKey);

	for (unsigned int i = 0; i < bufLen; i++)
	{
		*p ^= pKey[i % keyLen];
		p++;
	}
}
int Map_Data::getXTileNum()
{
	int x = width / tileWidth;
	return x + 1;
}
int Map_Data::getYTileNum()
{
	int x = height / tileHeight;
	//注意y坐标是交错的
	return x * 2 + 1;
}

int Map_Data::WriteMapData(char * path)
{
	if (!path)
		return -1;

	char * buf = (char *)malloc(1024 * 5);
	memset(buf, 0, 1024 * 5);

	sprintf(buf, "width:%d",this->width);
	sprintf(buf + strlen(buf), "height:%d", this->height);
	sprintf(buf + strlen(buf), "tileWidth:%d", this->tileWidth);
	sprintf(buf + strlen(buf), "tileHeight:%d", this->tileHeight);
	sprintf(buf + strlen(buf), "blockWidth:%d", this->blockWidth);
	sprintf(buf + strlen(buf), "blockHeight:%d", this->blockHeight);


	for (int j = 0; j < this->getYTileNum(); j++)
	{
		strcpy(buf + strlen(buf), "[");

		for (int i = 0; i < this->getXTileNum(); i++)
		{
			//在这就不用判断存不存在了
			//map<int, map<int, int>>::iterator it = this->map_TileData.find(i);
			
			sprintf(buf + strlen(buf), "%d", this->map_TileData[i][j]);

			if (i < this->getXTileNum() - 1)
				strcpy(buf + strlen(buf), ",");
		}

		strcpy(buf + strlen(buf), "]");
	}

	//写入数据
	FILE *fp = NULL;
	char ch = NULL;
	if ((fp = fopen(path, "wb")) == NULL) {
		return -1;
	}

	char * p = buf;
	char * pKey = KEY;
	int keyLen = strlen(pKey);
	int index = 0;
	//写入数据并加密
	while (*p)
	{
		*p ^= pKey[index % keyLen];
		fputc(*p, fp);
		p++;
		index++;
	}

	free(buf);
	fclose(fp);
}

int Map_Data::LoadMapData(int mapID, char * path)
{
	FILE *fp = NULL;
	char ch;
	if ((fp = fopen(path, "rb")) == NULL) {
		return -1;
	}

	this->initData();

	char * buf = (char *)malloc(sizeof(char) * 1024 * 5);
	memset(buf, 0, sizeof(char)* 1024 * 5);
	char * p = buf;
	int index = 0;
	int keyLen = strlen(KEY);
	char * pKey = KEY;

	//读取数据并解密
	while ((ch = fgetc(fp)) != EOF)
	{
		*p = ch;
		*p ^= pKey[index % keyLen];
		p++;
		index ++;
	}
	fclose(fp);

	//初始化本类数据
	char * key[6] = {
		"width:",
		"height:",
		"tileWidth:",
		"tileHeight:",
		"blockWidth:",
		"blockHeight:",
	};
	int * num[6] = {
		&(this->width),
		&(this->height),
		&(this->tileWidth),
		&(this->tileHeight),
		&(this->blockWidth),
		&(this->blockHeight)
	};

	p = buf;
	bool _continue = false;
	int x = 0;
	int y = 0;

	while (*p)
	{
		for (int i = 0; i < 6; i++)
		{
			if (!strncmp(p, key[i], strlen(key[i])))
			{
				p += strlen(key[i]);
				*(num[i]) = atoi(p);

				_continue = true;
				break;
			}
		}

		if (_continue)
		{
			_continue = false;
			continue;
		}

		if (*p == '[')
		{
			x = 0;
			this->setTileValue_Forced(x, y, atoi(p + 1));
			x++;
		}else
		if (*p == ']')
		{
			y++;
		}
		else
		if (*p == ',')
		{
			this->setTileValue_Forced(x, y, atoi(p + 1));
			x++;
		}

		p++;
	}

	this->mapID = mapID;
	free(buf);

}

void Map_Data::newMapData(int mapID,int width, int height, int tileWidth , int tileHeight)
{
	this->initData();

	this->width = width;
	this->height = height;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;

	//init map
	//前面半个格子
	int w = this->getXTileNum();
	int h = this->getYTileNum();

	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			this->setTileValue_Forced(i, j, 0);
		}
	}
}

int Map_Data::getTileValue(int x, int y)
{
	if (x < 0 || y < 0)
		return -1;

	map<int, map<int, int>>::iterator it = this->map_TileData.find(x);
	if (it == this->map_TileData.end())
		return -2;

	map<int, int> * _map = &(this->map_TileData[x]);
	map<int, int>::iterator it2 = (*_map).find(y);
	if (it2 == (*_map).end())
		return -3;
	else
		return it2->second;
}

void Map_Data::setTileValue(int x, int y, int value)
{
	map < int, map<int, int>>::iterator it = this->map_TileData.find(x);
	if (it == this->map_TileData.end())
		return;
	
	map<int, int> * _map = &(this->map_TileData[x]);
	map<int, int>::iterator itP = (*_map).find(y);

	if (itP == (*_map).end())
		return;

	(*_map)[y] = value;
}

//强制
void Map_Data::setTileValue_Forced(int x, int y, int value)
{
	map<int, map<int, int>>::iterator it = this->map_TileData.find(x);
	if (it == this->map_TileData.end())
	{
		map<int, int> _map;
		_map.insert(map<int, int>::value_type(y, value));
		this->map_TileData.insert(map<int, map<int, int>>::value_type(x, _map));
		return;
	}
	map<int, int> * _map = &(this->map_TileData[x]);

	(*_map)[y] = value;//不存在key时，会新建
}

/*
int Map_Data::getLineWidth()
{
	int zs = this->width / this->tileWidth;
	int yu = this->width % this->tileWidth;
	if (yu == 0)
		return this->width;
	else
		return (zs + 1) * this->tileWidth;
}
int Map_Data::getLineHeight()
{
	//height
	int zs = this->height / this->tileHeight;
	int yu = this->height % this->tileHeight;
	if (yu == 0)
		return this->height;
	else
		return (zs + 1) * this->tileHeight;
}
*/
bool Map_Data::mapPointToTilePoint(int in_x, int in_y, int * out_x, int * out_y)
{
	if (in_x < 0 || in_y < 0 || !out_x || !out_y)
		return false;

	//像素坐标转换成左上角的像素坐标，还要注意加上半个格子
	int px = in_x + this->tileWidth / 2;
	int py = getHeight() - in_y + this->tileHeight / 2;

	//int px = point.x();
	//int py = point.y();
	/*
	int x = (int)(0.5f * (py / (TileSizeHeight >> 1) + px / (TileSizeWidth >> 1)));
	int y = (int)(0.5f * (py / (TileSizeHeight >> 1) - px / (TileSizeWidth >> 1)));
	return QPoint(x, y);
	*/
	int xtile = 0;        //网格的x坐标
	int ytile = 0;        //网格的y坐标

	int cx, cy, rx, ry;
	cx = int(px / tileWidth) * tileWidth + tileWidth / 2;        //计算出当前X所在的以tileWidth为宽的矩形的中心的X坐标
	cy = int(py / tileHeight) * tileHeight + tileHeight / 2;     //计算出当前Y所在的以tileHeight为高的矩形的中心的Y坐标

	rx = (px - cx) * tileHeight / 2;
	ry = (py - cy) * tileWidth / 2;

	if (abs(rx) + abs(ry) <= tileWidth * tileHeight / 4)
	{
		//xtile = int(pixelPoint.x / tileWidth) * 2;
		xtile = int(px / tileWidth);
		ytile = int(py / tileHeight) * 2;
	}
	else
	{
		px = px - tileWidth / 2;
		//xtile = int(pixelPoint.x / tileWidth) * 2 + 1;
		xtile = int(px / tileWidth) + 1;

		py = py - tileHeight / 2;
		ytile = int(py / tileHeight) * 2 + 1;
	}

	//return QPoint(xtile - (ytile & 1), ytile);
	*out_x = xtile - (ytile & 1);
	*out_y = ytile;

	return true;
}
bool Map_Data::tilePointToMapPoint(int in_x, int in_y, int * out_x, int * out_y)
{

	if (in_x < 0 || in_y < 0 || !out_x || !out_y)
		return false;

	int tx = in_x;
	int ty = in_y;
	/**
	* 偶数行tile中心
	* */
	int tileCenter = (tx * tileWidth) + tileWidth / 2;
	/**
	* x象素  如果为奇数行加半个宽
	* */
	int xPixel = tileCenter + (ty & 1) * tileWidth / 2;

	/**
	* y象素
	* */
	int yPixel = (ty + 1) * tileHeight / 2;

	//return QPoint(xPixel, yPixel);

	//减半个格子
	*out_x = xPixel - tileWidth / 2;
	*out_y = getHeight() - (yPixel - tileHeight / 2);

	return true;
}

void Map_Data::addEventArea(int type, int beginTileX, int beginTileY, int endTileX, int endTileY)
{
	if (type < 0 || beginTileX < 0 || beginTileX < 0 || endTileX < 0 || endTileY < 0)
		return;

	map<int, vector<EventArea>>::iterator it = map_EventArea.find(type);
	EventArea eventArea;
	eventArea.beginTileX = beginTileX;
	eventArea.beginTileY = beginTileY;
	eventArea.endTileX = endTileX;
	eventArea.endTileY = endTileY;
	map_EventArea[type].push_back(eventArea);
	//map_EventArea

}

void Map_Data::deleteEventArea(int type, int tileX, int tileY)
{
	map<int, vector<EventArea>>::iterator it = map_EventArea.find(type);
	if (it == map_EventArea.end())
		return;
	//
	vector<EventArea> * v = &(it->second);
	for (vector<EventArea>::iterator it = v->begin(); it < v->end(); it++)
	{
		if (tileX >= (*it).beginTileX && tileX <= (*it).endTileX && tileY >= (*it).beginTileY && tileY <= (*it).endTileY)
		{
			v->erase(it);
			break;
		}
	}
}

const EventArea * Map_Data::getEventArea(int tileX, int tileY, int * out_eventType)
{
	if (!out_eventType)
		return NULL;
	for (map<int, vector<EventArea>>::iterator it = map_EventArea.begin(); it != map_EventArea.end(); it++)
	{
		for (vector<EventArea>::const_iterator _it = it->second.begin(); _it != it->second.end(); _it++)
		{
			if (tileX >= (*_it).beginTileX && tileX <= (*_it).endTileX && tileY >= (*_it).beginTileY && tileY <= (*_it).endTileY)
			{
				*out_eventType = it->first;
				return &(*_it);
			}
		}
	}
	return NULL;
}