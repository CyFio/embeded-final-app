/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:19:34 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: mainmenu.cpp
 * Project: embeded final supervisor
 * Description: 
 */

#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QPushButton>
#include "resistancepage/resistancepage.h"
#include "immornitorpage/immonitorpage.h"
#include "rchartpage/rchartpage.h"
#include "gallerypage/gallerypage.h"
#include "settingpage/settingpage.h"
#include "configure/include/configurationmanager.h"

MainMenu::MainMenu(QWidget *parent) :
    PageWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    ConfigurationManager& config = ConfigurationManager::Get();
    this->SetLabel(config.Query_String("pages.main_menu.title"));
    ui->rcurve_btn->setText(config.Query_String("pages.rchart.title"));
    ui->gallery_btn->setText(config.Query_String("pages.gallery.title"));
    ui->monitor_btn->setText(config.Query_String("pages.im_monitor.title"));
    ui->ressistance_btn->setText(config.Query_String("pages.resistance.title"));
    ui->settings_btn->setText(config.Query_String("pages.settings.title"));
}

MainMenu::~MainMenu()
{
    delete ui;
}

PageWidget *MainMenu::Clone()
{
    MainMenu* cloned = new MainMenu;
    cloned->SetBackend(this->_backend);
    return cloned;
}

void MainMenu::on_ressistance_btn_clicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if(btn != nullptr)
    {
        PageWidget* page = new ResistancePage(this, btn->text());
        page->SetBackend(this->_backend);
        emit PushRequest(page);
    }
}

void MainMenu::on_monitor_btn_clicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if(btn != nullptr)
    {
        PageWidget* page = new ImMonitorPage(this, btn->text());
        page->SetBackend(this->_backend);
        emit PushRequest(page);
    }
}

void MainMenu::on_rcurve_btn_clicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
     if(btn != nullptr)
     {
        PageWidget* page = new RChartPage(this, btn->text());
        page->SetBackend(this->_backend);
        emit PushRequest(page);
     }
}

void MainMenu::on_gallery_btn_clicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
     if(btn != nullptr)
     {
        PageWidget* page = new GalleryPage(this, btn->text());
        page->SetBackend(this->_backend);
        emit PushRequest(page);
     }
}

void MainMenu::on_settings_btn_clicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
     if(btn != nullptr)
     {
        PageWidget* page = new SettingPage(this, btn->text());
        page->SetBackend(this->_backend);
        emit PushRequest(page);
     }
}


int MainMenu::unlink_backend()
{
    return PageWidget::unlink_backend();
}

int MainMenu::link_backend(BackendManager *backend)
{
    return PageWidget::link_backend(backend);
}

void MainMenu::on_exit_btn_clicked()
{
    QWidget* w = this;
    QWidget* wp = qobject_cast<QWidget*>(w->parent());
    while(wp){
        w = wp;
        wp = qobject_cast<QWidget*>(w->parent());
    }
    w->close();
}
