#include "MapAIControl.h"
#include "MapDataManage.h"


MapAIControl::MapAIControl()
{
	//开启线程
	beginThread();
}


MapAIControl::~MapAIControl()
{
	isRun = false;

	deleteAllArray();
}

void MapAIControl::beginThread()
{
	HANDLE hThrd;
	DWORD threadId;

	isRun = true;
	hThrd = CreateThread(NULL, 0, run, (LPVOID)this, 0, &threadId);
}
DWORD WINAPI MapAIControl::run(LPVOID p)
{
	MapAIControl * aiControl = (MapAIControl *)p;
	MapAIData * data = NULL;

	bool ok = false;
	while (aiControl->isRun)
	{
		if (aiControl->deque_data.empty())
			continue;

		if (!data)
		{
			data = aiControl->deque_data.front();
			aiControl->deque_data.pop_front();

			if (data->begin_tile_Point.x == data->end_tile_Point.x || data->begin_tile_Point.y == data->end_tile_Point.y)
				ok = aiControl->lineRun1(data);
			else
				ok = aiControl->lineRun2(data);

			if (ok)
			{
				data->complete = true;
				continue;
			}
		}

		aiControl->axing(data);

		data = NULL;
	}
	return NULL;
}


//直线时，直接前往目标点，有障碍时，交给a星
bool MapAIControl::lineRun1(MapAIData * aiData)
{
	int beginTileX = aiData->begin_tile_Point.x;
	int beginTileY = aiData->begin_tile_Point.y;
	int endTileX = aiData->end_tile_Point.x;
	int endTileY = aiData->end_tile_Point.y;

	int beginMapX = 0;
	int beginMapY = 0;
	int endMapX = 0;
	int endMapY = 0;

	int curMapX = beginMapX;
	int curMapY = beginMapY;

	int curTileX = beginTileX;
	int curTileY = beginTileY;
	int upTileX = beginTileX;
	int upTileY = beginTileY;

	while (1)
	{
		if (beginMapY < endMapY)
		{
			curMapY += MapDataManage::getObject()->getMapData()->getTileHeight();
			if (curMapY >= endMapY)
			{
				curMapY = endMapY;
			}
		}
		else
		if (beginMapY > endMapY)
		{
			curMapY -= MapDataManage::getObject()->getMapData()->getTileHeight();
			if (curMapY <= endMapY)
			{
				curMapY = endMapY;
			}
		}

		if (beginTileX < endTileX)
		{
			curMapX += MapDataManage::getObject()->getMapData()->getTileWidth();
			if (curMapX > endMapX)
			{
				curMapX = endMapX;
			}
		}
		else
		if (beginTileX > endTileX)
		{
			curMapX -= MapDataManage::getObject()->getMapData()->getTileWidth();
			if (curMapX < endMapX)
			{
				curMapX = endMapX;
			}
		}

		MapDataManage::getObject()->getMapData()->mapPointToTilePoint(curMapX, curMapY, &curTileX, &curTileY);
		if (MapDataManage::getObject()->getMapData()->getTileValue(curTileX, curTileY) == 2)
		{
			aiData->begin_tile_Point = Vec2(upTileX, upTileY);
			aiData->tile_Point.push_back(aiData->begin_tile_Point);
			return false;
		}
		//
		if (curMapX == endMapX && curMapY == endMapY)
		{
			aiData->begin_tile_Point = aiData->end_tile_Point;
			aiData->tile_Point.push_back(aiData->end_tile_Point);
			return true;
		}

		if (curTileX != upTileX || curTileY != upTileY)
		{
			upTileX = curTileX;
			upTileY = curTileY;
		}
	}

	return false;
}

