#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


//    QString filename= "/home/procurator/imgcomp.png";
    QString filename= "/home/procurator/dota.png";


    loadOrig(filename);
    visual_attack(filename);
    x_2_attack(filename);

    connect(ui->action, SIGNAL(triggered()), SLOT(load()));
    connect(ui->action_2, SIGNAL(triggered()), SLOT(save()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::visual_attack(QString filename){
    QImage *attr1 = new QImage();
    if (!attr1->load(filename)){
        qDebug()<<"error";
        return;
    }

    for(int j=0;j<attr1->height();j++)
        for(int i=0;i<attr1->width();i++){
            QRgb p = attr1->pixel(i,j);
            QRgb np;
            if(attr1->hasAlphaChannel())
                np = qRgba((qRed(p)-((int)(qRed(p)/2))*2)*255,
                           (qGreen(p)-((int)(qGreen(p)/2))*2)*255,
                           (qBlue(p)-((int)(qBlue(p)/2))*2)*255,
                            (qAlpha(p)-((int)(qAlpha(p)/2))*2)*255);
            else
                np = qRgb((qRed(p)-((int)(qRed(p)/2))*2)*255,
                           (qGreen(p)-((int)(qGreen(p)/2))*2)*255,
                           (qBlue(p)-((int)(qBlue(p)/2))*2)*255);

            attr1->setPixel(i,j, np);
        }
    attr1->save("test.png");

    ui->label->setPixmap(QPixmap::fromImage(*attr1));
}

/*
 Обработка параметров исследуемого изображения.
*/

void MainWindow::loadOrig(QString filename){
    ui->label_2->setPixmap(QPixmap(filename));
    QImage orig;
    if(!orig.load(filename)){
        return;
    }
    ui->tableWidget->setRowCount(7);
    ui->tableWidget->setItem(0,0,new QTableWidgetItem(QString::fromLocal8Bit("Имя файла"))
                             );
    ui->tableWidget->setItem(0,1,new QTableWidgetItem(filename)
                             );

    ui->tableWidget->setItem(1,0,new QTableWidgetItem(QString::fromLocal8Bit("Ширина"))
                             );
    ui->tableWidget->setItem(1,1,new QTableWidgetItem(QString("%1").arg(orig.width()))
                             );

    ui->tableWidget->setItem(2,0,new QTableWidgetItem(QString::fromLocal8Bit("Высота"))
                             );
    ui->tableWidget->setItem(2,1,new QTableWidgetItem(QString("%1").arg(orig.height()))
                             );

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
}

/*
  Реализация атаки хи-квадрат
*/

void MainWindow::x_2_attack(QString filename){

    QImage orig;

    if(!orig.load(filename)){
        return;
    }

    int byte = 0;
    int height=220;
    int width = orig.byteCount()/100;

    const uchar* data = orig.constBits();

//    qDebug()<<width;

    if(width>1030){
        height = ((int) width/1030+1)*220;
        width = 1030;
    }
    QImage graph(width,height, orig.format());
    graph.fill(Qt::black);

    width = orig.byteCount()/100;

    for(int i=10;i<width;i++){ //Обработка одной полосы графика
        int offset = (int)(i/1030);

        graph.setPixel(i-offset*1030, 110 + (offset)*220, qRgb(0,0,255)); //Ось х

        if(i%102 == 10) //Вертикальная сетка
            for(int j=0; j<220;j++)
                graph.setPixel(i-offset*1030,j+offset*220,qRgb(0,0,255));

/*
Расчет среднего значения наименее значащего бита для интервала
*/

        int avg=0;
        for(int j = 0; j<100;j++){
            avg += *(data+byte+j)%2;
        }
        byte+=10;
        graph.setPixel(i-offset*1030,(int)(avg*220/100) + offset*220, qRgb(0,255,0));
    }

    graph.save("graph.PNG");
    ui->label_3->setPixmap(QPixmap::fromImage(graph));

}

void MainWindow::load(){
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "/home",
                                                     tr("Images (*.png *.xpm *.jpg *.bmp *.tiff)"));

    if(fileName.isEmpty())
        return;
    loadOrig(fileName);
    visual_attack(fileName);
    x_2_attack(fileName);

}

void MainWindow::save(){
    qDebug()<<fileName;
    ui->label_2->pixmap()->save(fileName);
    ui->label->pixmap()->save(fileName+"_LSBs.png");
    ui->label_3->pixmap()->save(fileName+"_X.png");
    qDebug()<<"end save";
}
