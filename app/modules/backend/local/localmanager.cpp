/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:17:16 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: localmanager.cpp
 * Project: embeded final supervisor
 * Description: 
 */

#include "localmanager.h"
#include "localdatamanager.h"
#include "rdatamanager.h"
#include "imgdatamanager.h"
#include "rdatamanager.h"

LocalManager::LocalManager(QObject *parent) : QObject(parent),
    db_manager(new LocalDataManager), rdata_manager(new RDataManager), imgdata_manager(new ImgDataManager())
{

}

LocalManager::~LocalManager()
{
    delete rdata_manager;
    delete imgdata_manager;
    delete db_manager;
}

int LocalManager::Setup(LocalManager::config &cfg)
{
    this->db_manager->SetUp(cfg.db_dir, cfg.db_name);
    this->rdata_manager->SetUp(*(this->db_manager));
    this->imgdata_manager->SetUp(*(this->db_manager));
    return 1;
}
