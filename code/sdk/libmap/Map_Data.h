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


/*����ǰ�˺ͺ��ͨ�ã�������δʹ��cocos�е������*/


enum TileValue
{
	changtongwuzu = 0,	//��ͨ����
	youzhedang,			//���ڵ�����ɫ�����˴�������
	bunengxingzou		//��������
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
	/*cocos2dx�ͻ��˻��߷������˿��Ե��õĺ���*/

	int getMapID(){ return this->mapID; }
	void initData();
	int LoadMapData(int mapID, char * allpath);//Success return 0,else return < 0
	int getTileValue(int x, int y);
	int getXTileNum();//x�����ϵĸ�������
	int getYTileNum();//y�����ϵĸ�������

	//����ת��,�ڵ�����͵�ͼ���껥��ת��
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

	//�����¼�����
	const map<int, vector<EventArea>> & getEventAreaData() const{ return this->map_EventArea; }
	void addEventArea(int type,int beginTileX,int beginTileY,int endTileX, int endTileY);
	void deleteEventArea(int type, int tileX,int tileY);
	void deleteAllEventArea(){ this->map_EventArea.clear(); }
	const EventArea * getEventArea(int tileX, int tileY, int * out_eventType);

	/////////////new event area



public:
	/*���������ͼ�༭�����õĺ���*/
	int WriteMapData(char * allpath);
	void newMapData(int mapID,int width, int heigth, int tileWidth, int tileHeight);
	void setTileValue(int x, int y, int value);//�������򲻸�ֵ
private:

	void Password(char * buf, int buflen);//�ӽ���,key�ھ�̬���ж���
	void setTileValue_Forced(int x, int y, int value);//ǿ�ƣ��������½�
private:
	int mapID;
	map<int, map<int, int>> map_TileData;	//��ͼ�赲����
	map<int, vector<EventArea>> map_EventArea;		//��ͼ�¼�����
	map<int, list<vector<EventArea>>> eventAreaData;
	//TODO...								//��ͼ·������
	int width;
	int height;
	int tileWidth;
	int tileHeight;
	int blockWidth;
	int blockHeight;
};

#endif