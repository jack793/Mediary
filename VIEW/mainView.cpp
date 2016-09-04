#include "mainView.h"

//-------------------------COSTRUTTORI------------------------

MainView::MainView(QWidget* parent): QWidget(parent) {this->centerWidget();}

MainView::~MainView() {}

//-------------------------METODI------------------------

void MainView::centerWidget(){
    int width = frameGeometry().width();
    int height = frameGeometry().height();
    
    QDesktopWidget wid;
    
    int screenWidth = wid.screen()->width();
    int screenHeight = wid.screen()->height();
    
    setGeometry((screenWidth/2)-(width/2),(screenHeight/2)-(height/2),width,height);
}
