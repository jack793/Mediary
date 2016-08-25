#include <iostream>

#include "registrationView.h"

//-------------------------COSTRUTTORI------------------------

registrationView::registrationView(MainView* parent): MainView(parent) {
    loadGraphic();
}

registrationView::~registrationView() {}

//-------------------------METODI------------------------

void registrationView::closeEvent(QCloseEvent* ){
    emit signalClose();
}

//-------------------------PV METODH------------------------

void registrationView::loadGraphic(){
    setWindowTitle("Registrazione - Mediary");
    
    mainLayout = new QVBoxLayout;
    mainGBox = new QGroupBox;
    
    QVBoxLayout* boxLayout= new QVBoxLayout;
    
    usernameEdit= new QLineEdit;
    QLabel* usernameLabel= new QLabel("Inserisci username:");
    
    passwordEdit= new QLineEdit;
    QLabel* passwordLabel= new QLabel("Inserisci password (minimo 4 caratteri):");
    
    nameEdit= new QLineEdit;
    QLabel* nameLabel= new QLabel("Inserisci nome:");
    
    surnameEdit= new QLineEdit;
    QLabel* surnameLabel= new QLabel("Inserisci cognome:");
    
    sexButtonG=new QButtonGroup;
    QLabel* sexLabel=new QLabel("Seleziona sesso:");
    sexM=new QRadioButton("Maschio");
    sexM->setChecked(true);
    sexF=new QRadioButton("Femmina");
    sexButtonG->addButton(sexM);
    sexButtonG->addButton(sexF);
    
    QPushButton* regButton= new QPushButton("Registrati");
    QPushButton* undoRegButton= new QPushButton("Indietro");
    
    boxLayout->addWidget(usernameLabel);
    boxLayout->addWidget(usernameEdit);
    boxLayout->addWidget(passwordLabel);
    boxLayout->addWidget(passwordEdit);
    boxLayout->addWidget(nameLabel);
    boxLayout->addWidget(nameEdit);
    boxLayout->addWidget(surnameLabel);
    boxLayout->addWidget(surnameEdit);
    boxLayout->addWidget(sexButtonG);
    
    connect(regButton,SIGNAL(clicked()),this,SLOT(checkRegistration()));
    connect(undoRegButton,SIGNAL(clicked()),this,SLOT(cancelRegistration()));
    
    mainGBox->setLayout(boxLayout);
    mainLayout->addWidget(mainGBox);
    
    setLayout(mainLayout);
        
}

//-------------------------PUBLIC SLOTS------------------------

void registrationView::checkRegistration(){
    
    std::string username=usernameEdit->text().toStdString();
    std::string password=passwordEdit->text().toStdString();
    std::string name=nameEdit->text().toStdString();
    std::string surname=surnameEdit->text().toStdString();
    bool sex=false;
    if(sexM->isChecked())
        sex=true;
    
    if(username.size()==0){
        dialMessage=new DialogMessage("Controllo dati","Non hai compilato il campo USERNAME","Indietro");
        dialMessage->show();
    }
    else if(ptdb->matchUser(username)){
        dialMessage=new DialogMessage("Controllo dati","Username già utilizzato, inseriscine uno diverso","Indietro");
        dialMessage->show();
    }
    else if(password.size()==0){
        dialMessage=new DialogMessage("Controllo dati","Non hai compilato il campo PASSWORD","Indietro");
        dialMessage->show();
    }
    else if(password.size()<4){
        dialMessage=new DialogMessage("Controllo dati","La password deve avere almeno 4 caratteri","Indietro");
        dialMessage->show();
    }
    else if(name.size()==0){
        dialMessage=new DialogMessage("Controllo dati","Non hai compilato il campo NOME","Indietro");
        dialMessage->show();
    }
    else if(surname.size()==0){
        dialMessage=new DialogMessage("Controllo dati","Non hai compilato il campo COGNOME","Indietro");
        dialMessage->show();
    }
    
    else //input dati corretto
        emit signalRegister(username,password,name,surname,sex);
}

void registrationView::cancelRegistration(){
    emit signalClose();
}

