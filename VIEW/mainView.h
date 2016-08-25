#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>
#include <QDesktopWidget>

class MainView : public QWidget {
    Q_OBJECT
private:
    void centerWidget();
   
public:
    explicit MainView(QWidget* parent=0);
    virtual ~MainView();
    virtual void loadGraphic() =0;
};

#endif // MAINVIEW_H
