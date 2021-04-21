/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:20:19 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: rchartpage.cpp
 * Project: embeded final supervisor
 * Description: 
 */

#include "rchartpage.h"
#include "ui_rchartpage.h"
#include "fromtoedit/fromtoedit.h"
#include "backend/local/localmanager.h"
#include "backend/local/rdatamanager.h"

using namespace QtCharts;

RChartPage::RChartPage(QWidget *parent, const QString& label) :
    PageWidget(parent,label),
    ui(new Ui::RChartPage), from_to_edit(new FromToEdit)
{
    ui->setupUi(this);
    ui->top_layout->insertWidget(1, from_to_edit);
    this->chart_view = new QChartView();
    this->ui->frame->layout()->addWidget(this->chart_view);
    connect(from_to_edit, &FromToEdit::from_to_apply, this, &RChartPage::on_from_to_apply);
}

RChartPage::~RChartPage()
{
    delete ui;
}

void RChartPage::on_return_btn_clicked()
{
    emit PopRequest();
}

void RChartPage::on_from_to_apply(QDateTime from, QDateTime to)
{
    if(this->chart_view){
        emit query_rchart(from, to, *(this->chart_view));
    }
}


int RChartPage::unlink_backend()
{
    PageWidget::unlink_backend();
    if(this->_backend)
    {
        LocalManager* local = this->_backend->GetLocal();
        RDataManager* rdata = local->Get_RDataManager();
        disconnect(this, &RChartPage::query_rchart, rdata, &RDataManager::on_chart_query);
    }
    return 1;
}

int RChartPage::link_backend(BackendManager *backend)
{
    PageWidget::unlink_backend();
    this->_backend = backend;
    if(backend)
    {
        LocalManager* local = this->_backend->GetLocal();
        RDataManager* rdata = local->Get_RDataManager();
        connect(this, &RChartPage::query_rchart, rdata, &RDataManager::on_chart_query);
        return 1;
    }
    return 0;
}
