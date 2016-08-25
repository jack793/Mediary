#include "dialogmessage.h"

DialogMessage::DialogMessage(std::string t,std::string m,std::string b){
    this->setWindowTitle(QString::fromStdString(t));
    this->setModal(true);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    vLay=new QVBoxLayout(this);
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);
    lblMessaggio=new QLabel(QString::fromStdString(m),this);
    btnConferma=new QPushButton(QString::fromStdString(b),this);
    btnConferma->setFixedWidth(125);
    vLay->addWidget(lblMessaggio);
    vLay->addWidget(btnConferma);
    vLay->setAlignment(btnConferma,Qt::AlignCenter);
    connect(btnConferma,SIGNAL(clicked()),this,SLOT(close()));
}

DialogMessage::~DialogMessage(){}

void DialogMessage::chiudi(){
    emit signalChiudi();
}
