#ifndef MEDIA_H
#define MEDIA_H

#include<QString>
#include<QDateTime>

#include<QXmlStreamWriter>

class Media
{
private:
    static int codMedia;    //un codice diverso per ogni media presente nel db
    int id; //id univoco del media autoincrementante tramite il codMedia quando viene costruito
    QString title;
    QDateTime creationDate; //data creazione
    QDateTime changeDate;   //data ultima modifca
    
public:
    Media(Qstring ="Unkwnown");  //creationDate e changeDate vengono settate correttamente tramite un funzione apposita
    
    virtual ~Media();   //GERARCHIA POLIMORFA
    
    const QString& getTitle() const;
    const QDateTime& getCreate() const;
    QDateTime getChange() const;
    int getId() const;
    
    virtual QString getType() const=0; // PURE VIRTUAL // ritorna il tipo polimorfo di media
    
    void setTitle(const QString& );
    void setCreationDate(const QDateTime& );
    void setChangeDate(const QDateTime& );
    void updateChangeDate();
    
    virtual void saveMedia(QXmlStreamWriter& ) const=0; // PURE VIRTUAL // salvataggio media polimorfo nel db .xml
};

#endif // MEDIA_H
