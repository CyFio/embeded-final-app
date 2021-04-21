/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:20:30 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: resistancepage.h
 * Project: embeded final supervisor
 * Description: 
 */

#ifndef RESISTANCEPAGE_H
#define RESISTANCEPAGE_H

#include "pagewidget/pagewidget.h"
#include <QDateTime>
//#include <QChartView>

namespace Ui {
class ResistancePage;
}

class WarningLabel;
class LabelSlider;

class ResistancePage : public PageWidget
{
    Q_OBJECT

public:
    explicit ResistancePage(QWidget *parent = nullptr, const QString& label="");
    ~ResistancePage();

//signals:
//    void interval_changed(float interval);

public slots:
    void on_resistance_receive(int resistance, QDateTime datetime);
    void on_interval_receive(float interval);

protected slots:
    void on_return_btn_clicked();

private:
    Ui::ResistancePage *ui;

    // PageWidget interface
protected:
    WarningLabel* resistance_lbl;
    LabelSlider* interval_slider;
//    QtCharts::QChartView* chart_view;
    virtual int unlink_backend() override;
    virtual int link_backend(BackendManager *backend) override;
};

#endif // RESISTANCEPAGE_H
