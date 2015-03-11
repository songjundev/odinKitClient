#ifndef _CAMERA3D_H_
#define _CAMERA3D_H_

#include "cocos2d.h"

NS_CC_BEGIN

class Camera3D : public cocos2d::Camera
{
public:
	enum CameraType {
		FreeCamera = 0,
		FirstCamera = 1,
		ThirdCamera = 2,
	};

public:
	static Camera3D* create(int cameraType, float fieldOfView, float aspectRatio, float nearPlane, float farPlane);

	void setCameraType(int type);

	void onZoom(cocos2d::Vec3 vec);
	void onRotate(cocos2d::Vec3 vec);
	void onTranslate(cocos2d::Vec3 vec);

protected:
	int m_CameraType;

};

NS_CC_END

#endif _CAMERA3D_H_
