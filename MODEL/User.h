#ifndef USER_H
#define USER_H

#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QString>
#include <iostream>

#include "Media.h"
#include "SerieTV.h"
#include "Film.h"


#include "Container.h"

class User
{
private:
    QString username;
    QString password;
    QString name;
    QString surname;
    bool sex;
    Container<const Media*> mediaDatabase;
public:
    User(const QString& ,const QString& ,const QString& ,const QString& ,bool );
    
    const QString& getUsername() const;
    const QString& getPsw() const;
    const QString& getName() const;
    const QString& getSurname() const;
    bool getSex() const;
    const Container<const Media*>& getMedia() const;
    Container<const Media*> getSerieTV() const;
    Container<const Media*> getFilms() const;
    
    void setUsername(const QString& );
    void setPsw(const QString& );
    void setName(const QString& );
    void setSurname(const QString& );
    void setSex(bool );
    
    //-----------altri metodi----------
    
    void writeUser(QXmlStreamWriter& xmlWriter) const;
    bool verifyUser(const QString&) const;
    
    void addMedia(const Media*);
    bool verifyMedia(const QString& ,const QDateTime& ) const;
    
    void modifySerieTV(const QString& t, const QDate& y, const QString& g, const QString& d, unsigned int s, unsigned int nep, unsigned int l, int id);
    void modifyFilm(const QString& t, const QDate& y, const QString& g, const QString& p, const QString& distr, const QTime& time, int id);
    
    void deleteMedia(int );
    const Media* findMedia(int ) const; //ritorna il puntatore al media polimorfo che corrisponde con l'id passato
    
    void loadMedia();
    void writeMedia() const;
    void emptyMediaDatabase();
       
};

#endif // USER_H
