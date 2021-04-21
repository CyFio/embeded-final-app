/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:18:11 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: configurationmanager.cpp
 * Project: embeded final supervisor
 * Description: 
 */

//#include "configuationmanager.h"
#include "configure/include/configurationmanager.h"
#include <QFile>
#include <QFileInfo>
#include <QStringList>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDateTime>

ConfigurationManager::~ConfigurationManager()
{
    if(this->configs != nullptr)
        delete this->configs;
}

int ConfigurationManager::Query_Int(const QString& url)
{
    if(this->configs == nullptr) return 0;
    QStringList list = url.split('.');
    QStringList::iterator i = list.begin();
    QJsonObject current_node = *(this->configs);
    QJsonObject::iterator child_iter = current_node.find(*i);
    for(; i < list.end()-1; ++i){
        child_iter=current_node.find(*i);
        if(child_iter == current_node.end() || child_iter->type() != QJsonValue::Object)
            return 0;
        current_node=child_iter.value().toObject();
    }
    return current_node.find(*i).value().toInt();
}

double ConfigurationManager::Query_Double(const QString &url)
{
    if(this->configs == nullptr) return 0.0f;
    QStringList list = url.split('.');
    QStringList::iterator i = list.begin();
    QJsonObject current_node = *(this->configs);
    QJsonObject::iterator child_iter = current_node.find(*i);
    for(; i < list.end()-1; ++i){
        child_iter=current_node.find(*i);
        if(child_iter == current_node.end() || child_iter->type() != QJsonValue::Object)
            return 0.0f;
        current_node=child_iter.value().toObject();
    }
    return current_node.find(*i).value().toDouble();
}

QString ConfigurationManager::Query_String(const QString &url)
{
    if(this->configs == nullptr) return "";
    QStringList list = url.split('.');
    QStringList::iterator i = list.begin();
    QJsonObject current_node = *(this->configs);
    QJsonObject::iterator child_iter = current_node.find(*i);
    for(; i < list.end()-1; ++i){
        child_iter=current_node.find(*i);
        if(child_iter == current_node.end() || child_iter->type() != QJsonValue::Object)
            return "";
        current_node=child_iter.value().toObject();
    }
    return current_node.find(*i).value().toString();
}

QJsonArray ConfigurationManager::Query_Array(const QString &url)
{
    if(this->configs == nullptr) return QJsonArray();
    QStringList list = url.split('.');
    QStringList::iterator i = list.begin();
    QJsonObject current_node = *(this->configs);
    QJsonObject::iterator child_iter = current_node.find(*i);
    for(; i < list.end()-1; ++i){
        child_iter=current_node.find(*i);
        if(child_iter == current_node.end() || child_iter->type() != QJsonValue::Array)
            return QJsonArray();
        current_node=child_iter.value().toObject();
    }
    return current_node.find(*i).value().toArray();
}

QJsonObject ConfigurationManager::Query_Object(const QString &url)
{
    if(this->configs == nullptr) return QJsonObject();
    QStringList list = url.split('.');
    QStringList::iterator i = list.begin();
    QJsonObject current_node = *(this->configs);
    QJsonObject::iterator child_iter = current_node.find(*i);
    for(; i < list.end()-1; ++i){
        child_iter=current_node.find(*i);
        if(child_iter == current_node.end() || child_iter->type() != QJsonValue::Object)
            return QJsonObject();
        current_node=child_iter.value().toObject();
    }
    return current_node.find(*i).value().toObject();
}

ConfigurationManager::ConfigurationManager()
{
    ConfigurationManager::configs = nullptr;
    QFile cfg_file(CONFIGURE_PATH);
    QFile default_cfg(DEFAULT_CONFIGURE_PATH);
    // create default configure if configure file not found in path
    // repace configure if default configure is newer
    if(!cfg_file.exists()){
        default_cfg.copy(CONFIGURE_PATH);
    }
    else
    {
        QFileInfo cfg_info(cfg_file.fileName());
        QFileInfo default_info(default_cfg.fileName());
        if(cfg_info.lastModified() < default_info.lastModified())
        {
            cfg_file.remove();
            default_cfg.copy(cfg_file.fileName());
        }
    }

    cfg_file.open(QIODevice::ReadOnly);
    QByteArray data=cfg_file.readAll();
    cfg_file.close();
    //使用json文件对象加载字符串
    QJsonDocument doc=QJsonDocument::fromJson(data);
    //判断是否对象
    if(doc.isObject())
    {
        ConfigurationManager::configs=new QJsonObject();
        *ConfigurationManager::configs=doc.object();
        return;
    }
    cfg_file.remove();
    default_cfg.copy(cfg_file.fileName());
    cfg_file.open(QIODevice::ReadOnly);
    data = cfg_file.readAll();
    cfg_file.close();
    doc = QJsonDocument::fromJson(data);
    if(doc.isObject())
    {
        ConfigurationManager::configs=new QJsonObject();
        *ConfigurationManager::configs=doc.object();
        return;
    }
}
