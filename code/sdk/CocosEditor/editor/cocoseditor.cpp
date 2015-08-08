#include "cocoseditor.h"
#include "qscrollarea.h"
#include "cocos2d.h"
#include "qtimer.h"
#include "ControlPanel.h"
#include "qtoolbutton.h"
#include "qfiledialog.h"
#include "qmessagebox.h"

CocosEditor::CocosEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	_fileMenu = NULL;
	_toolMenu = NULL;
	_helpMenu = NULL;

	InitUI();

	//��ʱ��
	QTimer * timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(RunCocos()));
	timer->start(0);

	//
	LocalMessageManage::getObject()->registerMessage(this, enum_MessageType_ShowQMessageBox);
}

CocosEditor::~CocosEditor()
{
	LocalMessageManage::getObject()->deleteMessage(this, enum_MessageType_ShowQMessageBox);
}

void CocosEditor::InitUI()
{
	/* ----------------------------�˵���------------------------------*/

	//�ļ�
	_fileMenu = menuBar()->addMenu(QString::fromLocal8Bit("�ļ�"));
	{
		QAction * newMap = new QAction(QString::fromLocal8Bit("new create map"), this);
		connect(newMap, SIGNAL(triggered()), this, SLOT(menuEvent_NewCreateMap()));

		QAction * _openAct = new QAction(QString::fromLocal8Bit("��"), this);
		connect(_openAct, SIGNAL(triggered()), this, SLOT(open()));
		
		QAction * save = new QAction(QString::fromLocal8Bit("����"), this);

		QAction * lingSave = new QAction(QString::fromLocal8Bit("���"), this);

		_fileMenu->addAction(newMap);
		_fileMenu->addAction(_openAct);
		_fileMenu->addAction(save);
		_fileMenu->addAction(lingSave);
	}

	//����
	_toolMenu = menuBar()->addMenu(QString::fromLocal8Bit("����"));
	{
		QAction * cutImg = new QAction(QString::fromLocal8Bit("��ͼ"), this);
		connect(cutImg, SIGNAL(triggered()), this, SLOT(cutImg()));

		_toolMenu->addAction(cutImg);
	}

	//����
	_handleMenu = menuBar()->addMenu(QString::fromLocal8Bit("����"));

	//����
	_helpMenu = menuBar()->addMenu(QString::fromLocal8Bit("����"));
	{
		QAction * help = new QAction(QString::fromLocal8Bit("����"), this);
		QAction * about = new QAction(QString::fromLocal8Bit("����"), this);

		_helpMenu->addAction(help);
		_helpMenu->addAction(about);
	}


	/*----------------------------������-------------------------------*/
	/*
	QToolBar *toolBar = addToolBar(tr("&File"));

	QToolButton *buttonOpen = new QToolButton();
	buttonOpen->setText("dianwo");
	ui.mainToolBar->addWidget(buttonOpen);
	buttonOpen->toggled(true);
	*/
}

#include "ImageCutting.h"
void CocosEditor::cutImg()
{
	ImageCutting * img = new ImageCutting(this);
	img->setWindowTitle(QString::fromLocal8Bit("�и�ͼƬ�����Ұ�~"));
	img->setWindowFlags(Qt::Dialog);
	img->setWindowModality(Qt::WindowModal);
	img->show();
}

#include "newcreatemap.h"
void CocosEditor::menuEvent_NewCreateMap()
{
	//�´�����ͼ
	NewCreateMap * newmap = new NewCreateMap(this);
	newmap->setWindowTitle(QString::fromLocal8Bit("������ͼ~"));
	newmap->setWindowFlags(Qt::Dialog);
	newmap->setWindowModality(Qt::WindowModal);
	newmap->show();
}

void CocosEditor::menuEvent_LingSaveMap()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Open Config"),
		"",
		tr("Config Files (*.ifg)"));

	if (!fileName.isNull())
	{
		//fileName���ļ���
	}
	else
	{
		//�����ȡ��
	}
}
void CocosEditor::menuEvent_SaveMap()
{

}

void CocosEditor::RunCocos()
{
	//�������
	this->controlPanel = new ControlPanel(this);
	controlPanel->show();
	controlPanel->move(0, menuBar()->size().height() + ui.mainToolBar->size().height());
	controlPanel->resize(300, 500);

	HWND hwnd = (HWND)(this->winId());
	//AppDelegate app;
	app.setParentHWND(hwnd);
	app.setPoint(cocos2d::Point(controlPanel->size().width(), this->menuBar()->size().height() + ui.mainToolBar->size().height()));


	auto director = cocos2d::Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = cocos2d::GLViewImpl::create("My Game");
		glview->setFrameSize(800, 600);
		director->setOpenGLView(glview);
	}

	//���������ڹ̶���С��������ק
	this->setFixedSize(controlPanel->size().width() + glview->getFrameSize().width, menuBar()->size().height() + ui.mainToolBar->size().height() + glview->getFrameSize().height); //���ô���̶���С
	//begin cocos run
	cocos2d::Application::getInstance()->run();
}


void CocosEditor::closeEvent(QCloseEvent *)
{
	cocos2d::Director::getInstance()->end();
	qApp->quit();
}


void CocosEditor::ReceiveMessage(int messageType, MessageData * data)
{
	if (messageType == enum_MessageType_ShowQMessageBox)
	{

		char * p = data->pop<char *>();
		QString string;
		QMessageBox::information(this,
			string.fromLocal8Bit("��ʾ��!"),
			string.fromLocal8Bit(p)
			);
	}
}