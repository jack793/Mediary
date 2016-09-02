#include "loginView.h"

//-------------------------COSTRUTTORI------------------------

loginView::loginView(MainView* parent): MainView(parent){
    loadGraphic();
}

loginView::~loginView() {}

//-------------------------PV METHOD-----------------------

void loginView::loadGraphic(){
    setWindowTitle("Login - Mediary");
    
    mainLayout = new QVBoxLayout;
    mainGBox= new QGroupBox;
    
    QVBoxLayout* boxLayout= new QVBoxLayout;
    
    usernameEdit= new QLineEdit;
    QLabel* usernameLabel= new QLabel("Username");
    
    passwordEdit = new QLineEdit;
    QLabel* passwordLabel= new QLabel("Password");
    passwordEdit->setEchoMode(QLineEdit::Password); //Display platform-dependent password mask characters instead of the characters actually entered.
    
    QPushButton* loginButton= new QPushButton("Effettua login");
    QPushButton* goToRegistrationButton= new QPushButton("Registra utente");
    
    boxLayout->addWidget(usernameLabel);
    boxLayout->addWidget(usernameEdit);
    boxLayout->addWidget(passwordLabel);
    boxLayout->addWidget(passwordEdit);
    boxLayout->addSpacing(20);
    
    boxLayout->addWidget(loginButton);
    boxLayout->addWidget(goToRegistrationButton);
    
    mainGBox->setLayout(boxLayout);
    mainLayout->addWidget(mainGBox);
    
    setLayout(mainLayout);
    
    connect(loginButton,SIGNAL(clicked()),this,SLOT(tryLogin()));
    connect(usernameEdit,SIGNAL(returnPressed()),this,SLOT(tryLogin()));
    connect(passwordEdit,SIGNAL(returnPressed()),this,SLOT(tryLogin()));
    
    connect(goToRegistrationButton,SIGNAL(clicked()),this,SLOT(openRegistration()));
}

//-------------------------PUBLIC SLOTS------------------------

void loginView::tryLogin(){
    
    /*if(usernameEdit->text()==""){
        dialMessage= new DialogMessage("Controllo login","E' necessario inserire uno USERNAME per loggarsi","Ok");
        dialMessage->show();
    }
    else if(passwordEdit->text()==""){
        dialMessage= new DialogMessage("Controllo login","E' necessario inserire una PASSWORD per loggarsi","OK");
        dialMessage->show();
    }
    
    else if(!ptdb->matchUser(usernameEdit->text()))
    {
        dialMessage=new DialogMessage("Controllo login","Username o password inseriti NON CORRETTI","Riprova");
        dialMessage->show();
    }
    else //esiste username
    {
        const User* u=ptdb->getUser(usernameEdit->text(),passwordEdit->text());
        if(!u){ //non esiste un utente con quella pwd
            dialMessage=new DialogMessage("Controllo login","Username o password inseriti NON CORRETTI","Riprova");
            dialMessage->show();
        }
    
        //else //login corretta
            emit signalLogin(usernameEdit->text(),passwordEdit->text());
    }*/
    emit signalLogin(usernameEdit->text(),passwordEdit->text());
}

void loginView::openRegistration(){
    emit signalGoRegistration();
}
