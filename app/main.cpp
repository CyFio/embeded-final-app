#include "widgets/mainwindow/mainwindow.h"

#include <QApplication>
#include <QDebug>
#include "backend/backendmanager.h"
#include "mytabwidget/mytabwidget.h"
#include "mainmenu/mainmenu.h"
#include "stackedpage/stackedpage.h"
#include "configure/include/configurationmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BackendManager backend;
//    qDebug()<<backend.Setup();
    MainWindow w;
    ConfigurationManager& global_cfg = ConfigurationManager::Get();

    BackendManager::config backend_cfg;
    backend_cfg.db_dir = global_cfg.Query_String("database.path");
    backend_cfg.db_filename = global_cfg.Query_String("database.name");
    if(backend.Setup(backend_cfg) == BackendManager::RETURN_SUCCESS)
    {

        MyTabWidget* my_tabs = new MyTabWidget;
        w.setCentralWidget(my_tabs);
        StackedPage* main_stackpage = new StackedPage;
        MainMenu* main_menu = new MainMenu;
        main_menu->SetBackend(&backend);
        main_stackpage->PushPage(main_menu);
        my_tabs->SetDefaultTabWidget(main_stackpage);
        my_tabs->Clear();
        w.LinkBackend(backend);
        w.show();
    }

    return a.exec();
}
