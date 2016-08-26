#include "serietvView.h"

//-------------------------COSTRUTTORI------------------------

SerietvView::SerietvView(const SerieTV* s, MainView* parent): serieTv(s), MainView(parent) 
{
    loadGraphic();    
}

SerietvView::~SerietvView() {}

//-------------------------METODI------------------------

void SerietvView::closeEvent(QCloseEvent* ){
    emit signalCancel();
}

//-------------------------PV METHOD------------------------


void SerietvView::loadGraphic(){
    setWindowTitle("Gestione info SerieTV - Mediary");
    
    //Common
    QLabel* titleLabel= new QLabel("Titolo:");
    QLabel* yearLabel= new QLabel("Anno:");
    QLabel* genreLabel= new QLabel("Genere:");
    
    if(serieTv){
        titleEdit= new QLineEdit(serieTv->getTitle());
        yearEdit= new QDateEdit(serieTv->getYear());
        genreEdit= new QLineEdit(serieTv->getGenre());
    }
    else{
        titleEdit= new QLineEdit();
        yearEdit= new QDateEdit(); //lascio data vuota?
        genreEdit= new QLineEdit();
    }
    //SerieTV
    QLabel* descriptionLabel= new QLabel("Descrizione:");
    QLabel* seasonLabel= new QLabel("Stagione:");
    QLabel* episodeLabel= new QLabel("Episodio n°:");
    QLabel* lenghtLabel= new QLabel("Lunghezza (in minuti):");
    
    seasonEdit= new QSpinBox();
        seasonEdit->setMinimum(1);
        seasonEdit->setMaximum(15);
        
    episodeEdit= new QSpinBox();
        episodeEdit->setMinimum(1);
        
    lenghtEdit= new QSpinBox();
        lenghtEdit->setMinimum(5);
        lenghtEdit->setMaximum(60);
        lenghtEdit->setSingleStep(5);
        
    if(serieTv){
        descriptionEdit= new QTextEdit(serieTv->getDescr());
        seasonEdit->setValue(serieTv->getSeason());
        episodeEdit->setValue(serieTv->getNumberEp());
        lenghtEdit->setValue(serieTv->getLengthEp());
    }
    else
        descriptionEdit= new QTextEdit();
    
    //Bottoni
    QPushButton* saveButton= new QPushButton("Salva SerieTV");
    QPushButton* cancelButton= new QPushButton("Annulla");
    
    //----SETTA LAYOUT----
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(titleEdit);
    mainLayout->addWidget(yearLabel);
    mainLayout->addWidget(yearEdit);
    mainLayout->addWidget(genreLabel);
    mainLayout->addWidget(genreEdit);
    
    mainLayout->addWidget(descriptionLabel);
    mainLayout->addWidget(descriptionEdit);
      // 3 layout orizzontali per stagione, episodio e lunghezza
      QHBoxLayout* seasHLay= new QHBoxLayout;
        seasHLay->addWidget(seasonLabel); seasHLay->addWidget(seasonEdit);
      QHBoxLayout* episHLay= new QHBoxLayout;
        episHLay->addWidget(episodeLabel); episHLay->addWidget(episodeEdit);
      QHBoxLayout* lengHLay= new QHBoxLayout;
        lengHLay->addWidget(lenghtLabel); lengHLay->addWidget(lenghtEdit);    
      // li inserisco uno sotto l'altro in un box verticale
    QVBoxLayout* spindVBox= new QVBoxLayout;
      spindVBox->addLayout(seasHLay);
      spindVBox->addLayout(episHLay);
      spindVBox->addLayout(lengHLay);
      
    mainLayout->addLayout(spindVBox);
    mainLayout->addWidget(saveButton);
    mainLayout->addWidget(cancelButton);
    
    setLayout(mainLayout);
    
    if(!serieTv) //quindi è nuovo
        connect(saveButton,SIGNAL(clicked()),this,SLOT(newSerieTV()));
    
    else    //esiste e lo voglio modificare
        connect(saveButton,SIGNAL(clicked()),this,SLOT(modifySerieTV()));
    
    //tasto per annullare
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(cancel()));
}

//-------------------------PUBLIC SLOTS------------------------

void SerietvView::newSerieTV(){
    //stagione,episodi e lunghezza sono delle spinBox e quindi avranno per forza dei valori
    
    if(titleEdit->text()==""){
        dialMessage= new DialogMessage("Controllo dati SerieTV","Il campo TITOLO non può rimanere vuoto","Ok");
        dialMessage->show();
    }
    else if(yearEdit->text()==""){
        dialMessage= new DialogMessage("Controllo dati SerieTV","Il campo ANNO non può rimanere vuoto","Ok");
        dialMessage->show();
    }
    else if(yearEdit->date().isNull()){
        dialMessage= new DialogMessage("Controllo dati SerieTV","Il campo ANNO è vuoto o non valido","Ok");
        dialMessage->show();
    }        
    else if(genreEdit->text()==""){
        dialMessage= new DialogMessage("Controllo dati SerieTV","Il campo GENERE non può rimanere vuoto","Ok");
        dialMessage->show();
    }
    else if(descriptionEdit->toPlainText()=="")
        descriptionEdit->insertPlainText("*Nessuna descrizione dell'episodio*");
    else
        emit signalSave(titleEdit->text(),yearEdit->date(),genreEdit->text(),descriptionEdit->toPlainText(),seasonEdit->value(),episodeEdit->value(),lenghtEdit->value());
}

void SerietvView::modifySerieTV(){
    //Controlli modifica identici alla creazione
    if(titleEdit->text()==""){
        dialMessage= new DialogMessage("Controllo modifica SerieTV","Il campo TITOLO non può rimanere vuoto","Ok");
        dialMessage->show();
    }
    else if(yearEdit->text()==""){
        dialMessage= new DialogMessage("Controllo modifica SerieTV","Il campo ANNO non può rimanere vuoto","Ok");
        dialMessage->show();
    }
    else if(genreEdit->text()==""){
        dialMessage= new DialogMessage("Controllo modifica SerieTV","Il campo GENERE non può rimanere vuoto","Ok");
        dialMessage->show();
    }
    else if(descriptionEdit->toPlainText()=="")
        descriptionEdit->insertPlainText("*Nessuna descrizione dell'episodio*");
    else
        emit signalChange(titleEdit->text(),yearEdit->date(),genreEdit->text(),descriptionEdit->toPlainText(),seasonEdit->value(),episodeEdit->value(),lenghtEdit->value(),serieTv->getId());
}

void SerietvView::cancel(){
    emit signalCancel();
}
