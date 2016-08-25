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

#include "MODEL/User.h"

class userDataView: public MainView
{
    Q_OBJECT
private:
    //Graphic
    QVBoxLayout* mainLayout;
    
    //Info e modifiche
    QLineEdit* usernameEdit;
    //QLineEdit* passwordEdit;
    QLineEdit* nameEdit;
    QLineEdit* surnameEdit;
    QButtonGroup* sexButtonG;
    QRadioButton* sexM;
    QRadioButton* sexF;
    
    //Output messages
    DialogMessage* dialMessage;
    
    const User* user;
    
public:
    userDataView(const User* u=0, MainView* parent=0);
    ~userDataView();
    
    void closeEvent(QCloseEvent* );
    
    virtual void loadGraphic();
    
public slots:
    void confirmChanges();
    void cancelChanges();
    
signals:
    void signalConfirm(const QString& ,const QString& ,const QString& ,bool );
    void signalCancel();
};

#endif // USERDATAVIEW_H
