#include "SerieTV.h"

//-------------------------COSTRUTTORI------------------------

SerieTV::SerieTV(const QString &t, unsigned int y, const QString &g, const QString &d, unsigned int s, unsigned int ep, unsigned int l): 
        Media(t,y,g), descriptionEp(d), season(s), numberEp(ep), lenghtEp(l) {}

//-------------------------GET------------------------

const QString& SerieTV::getDescr() const {return descriptionEp;}
unsigned int SerieTV::getSeason() const {return season;}
unsigned int SerieTV::getNumberEp() const {return numberEp;}
unsigned int SerieTV::getLengthEp() const {return lenghtEp;}

//-------------------------SET------------------------

void SerieTV::setDescription(const QString& d) {descriptionEp=d; this->updateChangeDate();}
void SerieTV::setSeasons(unsigned int s) {season=s; this->updateChangeDate();}
void SerieTV::setNumberEp(unsigned int n) {numberEp=n; this->updateChangeDate();}
void SerieTV::setLeghtEp(unsigned int l) {lenghtEp=l; this->updateChangeDate();}

//-------------------------PV METHODS------------------------

void SerieTV::saveMedia(QXmlStreamWriter& xmlWriter) const{
    xmlWriter.writeStartElement("serieTV"); //<SerieTV>
        xmlWriter.writeTextElement("titolo",getTitle());
        xmlWriter.writeTextElement("anno",QString::number(getYear()));
        xmlWriter.writeTextElement("genere",getGenre());
        xmlWriter.writeTextElement("dataCreazione",getCreateDate().toString());
        xmlWriter.writeTextElement("ultimaModifica",getLastChange().toString());        
        xmlWriter.writeTextElement("stagione",QString::number(getSeason()));
        xmlWriter.writeTextElement("no.episodio",QString::number(getNumberEp()));
        xmlWriter.writeTextElement("descrizione",getDescr());
        xmlWriter.writeTextElement("lunghezza",QString::number(getLengthEp()));
    xmlWriter.writeEndElement();            //</SerieTV>
}

QString SerieTV::getType() const { return "SerieTV"; }
