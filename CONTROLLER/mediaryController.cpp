#include "mediaryController.h"

//-------------------------COSTRUTTORI------------------------

mediaryController::mediaryController(Database* db, loginView* l, userController* c, QObject* parent):
           QObject(parent), usersDB(db), startUI(l), uController(c)
{
    l->show();
    
    connect(startUI,SIGNAL(signalLogin(const QString& ,const QString& )),this,SLOT(verifyLogin(const QString& ,const QString& )));
    connect(startUI,SIGNAL(signalGoRegistration()),this,SLOT(openRegistrationView()));
}

//-------------------------PUBLIC SLOTS------------------------

//--------OPEN
void mediaryController::openLoginView(){
    delete uController;
    uController=0;
    
    startUI->show();
}

void mediaryController::openRegistrationView(){
    registrationUI= new registrationView;
    
    startUI->hide(); //nascondo login
    registrationUI->show(); //apro reg
    
    connect(registrationUI,SIGNAL(signalRegister(const QString& ,const QString& ,const QString& ,const QString& ,bool )),this,SLOT(userRegistration(const QString& u,const QString& p,const QString& n,const QString& s)));
    connect(registrationUI,SIGNAL(signalClose()),this,SLOT(closeRegistrationView()));
}

//--------REGISTRATION

void mediaryController::userRegistration(const QString& username, const QString& psw, const QString& name, const QString& surname, bool sex){
    if(!usersDB->matchUser(username)){
        User* newUser= new User(username,psw,name,surname,sex);
        usersDB->addUser(newUser);
        usersDB->saveUserDb();
        
        dialMessage= new DialogMessage("Info","Registrazione nuovo utente avvenuta con successo!","Ok");
        dialMessage->setWindowIcon(QIcon(":/Icons/info_light.png"));
        dialMessage->show();
        
        closeRegistrationView();
    }
    else{
        dialMessage= new DialogMessage("Attenzione","USERNAME già utilizzato","Modifica");
        dialMessage->setWindowIcon(QIcon(":/Icons/warning_dark.png"));
        dialMessage->show();
    }
}

void mediaryController::closeRegistrationView(){
    registrationUI->hide();
    delete registrationUI; //distruggiamo la view di registrazione che non serve più
    startUI->show(); // e torniamo alla login iniziale
}

//--------VERIFY
void mediaryController::verifyLogin(const QString& usn, const QString& psw){
    if(usersDB->verifyUser(usn,psw)) //se login valida
    {
        uController= new userController(const_cast<User*>(usersDB->getUser(usn,psw)));
        if(uController){
            connect(uController,SIGNAL(signalHome()),this,SLOT(openLoginView()));
            startUI->hide(); //chiude la schermata iniziale di login
            uController->openUserView(); //ed apre quella dedicata a quello user
        }
    }
    else{ //se login non valida
        dialMessage= new DialogMessage("Controllo login","USERNAME o PASSWORD inseriti non corretti","Ok");
        dialMessage->setWindowIcon(QIcon(":/Icons/warning_dark2.png"));
        dialMessage->show();
    }
}
