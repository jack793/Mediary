#ifndef DIALOGMESSAGE_H
#define DIALOGMESSAGE_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <string>

class DialogMessage: public QDialog
{
    Q_OBJECT
private:
    QLabel* lblMessaggio;
    QPushButton* btnConferma;
    QVBoxLayout* vLay;
public:
    DialogMessage(std::string,std::string,std::string);
    ~DialogMessage();
private slots:
    void chiudi();
signals:
    void signalChiudi();
};

#endif // DIALOGMESSAGE_H
