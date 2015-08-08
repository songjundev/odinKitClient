
#ifndef Map_Define_h_
#define Map_Define_h_

#include "cocos2d.h"

//注册touch函数，点击地图时回调参数：tile_x, tile_y
typedef void (cocos2d::Ref::*TouchBegan_Function)(int , int);
typedef void (cocos2d::Ref::*TouchMove_Function)(int, int);
typedef void (cocos2d::Ref::*TouchEnd_Function)(int, int);

#define MAP_TOUCH_BEGIN(fun) static_cast<TouchBegan_Function>(&fun)
#define MAP_TOUCH_MOVE(fun) static_cast<TouchMove_Function>(&fun)
#define MAP_TOUCH_END(fun) static_cast<TouchEnd_Function>(&fun)

enum Direction
{
	//地图和模型的方向枚举
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
	enum_map_director = 0,	//地图导演，控制整个地图世界、移动、定位
	enum_map_layer,			//地图层，绘制地图块
	enum_map_editor,		//编辑层，地图编辑器绘制层
	enum_map_role,			//角色层，npc、主角、怪物畅游层
};

#endif