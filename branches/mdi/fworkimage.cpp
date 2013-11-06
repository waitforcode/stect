#include "fworkimage.h"
#include "ui_fworkimage.h"

fWorkImage::fWorkImage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fWorkImage)
{
    ui->setupUi(this);
}

fWorkImage::~fWorkImage()
{
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

}
