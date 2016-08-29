#ifndef FILMVIEW_H
#define FILMVIEW_H

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QLineEdit>
#include <QTextEdit>
#include <QTimeEdit>

#include "mainView.h"
#include "dialogMessage.h"

#include "MODEL/Film.h"

class FilmView: public MainView
{
    Q_OBJECT
private:
    //For get info
    const Film* film;
    
    //Graphic:
    //Common elements
    QVBoxLayout* mainLayout;
    QLineEdit* titleEdit;
    QDateEdit* yearEdit;
    QLineEdit* genreEdit;
    //Films elements
    QTextEdit* plotEdit;
    QLineEdit* distributionEdit;
    QTimeEdit* durationEdit;
    
    //Output messages
    DialogMessage* dialMessage;
    
public:
    FilmView(const Film* f=0,MainView* parent=0);
    ~FilmView();
    
    
    
    void closeEvent(QCloseEvent* );
    
    //Implement pv method
    virtual void loadGraphic();
    
public slots:
    void newFilm();
    void modifyFilm();
    void cancel();
    
signals:
    void signalSave(const QString& t,const QDate& y,const QString& g,const QString& p,const QString& d,const QTime& drt);
    void signalChange(const QString& t,const QDate& y,const QString& g,const QString& p,const QString& d,const QTime& drt,int id);
    void signalCancel();
};

#endif // FILMVIEW_H
