#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QImage>

namespace Ui {
class MainWindow;
}

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
};

#endif // MAINWINDOW_H
