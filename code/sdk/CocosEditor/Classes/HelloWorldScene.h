#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "message.h"

class Map_Layer;
class HelloWorld : public cocos2d::Layer, public LocalMessage
{
public:
	HelloWorld();
	~HelloWorld();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	virtual void update(float dt);
	virtual bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	cocos2d::Sprite * sprite;
	cocos2d::Point end;	//去的一个点
	cocos2d::Point begin;//起始点

	bool go;
	float jiaodu;

private:
	virtual void ReceiveMessage(int messageType, MessageData * data);
	void newCreateMap(MessageData * data);
};

#endif // __HELLOWORLD_SCENE_H__
