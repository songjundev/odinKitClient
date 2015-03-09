#ifndef _CAMERA3D_H_
#define _CAMERA3D_H_

#include "cocos2d.h"

class Camera3D : public cocos2d::Camera
{
public:
	enum CameraType {
		FreeCamera = 0,
		FirstCamera = 1,
		ThirdCamera = 2,
	};

public:
	void setCameraType(int type);

	void onZoom(cocos2d::Vec3 vec);
	void onRotate(cocos2d::Vec3 vec);
	void onTranslate(cocos2d::Vec3 vec);

protected:
	int m_CameraType;

};

#endif _CAMERA3D_H_
