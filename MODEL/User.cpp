#include "User.h"

//-------------------------COSTRUTTORI------------------------

User::User(const QString& usn, const QString& psw, const QString& nm, const QString& sur, bool sx):
        username(usn), password(psw), name(nm), surname(sur), sex(sx) {}

//-------------------------GET------------------------

const QString& User::getUsername() const {return username;}
const QString& User::getPsw() const {return password;}
const QString& User::getName() const {return name;}
const QString& User::getSurname() const {return surname;}
bool User::getSex() const {return sex;}
Container<const Media*> User::getMedia() const {return mediaDatabase;}

Container<const Media*> User::getSerieTV() const{
    Container<const Media*> ris;
    for(Container<const Media*>::Iterator it=mediaDatabase.begin(); it!=mediaDatabase.end(); ++it){
        const SerieTV* s=dynamic_cast<const SerieTV*>(mediaDatabase[it]);
        if(s)
            ris.push_front(s);
    }
    return ris;
}

Container<const Media*> User::getFilms() const{
    Container<const Media*> ris;
    for(Container<const Media*>::Iterator it=mediaDatabase.begin(); it!=mediaDatabase.end(); ++it){
        const Film* f=dynamic_cast<const Film*>(mediaDatabase[it]);
        if(f)
            ris.push_front(f);
    }
    return ris;
}

//-------------------------SET------------------------

void User::setUsername(const QString& usn) {username=usn;}
void User::setPsw(const QString& psw) {password=psw;}
void User::setName(const QString& n) {name=n;}
void User::setSurname(const QString& sn) {surname=sn;}
void User::setSex(bool s) {sex=s;}

//-------------------------ALTRI METODI------------------------

void User::writeUser(QXmlStreamWriter& xmlWriter) const{
    xmlWriter.writeStartElement("utente");
        xmlWriter.writeTextElement("username",getUsername());
        xmlWriter.writeTextElement("password",getPsw());
        xmlWriter.writeTextElement("nome",getName());
        xmlWriter.writeTextElement("cognome",getSurname());
        xmlWriter.writeTextElement("sesso",QString::number(getSex()));
    xmlWriter.writeEndElement();
}

bool User::verifyUser(const QString& usn) const{
    return (username==usn);
}

void User::addMedia(const Media* m){
    if(!findMedia(m->getId()))  //se non esiste già
        mediaDatabase.push_front(m);
}

bool User::verifyMedia(const QString& t, const QDateTime& cd) const{
    if(!mediaDatabase.isEmpty()){
        for(Container<const Media*>::Iterator it=mediaDatabase.begin(); it!=mediaDatabase.end(); ++it)
            if(mediaDatabase[it]->getTitle()==t && mediaDatabase[it]->getCreateDate()==cd)
                return true;
    }
    return false;
}

void User::modifySerieTV(const QString& t, const QDate& y, const QString& g, const QString& d, unsigned int seas, unsigned int nep, unsigned int l, int id){
    SerieTV* s=const_cast<SerieTV*>(dynamic_cast<const SerieTV*>(findMedia(id)));
    if(s){
        s->setTitle(t);
        s->setYear(y);
        s->setGenre(g);
        s->setDescription(d);
        s->setSeasons(seas);
        s->setNumberEp(nep);
        s->setLeghtEp(l);
    }
    //non trovata
}

void User::modifyFilm(const QString& t, const QDate& y, const QString& g, const QString& p, const QString& distr, const QTime& time, int id){
    Film* f=const_cast<Film*>(dynamic_cast<const Film*>(findMedia(id)));
    if(f){
        f->setTitle(t);
        f->setYear(y);
        f->setGenre(g);
        f->setPlot(p);
        f->setDistruitedBy(distr);
        f->setDuration(time);
    }
}

void User::deleteMedia(int i){
    if(!mediaDatabase.isEmpty())
        mediaDatabase.pop_element(findMedia(i));
}

const Media* User::findMedia(int i) const{
    if(!mediaDatabase.isEmpty()){
        for(Container<const Media*>::Iterator it=mediaDatabase.begin(); it!=mediaDatabase.end(); ++it)
            if(mediaDatabase[it]->getId()==i)
                return dynamic_cast<const Media*>(mediaDatabase[it]);
    }
    return 0;
}

