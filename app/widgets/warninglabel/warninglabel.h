/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:20:55 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: warninglabel.h
 * Project: embeded final supervisor
 * Description: 
 */

#ifndef WARNINGLABEL_H
#define WARNINGLABEL_H

#include <QWidget>

namespace Ui {
class WarningLabel;
}

class QPixmap;


class WarningLabel : public QWidget
{
    Q_OBJECT

public:
    struct config_t
    {
        QString title;
        QString unit;
        QString normal_pic_path;
        QString warn_pic_path;
        int min = 1000;
        int max = 9000;
        int thres = 50;
    };
    explicit WarningLabel(QWidget *parent, const config_t& cfg, int intial_value = 0);
    ~WarningLabel();
    void SetValue(int new_value);
    int GetValue();
    bool WarningCheck();

private:
    Ui::WarningLabel *ui;
    int min;
    int max;
    int value;
    int thres;
    bool safe_now;
    QPixmap normalPic;
    QPixmap warningPic;
    QString title;
    QString unit;
};

#endif // WARNINGLABEL_H
