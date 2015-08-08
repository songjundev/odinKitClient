#include "newcreatemap.h"
#include "qmessagebox.h"
#include "qfiledialog.h"
#include "message.h"
#include "MapDataManage.h"

#define TileWidth 64
#define TileHeight 32

NewCreateMap::NewCreateMap(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.btn_help, SIGNAL(clicked()), this, SLOT(help()));
	connect(ui.btn_create, SIGNAL(clicked()), this, SLOT(createMap()));
}

NewCreateMap::~NewCreateMap()
{

}

void NewCreateMap::createMap()
{
	if (ui.edit_width->text() == "" || ui.edit_height->text() == "")
	{
		showMessageBox("�������Ϊ�գ�\t");
		return;
	}

	char p1[12] = { 0 };
	char p2[12] = { 0 };

	strncpy(p1, this->ui.edit_width->text().toStdString().data(), 10);
	strncpy(p2, this->ui.edit_height->text().toStdString().data(), 10);

	if (!isNum(p1) || !isNum(p2))
	{
		showMessageBox("�����˷Ƿ����ַ�\t");
		return;
	}

	if (strlen(p1) >= 10 || strlen(p2) >= 10)
	{
		showMessageBox("�����ֵ̫���ˣ��ҳ��ܲ���\t");
		return;
	}

	int width = atoi(p1);
	int height = atoi(p2);

	if (width <= 0 || height <= 0)
	{
		showMessageBox("�����������ֵ��\t");
		return;
	}

	getMapSize(width,height,&width,&height);

	MapDataManage::getObject()->NewMapData(110,width, height, TileWidth, TileHeight);

	//��������
	LocalMessageManage::getObject()->sendMessage(enum_MessageType_NewCreateMap, NULL);
	this->close();

}

void NewCreateMap::getMapSize(int in_width, int in_height, int * out_width, int * out_height)
{
	//width
	int zs = in_width / TileWidth;
	int yu = in_width % TileWidth;
	if (yu == 0)
		*out_width = in_width;
	else
		*out_width = (zs + 1) * TileWidth;

	//height
	zs = in_height / TileHeight;
	yu = in_height % TileHeight;
	if (yu == 0)
		*out_height = in_height;
	else
		*out_height = (zs + 1) * TileHeight;
}

bool NewCreateMap::isNum(const char * p)
{
	bool ok = true;
	while (*p)
	{
		if (*p < '0' || *p > '9')
		{
			ok = false;
			break;
		}
		p++;
	}

	return ok;
}
#include "QTextCodec.h"
void NewCreateMap::showMessageBox(char * p)
{
	QString string;
	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
	QMessageBox::information(this,
		string.fromLocal8Bit("��ʾ����"),
		string.fromLocal8Bit(p)
		);
}

void NewCreateMap::help()
{
	showMessageBox("ʵ�ʵĿ���Ը��Ӷ��룡��˵�������Ӵ�С(64 * 32),��������������Ϊ��1000 * 500���������Ĵ�С��1024 * 512��.......\t");
}