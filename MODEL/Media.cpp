#include "Media.h"

int Media::codMedia=0;  //inizializzazione membro statico

//-------------------------COSTRUTTORI------------------------

Media::Media(Qstring t, int y, Qstring g): title(t), year(y), genre(g), creationDate(QDateTime::currentDateTime()), changeDate(QDateTime::currentDateTime())
{
    id=codMedia++;
}

Media::~Media() {}

//-------------------------GET------------------------

const QString& Media::getTitle() const {return title;}
int Media::getYear() const {return year;}
const QString& Media::getGenre() const {return genre;}
const QDateTime& Media::getCreate() const {return creationDate;}
QDateTime Media::getChange() const {return changeDate;}
int Media::getId() const {return id;}

//-------------------------SET------------------------

void Media::setTitle(const QString& t) {titolo=t; this->updateChangeDate();}
void Media::setYear(int y) {year=y;}
void Media::setGenre(const QString& g) {genre=g;}
void Media::setCreationDate(const QDateTime& d) {creationDate=d;}
void Media::setChangeDate(const QDateTime& cd) {changeDate=cd;}

//-------------------------ALTRI METODI------------------------

void Media::updateChangeDate() {changeDate=QDateTime::currentDateTime();}


