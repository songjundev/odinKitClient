#include "Camera3D.h"

using namespace cocos2d;

Camera3D* Camera3D::create(int cameraType, float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
	auto ret = new (std::nothrow) Camera3D();
	if (ret)
	{
		ret->initPerspective(fieldOfView, aspectRatio, nearPlane, farPlane);
		ret->setCameraType(cameraType);
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

void Camera3D::setCameraType(int type)
{
	m_CameraType = type;
}

void Camera3D::onZoom(Vec3 vec)
{
	if (m_CameraType == CameraType::ThirdCamera)
	{
		//Vec3 lookDir = this->getPosition3D() - _sprite3D->getPosition3D();
		Vec3 cameraPos = this->getPosition3D();
		//cameraPos += lookDir.getNormalized(); 
		cameraPos += vec;
		this->setPosition3D(cameraPos);
	}
	else if (m_CameraType == CameraType::FreeCamera)
	{
		Vec3 cameraPos = this->getPosition3D();
		//cameraPos += cameraPos.getNormalized();
		cameraPos += vec;
		this->setPosition3D(cameraPos);
	}
}

void Camera3D::onRotate(Vec3 vec)
{
	if (m_CameraType == CameraType::FirstCamera || m_CameraType == CameraType::FreeCamera)
	{
		Vec3  rotation3D = this->getRotation3D();
		rotation3D += vec;
		this->setRotation3D(rotation3D);
	}
}

void Camera3D::onTranslate(Vec3 vec)
{
	Vec3 cameraPos = this->getPosition3D();
	cameraPos += vec;
	this->setPosition3D(cameraPos);
}
