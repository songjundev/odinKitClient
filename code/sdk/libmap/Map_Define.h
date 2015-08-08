
#ifndef Map_Define_h_
#define Map_Define_h_

#include "cocos2d.h"

//ע��touch�����������ͼʱ�ص�������tile_x, tile_y
typedef void (cocos2d::Ref::*TouchBegan_Function)(int , int);
typedef void (cocos2d::Ref::*TouchMove_Function)(int, int);
typedef void (cocos2d::Ref::*TouchEnd_Function)(int, int);

#define MAP_TOUCH_BEGIN(fun) static_cast<TouchBegan_Function>(&fun)
#define MAP_TOUCH_MOVE(fun) static_cast<TouchMove_Function>(&fun)
#define MAP_TOUCH_END(fun) static_cast<TouchEnd_Function>(&fun)

enum Direction
{
	//��ͼ��ģ�͵ķ���ö��
	enum_up = 0,
	enum_down,
	enum_left,
	enum_right,

	enum_left_up,
	enum_right_up,
	enum_left_down,
	enum_right_down,
};

enum LayerType
{
	enum_map_director = 0,	//��ͼ���ݣ�����������ͼ���硢�ƶ�����λ
	enum_map_layer,			//��ͼ�㣬���Ƶ�ͼ��
	enum_map_editor,		//�༭�㣬��ͼ�༭�����Ʋ�
	enum_map_role,			//��ɫ�㣬npc�����ǡ����ﳩ�β�
};

#endif