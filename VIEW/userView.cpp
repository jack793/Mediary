#include "userView.h"

//-------------------------COSTRUTTORI------------------------

userView::userView(User *u, MainView *parent): user(u), MainView(parent)
{
    loadGraphic();
}

userView::~userView() {}

//-------------------------METODI------------------------

userView::closeEvent(QCloseEvent* ){
    emit signalLogout();
}

userView::loadMediaTable(const Container<const Media *>& userMedia){
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
            title->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            type->setFlags(Qt::NoItemFlags);
            creationDate->setFlags(Qt::NoItemFlags);
            lastChange->setFlags(Qt::NoItemFlags);
            erase->setFlags(Qt::NoItemFlags);
            
            mediaTable->setItem(row,0,id);
            mediaTable->setItem(row,1,title);
            mediaTable->setItem(row,2,type);
            mediaTable->setItem(row,3,creationDate);
            mediaTable->setItem(row,4,lastChange);
            mediaTable->setItem(row,5,erase);
            erase->setIcon(QIcon(":/Icons/remove_dark2.png"));
            
            row++;
            
        }
    }
}

//-------------------------PV METHOD------------------------

void userView::loadGraphic(){
    setWindowTitle("Diario utente - Mediary");
    
    mainLayout = new QVBoxLayout;
    mainGBox = new QGroupBox;
    
    mediaTable = new QTableWidget;
    mediaCBox= new QComboBox();
    
    newMediaButton = new QPushButton("Crea Media");
        newMediaButton->setCheckable(true);
    newSerieTvButton = new QPushButton("Crea SerieTV");
    newFilmButton = new QPushButton("Crea Film");
    
    QLabel* displayLabel= new QLabel("Visualizza:");
    
    mediaCBox->addItem("Tutti");
    mediaCBox->addItem("SerieTV");
    mediaCBox->addItem("Film");
    
    connect(mediaCBox,SIGNAL(currentIndexChanged(int)),SLOT(optionMediaLoad(int)));
    
    //Set info mediaTable
    QStringList info;
    info<<"Id"<<"Titolo"<<"Tipo"<<"Data di creazione"<<"Data ultima modifica";
    
    mediaTable->setColumnCount(6);  //numero colonne 0-5
    mediaTable->setHorizontalHeaderLabels(info); //setta i label sopra ogni colonna in ordine
    mediaTable->setAutoScroll(false);
    //Set dimensioni mediaTable
    mediaTable->setMinimumWidth(650);
    mediaTable->setMinimumHeight(300);
    mediaTable->setColumnWidth(0,10);   //Id
    mediaTable->setColumnWidth(1,150);  //Title
    mediaTable->setColumnWidth(2,100);  //Type
    mediaTable->setColumnWidth(3,150);  //Creation date
    mediaTable->setColumnWidth(4,150);  //Last change
    mediaTable->setColumnWidth(5,30);   //eraseButton
    
    //Carica la lista dei media e connetti le celle
    loadMediaTable(user->getMedia());
    connect(mediaTable,SIGNAL(cellClicked(int,int)),this,SLOT(optionMediaTable(int,int)));
    
    //Gestione e logout
    QPushButton* manageUserDataButton= new QPushButton("Gestisci Dati utente");
    QPushButton* logoutButton= new QPushButton("Logout");
    
    connect(manageUserDataButton,SIGNAL(clicked()),this,SLOT(openUserData()));
    connect(logoutButton,SIGNAL(clicked()),this,SLOT(Logout()));
    
    //---------SETTA LAYOUT-----------
    QVBoxLayout* boxLayout = new QVBoxLayout;
    
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
    
    connect(newMediaButton,SIGNAL(clicked()),this,SLOT(openMediaBox()));
}

//-------------------------PUBLIC SLOTS------------------------

//--------OPEN

void userView::openMediaBox(){
    newMediaButton->setChecked(true);
    disconnect(newMediaButton,SIGNAL(clicked()),this,SLOT(openMediaBox()));
    
    newSerieTvButton->show();
    connect(newSerieTvButton,SIGNAL(clicked()),this,SLOT(openNewSerieTv()));
    
    newFilmButton->show();
    connect(newFilmButton,SIGNAL(clicked()),this,SLOT(openNewFilm()));
    
    //.....ready for extensibility......
}

void userView::openNewSerieTv(){
    if(!serieTvView){
        serieTvView= new SerietvView;
        serieTvView->show();
        
        connect(serieTvView,SIGNAL(signalSave(const QString& ,const QDate& ,const QString& ,const QString& ,unsigned int ,unsigned int ,unsigned int )),this,SLOT(saveSerieTv(const QString& ,const QDate& ,const QString& ,const QString& ,unsigned int ,unsigned int ,unsigned int )));
        connect(serieTvView,SIGNAL(signalCancel()),this,SLOT(closeSerieTvView()));
    }
}

void userView::openNewFilm(){
    if(!filmView){
        filmView= new FilmView;
        filmView.show();
        
        connect(filmView,SIGNAL(signalSave(const QString& ,const QDate& ,const QString& ,const QString& ,const QString& ,const QTime& )),this,SLOT(saveFilm(const QString& ,const QDate& ,const QString& ,const QString& ,const QString& ,const QTime& )));
        connect(filmView,SIGNAL(signalCancel()),this,SLOT(closeFilmView()));
    }
}

void userView::openUserData(){
    if(!userInfoView){
        userInfoView= new userDataView;
        userInfoView->show;
        
        connect(userInfoView,SIGNAL(signalConfirm(QString,QString,QString,bool)),this,SLOT(modifyUserData(const QString& ,const QString& ,const QString& ,bool )));
        connect(userInfoView,SIGNAL(signalCancel()),this,SLOT(closeUserDataView()));
    }
}

