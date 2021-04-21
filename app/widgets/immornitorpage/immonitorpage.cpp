/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:19:20 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: immonitorpage.cpp
 * Project: embeded final supervisor
 * Description: 
 */

#include "immonitorpage.h"
#include "ui_immonitorpage.h"
#include "backend/backendmanager.h"
#include "backend/remote/remotemanager.h"
#include "backend/remote/remotecamera.h"
#include "backend/remote/remoteadc.h"
#include "labelslider/labelslider.h"
#include <QPixmap>

ImMonitorPage::ImMonitorPage(QWidget *parent, const QString& label) :
    PageWidget(parent, label),
    ui(new Ui::ImMonitorPage)
{
    ui->setupUi(this);
    LabelSlider::config_t label_slider_cfg;
    label_slider_cfg.title = "采样间隔";
    label_slider_cfg.unit = "s";
    label_slider_cfg.base = 0.1;
    label_slider_cfg.min = 1;
    label_slider_cfg.max = 50;
    label_slider_cfg.value = 10;
    interval_slider = new LabelSlider(nullptr, label_slider_cfg);
    ui->horizontalLayout->insertWidget(0, interval_slider);
}

ImMonitorPage::~ImMonitorPage()
{
    delete ui;
}

void ImMonitorPage::on_img_receive(QDateTime datetime)
{
    RemoteCamera* cam = qobject_cast<RemoteCamera*>(sender());
    if(cam)
    {
        this->ui->image_lbl->setPixmap(QPixmap::fromImage(cam->GetImage()));
    }
}

void ImMonitorPage::on_interval_receive(float interval)
{
     this->interval_slider->SetValue(interval);
}

void ImMonitorPage::on_return_btn_clicked()
{
    emit PopRequest();
}


int ImMonitorPage::unlink_backend()
{
    PageWidget::unlink_backend();
    if(this->_backend)
    {
        RemoteManager* remote = this->_backend->GetRemote();
        RemoteCamera* cam = remote->GetCamera();
        RemoteADC* adc = remote->GetADC();

        disconnect(interval_slider, &LabelSlider::ValueChanged, adc, &RemoteADC::on_interval_changed);
        disconnect(adc, &RemoteADC::interval_changed, this, &ImMonitorPage::on_interval_receive);

//        disconnect(interval_slider, &LabelSlider::ValueChanged, cam, &RemoteCamera::on_interval_changed);
//        disconnect(cam, &RemoteCamera::interval_changed, this, &ImMonitorPage::on_interval_receive);
        disconnect(cam, &RemoteCamera::img_received, this, &ImMonitorPage::on_img_receive);
    }
    return 1;
}

int ImMonitorPage::link_backend(BackendManager *backend)
{
    if(backend == nullptr)
        return PageWidget::link_backend(backend);
    this->_backend = backend;
    if(backend)
    {
        RemoteManager* remote = backend->GetRemote();
        RemoteCamera* cam = remote->GetCamera();
        RemoteADC* adc = remote->GetADC();

        connect(interval_slider, &LabelSlider::ValueChanged, adc, &RemoteADC::on_interval_changed);
        interval_slider->SetValue(adc->GetInterval());
        connect(adc, &RemoteADC::interval_changed, this, &ImMonitorPage::on_interval_receive);
//        connect(interval_slider, &LabelSlider::ValueChanged, cam, &RemoteCamera::on_interval_changed);
//        interval_slider->SetValue(cam->GetInterval());
//        connect(cam, &RemoteCamera::interval_changed, this, &ImMonitorPage::on_interval_receive);
        connect(cam, &RemoteCamera::img_received, this, &ImMonitorPage::on_img_receive);
        this->ui->image_lbl->setPixmap(QPixmap::fromImage(cam->GetImage()));
        return 1;
    }
    return 0;
}
