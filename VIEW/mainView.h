#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>
#include <QDesktopWidget>

class MainView : public QWidget {
    Q_OBJECT
private:
    void centraWidget();
   
public:
    explicit MainView(QWidget *parent = 0);
    virtual ~MainView();
    virtual void caricaGrafica() =0;
};

#endif // MAINVIEW_H
