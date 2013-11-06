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
    fWorkImage(QWidget *parent = 0);
    ~fWorkImage();

    void setPixmap(QPixmap img);
    void visualAttack();

protected:
    void changeEvent(QEvent *e);
    QPixmap* image;

private:
    Ui::fWorkImage *ui;
};

#endif // FWORKIMAGE_H
