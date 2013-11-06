#include "fworkimage.h"
#include "ui_fworkimage.h"

fWorkImage::fWorkImage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fWorkImage)
{
    ui->setupUi(this);
    image =NULL;
}

fWorkImage::~fWorkImage()
{
    if(image)
        delete image;
    delete ui;
}

void fWorkImage::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void fWorkImage::setPixmap(QPixmap img){
    setMinimumWidth(img.width());
    setMinimumHeight(img.height());
    ui->label->setMaximumWidth(img.width());
    ui->label->setMaximumHeight(img.height());
    ui->label->setPixmap(img);
    image = new QPixmap(img);
}

void fWorkImage::visualAttack(){

    QImage attr1 = image->toImage();
    for(int j=0;j<attr1.height();j++)
        for(int i=0;i<attr1.width();i++){
            QRgb p = attr1.pixel(i,j);
            QRgb np;
            if(attr1.hasAlphaChannel())
                np = qRgba((qRed(p)-((int)(qRed(p)/2))*2)*255,
                           (qGreen(p)-((int)(qGreen(p)/2))*2)*255,
                           (qBlue(p)-((int)(qBlue(p)/2))*2)*255,
                            (qAlpha(p)-((int)(qAlpha(p)/2))*2)*255);
            else
                np = qRgb((qRed(p)-((int)(qRed(p)/2))*2)*255,
                           (qGreen(p)-((int)(qGreen(p)/2))*2)*255,
                           (qBlue(p)-((int)(qBlue(p)/2))*2)*255);

            attr1.setPixel(i,j, np);
        }
//    attr1.save("test.png");

    ui->label->setPixmap(QPixmap::fromImage(attr1));

}
