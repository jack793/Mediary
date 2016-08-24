#ifndef SERIETV_H
#define SERIETV_H

#include "Media.h"

#include <QString>

class SerieTV: public Media
{
private:
    QString descriptionEp;  //descrizione episodio
    unsigned int seasons;   //no. di stagioni attuali
    unsigned int numberEp;  //numero episodio
    unsigned int lenghtEp; //durata ep in minuti
    
public:
    SerieTV(QString ="Unknown",int ,QString ="Unknown",QString ="Unkwnown",int ,int ,int);
            // titolo, anno, genere,  descrizione, stagioni, numeroEp, durataEp
    
    const QString& getDescr() const;
    unsigned int getSeasons() const;
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
