#include "Film.h"

//-------------------------COSTRUTTORI------------------------

Film::Film(const QString &t, const QDate &y, const QString &g, const QString &p, const QString &dis, const QTime &time):
        Media(t,y,g), plot(p), distribution(dis), duration(time) {}

//-------------------------GET------------------------

const QString& Film::getPlot() const {return plot;}
const QString& Film::getDistribution() const {return distribution;}
const QTime& Film::getDuration() const {return duration;}

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
        xmlWriter.writeTextElement("dataCreazione",getCreateDate().toString());
        xmlWriter.writeTextElement("ultimaModifica",getLastChange().toString()); 
        xmlWriter.writeTextElement("trama",getPlot());
        xmlWriter.writeTextElement("distribuzione",getDistribution());
        xmlWriter.writeTextElement("durata",getDuration().toString());
    xmlWriter.writeEndElement();
}

QString Film::getType() const { return "Film"; }
