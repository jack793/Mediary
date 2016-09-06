#include "userView.h"

//-------------------------COSTRUTTORI------------------------

userView::userView(User* u, MainView* parent): MainView(parent), user(u), serieTvView(0), filmView(0), userInfoView(0)
{
    loadGraphic();
}

userView::~userView() {}

//-------------------------METODI------------------------

void userView::closeEvent(QCloseEvent* ){
    emit signalLogout();
}

void userView::loadMediaTable(const Container<const Media*>& userMedia){
    if(!userMedia.isEmpty()){
        int row=0;
        for(Container<const Media*>::Iterator it=userMedia.begin(); it!=userMedia.end(); ++it){
            mediaTable->setRowCount(row+1);
            
            QTableWidgetItem* id= new QTableWidgetItem(QString::number(userMedia[it]->getId()));
            QTableWidgetItem* title= new QTableWidgetItem(userMedia[it]->getTitle());
            QTableWidgetItem* type= new QTableWidgetItem(userMedia[it]->getType()); //POLIMORFISMO
            QTableWidgetItem* creationDate= new QTableWidgetItem(userMedia[it]->getCreateDate().toString("dd/MM/yyyy hh:mm:ss"));
            QTableWidgetItem* lastChange= new QTableWidgetItem(userMedia[it]->getLastChange().toString("dd/MM/yyyy hh:mm:ss"));
            QTableWidgetItem* erase= new QTableWidgetItem;
            
            id->setFlags(Qt::NoItemFlags);
            title->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);    //unico selezionabile per modifiche!
            type->setFlags(Qt::NoItemFlags);
            creationDate->setFlags(Qt::NoItemFlags);
            lastChange->setFlags(Qt::NoItemFlags);
            erase->setFlags(Qt::ItemIsEnabled);
            
            mediaTable->setItem(row,0,id);
            mediaTable->setItem(row,1,title);
            mediaTable->setItem(row,2,type);
            mediaTable->setItem(row,3,creationDate);
            mediaTable->setItem(row,4,lastChange);
            mediaTable->setItem(row,5,erase);
            erase->setIcon(QIcon(":VIEW/IMGs/remove_dark.png"));
            
            row++;
            
        }
    }
}

//-------------------------PV METHOD------------------------

void userView::loadGraphic(){
    setWindowTitle("Diario utente - Mediary");
    
    setFixedSize(700,600);
    
    centerWidget();
    
    mainLayout = new QVBoxLayout;
    mainGBox = new QGroupBox;
    
    mediaTable = new QTableWidget;
    mediaCBox= new QComboBox();
    
    newMediaButton = new QPushButton("Crea Media");
        newMediaButton->setCheckable(true);
    newSerieTvButton = new QPushButton("Crea SerieTV");
    newFilmButton = new QPushButton("Crea Film");
    
    QVBoxLayout* boxLayout = new QVBoxLayout;
    
    QLabel* displayLabel= new QLabel("Visualizza:");
    
    mediaCBox->addItem("Tutti");
    mediaCBox->addItem("SerieTV");
    mediaCBox->addItem("Film");
    
    connect(mediaCBox,SIGNAL(currentIndexChanged(int)),SLOT(optionMediaLoad(int)));
    
    //Gestione e logout
    QPushButton* manageUserDataButton= new QPushButton("Gestisci Dati utente");
    QPushButton* logoutButton= new QPushButton("Logout");
    
    //Set info mediaTable
    QStringList info;
    info<<""<<"Titolo"<<"Tipo"<<"Data di creazione"<<"Data ultima modifica"<<"X";
    
    mediaTable->setColumnCount(6);  //numero colonne 0-5
    mediaTable->setColumnHidden(0,true);
    mediaTable->setHorizontalHeaderLabels(info); //setta i label sopra ogni colonna in ordine
    mediaTable->setAutoScroll(false);
    //Set dimensioni mediaTable
    mediaTable->setMinimumWidth(650);
    mediaTable->setMinimumHeight(250);
    
    mediaTable->setColumnWidth(0,11);   //Id
    mediaTable->setColumnWidth(1,177);  //Title
    mediaTable->setColumnWidth(2,100);  //Type
    mediaTable->setColumnWidth(3,160);  //Creation date
    mediaTable->setColumnWidth(4,160);  //Last change
    mediaTable->setColumnWidth(5,30);   //eraseButton
    
    //Carica la lista dei media e connetti le celle
    loadMediaTable(user->getMedia());
    connect(mediaTable,SIGNAL(cellClicked(int,int)),this,SLOT(optionMediaTable(int,int)));    
    
    //---------SETTA LAYOUT-----------
    
    boxLayout->addWidget(newMediaButton);
    boxLayout->addWidget(newSerieTvButton);
        newSerieTvButton->hide();
    boxLayout->addWidget(newFilmButton);
        newFilmButton->hide();
    boxLayout->addWidget(displayLabel);
    boxLayout->addWidget(mediaCBox);
    boxLayout->addWidget(mediaTable);
    boxLayout->addWidget(manageUserDataButton);
    boxLayout->addWidget(logoutButton);
    
    mainGBox->setLayout(boxLayout);
    mainLayout->addWidget(mainGBox);
    setLayout(mainLayout);   
    
    //Connessioni
    connect(manageUserDataButton,SIGNAL(clicked()),this,SLOT(openUserData()));
    connect(logoutButton,SIGNAL(clicked()),this,SLOT(Logout()));
    connect(newMediaButton,SIGNAL(clicked()),this,SLOT(openMediaBox()));
}

