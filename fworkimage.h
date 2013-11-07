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
        Blue

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
};

#endif // FWORKIMAGE_H
