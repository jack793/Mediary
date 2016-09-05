#include "Media.h"

int Media::codMedia=0;  //inizializzazione membro statico

//-------------------------COSTRUTTORI------------------------

Media::Media(const QString& t,unsigned int y,const QString& g): title(t), year(y), genre(g), creationDate(QDateTime::currentDateTime()), changeDate(QDateTime::currentDateTime())
{
    id=codMedia++;
}

Media::~Media() {}

//-------------------------GET------------------------

const QString& Media::getTitle() const {return title;}
unsigned int Media::getYear() const {return year;}
const QString& Media::getGenre() const {return genre;}
const QDateTime& Media::getCreateDate() const {return creationDate;}
QDateTime Media::getLastChange() const {return changeDate;}
int Media::getId() const {return id;}

//-------------------------SET------------------------

void Media::setTitle(const QString& t) {title=t; this->updateChangeDate();}
void Media::setYear(unsigned int y) {year=y; this->updateChangeDate();}
void Media::setGenre(const QString& g) {genre=g; this->updateChangeDate();}
void Media::setCreationDate(const QDateTime& d) {creationDate=d;}
void Media::setChangeDate(const QDateTime& cd) {changeDate=cd;}

//-------------------------ALTRI METODI------------------------

void Media::updateChangeDate() {changeDate=QDateTime::currentDateTime();}
