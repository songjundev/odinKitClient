#ifndef COCOSEDITOR_H
#define COCOSEDITOR_H

#include <QtWidgets/QMainWindow>
#include "ui_cocoseditor.h"
#include "AppDelegate.h"
#include "message.h"

class ControlPanel;
class QScrollArea;
class CocosEditor : public QMainWindow , public LocalMessage
{
	Q_OBJECT

public:
	CocosEditor(QWidget *parent = 0);
	~CocosEditor();

	//
	virtual void ReceiveMessage(int messageType, MessageData * data);
private:
	void InitUI();

	virtual void closeEvent(QCloseEvent *);

public slots:
	void cutImg();
	void menuEvent_NewCreateMap();
	void menuEvent_SaveMap();
	void menuEvent_LingSaveMap();
	void RunCocos();
private:
	AppDelegate app;
	ControlPanel * controlPanel;
	Ui::CocosEditorClass ui;
	QMenu *_fileMenu;
	QMenu *_handleMenu;
	QMenu *_toolMenu;
	QMenu *_helpMenu;
};

#endif // COCOSEDITOR_H