//-------------------------PUBLIC SLOTS------------------------

//--------OPEN

void userView::openMediaBox(){
    newMediaButton->setChecked(true);
    newSerieTvButton->show();
    newFilmButton->show();
    
    disconnect(newMediaButton,SIGNAL(clicked()),this,SLOT(openMediaBox())); // è già aperta. bisogna disconnettere!    
    connect(newMediaButton,SIGNAL(clicked()),this,SLOT(closeMediaBox()));   // se lo riclicco si chiude
    
    connect(newSerieTvButton,SIGNAL(clicked()),this,SLOT(openNewSerieTv()));
    connect(newFilmButton,SIGNAL(clicked()),this,SLOT(openNewFilm()));
        
    //.....ready for extensibility......
}

void userView::openNewSerieTv(){
    if(serieTvView==0){
        serieTvView= new SerietvView;
        serieTvView->show();
        
        connect(serieTvView,SIGNAL(signalSave(const QString& ,unsigned int ,const QString& ,const QString& ,unsigned int ,unsigned int ,unsigned int )),this,SLOT(saveSerieTv(const QString& ,unsigned int ,const QString& ,const QString& ,unsigned int ,unsigned int ,unsigned int )));
        connect(serieTvView,SIGNAL(signalCancel()),this,SLOT(closeSerieTvView()));
    }
}

void userView::openNewFilm(){
    if(filmView==0){
        filmView= new FilmView;
        filmView->show();
        
        connect(filmView,SIGNAL(signalSave(const QString& ,unsigned int ,const QString& ,const QString& ,const QString& ,const QTime& )),this,SLOT(saveFilm(const QString& ,unsigned int ,const QString& ,const QString& ,const QString& ,const QTime& )));
        connect(filmView,SIGNAL(signalCancel()),this,SLOT(closeFilmView()));
    }
}

void userView::openUserData(){
    if(userInfoView==0){
        userInfoView= new userDataView(user);
        userInfoView->show();
        
        connect(userInfoView,SIGNAL(signalConfirm(QString,QString,QString,const QString&)),this,SLOT(modifyUserData(const QString& ,const QString& ,const QString& ,const QString& )));
        connect(userInfoView,SIGNAL(signalCancel()),this,SLOT(closeUserDataView()));
    }
}

//--------CLOSE

void userView::closeMediaBox(){
    newMediaButton->setChecked(false);
    
    disconnect(newMediaButton,SIGNAL(clicked()),this,SLOT(closeMediaBox()));
    disconnect(newSerieTvButton,SIGNAL(clicked()),this,SLOT(openNewSerieTv()));
    disconnect(newFilmButton,SIGNAL(clicked()),this,SLOT(openNewFilm()));
    
    connect(newMediaButton,SIGNAL(clicked()),this,SLOT(openMediaBox()));
    newSerieTvButton->hide();
    newFilmButton->hide();
}

void userView::closeSerieTvView(){
    QMessageBox::StandardButton warning;
    warning=QMessageBox::question(this, "Attenzione, Salvataggio non effettuato!!" , "Le modifiche non salvate andranno perse! Sei sicuro di uscire?", QMessageBox::Yes|QMessageBox::No);
    
    if (warning==QMessageBox::Yes){
        delete serieTvView;
        serieTvView=0;
    }
}

void userView::closeFilmView(){
    QMessageBox::StandardButton warning;
    warning=QMessageBox::question(this, "Attenzione, Salvataggio non effettuato!!" , "Le modifiche non salvate andranno perse! Sei sicuro di uscire?", QMessageBox::Yes|QMessageBox::No);
    
    if (warning==QMessageBox::Yes){
        delete filmView;
        filmView=0;
    }
}

