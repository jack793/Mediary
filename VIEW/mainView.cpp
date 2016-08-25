#include "mainView.h"

//-------------------------COSTRUTTORI------------------------

MainView::MainView(QWidget* parent): QWidget(parent) {this->centerWidget();}

MainView::~MainView() {}

//-------------------------METODI------------------------

void MainView::centerWidget(){
    int w=frameGeometry().width();
    int h=frameGeometry().height()+150;
    QDesktopWidget wid;
    int sW=wid.screen()->width();
    int sH=wid.screen()->height();
    int x=static_cast<int>((sW-w)/2);
    int y=static_cast<int>((sH-h)/2);
    move(x,y);
}
