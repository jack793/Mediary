#include "userDataView.h"

//-------------------------COSTRUTTORI------------------------

userDataView::userDataView(const User* u, MainView* parent): user(u), MainView(parent){
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
    
    QFont usn("Verdana", 25);
    
    mainLayout= new QVBoxLayout;
    
    usernameEdit= new QLineEdit(user->getUsername());
    QLabel* usernameLabel= new QLabel("Username:");
    usernameLabel->setFont(usn);
    
    /*passwordEdit= new QLineEdit(user->getPsw());
    QLabel* passwordLabel= new QLabel("Password:");*/
    
    nameEdit = new QLineEdit(user->getName());
    QLabel* nameLabel= new QLabel("Nome:");
    
    surnameEdit= new QLineEdit(user->getSurname());
    QLabel* surnameLabel= new QLabel("Cognome:");
    
    sexButtonG=new QButtonGroup;
    QLabel* sexLabel=new QLabel("Sesso:");    
    sexM=new QRadioButton("Maschio");
    sexF=new QRadioButton("Femmina");  
    if(sexM->isChecked()){
        sexM->setChecked(true);
        sexF->setCheckable(true);
    }
    else{
        sexF->setChecked(true);
        sexM->setCheckable(true);
    }     
    sexButtonG->addButton(sexM);
    sexButtonG->addButton(sexF);
    
    QPushButton* confirmButton= new QPushButton("Conferma modifiche");
    QPushButton* cancelButton= new QPushButton("Annulla modifiche");
    
    mainLayout->addWidget(usernameLabel);
    mainLayout->addWidget(usernameEdit);
    mainLayout->addWidget(nameLabel);
    mainLayout->addWidget(nameEdit);
    mainLayout->addWidget(surnameLabel);
    mainLayout->addWidget(surnameEdit);
    mainLayout->addSpacing(40);
    
    mainLayout->addWidget(confirmButton);
    mainLayout->addWidget(cancelButton);
    
    setLayout(mainLayout);
    
    connect(confirmButton,SIGNAL(clicked()),this,SLOT(confirmChanges()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(cancelChanges()));
    
}

//-------------------------PUBLIC SLOTS--------------------------

void userDataView::confirmChanges(){
    std::string username=usernameEdit->text().toStdString();
    std::string name=nameEdit->text().toStdString();
    std::string surname=surnameEdit->text().toStdString();
    bool sex=false;
    if(sexM->isChecked())
        sex=true;
    
    if(username.size()==0){
        dialMessage= new DialogMessage("Controllo modifiche","Riempire il campo USERNAME","Ok");
        dialMessage->show();
    }
    else if(name.size()==0){
        dialMessage= new DialogMessage("Controllo modifiche","Riempire il campo NOME","Ok");
        dialMessage->show();
    }
    else if(surname.size()==0){
        dialMessage= new dialMessage("Controllo modifiche","Riempire il campo COGNOME","Ok");
        dialMessage->show();
    }
    else
        emit signalConfirm(username,name,surname,sex);
    
}

void userDataView::cancelChanges(){
    emit signalCancel();
}

