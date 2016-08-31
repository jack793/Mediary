#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QButtonGroup>
#include <QRadioButton>
#include <QLineEdit>

#include "mainView.h"
#include "dialogMessage.h"

#include "MODEL/Database.h"

class loginView: public MainView
{
    Q_OBJECT
private:
    Database* ptdb;
    
    //Graphics
    QVBoxLayout* mainLayout;
    QGroupBox* mainGBox;
    
    //Input login
    QLineEdit* usernameEdit;
    QLineEdit* passwordEdit;
    
    //Messaggi in output
    DialogMessage* dialMessage;
    
public:
    explicit loginView(MainView* =0);
    ~loginView();
    
    //Implement pv method
    virtual void loadGraphic();
    
public slots:
    void tryLogin();
    void openRegistration();
    
signals:
    void signalLogin(const QString& ,const QString& );
    void signalGoRegistration();
};

#endif // LOGINVIEW_H
