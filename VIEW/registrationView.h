#ifndef REGISTRATIONVIEW_H
#define REGISTRATIONVIEW_H

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

class registrationView: public MainView
{
    Q_OBJECT
private:
    Database* ptdb;
    
    //Graphics
    QVBoxLayout* mainLayout;
    QGroupBox* mainGBox;
    
    //Input form
    QLineEdit* usernameEdit;
    QLineEdit* passwordEdit;
    QLineEdit* nameEdit;
    QLineEdit* surnameEdit;
    QButtonGroup* sexButtonG;
    QRadioButton* sexM;
    QRadioButton* sexF;
    
    //Messaggi in output
    DialogMessage* dialMessage;
    
public:
    registrationView(MainView* parent=0);
    ~registrationView();
    
    void closeEvent(QCloseEvent* );
    
    //Implement pv method
    virtual void loadGraphic();
    
public slots:
    void checkRegistration();
    void cancelRegistration();
   
signals:
    void signalRegister(const QString& ,const QString& ,const QString& ,const QString& ,bool );
    void signalClose();
};

#endif // REGISTRATIONVIEW_H
