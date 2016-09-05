#ifndef MEDIA_H
#define MEDIA_H

#include<QString>
#include<QDateTime>

#include<QXmlStreamWriter>

class Media
{
private:
    static int codMedia; //un codice diverso per ogni media presente nel db
    int id; //id univoco del media autoincrementante tramite il codMedia quando viene costruito
    
    QString title;
    unsigned int year;
    QString genre;
    
    QDateTime creationDate; //data creazione
    QDateTime changeDate;   //data ultima modifica
    
public:
    Media(const QString& ="Unkwnown", unsigned int y=2016, const QString& ="Unkwnown");
    //creationDate e changeDate vengono settate correttamente tramite un funzione apposita
    
    virtual ~Media();   //GERARCHIA POLIMORFA
    
    const QString& getTitle() const;
    unsigned int getYear() const;
    const QString& getGenre() const;
    const QDateTime& getCreateDate() const;
    QDateTime getLastChange() const;
    int getId() const;
    
    virtual QString getType() const=0; // PURE VIRTUAL // ritorna il tipo polimorfo di media
    
    void setTitle(const QString& );
    void setYear(unsigned int );
    void setGenre(const QString& );
    void setCreationDate(const QDateTime& );
    void setChangeDate(const QDateTime& );
    void updateChangeDate();
    
    virtual void saveMedia(QXmlStreamWriter& xmlWriter) const=0; // PURE VIRTUAL // salvataggio media polimorfo nel db .xml
};

#endif // MEDIA_H
