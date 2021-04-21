/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:20:23 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: rchartpage.h
 * Project: embeded final supervisor
 * Description: 
 */

#ifndef RCHARTPAGE_H
#define RCHARTPAGE_H

#include "pagewidget/pagewidget.h"
#include <QDateTime>
#include <QtCharts/QChartView>

class FromToEdit;

namespace Ui {
class RChartPage;
}

class RChartPage : public PageWidget
{
    Q_OBJECT

public:
    explicit RChartPage(QWidget *parent = nullptr, const QString& label = "");
    ~RChartPage();

signals:
    void query_rchart(QDateTime from, QDateTime to, QtCharts::QChartView& chart_view);

private slots:
    void on_return_btn_clicked();
    void on_from_to_apply(QDateTime from, QDateTime to);

private:
    Ui::RChartPage *ui;
    FromToEdit* from_to_edit;
    QtCharts::QChartView* chart_view;

    // PageWidget interface
protected:
    virtual int unlink_backend() override;
    virtual int link_backend(BackendManager *backend) override;
};

#endif // RCHARTPAGE_H
