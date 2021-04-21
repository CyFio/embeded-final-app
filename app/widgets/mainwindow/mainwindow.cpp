/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:19:42 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: mainwindow.cpp
 * Project: embeded final supervisor
 * Description: 
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "backend/backendmanager.h"
#include "backend/remote/remotemanager.h"
#include "backend/remote/remotekeeper.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LinkBackend(BackendManager &backend)
{
    RemoteKeeper* keeper = backend.GetRemote()->GetKeeper();
    connect(keeper, &RemoteKeeper::ScoreChanged,this, &MainWindow::update_connection_state);
}

void MainWindow::update_connection_state(int val)
{
//    qDebug() << "score:" << val;
    if(val > 0){
        ui->statusBar->showMessage("connected");
    }
    else
    {
        ui->statusBar->showMessage("disconnected");
    }
}

