/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:18:05 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: backendmanager.h
 * Project: embeded final supervisor
 * Description: 
 */

#ifndef BACKENDMANAGER_H
#define BACKENDMANAGER_H

#include <QObject>

class RemoteManager;
class LocalManager;

class BackendManager : public QObject
{
    Q_OBJECT
public:
    struct config
    {
        QString db_dir;
        QString db_filename;
    };
    enum SETUP_RETURN_CODES{
        RETURN_SUCCESS = 0,
        CONNECTION_FAILED,
        LOCAL_FAILED
    };
    explicit BackendManager(QObject *parent = nullptr);
    ~BackendManager();
    int Setup(config&);

    RemoteManager* GetRemote(){return remote;}
    LocalManager* GetLocal(){return local;}

signals:

private:
    RemoteManager* remote;
    LocalManager* local;
};

#endif // BACKENDMANAGER_H