void User::loadMedia()
{   
    //var. temporanee
    
    //---media----
    QString title;
    QDate year;
    QString genre;
    QDateTime creationDate;
    QDateTime changeDate;
    
    //---serietv-----
    QString descriptionEp;
    unsigned int season;
    unsigned int numberEp;
    unsigned int lenghtEp;
    
    //----film-----
    QString plot;
    QString distribution;
    QTime duration;
    
    QFile mediaFile(""+getUsername()+"mediaDatabase.xml");
    mediaFile.open(QFile::ReadWrite);
    mediaFile.close();
    if(!mediaFile.open(QFile::ReadOnly | QFile::Text))
        std::cout<<"Media database not found, load failed!"<<std::endl;
    
    QXmlStreamReader xmlReader(&mediaFile); //Creates a new stream reader that reads from device.
    xmlReader.readNext();
    
    while(!xmlReader.atEnd()){
        if(xmlReader.isStartElement()){ //lettura dei tag aperti <namespaceURI>
            if(xmlReader.name()=="media" || xmlReader.name()=="serieTV" || xmlReader.name()=="film")
                xmlReader.readNext();
            else if(xmlReader.name()=="titolo")
                title=xmlReader.readElementText();
            else if(xmlReader.name()=="anno")
                year=QDate::fromString(xmlReader.readElementText());
            else if(xmlReader.name()=="genere")
                genre=xmlReader.readElementText();
            else if(xmlReader.name()=="dataCreazione")
                creationDate=QDateTime::fromString(xmlReader.readElementText());
            else if(xmlReader.name()=="ultimaModifica")
                changeDate=QDateTime::fromString(xmlReader.readElementText());
            
            else if(xmlReader.name()=="stagione")
                season=xmlReader.readElementText().toUInt();
            else if(xmlReader.name()=="no.episodio")
                numberEp=xmlReader.readElementText().toUInt();
            else if(xmlReader.name()=="descrizione")
                descriptionEp=xmlReader.readElementText();
            else if(xmlReader.name()=="lunghezza")
                lenghtEp=xmlReader.readElementText().toUInt();
            
            else if(xmlReader.name()=="trama")
                plot=xmlReader.readElementText();
            else if(xmlReader.name()=="distribuzione")
                distribution=xmlReader.readElementText();
            else if(xmlReader.name()=="durata")
                duration=QTime::fromString(xmlReader.readElementText());
        }
        else if(xmlReader.isEndElement() && xmlReader.name()=="serieTV"){
            SerieTV* serieTV=new SerieTV(title,year,genre,descriptionEp,season,numberEp,lenghtEp);
            
            serieTV->setCreationDate(creationDate);
            serieTV->setChangeDate(changeDate);
            
            mediaDatabase.push_front(serieTV);
            xmlReader.readNext();
        }
        else if(xmlReader.isEndElement() && xmlReader.name()=="film"){
            Film* film=new Film(title,year,genre,plot,distribution,duration);
            
            film->setCreationDate(creationDate);
            film->setChangeDate(changeDate);
            
            mediaDatabase.push_front(film);
            xmlReader.readNext();
        }
        else
            xmlReader.readNext();
    }
    std::cout<<"Media database loaded!"<<std::endl;
    
    mediaFile.close();
}

void User::writeMedia() const{
    QFile mediaFile(""+getUsername()+"mediaDatabase.xml");
    if(!mediaFile.open(QIODevice::WriteOnly))
        std::cout<<"Media database not found, saving failed!"<<std::endl;
    
    QXmlStreamWriter xmlWriter(&mediaFile);
    xmlWriter.setAutoFormatting(true);
    
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("media");
    if(!mediaDatabase.isEmpty())
        for(Container<const Media*>::Iterator it=mediaDatabase.begin(); it!=mediaDatabase.end(); ++it)
            mediaDatabase[it]->saveMedia(xmlWriter);    //CHIAMATA POLIMORFA
    
    xmlWriter.writeEndDocument();
    std::cout<<"Media database saved!"<<std::endl;
    
    mediaFile.close();
}

void User::emptyMediaDatabase(){
    while(!mediaDatabase.isEmpty())
        mediaDatabase.pop_front();
}
