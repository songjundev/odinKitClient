#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include "ui_ControlPanel.h"

class ControlPanel : public QWidget
{
	Q_OBJECT

public:
	ControlPanel(QWidget *parent = 0);
	~ControlPanel();

	void InitUI();
	virtual void paintEvent(QPaintEvent*);

public slots:
	void dragBtn_Event();
	void editBtn_Event();
	void eventArea_Event();
	void deleteAreaEvent_Event();
	void selectedAreaEvent_Event();

	void buttonclick();
private:
	Ui::ControlPanel ui;
};

#endif // CONTROLPANEL_H
