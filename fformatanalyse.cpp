#include "fformatanalyse.h"
#include "ui_fformatanalyse.h"

FFormatAnalyse::FFormatAnalyse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FFormatAnalyse)
{
    ui->setupUi(this);

}

FFormatAnalyse::~FFormatAnalyse()
{
    delete ui;
}

void FFormatAnalyse::changeEvent(QEvent *e)
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

void FFormatAnalyse::appended(bool status){
    if(status){
        ui->label_3->setPixmap(QPixmap(":/small/dialog-ok.png"));
        ui->toolButton->setEnabled(true);
    }else{
        ui->label_3->setPixmap(QPixmap(":/small/dialog-cancel.png"));
        ui->toolButton->setEnabled(false);
        ui->tabWidget->removeTab(1);
    }
}

void FFormatAnalyse::setAppended(QByteArray text){
    ui->textBrowser->setText(QString::fromLocal8Bit(text));
    ui->tabWidget->setCurrentIndex(0);

}
