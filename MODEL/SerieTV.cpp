#include "SerieTV.h"

//-------------------------COSTRUTTORI------------------------

SerieTV::SerieTV(QString t, QDate y, QString g, QString d, unsigned int s, unsigned int ep, unsigned int l): 
        Media(t,y,g), descriptionEp(d), season(s), numberEp(ep), lenghtEp(l) {}

//-------------------------GET------------------------

const QString& SerieTV::getDescr() const {return descriptionEp;}
unsigned int SerieTV::getSeason() const {return season;}
unsigned int SerieTV::getNumberEp() const {return numberEp;}
unsigned int SerieTV::getLengthEp() const {return lenghtEp;}

//-------------------------SET------------------------

void SerieTV::setDescription(const QString& d) {descriptionEp=d; this->updateChangeDate();}
void SerieTV::setSeason(unsigned int s) {season=s; this->updateChangeDate();}
void SerieTV::setNumberEp(unsigned int n) {numberEp=n; this->updateChangeDate();}
void SerieTV::setLeghtEp(unsigned int l) {lenghtEp=l; this->updateChangeDate();}

//-------------------------PV METHODS------------------------

void SerieTV::saveMedia(QXmlStreamWriter& xmlWriter) const{
    xmlWriter.writeStartElement("SerieTV"); //<SerieTV>
        xmlWriter.writeTextElement("titolo",getTitle());
        xmlWriter.writeTextElement("anno",getYear().toString());
        xmlWriter.writeTextElement("genere",getGenre());
        xmlWriter.writeTextElement("Stagione",QString::number(getSeason()));
        xmlWriter.writeTextElement("no.episodio",QString::number(getNumberEp()));
        xmlWriter.writeTextElement("descrizione",getDescr());
        xmlWriter.writeTextElement("lunghezza",QString::number(getLengthEp()));
    xmlWriter.writeEndElement();            //</SerieTV>
}

QString SerieTV::getType() const { return "SerieTV"; }
