/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:22:03 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: settingpage.h
 * Project: embeded final supervisor
 * Description: 
 */

#ifndef SETTINGPAGE_H
#define SETTINGPAGE_H

#include "pagewidget/pagewidget.h"

namespace Ui {
class SettingPage;
}

class SettingPage : public PageWidget
{
    Q_OBJECT

public:
    explicit SettingPage(QWidget *parent = nullptr, const QString& label = "");
    ~SettingPage();

private slots:
    void on_return_btn_clicked();

private:
    Ui::SettingPage *ui;
};

#endif // SETTINGPAGE_H
