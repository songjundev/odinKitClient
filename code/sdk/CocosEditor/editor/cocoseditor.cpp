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

	//定时器
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
	/* ----------------------------菜单栏------------------------------*/

	//文件
	_fileMenu = menuBar()->addMenu(QString::fromLocal8Bit("文件"));
	{
		QAction * newMap = new QAction(QString::fromLocal8Bit("new create map"), this);
		connect(newMap, SIGNAL(triggered()), this, SLOT(menuEvent_NewCreateMap()));

		QAction * _openAct = new QAction(QString::fromLocal8Bit("打开"), this);
		connect(_openAct, SIGNAL(triggered()), this, SLOT(open()));
		
		QAction * save = new QAction(QString::fromLocal8Bit("保存"), this);

		QAction * lingSave = new QAction(QString::fromLocal8Bit("另存"), this);

		_fileMenu->addAction(newMap);
		_fileMenu->addAction(_openAct);
		_fileMenu->addAction(save);
		_fileMenu->addAction(lingSave);
	}

	//工具
	_toolMenu = menuBar()->addMenu(QString::fromLocal8Bit("工具"));
	{
		QAction * cutImg = new QAction(QString::fromLocal8Bit("切图"), this);
		connect(cutImg, SIGNAL(triggered()), this, SLOT(cutImg()));

		_toolMenu->addAction(cutImg);
	}

	//操作
	_handleMenu = menuBar()->addMenu(QString::fromLocal8Bit("操作"));

	//帮助
	_helpMenu = menuBar()->addMenu(QString::fromLocal8Bit("帮助"));
	{
		QAction * help = new QAction(QString::fromLocal8Bit("帮助"), this);
		QAction * about = new QAction(QString::fromLocal8Bit("关于"), this);

		_helpMenu->addAction(help);
		_helpMenu->addAction(about);
	}


	/*----------------------------工具栏-------------------------------*/
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
	img->setWindowTitle(QString::fromLocal8Bit("切割图片，找我啊~"));
	img->setWindowFlags(Qt::Dialog);
	img->setWindowModality(Qt::WindowModal);
	img->show();
}

#include "newcreatemap.h"
void CocosEditor::menuEvent_NewCreateMap()
{
	//新创建地图
	NewCreateMap * newmap = new NewCreateMap(this);
	newmap->setWindowTitle(QString::fromLocal8Bit("创建地图~"));
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
		//fileName是文件名
	}
	else
	{
		//点的是取消
	}
}
void CocosEditor::menuEvent_SaveMap()
{

}

void CocosEditor::RunCocos()
{
	//控制面板
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

	//设置主窗口固定大小，不能拖拽
	this->setFixedSize(controlPanel->size().width() + glview->getFrameSize().width, menuBar()->size().height() + ui.mainToolBar->size().height() + glview->getFrameSize().height); //设置窗体固定大小
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
			string.fromLocal8Bit("提示您!"),
			string.fromLocal8Bit(p)
			);
	}
}