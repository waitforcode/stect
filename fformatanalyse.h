#ifndef FFORMATANALYSE_H
#define FFORMATANALYSE_H

#include <QWidget>

namespace Ui {
    class FFormatAnalyse;
}

class FFormatAnalyse : public QWidget {
    Q_OBJECT
public:
    FFormatAnalyse(QWidget *parent = 0);
    ~FFormatAnalyse();

    void appended(bool);
    void setAppended(QByteArray text);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FFormatAnalyse *ui;
};

#endif // FFORMATANALYSE_H
