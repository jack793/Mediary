#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>
#include <QDesktopWidget>

class MainView : public QWidget {
    Q_OBJECT

public:
    MainView(QWidget* parent=0);
    virtual ~MainView();
    void centerWidget();
    virtual void loadGraphic() =0;
};

#endif // MAINVIEW_H
