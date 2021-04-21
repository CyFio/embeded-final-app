/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:19:00 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: fromtoedit.cpp
 * Project: embeded final supervisor
 * Description: 
 */

#include "fromtoedit.h"
#include "ui_fromtoedit.h"
//#include <QDateTime>

FromToEdit::FromToEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FromToEdit)
{
    ui->setupUi(this);
    ui->to_det->setDate(QDate::currentDate());
    ui->to_tet->setTime(QTime::currentTime());
    ui->from_det->setDate(QDate::currentDate());
    ui->from_tet->setTime(QTime::currentTime().addSecs(-3600));

}

FromToEdit::~FromToEdit()
{
    delete ui;
}

void FromToEdit::on_apply_btn_clicked()
{
    QDateTime from = QDateTime(ui->from_det->date(),ui->from_tet->time());
    QDateTime to = QDateTime(ui->to_det->date(), ui->to_tet->time());
    emit from_to_apply(from, to);
}


void FromToEdit::validate_filter()
{
    QDateTime from = QDateTime(ui->from_det->date(),ui->from_tet->time());
    QDateTime to = QDateTime(ui->to_det->date(), ui->to_tet->time());
    if(from >= to){
        this->ui->from_det->setDate(to.date());
        this->ui->from_tet->setTime(to.time().addSecs(-1));
    }
}

void FromToEdit::on_to_tet_timeChanged(const QTime &time)
{
    validate_filter();
}

void FromToEdit::on_to_det_dateChanged(const QDate &date)
{
    validate_filter();
}

void FromToEdit::on_from_tet_timeChanged(const QTime &time)
{
    validate_filter();
}

void FromToEdit::on_from_det_dateChanged(const QDate &date)
{
    validate_filter();
}
