/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:20:34 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: settingpage.cpp
 * Project: embeded final supervisor
 * Description: 
 */

#include "settingpage.h"
#include "ui_settingpage.h"

SettingPage::SettingPage(QWidget *parent, const QString& label) :
    PageWidget(parent,label),
    ui(new Ui::SettingPage)
{
    ui->setupUi(this);
}

SettingPage::~SettingPage()
{
    delete ui;
}

void SettingPage::on_return_btn_clicked()
{
    emit PopRequest();
}
