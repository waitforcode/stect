#include "finfo.h"
#include "ui_finfo.h"
#include <QDebug>

fInfo::fInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fInfo)
{
    ui->setupUi(this);
    on_comboBox_currentIndexChanged(0);

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

void fInfo::on_comboBox_currentIndexChanged(int index)
{
    switch(index){
    case 0:
        ui->listWidget->selectAll();
        ui->listWidget->item(0)->setText("Red (1)");
        ui->listWidget->item(1)->setText("Green (2)");
        ui->listWidget->item(2)->setText("Blue (3)");
        break;
    case 1:
        ui->listWidget->selectAll();
        ui->listWidget->item(0)->setText("Luma (1)");
        ui->listWidget->item(1)->setText("blue-difference (2)");
        ui->listWidget->item(2)->setText("red-difference (3)");
        break;
    }
}

void fInfo::on_listWidget_itemClicked(QListWidgetItem* item)
{
    int index = ui->listWidget->row(item);
    if(index == ui->listWidget->count()-1){
        ui->listWidget->selectAll();
        emit allChannels();
    }else{
        ui->listWidget->clearSelection();
        ui->listWidget->setItemSelected(item, true);
        if(ui->comboBox->currentIndex() == 1)
            index += 4;
        emit setChannel(index);
    }

}
