#include "filmView.h"

//-------------------------COSTRUTTORI------------------------

FilmView::FilmView(const Film* f, MainView* parent): film(f), MainView(parent)
{
    loadGraphic();
}

FilmView::~FilmView() {}

//-------------------------METODI------------------------

void FilmView::closeEvent(QCloseEvent *){
    emit signalCancel();
}

//-------------------------PV METHOD------------------------

void FilmView::loadGraphic(){
    setWindowTitle("Gestione info Films - Mediary");
    
    //Common
    QLabel* titleLabel= new QLabel("Titolo:");
    QLabel* yearLabel= new QLabel("Anno:");
    QLabel* genreLabel= new QLabel("Genere:");
    
    if(film){
        titleEdit= new QLineEdit(film->getTitle());
        yearEdit= new QDateEdit(film->getYear());
        genreEdit= new QLineEdit(film->getGenre());
    }
    else{
        titleEdit= new QLineEdit();
        yearEdit= new QDateEdit(); //lascio data vuota?
        genreEdit= new QLineEdit();
    }
    //Film
    QLabel* plotLabel= new QLabel("Trama:");
    QLabel* distributionLabel= new QLabel("Distribuito da:");
    QLabel* durationLabel= new QLabel("Durata (hh:mm::ss):");
    
    if(film){
        plotEdit= new QTextEdit(film->getPlot());
        distributionEdit= new QLineEdit(film->getDistribution());
        durationEdit= new QTimeEdit(film->getDuration());
    }
    else{
        plotEdit= new QTextEdit();
        distributionEdit= new QLineEdit();
        durationEdit= new QTimeEdit();
    }
    
    //Bottoni
    QPushButton* saveButton= new QPushButton("Salva Film");
    QPushButton* cancelButton= new QPushButton("Annulla");
    
    
    //----SETTA LAYOUT----
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(titleEdit);
    mainLayout->addWidget(yearLabel);
    mainLayout->addWidget(yearEdit);
    mainLayout->addWidget(genreLabel);
    mainLayout->addWidget(genreEdit);
    
    mainLayout->addWidget(plotLabel);
    mainLayout->addWidget(plotEdit);
    mainLayout->addWidget(distributionLabel);
    mainLayout->addWidget(distributionEdit);
    mainLayout->addWidget(durationLabel);
    mainLayout->addWidget(durationEdit);
    
    setLayout(mainLayout);
    
    if(!film) //quindi è nuovo
        connect(saveButton,SIGNAL(clicked()),this,SLOT(newFilm()));
    
    else    //esiste e lo voglio modificare
        connect(saveButton,SIGNAL(clicked()),this,SLOT(modifyFilm()));
    
    //tasto per annullare
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(cancel()));   
}

//-------------------------PUBLIC SLOTS------------------------

void FilmView::newFilm(){
    if(titleEdit->text()==""){
        dialMessage= new DialogMessage("Controllo dati Film","Il campo TITOLO non può rimanere vuoto","Ok");
        dialMessage->show();
    }
    else if(yearEdit->text()==""){
        dialMessage= new DialogMessage("Controllo dati Film","Il campo ANNO non può rimanere vuoto","Ok");
        dialMessage->show();
    }
    else if(genreEdit->text()==""){
        dialMessage= new DialogMessage("Controllo dati Film","Il campo GENERE non può rimanere vuoto","Ok");
        dialMessage->show();
    }
    else if(plotEdit->toPlainText()=="")
        plotEdit->setPlainText("*Nessuna trama indicata per questo film*");
    else if(distributionEdit->text()=="")
        distributionEdit->setText("*Nessuna casa cinematografica/produttrice indicata*");
    else if(durationEdit->time().isNull()){
        dialMessage= new DialogMessage("Controllo dati Film","Il campo DURATA è vuoto o non valido","Ok");
        dialMessage->show();
    }
    else
        emit signalSave(titleEdit->text(),yearEdit->date(),genreEdit->text(),plotEdit->toPlainText(),distributionEdit->text(),durationEdit->time());
}

void FilmView::modifyFilm(){
    //controlli uguali come per nuovo film
    
    if(titleEdit->text()==""){
        dialMessage= new DialogMessage("Controllo dati Film","Il campo TITOLO non può rimanere vuoto","Ok");
        dialMessage->show();
    }
    else if(yearEdit->text()==""){
        dialMessage= new DialogMessage("Controllo dati Film","Il campo ANNO non può rimanere vuoto","Ok");
        dialMessage->show();
    }
    else if(genreEdit->text()==""){
        dialMessage= new DialogMessage("Controllo dati Film","Il campo GENERE non può rimanere vuoto","Ok");
        dialMessage->show();
    }
    else if(plotEdit->toPlainText()=="")
        plotEdit->setPlainText("*Nessuna trama indicata per questo film*");
    else if(distributionEdit->text()=="")
        distributionEdit->setText("*Nessuna casa cinematografica/produttrice indicata*");
    else if(durationEdit->time().isNull()){
        dialMessage= new DialogMessage("Controllo dati Film","Il campo DURATA è vuoto o non valido","Ok");
        dialMessage->show();
    }
    else
        emit signalChange(titleEdit->text(),yearEdit->date(),genreEdit->text(),plotEdit->toPlainText(),distributionEdit->text(),durationEdit->time(),film->getId());
    
}

void FilmView::cancel(){
    emit signalCancel();
}
