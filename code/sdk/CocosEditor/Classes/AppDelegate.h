#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by Director.
*/
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    virtual void initGLContextAttrs();

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();

public:
	HWND getParentHWND()
	{
		return this->parent_hwnd;
	}

	void setParentHWND(HWND parent_hwnd)
	{
		this->parent_hwnd = parent_hwnd;
	}

	void setPoint(const cocos2d::Point & point)
	{
		this->point = point;
	}
	cocos2d::Point getPoint()
	{
		return this->point;
	}

	void setShowData();
private:
	::HWND parent_hwnd;
	cocos2d::Point point;
};

#endif // _APP_DELEGATE_H_

