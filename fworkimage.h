#ifndef FWORKIMAGE_H
#define FWORKIMAGE_H

#include <QWidget>
#include <QPixmap>

namespace Ui {
    class fWorkImage;
}

class fWorkImage : public QWidget {
    Q_OBJECT
public:
    enum Channel{
        Red,
        Green,
        Blue,
        Y=4,
        Cb,
        Cr

    };

    enum Filters{
        VisualAttack=1
    };

public:
    fWorkImage(QWidget *parent = 0);
    ~fWorkImage();

    void setPixmap(QPixmap img);
    void visualAttack();
    void reset();
    void setChannel(Channel channel);

protected:
    void changeEvent(QEvent *e);
    QPixmap* image;

private:
    Ui::fWorkImage *ui;
    QImage* setRChannel();
    QImage* setGChannel();
    QImage* setBChannel();
    QImage* setYChannel();
    QImage* setCbChannel();
    QImage* setCrChannel();

    int state;
};

#endif // FWORKIMAGE_H
