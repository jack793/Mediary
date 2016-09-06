#include "userDataView.h"

//-------------------------COSTRUTTORI------------------------

userDataView::userDataView(const User* u, MainView* parent): MainView(parent), user(u){
    loadGraphic();
}

userDataView::~userDataView() {}

//-------------------------METODI------------------------

void userDataView::closeEvent(QCloseEvent *){
    emit signalCancel();
}

//-------------------------PV METHOD------------------------

void userDataView::loadGraphic(){
    setWindowTitle("Gestione dati personali - Mediary");
    
    setFixedWidth(270);
    
    centerWidget();
    
    QFont usn("Verdana", 15);
    
    mainLayout= new QVBoxLayout;
    
    usernameEdit= new QLineEdit(user->getUsername());
    QLabel* usernameLabel= new QLabel("Username:");
    usernameLabel->setFont(usn);
    
    nameEdit = new QLineEdit(user->getName());
    QLabel* nameLabel= new QLabel("Nome:");
    
    surnameEdit= new QLineEdit(user->getSurname());
    QLabel* surnameLabel= new QLabel("Cognome:");
    
    sexEdit= new QLineEdit(user->getSex());
    sexButtonsLay=new QVBoxLayout;
    QLabel* sexLabel=new QLabel("Sesso:");    
    sexM=new QRadioButton("Maschio");
    sexF=new QRadioButton("Femmina");  
    
    if(sexEdit->text()=="Maschio")
        sexM->setChecked(true);
    else
        sexF->setChecked(true);
    
    sexButtonsLay->addWidget(sexM);
    sexButtonsLay->addWidget(sexF);
    
    QPushButton* confirmButton= new QPushButton("Conferma modifiche");
    QPushButton* cancelButton= new QPushButton("Annulla modifiche");
    
    mainLayout->addWidget(usernameLabel);
    mainLayout->addWidget(usernameEdit);
    mainLayout->addWidget(nameLabel);
    mainLayout->addWidget(nameEdit);
    mainLayout->addWidget(surnameLabel);
    mainLayout->addWidget(surnameEdit);
    mainLayout->addWidget(sexLabel);
    mainLayout->addLayout(sexButtonsLay);
    mainLayout->addSpacing(40);
    
    mainLayout->addWidget(confirmButton);
    mainLayout->addWidget(cancelButton);
    
    setLayout(mainLayout);
    
    connect(confirmButton,SIGNAL(clicked()),this,SLOT(confirmChanges()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(cancelChanges()));
    
}

//-------------------------PUBLIC SLOTS--------------------------

void userDataView::confirmChanges(){
   
    QString sex="";
    
    if(sexM->isChecked())
        sex="Maschio";
    else if(sexF->isChecked())
        sex="Femmina";
    
    if(usernameEdit->text()==""){
        dialMessage= new DialogMessage("Controllo modifiche","Riempire il campo USERNAME","Ok");
        dialMessage->show();
    }
    else if(nameEdit->text()==""){
        dialMessage= new DialogMessage("Controllo modifiche","Riempire il campo NOME","Ok");
        dialMessage->show();
    }
    else if(surnameEdit->text()==""){
        dialMessage= new DialogMessage("Controllo modifiche","Riempire il campo COGNOME","Ok");
        dialMessage->show();
    }
    else
        emit signalConfirm(usernameEdit->text(),nameEdit->text(),surnameEdit->text(),sex);
    
}

void userDataView::cancelChanges(){
    emit signalCancel();
}

