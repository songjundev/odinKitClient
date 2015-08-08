#include "MoveModel.h"
#include "MapDataManage.h"

MoveModel::MoveModel()
{
	this->runObject = NULL;

	speed = 0;
	run = false;
	angle = 0;

	begin.x = 0;
	begin.y = 0;
	end.x = 0;
	end.y = 0;
}


MoveModel::~MoveModel()
{
}

bool MoveModel::init()
{
	Node::init();

	this->scheduleUpdate();

	return true;
}

void MoveModel::onEnter()
{
	Node::onEnter();

}

void MoveModel::onExit()
{
	Node::onExit();

}

//添加一组坐标，自动移动
void MoveModel::addPointArray(vector<Vec2> * vect)
{
	deque_point.clear();
	//tile_Point = *vect;
	while (!vect->empty())
	{
		deque_point.push_front(vect->back());
		vect->pop_back();
	}

	this->Analysis();
	run = true;
}

void MoveModel::update(float dt)
{
	/*
	已知斜边和角度，求对边和临边：

	printf("请输入直角三角形的斜边“);
	scanf("%f", &l);
	printf("请A角的度数 “);
	scanf("%f", &A);
	printf("直角三角形A角的对边是：%f，邻边是：%f。\n", l*sin(A*pi / 180), l*cos(A*pi / 180));
	*/
	if (!run)
		return;

	if (begin.x == end.y || begin.y == end.y)
	{
		update2(dt);
		return;
	}

	float lucheng = dt * this->speed;
	float duibian = lucheng * sin(angle * 3.1415926 / 180);
	float linbian = lucheng * cos(angle * 3.1415926 / 180);

	if (begin.x < end.y)
	{
		point.x += linbian;
		if (point.x > end.x)
			point.x = end.x;
	}
	else
	{
		point.x -= linbian;
		if (point.x < end.x)
			point.x = end.x;
	}

	if (begin.y < end.y)
	{
		point.y += duibian;
		if (point.y > end.y)
			point.y = end.y;
	}
	else
	{
		point.y -= duibian;
		if (point.y < end.y)
			point.y = end.y;
	}

	bindingRunObject();

	if (point == end)
	{
		Analysis();
	}
}

void MoveModel::update2(float dt)
{
	if (begin.x == end.x)
	{
		if (begin.y < end.y)
		{
			point.y += dt * this->speed;
			if (point.y >= end.y)
				point.y = end.y;
		}
		else
		{
			point.y -= dt * this->speed;
			if (point.y < end.y)
				point.y = end.y;
		}
	}
	else
	{
		if (begin.x < end.x)
		{
			point.x += dt * this->speed;
			if (point.x >= end.x)
				point.x = end.x;
		}
		else
		{
			point.x -= dt * this->speed;
			if (point.x <= end.x)
				point.x = end.x;
		}
	}

	bindingRunObject();

	if (point == end)
	{
		Analysis();
	}
}

void MoveModel::bindingRunObject()
{
	this->runObject->setPosition(point);
}

void MoveModel::Analysis()
{
	if (deque_point.empty())
	{
		run = false;
		return;
	}

	Vec2 vec = deque_point.front();
	deque_point.pop_front();

	int endTileX = vec.x;
	int endTIleY = vec.y;
	int beginTileX = 0;
	int beginTileY = 0;

	int beginMapX = point.x;
	int beginMapY = point.y;
	int endMapX = 0;
	int endMapY = 0;

	MapDataManage::getObject()->getMapData()->tilePointToMapPoint(beginMapX, beginMapY, &beginTileX, &beginTileY);
	MapDataManage::getObject()->getMapData()->tilePointToMapPoint(endTileX, endTIleY, &endMapX, &endMapY);

	this->begin.x = beginMapX;
	this->begin.y = beginMapY;
	this->end.x = endMapX;
	this->end.y = endMapY;

	float duibian = abs(beginMapY - endMapY);
	float linbian = abs(beginMapX - endMapY);

	/*
	求角度：

	tan a = 对边/临边

	float angle,pi_angle;
	pi_angle=atan(tanA);//弧度
	angle=pi_angle*180/3.14159;//角度，另注：反正弦余弦函数类似，asin,acos
	*/
	float tanA = duibian / linbian;
	float pi_angle;
	pi_angle = atan(tanA);//弧度
	angle = pi_angle * 180 / 3.14159;//角度
}