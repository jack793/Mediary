#include <QMessageBox>

#include "loginView.h"

//-------------------------COSTRUTTORI------------------------

loginView::loginView(MainView* parent): MainView(parent)
{
    loadGraphic();
}

loginView::~loginView() {}

//-------------------------GET------------------------

QLineEdit* loginView::getUsername() const {return usernameEdit;}
QLineEdit* loginView::getPsw() const {return passwordEdit;}

//-------------------------PV METHOD-----------------------

void loginView::loadGraphic(){
    setWindowTitle("Login - Mediary");
    
    this->setWindowIcon(QIcon(":VIEW/IMGs/Wall.png"));
    
    setFixedSize(800,500);
    
    centerWidget();
    
    mainLayout = new QVBoxLayout;
    mainGBox= new QGroupBox;
    
    QVBoxLayout* boxLayout= new QVBoxLayout;
    
    QLabel* WelcomeMessage= new QLabel("Benvenuto in Mediary");
    WelcomeMessage->setStyleSheet("color: #318bfc");
    WelcomeMessage->setFont(QFont("Aaargh",45,QFont::Bold));
    
    QLabel* WelcomeLabel= new QLabel("Il tuo personale diario multimediale");
    WelcomeLabel->setStyleSheet("color: #318bfc");
    WelcomeLabel->setFont(QFont("Aaargh",15,QFont::Bold));
       
    usernameEdit= new QLineEdit;
    usernameEdit->setPlaceholderText("Inserisci qui il tuo username");
    usernameEdit->setFixedWidth(200);
    usernameEdit->setAlignment(Qt::AlignCenter);   
    QLabel* usernameLabel= new QLabel("Username");
    usernameLabel->setAlignment(Qt::AlignCenter);

    passwordEdit = new QLineEdit;
    passwordEdit->setPlaceholderText("Inserisci qui la tua password");
    passwordEdit->setFixedWidth(200);
    passwordEdit->setAlignment(Qt::AlignCenter);
    QLabel* passwordLabel= new QLabel("Password");
    passwordEdit->setEchoMode(QLineEdit::Password); //Display platform-dependent password mask characters instead of the characters actually entered.
    passwordLabel->setAlignment(Qt::AlignCenter);
    
    QPushButton* loginButton= new QPushButton("Effettua login");
    QPushButton* goToRegistrationButton= new QPushButton("Registra utente");
    
    QPushButton* quit= new QPushButton("Esci",this);
    
    connect(quit,SIGNAL(clicked()),this,SLOT(close()));
    
    boxLayout->addWidget(quit,0,Qt::AlignRight);
   
    boxLayout->addWidget(WelcomeMessage,0,Qt::AlignCenter);
    boxLayout->addWidget(WelcomeLabel,0,Qt::AlignCenter);
    boxLayout->addSpacing(300);
    boxLayout->addWidget(usernameLabel);
    boxLayout->addWidget(usernameEdit,0,Qt::AlignCenter);
    boxLayout->addWidget(passwordLabel);
    boxLayout->addWidget(passwordEdit,0,Qt::AlignCenter);
    boxLayout->addSpacing(50);
        
    boxLayout->addWidget(loginButton,0,Qt::AlignCenter);
        QLabel* op=new QLabel("Oppure");
            op->setFont(QFont("Verdana",9));
        boxLayout->addWidget(op,0,Qt::AlignCenter);    
    boxLayout->addWidget(goToRegistrationButton,0,Qt::AlignCenter);
    
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
    emit signalLogin(usernameEdit->text(),passwordEdit->text());
}

void loginView::openRegistration(){
    emit signalGoRegistration();
}
