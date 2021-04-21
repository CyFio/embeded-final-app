/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:20:27 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: resistancepage.cpp
 * Project: embeded final supervisor
 * Description: 
 */

#include "resistancepage.h"
#include "ui_resistancepage.h"
#include <QPixmap>
#include "warninglabel/warninglabel.h"
#include "backend/backendmanager.h"
#include "backend/remote/remotemanager.h"
#include "backend/remote/remoteadc.h"
#include "backend/local/localmanager.h"
#include "backend/local/rdatamanager.h"
#include "labelslider/labelslider.h"

using namespace QtCharts;

ResistancePage::ResistancePage(QWidget *parent, const QString& label) :
    PageWidget(parent, label),
    ui(new Ui::ResistancePage)
{
    ui->setupUi(this);
    WarningLabel::config_t resistance_lbl_cfg ;
    resistance_lbl_cfg.title = "当前阻值";
    resistance_lbl_cfg.unit = "Ω";
    resistance_lbl_cfg.normal_pic_path = ":/ui/awesomes/icons/ok.png";
    resistance_lbl_cfg.warn_pic_path = ":/ui/awesomes/icons/warn.png";
    resistance_lbl = new WarningLabel(nullptr, resistance_lbl_cfg, 15000);
    LabelSlider::config_t label_slider_cfg;
    label_slider_cfg.title = "采样间隔";
    label_slider_cfg.unit = "s";
    label_slider_cfg.base = 0.1;
    label_slider_cfg.min = 1;
    label_slider_cfg.max = 50;
    label_slider_cfg.value = 10;
    interval_slider = new LabelSlider(nullptr, label_slider_cfg);
    ui->horizontalLayout->insertWidget(0, interval_slider);
    ui->horizontalLayout->insertWidget(0, resistance_lbl);
//    this->chart_view = new QChartView;
//    this->ui->rchart_container->layout()->addWidget(chart_view);
}

ResistancePage::~ResistancePage()
{
    delete ui;
}

void ResistancePage::on_resistance_receive(int resistance, QDateTime datetime)
{
    this->resistance_lbl->SetValue(resistance);
    if(_backend)
    {
        LocalManager* local = _backend->GetLocal();
        local->Get_RDataManager()->update_rt_chart(*(this->ui->rchart_lbl));
    }
}

void ResistancePage::on_interval_receive(float interval)
{
    this->interval_slider->SetValue(interval);
}

void ResistancePage::on_return_btn_clicked()
{
    emit PopRequest();
}


int ResistancePage::unlink_backend()
{
    PageWidget::unlink_backend();
    if(this->_backend)
    {
        RemoteManager* remote = this->_backend->GetRemote();
        RemoteADC* adc = remote->GetADC();
        disconnect(adc, &RemoteADC::resistance_changed, this, &ResistancePage::on_resistance_receive);
        disconnect(interval_slider, &LabelSlider::ValueChanged, adc, &RemoteADC::on_interval_changed);
        disconnect(adc, &RemoteADC::interval_changed, this, &ResistancePage::on_interval_receive);
    }
    return 1;
}

int ResistancePage::link_backend(BackendManager *backend)
{
    if(backend == nullptr)
        return PageWidget::link_backend(backend);
    this->_backend = backend;
    if(backend)
    {
        RemoteManager* remote = backend->GetRemote();
        RemoteADC* adc = remote->GetADC();
        connect(adc, &RemoteADC::resistance_changed, this, &ResistancePage::on_resistance_receive);
        resistance_lbl->SetValue(adc->GetResistance());
        connect(interval_slider, &LabelSlider::ValueChanged, adc, &RemoteADC::on_interval_changed);
        interval_slider->SetValue(adc->GetInterval());
        connect(adc, &RemoteADC::interval_changed, this, &ResistancePage::on_interval_receive);
        return 1;
    }
    return 0;
}
