#ifndef USERDATAVIEW_H
#define USERDATAVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QButtonGroup>
#include <QRadioButton>
#include <QLineEdit>
#include <QFont>
#include <QVBoxLayout>

#include "mainView.h"
#include "dialogMessage.h"

#include "MODEL/Database.h"
#include "MODEL/User.h"

class userDataView: public MainView
{
    Q_OBJECT
private:
    //Graphic
    QVBoxLayout* mainLayout;
    
    //Info e modifiche
    QLineEdit* usernameEdit;
    QLineEdit* nameEdit;
    QLineEdit* surnameEdit;
    QLineEdit* sexEdit;
    QVBoxLayout* sexButtonsLay;
    QRadioButton* sexM;
    QRadioButton* sexF;
    
    //Output messages
    DialogMessage* dialMessage;
    
    //Dati dal model 
    Database* userDB;
    const User* user;
    
public:
    userDataView(const User* u=0, MainView* parent=0);
    ~userDataView();
    
    void closeEvent(QCloseEvent* );
    //Questo gestore di eventi viene chiamato con l'evento dato quando Qt riceve una richiesta
    //di chiusura della finestra per un widget di alto livello da sistema a finestre .
    
    //Implement pv method
    virtual void loadGraphic();
    
public slots:
    void confirmChanges();
    void cancelChanges();
    
signals:
    void signalConfirm(const QString& ,const QString& ,const QString& ,const QString& );
    void signalCancel();
};

#endif // USERDATAVIEW_H
