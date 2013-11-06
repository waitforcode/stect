#ifndef FINFO_H
#define FINFO_H

#include <QWidget>

namespace Ui {
    class fInfo;
}

class fInfo : public QWidget {
    Q_OBJECT
public:
    fInfo(QWidget *parent = 0);
    ~fInfo();
    void setFileName(QString fn);
    void setWidth(int orig);
    void setHeight(int orig);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::fInfo *ui;
};

#endif // FINFO_H
