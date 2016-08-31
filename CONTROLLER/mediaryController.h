#ifndef MEDIARYCONTROLLER_H
#define MEDIARYCONTROLLER_H

#include <QObject>

#include "MODEL/Database.h"
#include "VIEW/loginView.h"
#include "VIEW/registrationView.h"
#include "VIEW/dialogMessage.h"

#include "userController.h"


class mediaryController:public QObject
{
    Q_OBJECT
private:
    Database* usersDB;
    loginView* startUI;
    registrationView* registrationUI;
    userController* uController;
    
    DialogMessage* dialMessage;
    
public:
    explicit mediaryController(Database* , loginView* =0, userController* =0, QObject* =0);
        //la view registrazione si inizializza quando si apre
    
public slots:
    //Open
    void openLoginView();
    void openRegistrationView();
    
    //Registration
    void userRegistration(const QString& u, const QString& p, const QString& n, const QString& s, bool);
    void closeRegistrationView();
    
    //Verify
    void verifyLogin(const QString& usn,const QString& psw);
};

#endif // MEDIARYCONTROLLER_H
