#ifndef DATABASE_H
#define DATABASE_H

#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QString>
#include <iostream>

#include "User.h"
#include "Media.h"

#include "Container.h"

class Database{
private:
    Container<const User*> userDatabase;
    
public:
    explicit Database();
    ~Database();
    
    bool matchUser(const QString& ) const;  //true sse matcha un username nel db utenti
    bool verifyUser(const QString& usn,const QString& psw) const; //true sse username e password presenti associati nel db 
    void addUser(const User* );
    const User* getUser(const QString& , const QString& ) const; //ritorna pnt all'utente verificato
    
    void loadUserDb();
    void saveUserDb();
    
    void printLoginData() const;
};

#endif // DATABASE_H