//斜线时，直接前往目标点，有障碍时，交给a星
bool MapAIControl::lineRun2(MapAIData * aiData)
{
	/*
	已知斜边和角度，求对边和临边：

		printf("请输入直角三角形的斜边“);
		scanf("%f", &l);
	printf("请A角的度数 “);
		scanf("%f", &A);
	printf("直角三角形A角的对边是：%f，邻边是：%f。\n", l*sin(A*pi / 180), l*cos(A*pi / 180));
	*/
		/*
		求角度：

		tan a = 对边/临边

		float angle,pi_angle;
		pi_angle=atan(tanA);//弧度
		angle=pi_angle*180/3.14159;//角度，另注：反正弦余弦函数类似，asin,acos
		*/

	int beginTileX = aiData->begin_tile_Point.x;
	int beginTileY = aiData->begin_tile_Point.y;
	int endTileX = aiData->end_tile_Point.x;
	int endTileY = aiData->end_tile_Point.y;

	int beginMapX = 0;
	int beginMapY = 0;
	int endMapX = 0;
	int endMapY = 0;

	//函数内部用的都是局部变量，不用枷锁
	MapDataManage::getObject()->getMapData()->tilePointToMapPoint(beginTileX, beginTileY, &beginMapX, &beginMapY);
	MapDataManage::getObject()->getMapData()->tilePointToMapPoint(endTileX, endTileY, &endMapX, &endMapY);

	float duibian = abs(endMapY - beginMapY);
	float linbian = abs(endMapX - beginMapX);
	//tan
	float tanA = duibian / linbian;
	float angle, pi_angle;
	pi_angle = atan(tanA);//弧度
	angle = pi_angle * 180 / 3.14159;//角度

	//
	int upTileX = beginTileX;
	int upTileY = beginTileY;
	int curTileX = beginTileX;
	int curTileY = beginTileY;

	int curMapX = beginMapX;
	int curMapY = beginMapY;

	int len = 0;
	while (1)
	{
		len += MapDataManage::getObject()->getMapData()->getTileHeight() / 2;
		duibian = len * sin(angle * 3.1415926 / 180);
		linbian = len * cos(angle * 3.1415926 / 180);

		if (beginMapX > endMapX)
		{
			curMapX -= linbian;
			if (curMapX <= endMapX)
				curMapX = endMapX;
		}
		else
		{
			curMapX += linbian;
			if (curMapX >= endMapX)
				curMapX = endMapX;
		}

		if (beginMapY > endMapY)
		{
			curMapY -= duibian;
			if (curMapY <= endMapY)
				curMapY = endMapY;
		}
		else
		{
			curMapY += duibian;
			if (curMapY >= endMapY)
				curMapY = endMapY;
		}

		MapDataManage::getObject()->getMapData()->mapPointToTilePoint(curMapX, curMapY, &curTileX, &curTileY);

		if (MapDataManage::getObject()->getMapData()->getTileValue(curTileX, curTileY) == 2)
		{
			aiData->begin_tile_Point.x = upTileX;
			aiData->begin_tile_Point.y = upTileY;
			aiData->tile_Point.push_back(Vec2(upTileX, upTileY));
			return false;
		}

		if (curMapX == endMapX && curMapY == endMapY)
		{
			//结束
			aiData->begin_tile_Point = aiData->end_tile_Point;
			aiData->tile_Point.push_back(Vec2(curTileX, curTileY));
			return true;
		}

		if (upTileX != curTileX || upTileY != curTileY)
		{
			upTileX = curTileX;
			upTileY = curTileY;
		}
	}

	return false;
}

void MapAIControl::axing(MapAIData * aiData)
{
	int beginTileX = aiData->begin_tile_Point.x;
	int beginTileY = aiData->begin_tile_Point.y;
	int endTileX = aiData->end_tile_Point.x;
	int endTileY = aiData->end_tile_Point.y;

	int beginMapX = 0;
	int beginMapY = 0;
	int endMapX = 0;
	int endMapY = 0;

	int curTileX = beginTileX;
	int curTileY = beginTileY;

	int curG = 0;

	AiNode * curNode = new AiNode();
	curNode->g = 0;
	curNode->h = abs(curTileX - endTileX) + abs(curTileY - endTileY);
	curNode->parentP = NULL;
	curNode->tilePoint.x = curTileX;
	curNode->tilePoint.y = curTileY;

	deleteAllArray();

	close.push_back(curNode);

	while (1)
	{
		addOpen(aiData, curNode);
		//从open中寻找最适合的路径
		AiNode * node = getOpenNode();
		if (!node)
		{
			//open列表为空，寻路失败了
			return;
		}
		curNode = node;
		close.push_back(node);
		if (node->tilePoint.x == endTileX && node->tilePoint.y == endTileY)
		{
			break;
		}
	}

	//寻路完成
	while (!close.empty())
	{
		AiNode * node = close.front();
		if (node)
		{
			aiData->tile_Point.push_back(node->tilePoint);
			delete node;
		}
		close.pop_front();
	}
	aiData->complete = true;
}

