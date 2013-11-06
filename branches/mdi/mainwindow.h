#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>

#include <QImage>
#include "finfo.h"
#include "fworkimage.h"


namespace Ui {
class MainWindow;
}

//class QMdiSubWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void loadOrig(QString filename);
    void visual_attack(QString filename);
    void x_2_attack(QString filename);
    ~MainWindow();

protected slots:
    void load();
    void save();
    
private:
    Ui::MainWindow *ui;
    QString fileName;
    QMdiSubWindow * info;
    fWorkImage* active;

private slots:
    void on_action_8_triggered();
    void on_action_5_triggered(bool checked);
};

#endif // MAINWINDOW_H
