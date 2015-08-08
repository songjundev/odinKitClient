#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "lua_register.h"
#include "Map_Director.h"
#include "MapDataManage.h"

USING_NS_CC;

AppDelegate::AppDelegate() 
{
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() 
{
#if	(COCOS2D_DEBUG > 0)
    // turn on display FPS
	Director::getInstance()->setDisplayStats(true);
#else
	// turn off display FPS
	Director::getInstance()->setDisplayStats(false);
#endif

    // set FPS. the default value is 1.0/60 if you don't call this
	Director::getInstance()->setAnimationInterval(1.0 / 60);

	auto engine = LuaEngine::getInstance();
	ScriptEngineManager::getInstance()->setScriptEngine(engine);
	lua_State* L = engine->getLuaStack()->getLuaState();
	lua_module_register(L);
	lua_custom_register(L);

	LuaStack* stack = engine->getLuaStack();
	stack->setXXTEAKeyAndSign("2dxLua", strlen("2dxLua"), "XXTEA", strlen("XXTEA"));

	engine->executeScriptFile("lua/game/main.lua");

	Scene* scene = Scene::create();
	MapDataManage::getObject()->LoadMapData(110, "./Resources/map");
	scene->addChild(Map_Director::createMap("./Resources/map", true));

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() 
{
	Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() 
{
	Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
