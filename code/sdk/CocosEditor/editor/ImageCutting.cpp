#include "ImageCutting.h"
#include "ui_ImageCutting.h"
#include "qfiledialog.h"
#include "qscrollarea.h"
#include "qmessagebox.h"

ImageCutting::ImageCutting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageCutting)
{
    ui->setupUi(this);

    this->img = NULL;
    this->scroll = NULL;
    ui->lbl_savePath->setText("");
}

ImageCutting::~ImageCutting()
{
    delete ui;
}

void ImageCutting::paintEvent ( QPaintEvent * )
{
    if(scroll)
    {
            scroll->setGeometry(0, ui->groupBox->size().height(), this->size().width() ,this->size().height()- ui->groupBox->size().height());
    }

}

void ImageCutting::on_btn_selected_clicked()
{
    QString filename = QFileDialog::getOpenFileName(NULL, "selected","","*.png *.jpg");

    this->img = new QImage();

            if(! ( img->load(filename) ) ) //����ͼ��
            {
				showMessageBox("��ͼ��ʧ��");
                delete this->img;
                this->img = NULL;
                return;
            }

    QLabel * label = new QLabel();
    label->setPixmap(QPixmap::fromImage(*img));
    label->resize(QSize(img->width(),img->height()));

    this->scroll = new QScrollArea(this);

    scroll->setWidget(label);
    scroll->resize(this->size());
    scroll->show();
    this->update();
}


void ImageCutting::cutImage(int saveX,int saveY, int x, int y, int width , int height)
{
    char buf[40] = {0};
    QImage image = img->copy(x, y , width,height);

    sprintf(buf,"%d_%d.png", saveX, saveY);
    image.save(ui->lbl_savePath->text() + "/" + buf);
}

void ImageCutting::jisuan(int width, int height)
{
	//�и�����
	int x = 0;
	int y = 0;
	int cutW = 0;
	int cutH = 0;

	//ʣ���
	int surplusW = 0;

	for (int h = 1;; h++)
	{
		cutW = width;
		cutH = height;

		for (int w = 0;; w++)
		{
			x = w * width;
			y = img->size().height() - h * height;

			surplusW = img->size().width() - (x + width);

			if (surplusW < 0)
				cutW = width - abs(surplusW);

			if (y < 0)
			{
				cutH = height - abs(y);
				y = 0;
			}
			//
			cutImage(w, h - 1, x, y, cutW, cutH);
			//
			if (surplusW <= 0)
				break;
		}

		if (img->size().height() - h * height <= 0)
			break;

	}
}

bool ImageCutting::isNum(const char * p)
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
void ImageCutting::on_btn_begin_clicked()
{
	if (!img)
	{
		showMessageBox("�뵼��ͼƬ��");
		return;
	}

    if(ui->edit_width->text() == "" || ui->edit_height->text() == "")
    {
		showMessageBox("�������Ϊ�գ�\t");
        return;
    }

	char p1[12] = { 0 };
	char p2[12] = { 0 };

	strncpy(p1, this->ui->edit_width->text().toStdString().data(), 10);
	strncpy(p2, this->ui->edit_height->text().toStdString().data(), 10);

	if (!isNum(p1) || !isNum(p2))
	{
		showMessageBox("�����˷Ƿ����ַ�\t");
		return;
	}

	if (strlen(p1) >= 5 || strlen(p2) >= 5)
	{
		showMessageBox("�����ֵ̫���ˣ��ҳ��ܲ���\t");
		return;
	}

    int width = atoi(p1);
    int height = atoi(p2);

    if(width <= 0 || height <= 0 || width > this->img->size().width()|| height > this->img->size().height())
    {
		showMessageBox("�����������ֵ��\t");
        return;
    }

    if(ui->lbl_savePath->text() == "")
    {
		showMessageBox("�������úñ���·��.\t");
        return;
    }

	jisuan(width, height);
}

void ImageCutting::on_btn_setSavePath_clicked()
{
    QString path = QFileDialog::getExistingDirectory ( NULL, "ѡ��Ҫ������ļ���:", "" );
    ui->lbl_savePath->setText(path);
    ui->lbl_savePath->adjustSize();
}

void ImageCutting::showMessageBox(char * p)
{
	QString string;
	QMessageBox::information(this,
		string.fromLocal8Bit("��ʾ��!"),
		string.fromLocal8Bit(p)
		);
	
}