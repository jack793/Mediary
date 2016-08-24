#include "SerieTV.h"

//-------------------------COSTRUTTORI------------------------

SerieTV::SerieTV(QString t, int y, QString g, QString d, int s, int ep, int l): 
        Media(t,y,g), descriptionEp(d), seasons(s), numberEp(ep), lenghtEp(l) {}

//-------------------------GET------------------------

const QString& SerieTV::getDescr() const {return descriptionEp;}
unsigned int SerieTV::getSeasons() const {return seasons;}
unsigned int SerieTV::getNumberEp() const {return numberEp;}
unsigned int SerieTV::getLengthEp() const {return lenghtEp;}

//-------------------------SET------------------------

void SerieTV::setDescription(const QString& d) {descriptionEp=d;}
void SerieTV::setSeasons(unsigned int s) {seasons=s;}
void SerieTV::setNumberEp(unsigned int n) {numberEp=n;}
void SerieTV::setLeghtEp(unsigned int l) {lenghtEp=l;}

//-------------------------PV METHODS------------------------

void SerieTV::saveMedia(QXmlStreamWriter& xmlWriter) const{
    xmlWriter.writeStartElement("SerieTV");
        xmlWriter.writeTextElement("titolo",getTitle());
        xmlWriter.writeTextElement("anno",getYear());
}
