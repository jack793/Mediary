#ifndef SERIETV_H
#define SERIETV_H

#include "Media.h"

#include <QString>
#include <QXmlStreamWriter>

class SerieTV: public Media
{
private:
    QString descriptionEp;  //descrizione episodio
    unsigned int season;   //stagione dell'episodio
    unsigned int numberEp;  //numero episodio
    unsigned int lenghtEp; //durata ep in minuti
    
public:
    SerieTV(const QString& ="Unknown",unsigned int y=2016 ,const QString& ="Unknown",const QString& ="Unkwnown",unsigned int =0 ,unsigned int =0,unsigned int =0);
            // titolo, anno (yyyy,mm,dd), genere,   descrizione, stagioni, numeroEp, durataEp
    
    const QString& getDescr() const;
    unsigned int getSeason() const;
    unsigned int getNumberEp() const;
    unsigned int getLengthEp() const;
    
    void setDescription(const QString& );
    void setSeasons(unsigned int );
    void setNumberEp(unsigned int );
    void setLeghtEp(unsigned int );
    
    //IMPLEMENTS PV METHODS
    void saveMedia(QXmlStreamWriter& xmlWriter) const;
    QString getType() const;
};

#endif // SERIETV_H
