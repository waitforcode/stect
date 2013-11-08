#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fInfo *finfo = new fInfo(ui->mdiArea);
    info = ui->mdiArea->addSubWindow(finfo,Qt::Widget);
    info->setFixedHeight(200);
    info->setFixedWidth(362);
    info->move(width()-362, height()-200);
    info->move(362, 200);

    connect(finfo, SIGNAL(allChannels()), this, SLOT(allChannels()));
    connect(finfo, SIGNAL(setChannel(int)),this, SLOT(setChannel(int)));


//    info->hide();

    connect(ui->action, SIGNAL(triggered()), SLOT(load()));
    connect(ui->action_2, SIGNAL(triggered()), SLOT(save()));
    active = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent ( QResizeEvent * event ){
    info->move(event->size().width()-392, event->size().height()-320);
}

/*
 Обработка параметров исследуемого изображения.
*/

void MainWindow::loadOrig(QString filename){
    QImage orig;
    if(!orig.load(filename)){
        return;
    }
    fWorkImage *task = new fWorkImage(ui->mdiArea);
    QMdiSubWindow *sub =  ui->mdiArea->addSubWindow(task);
    task->setWindowTitle(filename);
    task->setPixmap(QPixmap(filename));
    task->show();

    sub->setMinimumSize(orig.size().width(), orig.height()+30);

    active = task;

    fInfo* fi = (fInfo*)info->widget();
    fi->setFileName(filename);
    fi->setWidth(orig.width());
    fi->setHeight(orig.height());

/*
    ui->tableWidget->setItem(3,0,new QTableWidgetItem(QString::fromLocal8Bit("Число цветов"))
                             );
    ui->tableWidget->setItem(3,1,new QTableWidgetItem(QString("%1").arg(orig.colorCount()))
                             );

    ui->tableWidget->setItem(4,0,new QTableWidgetItem(QString::fromLocal8Bit("Глубина цвета"))
                             );
    ui->tableWidget->setItem(4,1,new QTableWidgetItem(QString("%1").arg(orig.depth()))
                             );

    ui->tableWidget->setItem(5,0,new QTableWidgetItem(QString::fromLocal8Bit("Канал яркости"))
                             );
    ui->tableWidget->setItem(5,1,new QTableWidgetItem(QString("%1").arg(orig.hasAlphaChannel()))
                             );

    ui->tableWidget->setItem(6,0,new QTableWidgetItem(QString::fromLocal8Bit("Ч/Б изображение"))
                             );
    ui->tableWidget->setItem(6,1,new QTableWidgetItem(QString("%1").arg(orig.isGrayscale()))
                             );

    ui->tableWidget->resizeColumnsToContents();
    */
}

void MainWindow::load(){
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     ".",
                                                     tr("Images (*.png *.xpm *.jpg *.bmp *.tiff)"));

    if(fileName.isEmpty())
        return;
    loadOrig(fileName);
}

void MainWindow::save(){
}

void MainWindow::on_action_5_triggered(bool checked)
{
    if(checked)
        info->show();
    else
        info->hide();
}


void MainWindow::on_action_8_triggered()
{

}

void MainWindow::on_action_8_triggered(bool checked)
{
    if(active){
        if(checked){
            ui->action_8->setIcon(QIcon(":/images/layer-visible-on.png"));
            active->visualAttack();
        }else{
            ui->action_8->setIcon(QIcon(":/images/layer-visible-off.png"));
            active->reset();
        }
    }
}

void MainWindow::setChannel(int chan){
    if(active){
        active->setChannel((fWorkImage::Channel) chan);
    }

}

void MainWindow::allChannels(){
    if(active){
/*        ui->action_8->setCheckable(false);
        ui->action_8->setIcon(QIcon(":/images/layer-visible-off.png"));
*/        active->reset();
    }
}
