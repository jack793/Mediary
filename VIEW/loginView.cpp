#include "loginView.h"

//-------------------------COSTRUTTORI------------------------

loginView::loginView(MainView* parent): MainView(parent){
    loadGraphic();
}

loginView::~loginView() {}

//-------------------------PV METHOD-----------------------

loginView::loadGraphic(){
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
    
    boxLayout->addWidget(loginButton);
    boxLayout->addWidget(goToRegistrationButton);
    
    mainGBox->setLayout(boxLayout);
    mainLayout->addWidget(mainGBox);
    
    setLayout(mainLayout);
    
    connect(loginButton,SIGNAL(clicked()),this,SLOT(tryLogin()));
    connect(goToRegistrationButton,SIGNAL(clicked()),this,SLOT(openRegistration()));
}

//-------------------------PUBLIC SLOTS------------------------

void loginView::tryLogin(){
    std::string username=usernameEdit->text().toStdString();
    std::string password=passwordEdit->text().toStdString();
    
    if(username.size()==0){
        dialMessage= new DialogMessage("Controllo login","E' necessario inserire uno USERNAME per loggarsi","Ok");
        dialMessage->show();
    }
    else if(password.size()==0){
        dialMessage= new DialogMessage("Controllo login","E' necessario inserire una PASSWORD per loggarsi","OK");
        dialMessage->show();
    }
    
    else if(!ptdb->matchUser(username))
    {
        dialMessage=new DialogMessage("Controllo login","Username o password inseriti NON CORRETTI","Riprova");
        dialMessage->show();
    }
    else if //esiste username
    {
        User* u=ptdb->getUser(username,password);
        if(!u){ //non esiste un utente con quella pwd
            dialMessage=new DialogMessage("Controllo login","Username o password inseriti NON CORRETTI","Riprova");
            dialMessage->show();
        }
    
        else //login corretta
            emit signalLogin(username,password);
    }
}

void loginView::openRegistration(){
    emit signalGoRegistration();
}
