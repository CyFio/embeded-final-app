/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:20:45 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: stackedpage.cpp
 * Project: embeded final supervisor
 * Description: 
 */

#include "stackedpage.h"
#include "ui_stackedpage.h"
#include <QStackedWidget>

StackedPage::StackedPage(QWidget *parent) :
    PageWidget(parent),
    ui(new Ui::StackedPage),
    ui_stack(new QStackedWidget(parent))
{
    ui->setupUi(this);
    ui->horizontalLayout->addWidget(ui_stack);
    connect(ui_stack,&QStackedWidget::currentChanged,this, &StackedPage::SetLabelFromCurrentId);
}

StackedPage::~StackedPage()
{
    delete ui;
}

PageWidget *StackedPage::Clone()
{
    StackedPage* cloned_instance = new StackedPage;
    for (auto i = page_stack.begin();i < page_stack.end(); ++i) {
        cloned_instance->PushPage((*i)->Clone());
    }
    return cloned_instance;
}

bool StackedPage::PushPage(PageWidget *page)
{
    if(page != nullptr)
    {
        int id = ui_stack->addWidget(page);
        page_stack.push(page);
        ui_stack->setCurrentIndex(id);
        connect(page, &PageWidget::PushRequest, this, &StackedPage::On_Push_Request);
        connect(page, &PageWidget::PopRequest, this, &StackedPage::On_Pop_Request);
        return true;
    }
    return false;
}

bool StackedPage::PopPage()
{
    if(ui_stack->count()<1){
        return false;
    }
    PageWidget* page_to_remove = page_stack.pop();
    ui_stack->removeWidget(page_to_remove);
    ui_stack->setCurrentIndex(ui_stack->count()-1);
    page_to_remove->deleteLater();
    return true;
}

void StackedPage::On_Push_Request(PageWidget *page_to_push)
{
    if(page_to_push != nullptr)
    {
        PushPage(page_to_push);
    }
}

void StackedPage::On_Pop_Request()
{
    PopPage();
}

void StackedPage::SetLabelFromCurrentId(int id)
{
    PageWidget* current = qobject_cast<PageWidget*>(ui_stack->currentWidget());
    this->SetLabel(current->GetLabel());
}
