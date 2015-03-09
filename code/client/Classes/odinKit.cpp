// odinKit.cpp : �������̨Ӧ�ó������ڵ㡣
//

#pragma once

#include <SDKDDKVer.h>

#include <stdio.h>
#include <tchar.h>

#include "AppDelegate.h"

USING_NS_CC;

int _tmain(int argc, _TCHAR* argv[])
{
	// create the application instance
    AppDelegate app;

	GLViewImpl* glView = GLViewImpl::create("OdinKit");
	glView->setFrameSize(960, 640);

	Director::getInstance()->setOpenGLView(glView);

	return Application::getInstance()->run();
}
