/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:20:58 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: warninglabel.cpp
 * Project: embeded final supervisor
 * Description: 
 */

#include "warninglabel.h"
#include "ui_warninglabel.h"

#include <QPixmap>
#include <QDebug>

WarningLabel::WarningLabel(QWidget *parent, const config_t &cfg, int initial_value)
    :QWidget(parent),ui(new Ui::WarningLabel),min(cfg.min),max(cfg.max),value(initial_value),thres(cfg.thres),
      normalPic(cfg.normal_pic_path),warningPic(cfg.warn_pic_path), title(cfg.title),unit(cfg.unit)
{
    ui->setupUi(this);
    ui->title_lbl->setText(QString("%1:").arg(title));
    safe_now = !(value < min || value > max);
    ui->value_lbl->setText(QString("%1%2").arg(value).arg(unit));

    normalPic = normalPic.scaledToHeight(ui->icon_lbl->height());
    warningPic = warningPic.scaledToHeight(ui->icon_lbl->height());
    ui->icon_lbl->setPixmap(safe_now ? normalPic : warningPic);
}

WarningLabel::~WarningLabel()
{
    delete ui;
//    delete normalPic;
//    delete warningPic;
}

void WarningLabel::SetValue(int new_value)
{
    value = new_value;
    ui->value_lbl->setText(QString("%1%2").arg(value).arg(unit));
    bool safe_then = !WarningCheck();
    if(safe_then != safe_now){
        ui->icon_lbl->setPixmap(safe_then ? normalPic : warningPic);
    }
    safe_now = safe_then;
}

int WarningLabel::GetValue()
{
    return value;
}

bool WarningLabel::WarningCheck()
{
    if(safe_now)
    {
        return value < min - thres || value > max + thres;
    }
    else
    {
        return value < min + thres || value > max - thres;
    }
}
