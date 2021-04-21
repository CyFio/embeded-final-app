/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:18:55 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: fromtoedit.h
 * Project: embeded final supervisor
 * Description: 
 */

#ifndef FROMTOEDIT_H
#define FROMTOEDIT_H

#include <QWidget>
#include <QDateTime>

namespace Ui {
class FromToEdit;
}

class FromToEdit : public QWidget
{
    Q_OBJECT

public:
    explicit FromToEdit(QWidget *parent = nullptr);
    ~FromToEdit();

signals:
    void from_to_apply(QDateTime from, QDateTime to);

private slots:
    void on_apply_btn_clicked();

    void on_to_tet_timeChanged(const QTime &time);

    void on_to_det_dateChanged(const QDate &date);

    void on_from_tet_timeChanged(const QTime &time);

    void on_from_det_dateChanged(const QDate &date);

private:
    void validate_filter();
    Ui::FromToEdit *ui;
};

#endif // FROMTOEDIT_H
