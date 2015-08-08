#include "HelloWorldScene.h"
#include "MapControl.h"

USING_NS_CC;

HelloWorld::HelloWorld()
{
	this->sprite = NULL;
	end.x = -1;
	end.y = -1;
	begin.x = 0;
	begin.y = 0;
	jiaodu = -1;
	go = false;

	LocalMessageManage::getObject()->registerMessage(this, enum_MessageType_NewCreateMap);
}
HelloWorld::~HelloWorld()
{
	LocalMessageManage::getObject()->deleteMessage(this, enum_MessageType_NewCreateMap);
}
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	this->setTouchEnabled(true);
	this->setTouchMode(cocos2d::Touch::DispatchMode::ONE_BY_ONE);
	this->scheduleUpdate();
	/*
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "../CocosEditor/Resources/CloseNormal.png",
                                           "../CocosEditor/Resources/CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
	
    auto label = Label::createWithTTF("Hello World", "../CocosEditor/Resources/fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);
	

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("../CocosEditor/Resources/HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    */

	/*

	/*
	已知斜边和角度，求对边和临边：

	printf("请输入直角三角形的斜边“);
   scanf("%f",&l);
   printf("请A角的度数 “);
   scanf("%f",&A);
   printf("直角三角形A角的对边是：%f，邻边是：%f。\n",l*sin(A*pi/180),l*cos(A*pi/180));
	*/
	/*
	求角度：

	tan a = 对边/临边

	float angle,pi_angle;
	pi_angle=atan(tanA);//弧度
	angle=pi_angle*180/3.14159;//角度，另注：反正弦余弦函数类似，asin,acos
	*/

	/*this->sprite = Sprite::create("../CocosEditor/Resources/CloseNormal.png");
	this->addChild(this->sprite);
	this->sprite->setPosition(Vec2(0, 0));*/

	CCLabelTTF * lbl = CCLabelTTF::create("Welcome to use the map editor \n to create your wonderful world.","", 30);
	Size winSize = Director::getInstance()->getWinSize();
	this->addChild(lbl);
	lbl->setPosition(Vec2(winSize.width / 2, 0));
	  
	MoveTo * move = MoveTo::create(3.0f, Vec2(winSize.width / 2, winSize.height / 2));
	lbl->runAction(move);
    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::update(float dt)
{
	if (jiaodu < 0 && go)
	{
		//tan
		float x = abs(abs(end.x) - abs(sprite->getPositionX()));
		float y = abs(abs(end.y) - abs(sprite->getPositionY()));
		float tan = (x == 0) ? 0 : (y / x);

		//角度
		float angle, pi_angle;
		pi_angle = atan(tan);//弧度
		angle = pi_angle * 180 / 3.14159;

		jiaodu = angle;

		begin = this->sprite->getPosition();
	}

	if (go)
	{
		float lc = dt * 200;
		//对边：y坐标，邻边：x坐标
		float duibian = lc * sin(jiaodu * 3.14159 / 180);
		float linbian =  lc * cos(jiaodu * 3.14159 / 180);

		if (end.x > begin.x)
		{
			this->sprite->setPositionX(this->sprite->getPositionX() + linbian);
			if (this->sprite->getPositionX() >= end.x)
				this->sprite->setPositionX(end.x);
		}
		else
		{
			this->sprite->setPositionX(this->sprite->getPositionX() - linbian);
			if (this->sprite->getPositionX() <= end.x)
				this->sprite->setPositionX(end.x);
		}
		if (end.y > begin.y)
		{
			this->sprite->setPositionY(this->sprite->getPositionY() + duibian);
			if (this->sprite->getPositionY() >= end.y)
				this->sprite->setPositionY(end.y);
		}
		else
		{
			this->sprite->setPositionY(this->sprite->getPositionY() - duibian);
			if (this->sprite->getPositionY() <= end.y)
				this->sprite->setPositionY(end.y);
		}

		if (this->sprite->getPosition() == end)
		{
			go = false;
		}

		this->sprite->getPosition();
	}

	return;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	jiaodu = -1;
	go = true;
	end = pTouch->getLocation();
	return true;
}

//接收消息
void HelloWorld::ReceiveMessage(int messageType, MessageData * data)
{
	switch (messageType)
	{
	case enum_MessageType_NewCreateMap:
		this->newCreateMap(data);
		break;
	default:
		break;
	}
}

void HelloWorld::newCreateMap(MessageData * data)
{
	this->unscheduleUpdate();
	this->removeAllChildren();

	this->addChild( MapControl::create() );
}