void userView::closeUserDataView(){
    QMessageBox::StandardButton warning;
    warning=QMessageBox::question(this, "Attenzione, Salvataggio non effettuato!!" , "Le modifiche non salvate andranno perse! Sei sicuro di uscire?", QMessageBox::Yes|QMessageBox::No);
    
    if (warning==QMessageBox::Yes){
        delete userInfoView;
        userInfoView=0;
    }
    this->show();
}


//--------SAVE

void userView::saveSerieTv(const QString& title, unsigned int year, const QString& genre, const QString& descr, unsigned int season, unsigned int numEp, unsigned int lenght){
    emit signalSaveSerieTv(title,year,genre,descr,season,numEp,lenght);
    
    loadMediaTable(user->getMedia()); //Update vista
    
    delete serieTvView;
    serieTvView=0;
}

void userView::saveFilm(const QString& title, unsigned int year, const QString& genre, const QString& plot, const QString& distribution, const QTime& duration){
    emit signalSaveFilm(title,year,genre,plot,distribution,duration);
    
    loadMediaTable(user->getMedia());
    
    delete filmView;
    filmView=0;
}

//--------MODIFICATION

void userView::modifySerieTv(const QString& title, unsigned int year, const QString& genre, const QString& descr, unsigned int season, unsigned int numEp, unsigned int lenght, int id){
    emit signalChangeSerieTv(title,year,genre,descr,season,numEp,lenght,id);
    
    loadMediaTable(user->getMedia());
    
    delete serieTvView;
    serieTvView=0;
}

void userView::modifyFilm(const QString& title, unsigned int year, const QString& genre, const QString& plot, const QString& distribution, const QTime& duration, int id){
    emit signalChangeFilm(title,year,genre,plot,distribution,duration,id);
    
    loadMediaTable(user->getMedia());
    
    delete filmView;
    filmView=0;
}

void userView::modifyUserData(const QString& username, const QString& name, const QString& surname, const QString& sex){
    emit signalChangeUserData(username,name,surname,sex);
    
    delete userInfoView;
    userInfoView=0;
}

//--------FEATURES

void userView::optionMediaTable(int row, int c){
    //prelevo id
    int id= mediaTable->item(row,0)->text().toInt();
    
    if(c==5){   // cliccato il bottone per cancellazione media (in col. 5)
        QMessageBox::StandardButton warning;
        warning=QMessageBox::question(this,"Elimizazione media","Confermi di voler eliminare questo media dal tuo diario?",QMessageBox::Yes|QMessageBox::No);
        if(warning==QMessageBox::Yes){
            mediaTable->removeRow(row);
            
            emit signalDeleteMedia(id);
            
            loadMediaTable(user->getMedia()); //update vista 
        }
    }
    else if(c==1 && mediaTable->item(row,2)->text()=="SerieTV"){   //open existing serieTV
        const Media* ptm=user->findMedia(id);
        
        serieTvView= new SerietvView(dynamic_cast<const SerieTV*>(ptm));
        serieTvView->show();
        
        connect(serieTvView,SIGNAL(signalChange(const QString& ,unsigned int ,const QString& ,const QString& ,unsigned int ,unsigned int ,unsigned int ,int )),this,SLOT(modifySerieTv(const QString& ,unsigned int ,const QString& ,const QString& ,unsigned int ,unsigned int ,unsigned int ,int )));
        connect(serieTvView,SIGNAL(signalCancel()),this,SLOT(closeSerieTvView()));
        
    }
    else if(c==1 && mediaTable->item(row,2)->text()=="Film"){ //open existing film
        const Media* ptm=user->findMedia(id);
       
        filmView= new FilmView(dynamic_cast<const Film*>(ptm));
        filmView->show();
        
        connect(filmView,SIGNAL(signalChange(const QString& ,unsigned int ,const QString& ,const QString& ,const QString& ,const QTime& ,int )),this,SLOT(modifyFilm(const QString& ,unsigned int ,const QString& ,const QString& ,const QString& ,const QTime& ,int )));
        connect(filmView,SIGNAL(signalCancel()),this,SLOT(closeFilmView()));
        
    }
}

void userView::optionMediaLoad(int get){
    if(get==0)//all
        loadMediaTable(user->getMedia());
    else if(get==1)//serie
        loadMediaTable(user->getSerieTV());
    else if(get==2)//films
        loadMediaTable(user->getFilms());
}

//--------LOGOUT

void userView::Logout(){
    if(serieTvView)
        delete serieTvView;
    if(filmView)
        delete filmView;
    if(userInfoView)
        delete userInfoView;
    
    emit signalLogout();
}
