/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:19:27 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: labelslider.cpp
 * Project: embeded final supervisor
 * Description: 
 */

#include "labelslider.h"
#include "ui_labelslider.h"
#include <cmath>

LabelSlider::LabelSlider(QWidget *parent, const config_t& cfg) :
    QWidget(parent), ui(new Ui::LabelSlider),
    min(cfg.min), max(cfg.max), base(cfg.base), title(cfg.title),unit(cfg.unit)
{
    ui->setupUi(this);
    this->value = clamp(cfg.value, min, max);
    ui->title_lbl->setText(QString("%1:").arg(title));
    ui->value_lbl->setText(QString("%1%2").arg(value*base, 0, 'f', 1).arg(unit));
    ui->slider->setRange(min, max);
    ui->slider->setValue(this->value);
}

LabelSlider::~LabelSlider()
{
    delete ui;
}

void LabelSlider::SetValue(float raw_value)
{
    int new_value = clamp(raw_value/base, min, max);
    this->value = new_value;
    ui->value_lbl->setText(QString("%1%2").arg(value*base, 0, 'f', 1).arg(unit));
    ui->slider->setValue(this->value);
}

void LabelSlider::on_slider_valueChanged(int value)
{
    int new_value = clamp(value, min, max);
    if(new_value!=value)
    {
        emit ValueChanged(new_value*base);
    }
    this->value = new_value;
    ui->value_lbl->setText(QString("%1%2").arg(value*base, 0, 'f', 1).arg(unit));
//    if(ui->slider->isSliderDown() && this->pending_for_change){
//        ui->slider->setSliderDown(false);
//    }
}

void LabelSlider::on_slider_sliderReleased()
{
    emit ValueChanged(this->value*base);
}

void LabelSlider::on_slider_actionTriggered(int action)
{
    switch (action) {
    case QAbstractSlider::SliderPageStepAdd:
    case QAbstractSlider::SliderPageStepSub:
//    case QAbstractSlider::SliderSingleStepAdd:
//    case QAbstractSlider::SliderSingleStepSub:
//        ui->slider->setSliderDown(true);
//        this->pending_for_change = true;
        break;
    default:
        break;
    }
}
