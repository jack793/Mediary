#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <QDateTime>

#include "MODEL/User.h"
#include "VIEW/userView.h"
#include "VIEW/dialogMessage.h"

class userController: public QObject
{
    Q_OBJECT
private:
    userView* userUI;
    User* user;
    
    DialogMessage* dialMessage;
public:
    userController(User* ,QObject* parent=0);
    ~userController();
    
    void openUserView() const;
    
public slots:
    //Save
    void saveSerieTv(const QString& t,unsigned int y,const QString& g,const QString& d,unsigned int s,unsigned int n,unsigned int l);
    void saveFilm(const QString& t,unsigned int y,const QString& g,const QString& p,const QString& d,const QTime& drt);
    
    //Modification
    void modifySerieTv(const QString& t,unsigned int y,const QString& g,const QString& d,unsigned int s,unsigned int n,unsigned int l,int id);
    void modifyFilm(const QString& t,unsigned int y,const QString& g,const QString& p,const QString& d,const QTime& drt,int id);
    void modifyUserData(const QString& u, const QString& n, const QString& s, const QString &sx);
    void deleteMedia(int);
    
    //Close
    void closeUserView();
    
signals:
    void signalHome();
    
};

#endif // USERCONTROLLER_H
