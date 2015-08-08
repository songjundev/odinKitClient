#include "ControlPanel.h"
#include "qtoolbutton.h"
#include "qpushbutton.h"
#include "message.h"

ControlPanel::ControlPanel(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//
	this->InitUI();

	connect(ui.btn_drag, SIGNAL(clicked()), this, SLOT(dragBtn_Event()));
	connect(ui.btn_edit, SIGNAL(clicked()), this, SLOT(editBtn_Event()));
	connect(ui.btn_editEventArea, SIGNAL(clicked()), this, SLOT(eventArea_Event()));
	connect(ui.btn_deleteEvent, SIGNAL(clicked()), this, SLOT(deleteAreaEvent_Event()));
	connect(ui.btn_selectedEvent, SIGNAL(clicked()), this, SLOT(selectedAreaEvent_Event()));
}

ControlPanel::~ControlPanel()
{

}


void ControlPanel::InitUI()
{

}

void ControlPanel::paintEvent(QPaintEvent*)
{
	/*
	static QPushButton * button = new QPushButton("nihaowohaodajiahao", this);
	button->show();
	button->resize(this->size());
	*/
}

void ControlPanel::buttonclick()
{
	//if (toolbutton->seton)
}


void ControlPanel::dragBtn_Event()
{
	LocalMessageManage::getObject()->sendMessage(enum_MessageType_DragMode, NULL);
}

void ControlPanel::editBtn_Event()
{
	int index = ui.cbo_stop->currentIndex();

	MessageData data;
	data.push<int>(index);
	LocalMessageManage::getObject()->sendMessage(enum_MessageType_EditStopData, &data);
}

void ControlPanel::eventArea_Event()
{
	int type = ui.edit_eventType->text().toInt();

	MessageData data;
	data.push<int>(type);
	LocalMessageManage::getObject()->sendMessage(enum_MessageType_EditEventArea, &data);
}

void ControlPanel::deleteAreaEvent_Event()
{
	int type = ui.edit_eventType->text().toInt();

	MessageData data;
	data.push<int>(type);
	LocalMessageManage::getObject()->sendMessage(enum_MessageType_DeleteEventArea, &data);
}

void ControlPanel::selectedAreaEvent_Event()
{
	LocalMessageManage::getObject()->sendMessage(enum_MessageType_SelectedEventArea, NULL);
}