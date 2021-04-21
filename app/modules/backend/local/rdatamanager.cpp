/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:17:23 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: rdatamanager.cpp
 * Project: embeded final supervisor
 * Description: 
 */

#include "rdatamanager.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QLabel>
#include <QDebug>
#include "localdatamanager.h"

using namespace QtCharts;

RDataManager::RDataManager(QObject* parent):
    QObject(parent)
{
    QDateTime time = QDateTime::currentDateTime();
    QChart* rt_chart = new QChart;
    QLineSeries* series = new QLineSeries();
    series->replace(rt_pts);
    rt_chart->addSeries(series);
    rt_chart->legend()->hide();
    rt_chart->setTitle("阻值曲线");
    QDateTimeAxis* axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setRange(time.addSecs(-5), time.addSecs(1));

    axisX->setFormat("mm:ss");
    axisX->setTitleText("时间");
    rt_chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("阻值/Ω");
    axisY->setRange(0, 10000);
    rt_chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    rt_chart_view = new QChartView(rt_chart);

    rt_chart_view->setRenderHint(QPainter::SmoothPixmapTransform);
}

RDataManager::~RDataManager()
{
    rt_chart_view->deleteLater();
}

int RDataManager::SetUp(LocalDataManager &manager)
{
    this->db_manager = &manager;
    if(this->db_manager != nullptr)
    {
        QSqlDatabase& db = db_manager->GetDB();
        if(db.isOpen())
        {
            db.exec("CREATE TABLE IF NOT EXISTS resistance ("
                     "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                     "msecs_from_utc INTEGER NOT NULL DEFAULT 0, "
                     "resistance INTEGER NOT NULL DEFAULT 0)");
        }
        return 1;
    }
    return 0;
}

void RDataManager::update_rt_chart(QLabel &label)
{
//    QChartView* chart_view = new QChartView(rt_chart_view);
//    rt_chart_view->chart()->resize(label.width(), label.height());
    rt_chart_view->resize(label.width(), label.height());
    QPixmap pic = rt_chart_view->grab().scaled(label.width(), label.height());
    label.setPixmap(pic);
//    chart_view->setChart(nullptr);
}

void RDataManager::on_resistance_received(int resistance, QDateTime time)
{
    if(this->db_manager != nullptr)
    {
        QSqlDatabase& db = db_manager->GetDB();
        if(db.isOpen())
        {
            int64_t msecs_from_utc = time.toMSecsSinceEpoch();
            db.exec(QString("INSERT INTO resistance (msecs_from_utc, resistance)""VALUES('%1','%2')").arg(msecs_from_utc).arg(resistance));
        }
    }
    rt_pts.push_back(QPointF(time.toMSecsSinceEpoch(), resistance));
    if(rt_pts.length() > 200)
    {
        rt_pts.pop_front();
    }
    QLineSeries* series = qobject_cast<QLineSeries*>(rt_chart_view->chart()->series().first());
    if(series)
    {
        series->replace(rt_pts);
        QDateTimeAxis* axisX = qobject_cast<QDateTimeAxis*>(rt_chart_view->chart()->axes().first());
        if(axisX)
        {
            axisX->setRange(time.addSecs(-5), time.addSecs(1));
        }
    }
}

void RDataManager::on_chart_query(QDateTime from, QDateTime to, QtCharts::QChartView& chart_view)
{
    int64_t msecs_from = from.toMSecsSinceEpoch();
    int64_t msecs_to = to.toMSecsSinceEpoch();
    QSqlDatabase& db = db_manager->GetDB();
    if(db.open()){
        QSqlQuery select_result(db);
        bool succeed = select_result.exec(
                    QString(
                        "SELECT msecs_from_utc,resistance from resistance WHERE msecs_from_utc BETWEEN %1 AND %2").arg(msecs_from).arg(msecs_to)
                    );
        if(!succeed)
        {
            qDebug() << select_result.lastError().text();
            return;
        }
        QChart* chart = new QChart;
        QLineSeries* series = new QLineSeries();
        while(select_result.next())
        {
//            QDateTime datetime = QDateTime::fromMSecsSinceEpoch(select_result.value(0).toLongLong());
            quint64 datetime = select_result.value(0).toULongLong();
//            qDebug() << datetime;
            series->append(datetime, select_result.value(1).toInt());
//            qDebug() << select_result.value(0).toString();
        }
        chart->addSeries(series);
        chart->legend()->hide();
        chart->setTitle("阻值曲线");
        QDateTimeAxis* axisX = new QDateTimeAxis;
        axisX->setTickCount(10);
//        int delta_secs = abs(to.secsTo(from));

        axisX->setFormat("mm:ss");
        axisX->setTitleText("时间");
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);
        QValueAxis *axisY = new QValueAxis;
        axisY->setLabelFormat("%i");
        axisY->setTitleText("阻值/Ω");
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        QChart* old_chart = chart_view.chart();
        chart_view.setChart(chart);
        chart_view.setRenderHint(QPainter::SmoothPixmapTransform);

        if(old_chart != nullptr)old_chart->deleteLater();
    }
}

