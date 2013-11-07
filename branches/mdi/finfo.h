#ifndef FINFO_H
#define FINFO_H

#include <QWidget>

class QListWidgetItem;

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

signals:
    void allChannels();
    void setChannel(int);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::fInfo *ui;

private slots:
    void on_listWidget_itemClicked(QListWidgetItem* item);
    void on_comboBox_currentIndexChanged(int index);
};

#endif // FINFO_H
