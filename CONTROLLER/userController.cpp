#include "userController.h"

//-------------------------COSTRUTTORI------------------------

userController::userController(User* u, QObject* parent): QObject(parent), user(u)
{
    user->loadMedia();  //Riempie il container dell'user con la load da db
    userUI= new userView(u);    //Creo la user view passandogli un pt user che contiente tutti i suoi dati nel model
        
    //All view connections
    connect(userUI,SIGNAL(signalSaveSerieTv(const QString& ,const QDate& ,const QString& ,const QString& ,unsigned int ,unsigned int ,unsigned int )),this,SLOT(saveSerieTv(const QString& ,const QDate& ,const QString& ,const QString& ,unsigned int ,unsigned int ,unsigned int )));
    connect(userUI,SIGNAL(signalSaveFilm(const QString& ,const QDate& ,const QString& ,const QString& ,const QString& ,const QTime& )),this,SLOT(saveFilm(const QString& ,const QDate& ,const QString& ,const QString& ,const QString& ,const QTime& )));
    connect(userUI,SIGNAL(signalChangeSerieTv(const QString& ,const QDate& ,const QString& ,const QString& ,unsigned int ,unsigned int ,unsigned int ,int )),this,SLOT(modifySerieTv(const QString& ,const QDate& ,const QString& ,const QString& ,unsigned int ,unsigned int ,unsigned int ,int )));
    connect(userUI,SIGNAL(signalChangeFilm(const QString& ,const QDate& ,const QString& ,const QString& ,const QString& ,const QTime& ,int )),this,SLOT(modifyFilm(const QString& ,const QDate& ,const QString& ,const QString& ,const QString& ,const QTime& ,int )));
    connect(userUI,SIGNAL(signalChangeUserData(const QString& ,const QString& ,const QString& ,bool )),this,SLOT(modifyUserData(const QString& ,const QString& ,const QString& ,bool )));
    connect(userUI,SIGNAL(signalDeleteMedia(int )),this,SLOT(deleteMedia(int )));
    connect(userUI,SIGNAL(signalLogout()),this,SLOT(closeUserView()));
}

userController::~userController(){
    delete userUI;
}

//-------------------------METODI------------------------

void userController::openUserView() const{
    userUI->show();
}

//-------------------------PUBLIC SLOTS------------------------

//--------SAVE
void userController::saveSerieTv(const QString& title, const QDate& year, const QString& genre, const QString& descr, unsigned int season, unsigned int numEp, unsigned int lenght){
    SerieTV* serieTv= new SerieTV(title,year,genre,descr,season,numEp,lenght);
    user->addMedia(serieTv); //ci sono già i controlli nella funzione (che non esista già lo stesso identico media)
}

void userController::saveFilm(const QString& title, const QDate& year, const QString& genre, const QString& plot, const QString& distribution, const QTime& duration){
    Film* film= new Film(title,year,genre,plot,distribution,duration);
    user->addMedia(film);
}

//--------MODIFICATION
void userController::modifySerieTv(const QString& title, const QDate& year, const QString& genre, const QString& descr, unsigned int season, unsigned int numEp, unsigned int lenght, int id){
    user->modifySerieTV(title,year,genre,descr,season,numEp,lenght,id);
}

void userController::modifyFilm(const QString& title, const QDate& year, const QString& genre, const QString& plot, const QString& distribution, const QTime& duration, int id){
    user->modifyFilm(title,year,genre,plot,distribution,duration,id);
}

void userController::modifyUserData(const QString& username, const QString& name, const QString& surname, bool sex){
    user->setUsername(username);
    user->setName(name);
    user->setSurname(surname);
    user->setSex(sex);
    
    dialMessage= new DialogMessage("Info","Modifiche effettuate con successo","Ok");
    dialMessage->setWindowIcon(QIcon(":/Icons/info_light.png"));
    dialMessage->show();
}

void userController::deleteMedia(int id){
    user->deleteMedia(id);
}

//--------CLOSE

void userController::closeUserView(){
    user->writeMedia(); //scrive tutti i dati attuali dello user nel database 
    user->emptyMediaDatabase(); //prima di svuotare
    emit signalHome();
}
