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
    const Container<const Media*>& getSerieTV() const;
    const Container<const Media*>& getFilms() const;
    
    void setUsername(const QString& );
    void setPsw(const QString& );
    void setName(const QString& );
    void setSurname(const QString& );
    void setSex(bool );
    
    //-----------altri metodi----------
    
    void writeUser(QXmlStreamWriter& xmlWriter) const;
    bool verifyUser(const User&);
    
    void
};

#endif // USER_H
