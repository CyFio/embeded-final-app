/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:20:12 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: pagewidget.cpp
 * Project: embeded final supervisor
 * Description: 
 */

#include "pagewidget.h"

PageWidget::PageWidget(QWidget *parent, const QString& label)
    : QWidget(parent), _label(label)
{
}

PageWidget::~PageWidget()
{
    unlink_backend();
}

int PageWidget::SetBackend(BackendManager *backend)
{
    return this->link_backend(backend);
}

PageWidget *PageWidget::Clone()
{
    PageWidget* cloned = new PageWidget((QWidget*)parent(), _label);
    cloned->SetBackend(this->_backend);
    return cloned;
}

int PageWidget::unlink_backend()
{
    return 1;
}

int PageWidget::link_backend(BackendManager *backend)
{
    this->_backend = backend;
    return 1;
}
