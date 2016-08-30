#include <QApplication>

#include "MODEL/Database.h"
#include "VIEW/loginView.h"
#include "CONTROLLER/mediaryController.h"

int main(int argc, char *argv[])
{
    QApplication Mediary(argc, argv);
    Database db;
    loginView startView;
    mediaryController controller(&db,&startView);
    
    return Mediary.exec();
}
