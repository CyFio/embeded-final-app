/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:19:51 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: mytabwidget.cpp
 * Project: embeded final supervisor
 * Description: 
 */

#include "mytabwidget.h"
#include "ui_mytabwidget.h"
#include <QTabWidget>
#include <QPushButton>
#include "pagewidget/pagewidget.h"

MyTabWidget::MyTabWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyTabWidget)
{
    this->default_page = new PageWidget;
    ui->setupUi(this);
//    ui->tabWidget->setCornerWidget(new QPushButton);
    ui->tabWidget->setCornerWidget(ui->addTab_btn);
//    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);
}

bool MyTabWidget::SetDefaultTabWidget(PageWidget *widget)
{
    if(widget != nullptr){
        PageWidget* tmp = this->default_page;
        this->default_page = widget;
        if(tmp != nullptr)
        {
            tmp->deleteLater();
        }
        return true;
    }
    return false;
}

bool MyTabWidget::Clear()
{
    ui->tabWidget->clear();
    PageWidget* new_page = this->default_page == nullptr? new PageWidget : this->default_page->Clone();
    AddWidget(new_page);
    return true;
}

bool MyTabWidget::AddWidget(PageWidget *new_widget, int index)
{
    if(new_widget == nullptr){
        new_widget = this->default_page->Clone();
    }
    ui->tabWidget->insertTab(index, new_widget, new_widget->GetLabel());
    connect(new_widget, &PageWidget::LabelChanged, this, &MyTabWidget::on_tabWidget_labelChanged);
    return true;
}

bool MyTabWidget::RemoveWidget(int index)
{
    if(index == -1){
        index = ui->tabWidget->count() - 1;
    }
    QWidget* page_to_remove = ui->tabWidget->widget(index);
    ui->tabWidget->removeTab(index);
//    PageWidget* page = qobject_cast<PageWidget*>(page_to_remove);
//    if(page != nullptr)
//        disconnect(page, &PageWidget::LabelChanged, this, &MyTabWidget::on_tabWidget_labelChanged);
    page_to_remove->deleteLater();
    return true;
}

MyTabWidget::~MyTabWidget()
{
    delete ui;
}

void MyTabWidget::on_addTab_btn_clicked()
{
    AddWidget();
    int index = ui->tabWidget->count() - 1;
    ui->tabWidget->setCurrentIndex(index);
}

void MyTabWidget::on_tabWidget_tabCloseRequested(int index)
{
    RemoveWidget(index);
    if(ui->tabWidget->count() == 0){
        AddWidget();
    }
}

void MyTabWidget::on_tabWidget_labelChanged(const QString& new_label)
{
    PageWidget* sender_page = qobject_cast<PageWidget*>(QObject::sender());
    if(sender_page != nullptr){
        int id = ui->tabWidget->indexOf(sender_page);
        ui->tabWidget->setTabText(id, new_label);
    }
}
