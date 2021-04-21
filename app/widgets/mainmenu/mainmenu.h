/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:19:38 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: mainmenu.h
 * Project: embeded final supervisor
 * Description: 
 */

#ifndef MAINMENU_H
#define MAINMENU_H

#include "pagewidget/pagewidget.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public PageWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();
    virtual PageWidget *Clone() override;
private slots:
    void on_ressistance_btn_clicked();

    void on_monitor_btn_clicked();

    void on_rcurve_btn_clicked();

    void on_gallery_btn_clicked();

    void on_settings_btn_clicked();

    void on_exit_btn_clicked();

private:
    Ui::MainMenu *ui;

    // PageWidget interface

    // PageWidget interface
protected:
    virtual int unlink_backend() override;
    virtual int link_backend(BackendManager *backend) override;
};

#endif // MAINMENU_H
