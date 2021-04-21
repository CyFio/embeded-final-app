/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:18:03 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: backendmanager.cpp
 * Project: embeded final supervisor
 * Description: 
 */

#include "backendmanager.h"
#include "remote/remotemanager.h"
#include "local/localmanager.h"
#include "local/rdatamanager.h"
#include "remote/remoteadc.h"
#include "remote/remotecamera.h"
#include "local/imgdatamanager.h"

BackendManager::BackendManager(QObject *parent)
    : QObject(parent), remote(new RemoteManager), local(new LocalManager)
{

}

BackendManager::~BackendManager()
{
    RemoteADC* adc = remote->GetADC();
    RDataManager* rdata = local->Get_RDataManager();
    RemoteCamera* cam = remote->GetCamera();
    ImgDataManager* img_data = local->Get_ImgDataManager();
    disconnect(adc,&RemoteADC::resistance_changed, rdata, &RDataManager::on_resistance_received);
//    disconnect(cam, &RemoteCamera::img_received, img_data, &ImgDataManager::on_img_received);

    remote->deleteLater();
    local->deleteLater();
}

int BackendManager::Setup(config& cfg)
{
    if(!remote->Setup("cyfio2.tpddns.cn:12183", "Supervisor", "xjh", "213170687", 1.0f))
    {
        return CONNECTION_FAILED;
    }
    LocalManager::config local_cfg;
    local_cfg.db_dir = cfg.db_dir;
    local_cfg.db_name = cfg.db_filename;
    if(!local->Setup(local_cfg)){
        return LOCAL_FAILED;
    }
    RemoteADC* adc = remote->GetADC();
    RDataManager* rdata = local->Get_RDataManager();
    connect(adc,&RemoteADC::resistance_changed, rdata, &RDataManager::on_resistance_received);
    RemoteCamera* cam = remote->GetCamera();
    ImgDataManager* img_data = local->Get_ImgDataManager();
    connect(cam, &RemoteCamera::img_received, img_data, &ImgDataManager::on_img_received);

    return RETURN_SUCCESS;
}
