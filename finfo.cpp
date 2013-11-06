#include "finfo.h"
#include "ui_finfo.h"

fInfo::fInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fInfo)
{
    ui->setupUi(this);
}

fInfo::~fInfo()
{
    delete ui;
}

void fInfo::changeEvent(QEvent *e)
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

void fInfo::setFileName(QString fn){ui->label_4->setText(fn);};
void fInfo::setWidth(int orig){ui->label_5->setText(QString("%1").arg(orig));};
void fInfo::setHeight(int orig){ui->label_6->setText(QString("%1").arg(orig));};
