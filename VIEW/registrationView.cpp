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

//-------------------------PV METHOD------------------------

void registrationView::loadGraphic(){
    setWindowTitle("Registrazione - Mediary");
    
    setFixedWidth(300);
    
    centerWidget();
    
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
    
    sexButtonsLay=new QVBoxLayout;
    QLabel* sexLabel=new QLabel("Seleziona sesso:");
    sexM=new QRadioButton("Maschio");
    sexM->setChecked(true);
    sexF=new QRadioButton("Femmina");
    sexButtonsLay->addWidget(sexM);
    sexButtonsLay->addWidget(sexF);
    QPushButton* regButton= new QPushButton("Registrati");
    QPushButton* undoRegButton= new QPushButton("Indietro");
    
    QLabel* welcomeReg=new QLabel("Benvenuto nella registrazione. \nCompila tutti i campi della form per \naggiungere un nuovo utente.");
    
    boxLayout->addWidget(welcomeReg,0,Qt::AlignLeft);
    boxLayout->addSpacing(30);
    boxLayout->addWidget(usernameLabel);
    boxLayout->addWidget(usernameEdit);
    boxLayout->addWidget(passwordLabel);
    boxLayout->addWidget(passwordEdit);
    boxLayout->addWidget(nameLabel);
    boxLayout->addWidget(nameEdit);
    boxLayout->addWidget(surnameLabel);
    boxLayout->addWidget(surnameEdit);
    boxLayout->addWidget(sexLabel);
    boxLayout->addLayout(sexButtonsLay);
    
    boxLayout->addWidget(regButton);
    boxLayout->addWidget(undoRegButton);
    
    connect(regButton,SIGNAL(clicked()),this,SLOT(checkRegistration()));
    connect(undoRegButton,SIGNAL(clicked()),this,SLOT(cancelRegistration()));
    
    mainGBox->setLayout(boxLayout);
    mainLayout->addWidget(mainGBox);
    
    setLayout(mainLayout);
        
}

//-------------------------PUBLIC SLOTS------------------------

void registrationView::checkRegistration(){
    
    QString password=passwordEdit->text();
    QString sex="";
    ptdb= new Database();
    
    if(sexM->isChecked())
        sex="Maschio";
    else if(sexF->isChecked())
        sex="Femmina";
        
    if(usernameEdit->text()==""){
        dialMessage=new DialogMessage("Controllo dati","Non hai compilato il campo USERNAME","Indietro");
        dialMessage->show();
    }    
    else if(ptdb->matchUser(usernameEdit->text())){
        dialMessage=new DialogMessage("Controllo dati","USERNAME già utilizzato, inseriscine uno diverso","Indietro");
        dialMessage->show();
    }
    else if(passwordEdit->text()==""){
        dialMessage=new DialogMessage("Controllo dati","Non hai compilato il campo PASSWORD","Indietro");
        dialMessage->show();
    }
    else if(password.size()<4){
        dialMessage=new DialogMessage("Controllo dati","La password deve avere almeno 4 caratteri","Indietro");
        dialMessage->show();
    }
    else if(nameEdit->text()==""){
        dialMessage=new DialogMessage("Controllo dati","Non hai compilato il campo NOME","Indietro");
        dialMessage->show();
    }
    else if(surnameEdit->text()==""){
        dialMessage=new DialogMessage("Controllo dati","Non hai compilato il campo COGNOME","Indietro");
        dialMessage->show();
    }
    
    else //input dati corretto
        emit signalRegister(usernameEdit->text(),passwordEdit->text(),nameEdit->text(),surnameEdit->text(),sex);
}

void registrationView::cancelRegistration(){
    emit signalClose();
}