//--------CLOSE

void userView::closeMediaBox(){
    newMediaButton->setChecked(false);
    newSerieTvButton->hide();
    newFilmButton->hide();
    
    disconnect(newMediaButton,SIGNAL(clicked()),this,SLOT(closeMediaBox()));
    disconnect(newSerieTvButton,SIGNAL(clicked()),this,SLOT(openNewSerieTv()));
    disconnect(newFilmButton,SIGNAL(clicked()),this,SLOT(openNewFilm()));
    
    connect(newMediaButton,SIGNAL(clicked()),this,SLOT(openMediaBox()));
}

void userView::closeSerieTvView(){
    QMessageBox::StandardButton warning;
    warning=QMessageBox::question(this, "Attenzione, Salvataggio non effettuato!!" , "Le modifiche non salvate andranno perse! Sei sicuro di uscire?", QMessageBox::Yes|QMessageBox::No);
    warning.setIcon(QIcon(":/Icons/warning_dark.png"));
    warning.show();
    
    if (warning==QMessageBox::Yes){
        delete serieTvView;
        serieTvView=0;
    }
}

void userView::closeFilmView(){
    QMessageBox::StandardButton warning;
    warning=QMessageBox::question(this, "Attenzione, Salvataggio non effettuato!!" , "Le modifiche non salvate andranno perse! Sei sicuro di uscire?", QMessageBox::Yes|QMessageBox::No);
    warning.setIcon(QIcon(":/Icons/warning_dark.png"));
    warning.show();
    
    if (warning==QMessageBox::Yes){
        delete filmView;
        filmView=0;
    }
}

void userView::closeUserDataView(){
    QMessageBox::StandardButton warning;
    warning=QMessageBox::question(this, "Attenzione, Salvataggio non effettuato!!" , "Le modifiche non salvate andranno perse! Sei sicuro di uscire?", QMessageBox::Yes|QMessageBox::No);
    warning.setIcon(QIcon(":/Icons/warning_dark.png"));
    warning.show();
    
    if (warning==QMessageBox::Yes){
        delete userInfoView;
        userInfoView=0;
    }
}

//--------SAVE

void userView::saveSerieTv(const QString& title, const QDate& year, const QString& genre, const QString& descr, unsigned int season, unsigned int numEp, unsigned int lenght){
    emit signalSaveSerieTv(title,year,genre,descr,season,numEp,lenght);
    
    loadMediaTable(user->getMedia()); //Update vista
    
    delete serieTvView;
    serieTvView=0;
}

void userView::saveFilm(const QString& title, const QDate& year, const QString& genre, const QString& plot, const QString& distribution, const QTime& duration){
    emit signalSaveFilm(title,year,genre,plot,distribution,duration);
    
    loadMediaTable(user->getMedia());
    
    delete filmView;
    filmView=0;
}

//--------MODIFICATION

void userView::modifySerieTv(const QString& title, const QDate& year, const QString& genre, const QString& descr, unsigned int season, unsigned int numEp, unsigned int lenght, int id){
    emit signalChangeSerieTv(title,year,genre,descr,season,numEp,lenght,id);
    
    loadMediaTable(user->getMedia());
    
    delete serieTvView;
    serieTvView=0;
}

void userView::modifyFilm(const QString& title, const QDate& year, const QString& genre, const QString& plot, const QString& distribution, const QTime& duration, int id){
    emit signalChangeFilm(title,year,genre,plot,distribution,duration,id);
    
    loadMediaTable(user->getMedia());
    
    delete filmView;
    filmView=0;
}

void userView::modifyUserData(const QString& username, const QString& name, const QString& surname, bool sex){
    emit signalChangeUserData(username,name,surname,sex);
    
    delete userInfoView;
    userInfoView=0;
}

//--------FEATURES

void userView::optionMediaTable(int row, int choice){
    //prelevo id
    int id= mediaTable->item(row,0)->text().toInt();
    
    if(!choice){
        QMessageBox::standardButton warning;
        warning=QMessageBox::question(this,"Elimizazione media","Confermi di voler eliminare questo media dal tuo diario?",QMessageBox::Yes|QMessageBox::No);
        if(warning==QMessageBox::Yes){
            mediaTable->removeRow(row);
            
            emit signalDeleteMedia(id);
            
            loadMediaTable(user->getMedia()); //update vista 
        }
    }
    else if(c && mediaTable->item(row,2)->text()=="SerieTV"){   //open existing serieTV
        const Media* ptm=user->findMedia(id);
        
        if(ptm){
            serieTvView= new SerietvView(dynamic_cast<const SerieTV*>(ptm));
            serieTvView->show();
            
            connect(serieTvView,SIGNAL(signalChange(const QString& t,const QDate& y,const QString& g,const QString& d,unsigned int s,unsigned int n,unsigned int l,int id)),this,SLOT(modifySerieTv(const QString& t,const QDate& y,const QString& g,const QString& d,unsigned int s,unsigned int n,unsigned int l,int id)));
            connect(serieTvView,SIGNAL(signalCancel()),this,SLOT(closeSerieTvView()));
        }
    }
    else if(c && mediaTable->item(row,2)->text()=="Film"){
        const Media* ptm=user->findMedia(id);
        
        if(ptm){
            filmView= new FilmView(dynamic_cast<const Film*>(ptm));
            filmView->show();
            
            connect(filmView,SIGNAL(signalChange(const QString& t,const QDate& y,const QString& g,const QString& p,const QString& d,const QTime& dur,int id)),this,SLOT(modifyFilm(const QString& t,const QDate& y,const QString& g,const QString& p,const QString& d,const QTime& dur,int id)));
            connect(filmView,SIGNAL(signalCancel()),this,SLOT(closeFilmView()));
        }
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
