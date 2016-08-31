#ifndef SERIETVVIEW_H
#define SERIETVVIEW_H

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QDateEdit>
#include <QDateTimeEdit>

#include "mainView.h"
#include "dialogMessage.h"

#include "MODEL/SerieTV.h"

class SerietvView: public MainView
{
    Q_OBJECT
private:
    //For get info
    const SerieTV* serieTv;
    
    //Graphic:
    //Common elements
    QVBoxLayout* mainLayout;
    QLineEdit* titleEdit;
    QDateEdit* yearEdit;
    QLineEdit* genreEdit;
    //SerieTv elements
    QTextEdit* descriptionEdit;
    QSpinBox* seasonEdit;
    QSpinBox* episodeEdit;
    QSpinBox* lenghtEdit;
    
    //Output messages
    DialogMessage* dialMessage;
    
public:
    explicit SerietvView(const SerieTV* s=0, MainView* parent=0);
    ~SerietvView();
    
    void closeEvent(QCloseEvent* );
    
    //Implement pv method
    virtual void loadGraphic();
    
public slots:
    void newSerieTV();
    void modifySerieTV();
    void cancel();
    
signals:
    void signalSave(const QString& t,const QDate& y,const QString& g,const QString& d,unsigned int s,unsigned int n,unsigned int l);
    void signalChange(const QString& t,const QDate& y,const QString& g,const QString& d,unsigned int s,unsigned int n,unsigned int l,int id);
    void signalCancel();
};

#endif // SERIETVVIEW_H
