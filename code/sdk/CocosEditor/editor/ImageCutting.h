#ifndef IMAGECUTTING_H
#define IMAGECUTTING_H

#include <QWidget>

namespace Ui {
class ImageCutting;
}

class QScrollArea;
class ImageCutting : public QWidget
{
    Q_OBJECT

public:
    explicit ImageCutting(QWidget *parent = 0);
    ~ImageCutting();
    virtual void paintEvent ( QPaintEvent * );
private slots:
    void on_btn_selected_clicked();

    void on_btn_begin_clicked();

    void on_btn_setSavePath_clicked();

private:
	bool isNum(const char * );
	void jisuan(int width, int height);
    void cutImage(int saveX,int saveY, int x, int y, int width , int height);
	void showMessageBox(char *);
private:
    Ui::ImageCutting *ui;
    QImage * img;
    QScrollArea * scroll;
};

#endif // IMAGECUTTING_H
