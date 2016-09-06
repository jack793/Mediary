#ifndef USERVIEW_H
#define USERVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <QIcon>
#include <QMessageBox>
#include <QComboBox>
#include <iostream>

#include "mainView.h"
#include "userDataView.h"
#include "serietvView.h"
#include "filmView.h"

#include "MODEL/Container.h"
#include "MODEL/SerieTV.h"
#include "MODEL/Film.h"

class userView: public MainView
{
    Q_OBJECT
private:
    //Pt al model
    User* user;  
    //Pt alle view
    SerietvView* serieTvView;
    FilmView* filmView;
    userDataView* userInfoView;
    
    //Graphic:
    QVBoxLayout* mainLayout;
    QGroupBox* mainGBox;   
    
    QTableWidget* mediaTable;  
    QComboBox* mediaCBox;
    
    QPushButton* newMediaButton;
    QPushButton* newSerieTvButton;
    QPushButton* newFilmButton; 

public:
    userView(User* u,MainView* parent=0);
    ~userView();
    
    //metodi
    void closeEvent(QCloseEvent* );
    void loadMediaTable(const Container<const Media*>& userMedia);
    //---------const Container<const Media*>& getMedia() const;
    
    //Implement pv method
    virtual void loadGraphic();
    
public slots:
    //Open
    void openMediaBox();
    void openNewSerieTv();
    void openNewFilm();
    void openUserData();
    
    //Close
    void closeMediaBox();
    void closeSerieTvView();
    void closeFilmView();
    void closeUserDataView();
    
    //Save
    void saveSerieTv(const QString& t,unsigned int y,const QString& g,const QString& d,unsigned int s,unsigned int n,unsigned int l);
    void saveFilm(const QString& t,unsigned int y,const QString& g,const QString& p,const QString& d,const QTime& drt);
    
    //Modification
    void modifySerieTv(const QString& t,unsigned int y,const QString& g,const QString& d,unsigned int s,unsigned int n,unsigned int l,int id);
    void modifyFilm(const QString& t,unsigned int y,const QString& g,const QString& p,const QString& d,const QTime& drt,int id);
    void modifyUserData(const QString& u, const QString& n, const QString& s, const QString &sx);
    
    //Features
    void optionMediaTable(int,int);
    void optionMediaLoad(int);
    
    //Logout
    void Logout();
    
signals:
    void signalSaveSerieTv(const QString& t,unsigned int y,const QString& g,const QString& d,unsigned int s,unsigned int n,unsigned int l);
    void signalSaveFilm(const QString& t,unsigned int y,const QString& g,const QString& p,const QString& d,const QTime& drt);
    
    void signalChangeSerieTv(const QString& t,unsigned int y,const QString& g,const QString& d,unsigned int s,unsigned int n,unsigned int l,int id);
    void signalChangeFilm(const QString& t,unsigned int y,const QString& g,const QString& p,const QString& d,const QTime& drt,int id);
    void signalChangeUserData(const QString& u,const QString& n,const QString& s,const QString& sx);
    
    void signalDeleteMedia(int id);
    
    void signalLogout();
};

#endif // USERVIEW_H
