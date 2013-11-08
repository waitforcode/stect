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
//    this->setWindowTitle(img.);
//    setChannel(Y);
}

void fWorkImage::visualAttack(){

    QImage attr1 = ui->label->pixmap()->toImage();
    for(int j=0;j<attr1.height();j++)
        for(int i=0;i<attr1.width();i++){
            QRgb p = attr1.pixel(i,j);
            QRgb np;
            if(attr1.hasAlphaChannel())
                np = qRgba((qRed(p) & 1)*255,
                           (qGreen(p)&1)*255,
                           (qBlue(p)&1)*255,
                            (qAlpha(p)&1)*255);
            else
                np = qRgb((qRed(p)&1)*255,
                           (qGreen(p)&1)*255,
                           (qBlue(p)&1)*255);

            attr1.setPixel(i,j, np);
        }
//    attr1.save("test.png");

    ui->label->setPixmap(QPixmap::fromImage(attr1));

    state|=VisualAttack;

}

void fWorkImage::reset(){
    if(image)
        ui->label->setPixmap(*image);

    state = 0;
}

/*void fWorkImage::x_2_attack(QString filename){

    QImage orig;

    if(!orig.load(filename)){
        return;
    }

    int byte = 0;
    int height=220;
    int width = orig.byteCount()/100;

    const uchar* data = orig.bits();

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


//Расчет среднего значения наименее значащего бита для интервала


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
*/
#include <QDebug>
void fWorkImage::setChannel(Channel channel){
    QImage *chan = NULL;
    switch(channel){
    case Red:
        chan= setRChannel();
        break;
    case Green:
        chan= setGChannel();
        break;
    case Blue:
        chan= setBChannel();
        break;
    case Y:
        chan = setYChannel();
        break;
    case Cb:
        chan = setCbChannel();
        break;
    case Cr:
        chan = setCrChannel();
        break;
    }    
    if(image)
        ui->label->setPixmap(QPixmap::fromImage(*chan));
    if(state & VisualAttack)
        visualAttack();
    delete chan;
}

QImage* fWorkImage::setRChannel(){
    QImage *attr1 = new QImage(image->toImage());

    for(int j=0;j<attr1->height();j++)
        for(int i=0;i<attr1->width();i++){
            QRgb p = attr1->pixel(i,j);
            attr1->setPixel(i,j,  qRgb(qRed(p), 0, 0));
        }

    return attr1;
}

QImage* fWorkImage::setGChannel(){
    QImage *attr1 = new QImage(image->toImage());

    for(int j=0;j<attr1->height();j++)
        for(int i=0;i<attr1->width();i++){
            QRgb p = attr1->pixel(i,j);
            attr1->setPixel(i,j,  qRgb(0, qGreen(p), 0));
        }

    return attr1;
}

QImage* fWorkImage::setBChannel(){

    QImage *attr1 = new QImage(image->toImage());

    for(int j=0;j<attr1->height();j++)
        for(int i=0;i<attr1->width();i++){
            QRgb p = attr1->pixel(i,j);
            attr1->setPixel(i,j,  qRgb(0, 0, qBlue(p)));
        }

    return attr1;
}

QImage* fWorkImage::setYChannel(){

    QImage *attr1 =  new QImage(image->toImage());

    for(int j=0;j<attr1->height();j++)
        for(int i=0;i<attr1->width();i++){
            QRgb p = attr1->pixel(i,j);
            int pixel = 0.299*qRed(p) + 0.578 *qGreen(p) +0.114 * qBlue(p);
            attr1->setPixel(i,j, qRgb(pixel, pixel, pixel));
        }
    return attr1;
}


QImage* fWorkImage::setCbChannel(){

    QImage *attr1 =  new QImage(image->toImage());

    for(int j=0;j<attr1->height();j++)
        for(int i=0;i<attr1->width();i++){
            QRgb p = attr1->pixel(i,j);
            uint pixel = 128 - 0.168736*qRed(p) - 0.331264 *qGreen(p) +0.5 * qBlue(p);
            attr1->setPixel(i,j, qRgb(pixel, pixel, pixel));
        }
    return attr1;
}

QImage* fWorkImage::setCrChannel(){

    QImage *attr1 =  new QImage(image->toImage());

    for(int j=0;j<attr1->height();j++)
        for(int i=0;i<attr1->width();i++){
            QRgb p = attr1->pixel(i,j);
            int pixel = 128 + 0.5*qRed(p) - 0.418688 *qGreen(p) - 0.081312 * qBlue(p);
            attr1->setPixel(i,j, qRgb(pixel, pixel, pixel));
        }
    return attr1;
}