void MapAIControl::addOpen(MapAIData * aiData, AiNode * curNode)
{
	int endTileX = aiData->end_tile_Point.x;
	int endTileY = aiData->end_tile_Point.y;

	int curTileX = curNode->tilePoint.x;
	int curTileY = curNode->tilePoint.y;

	int curMapX = 0;
	int curMapY = 0;

	MapDataManage::getObject()->getMapData()->tilePointToMapPoint(curTileX, curTileY, &curMapX, &curMapY);

	int l1 = MapDataManage::getObject()->getMapData()->getWidth() / 2;
	int l2 = MapDataManage::getObject()->getMapData()->getHeight() / 2;

	//up
	int tmpTileX = curTileX;
	int tmpTileY = curTileY - 2;
	_addOpen(aiData, curNode, tmpTileX, tmpTileY);
	//down
	tmpTileX = curTileX;
	tmpTileY = curTileY + 2;
	_addOpen(aiData, curNode, tmpTileX, tmpTileY);
	//left
	tmpTileX = curTileX - 2;
	tmpTileY = curTileY;
	_addOpen(aiData, curNode, tmpTileX, tmpTileY);
	//right
	tmpTileX = curTileX + 2;
	tmpTileY = curTileY;
	_addOpen(aiData, curNode, tmpTileX, tmpTileY);
	// left up
	MapDataManage::getObject()->getMapData()->mapPointToTilePoint(curMapX - l1, curMapY + l2, &tmpTileX, &tmpTileY);
	_addOpen(aiData, curNode, tmpTileX, tmpTileY);
	//right up
	MapDataManage::getObject()->getMapData()->mapPointToTilePoint(curMapX + l1, curMapY + l2, &tmpTileX, &tmpTileY);
	_addOpen(aiData, curNode, tmpTileX, tmpTileY);
	//left down
	MapDataManage::getObject()->getMapData()->mapPointToTilePoint(curMapX - l1, curMapY - l2, &tmpTileX, &tmpTileY);
	_addOpen(aiData, curNode, tmpTileX, tmpTileY);
	//right down
	MapDataManage::getObject()->getMapData()->mapPointToTilePoint(curMapX + l1, curMapY - l2, &tmpTileX, &tmpTileY);
	_addOpen(aiData, curNode, tmpTileX, tmpTileY);
}


void MapAIControl::_addOpen(MapAIData * aiData, AiNode * curNode, int tile_x, int tile_y)
{
	int endTileX = aiData->end_tile_Point.x;
	int endTileY = aiData->end_tile_Point.y;

	AiNode * aiNode = inOpen(tile_x, tile_y);
	if (aiNode)
	{
		aiNode->g = curNode->g + 1;
		aiNode->h = abs(tile_x - endTileX) + abs(tile_y - endTileY);
		aiNode->parentP = curNode;
		aiNode->tilePoint.x = tile_x;
		aiNode->tilePoint.y = tile_y;

		return;
	}

	if (MapDataManage::getObject()->getMapData()->getTileValue(tile_x, tile_y) != 2 && !inCose(tile_x, tile_y))
	{
		AiNode * node = new AiNode();
		node->g = curNode->g + 1;
		node->h = abs(tile_x - endTileX) + abs(tile_y - endTileY);
		node->parentP = curNode;
		node->tilePoint.x = tile_x;
		node->tilePoint.y = tile_y;

		open.push_back(node);
	}
}

AiNode * MapAIControl::getOpenNode()
{
	int minF = 0;
	int curF = 0;
	list<AiNode*>::iterator itP = open.end();

	for (list<AiNode*>::iterator it = open.begin(); it != open.begin(); it++)
	{
		curF = (*it)->g + (*it)->h;
		if (itP == open.end() || curF < minF)
		{
			minF = curF;
			itP = it;
		}
	}

	if (itP == open.end())
		return NULL;
	AiNode * node = *itP;
	open.erase(itP);
	return node;
}

//判断某一个格子是否在close列表
AiNode * MapAIControl::inCose(int tile_x, int tile_y)
{
	for (list<AiNode *>::iterator it = close.begin(); it != close.end(); it++)
	{

		if ((int)(*it)->tilePoint.x == tile_x && (int)(*it)->tilePoint.y == tile_y)
		{
			return *it;
		}
	}
	return NULL;
}

AiNode * MapAIControl::inOpen(int tile_x, int tile_y)
{
	for (list<AiNode *>::iterator it = open.begin(); it != open.end(); it++)
	{

		if ((int)(*it)->tilePoint.x == tile_x && (int)(*it)->tilePoint.y == tile_y)
		{
			return *it;
		}
	}
	return NULL;
}

int MapAIControl::addAITask(MapAIData * aiData)
{
	if (!aiData)
		return - 1;

	if (aiData->begin_tile_Point == aiData->end_tile_Point)
		return -2;


	aiData->complete = false;
	aiData->tile_Point.clear();
	deque_data.push_back(aiData);
}


void MapAIControl::deleteAllArray()
{
	//close列表
	while (!close.empty())
	{
		AiNode * node = close.front();
		if (node)
			delete node;
		close.pop_front();
	}
	//open列表
	while (!open.empty())
	{
		AiNode * node = open.front();
		if (node)
			delete node;
		open.pop_front();
	}
}