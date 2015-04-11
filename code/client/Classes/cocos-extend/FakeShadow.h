#ifndef _FAKESHADOW_H_
#define _FAKESHADOW_H_

#include "cocos2d.h"

NS_CC_BEGIN

class FakeShadow : public cocos2d::GLProgramState
{
public:
	static FakeShadow* create(cocos2d::Sprite3D* plane);

	void setPosition3D(const cocos2d::Vec3& position);

};

NS_CC_END

#endif _FAKESHADOW_H_
