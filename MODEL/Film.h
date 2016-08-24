#ifndef FILM_H
#define FILM_H

#include "Media.h"

#include <QString>
#include <QTime>
#include <QXmlStreamWriter>

class Film: public Media
{
private:
    QString plot;
    QString distribution;
    QTime duration; //A QTime object contains a clock time, i.e. the number of hours, minutes, seconds, and milliseconds since midnight
        
public:
    Film(QString ="Unknown",QDate d=QDate(1970,1,1) ,QString ="Unknown", QString ="Unknown", QString ="Unknown", QTime t=QTime(0,0,0));
            // titolo, anno (yyy.mm.dd), genere,  trama, distribuito da, durata(h,m,s)
    
    const QString& getPlot() const;
    const QString& getDistribution() const;
    QTime getDuration() const;
    
    void setPlot(const QString& );
    void setDistruitedBy(const QString& );
    void setDuration(QTime );
    
    //IMPLEMENTS PV METHODS
    void saveMedia(QXmlStreamWriter& xmlWriter) const;
    QString getType() const;    
};

#endif // FILM_H
