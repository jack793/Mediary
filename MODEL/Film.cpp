#include "Film.h"

//-------------------------COSTRUTTORI------------------------

Film::Film(QString t, QDate d, QString g, QString p, QString dis, QTime time):
        Media(t,y,g), plot(p), distribution(dis), duration(time) {}

//-------------------------GET------------------------

const QString& Film::getPlot() const {return plot;}
const QString& Film::getDistribution() const {return distribution;}
QTime Film::getDuration() const {return duration;}

//-------------------------SET------------------------

void Film::setPlot(const QString& p) {plot=p; this->updateChangeDate();}
void Film::setDistruitedBy(const QString& dis) { distribution=dis; this->updateChangeDate();}
void Film::setDuration(QTime t) {duration=t; this->updateChangeDate();}

//-------------------------PV METHODS------------------------

void Film::saveMedia(QXmlStreamWriter& xmlWriter) const
{
    xmlWriter.writeStartElement("film");
        xmlWriter.writeTextElement("titolo",getTitle());
        xmlWriter.writeTextElement("anno",getYear().toString());
        xmlWriter.writeTextElement("genere",getGenre());
        xmlWriter.writeTextElement("data creazione",getCreate());
        xmlWriter.writeTextElement("ultima modifica",getChange()); 
        xmlWriter.writeTextElement("trama",getPlot());
        xmlWriter.writeTextElement("distribuito da",getDistribution());
        xmlWriter.writeTextElement("durata",getDuration().toString());
    xmlWriter.writeEndElement();
}

QString Film::getType() const { return "Film"; }
