/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:17:26 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: rdatamanager.h
 * Project: embeded final supervisor
 * Description: 
 */

#ifndef RDATAMANAGER_H
#define RDATAMANAGER_H

#include <QObject>
#include <QDateTime>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QDateTimeAxis>
#include <QVector>
#include <QPointF>

class QLabel;
class LocalDataManager;

class RDataManager:public QObject
{
    Q_OBJECT
public:
    RDataManager(QObject* parent = nullptr);
    ~RDataManager();
    int SetUp(LocalDataManager& manager);


public slots:
    void update_rt_chart(QLabel&);
    void on_resistance_received(int resistance, QDateTime time);
    void on_chart_query(QDateTime from, QDateTime to, QtCharts::QChartView& chart_view);
signals:


private:
    LocalDataManager* db_manager;
    QtCharts::QChartView* rt_chart_view;
//    QtCharts::QLineSeries* rt_series;
//    QtCharts::QDateTimeAxis* rt_x;
//    QtCharts::QValueAxis* rt_y;
    QVector<QPointF> rt_pts;
};

#endif // RDATAMANAGER_H
