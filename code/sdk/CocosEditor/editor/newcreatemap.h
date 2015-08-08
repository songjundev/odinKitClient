#ifndef NEWCREATEMAP_H
#define NEWCREATEMAP_H

#include <QWidget>
#include "ui_newcreatemap.h"

class NewCreateMap : public QWidget
{
	Q_OBJECT

public:
	NewCreateMap(QWidget *parent = 0);
	~NewCreateMap();

public slots:
	void createMap();
	void help();
private:
	void getMapSize(int in_width, int in_height, int * out_width, int * out_height);
	bool isNum(const char * p);
	void showMessageBox(char *);
private:
	Ui::NewCreateMap ui;
};

#endif // NEWCREATEMAP_H
