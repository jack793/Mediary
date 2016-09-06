#include "Database.h"

//-------------------------COSTRUTTORI------------------------

Database::Database() { loadUserDb(); }

Database::~Database(){
    saveUserDb();
    //svuoto tutto
    while(!userDatabase.isEmpty())
        userDatabase.pop_front();
}

//-------------------------METODI------------------------

bool Database::matchUser(const QString& usn) const{
    for(Container<const User*>::Iterator it=userDatabase.begin(); it!=userDatabase.end(); ++it)
        if(userDatabase[it]->getUsername()==usn)
            return true;
    return false;
}

bool Database::verifyUser(const QString& usn, const QString& psw) const{
    for(Container<const User*>::Iterator it=userDatabase.begin(); it!=userDatabase.end(); ++it)
        if(userDatabase[it]->getUsername()==usn && userDatabase[it]->getPsw()==psw)
            return true;
    return false;
}

void Database::addUser(const User* u) {
    if(!getUser(u->getUsername(),u->getPsw()))
        userDatabase.push_front(u);
}

const User* Database::getUser(const QString& usn, const QString& psw) const{
    for(Container<const User*>::Iterator it=userDatabase.begin(); it!=userDatabase.end(); ++it)
        if(userDatabase[it]->getUsername()==usn && userDatabase[it]->getPsw()==psw)
            return userDatabase[it];
    return 0;
}

//---------------LOAD E SAVE-------------------

void Database::loadUserDb(){
    //var. temp
    //c.d. user
    QString username;
    QString password;
    QString name;
    QString surname;
    QString sex;
    
    QFile userFile("userDatabase.xml");
    userFile.open(QFile::ReadWrite);
    userFile.close();
    if(!userFile.open(QFile::ReadOnly | QFile::Text))
        std::cout<<"Users database not found, load failed!"<<std::endl;
    
    QXmlStreamReader xmlReader(&userFile);
    xmlReader.readNext();
    
    while(!xmlReader.atEnd()){
        if(xmlReader.isStartElement()){
            if(xmlReader.name()=="database" || xmlReader.name()=="utente")
                xmlReader.readNext();
            else if(xmlReader.name()=="username")
                username=xmlReader.readElementText();
            else if(xmlReader.name()=="password")
                password=xmlReader.readElementText();
            else if(xmlReader.name()=="nome")
                name=xmlReader.readElementText();
            else if(xmlReader.name()=="cognome")
                surname=xmlReader.readElementText();
            else if(xmlReader.name()=="sesso")
                sex=xmlReader.readElementText();
        }
        else if(xmlReader.isEndElement() && xmlReader.name()=="utente"){    // legge </utente>
            User* u=new User(username,password,name,surname,sex);
            userDatabase.push_back(u);
            xmlReader.readNext();
        }
        else
            xmlReader.readNext();
    }
    std::cout<<"Users database loaded!"<<std::endl;
    
    userFile.close();
}

void Database::saveUserDb(){
    QFile userFile("userDatabase.xml");
    
    if(!userFile.open(QIODevice::WriteOnly))
        std::cout<<"Users database not found, saving failed!"<<std::endl;
    
    QXmlStreamWriter xmlWriter(&userFile);
    xmlWriter.setAutoFormatting(true);
    
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("database");
    
    if(!userDatabase.isEmpty())
        for(Container<const User*>::Iterator it=userDatabase.begin(); it!=userDatabase.end(); ++it)
            userDatabase[it]->writeUser(xmlWriter);     //PRONTO PER ESTENSIBILITA' POLIMORFA
    xmlWriter.writeEndDocument();
    
    std::cout<<"Users database saved!"<<std::endl;
    userFile.close();
}

void Database::printLoginData() const{
    for(Container<const User*>::Iterator it=userDatabase.begin(); it!=userDatabase.end(); ++it)
        std::cout<<"Username: "<<userDatabase[it]->getUsername().toUtf8().constData()<<"Nome: "<<userDatabase[it]->getName().toUtf8().constData()<<"Cognome: "<<userDatabase[it]->getSurname().toUtf8().constData()<<std::endl;
}

