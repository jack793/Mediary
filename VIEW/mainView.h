#ifndef SUPERWIDGET_H
#define SUPERWIDGET_H

#include <QWidget>
#include <QDesktopWidget>

class SuperWidget : public QWidget {
    Q_OBJECT
private:
    void centraWidget();
public:
    explicit SuperWidget(QWidget *parent = 0);
    virtual ~SuperWidget();
    virtual void caricaGrafica() =0;
};

#endif // SUPERWIDGET_H
