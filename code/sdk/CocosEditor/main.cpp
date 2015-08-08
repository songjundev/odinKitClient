#include "cocoseditor.h"
#include <QtWidgets/QApplication>

#include "cocos2d.h"
#include "AppDelegate.h"
#include "qpushbutton.h"
#include <WinUser.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CocosEditor w;
	w.show();
	
	return a.exec();
}
