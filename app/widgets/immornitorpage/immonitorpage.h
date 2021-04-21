/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:19:23 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: immonitorpage.h
 * Project: embeded final supervisor
 * Description: 
 */

#ifndef IMMONITORPAGE_H
#define IMMONITORPAGE_H

#include "pagewidget/pagewidget.h"
#include <QDateTime>

namespace Ui {
class ImMonitorPage;
}

class LabelSlider;

class ImMonitorPage : public PageWidget
{
    Q_OBJECT

public:
    explicit ImMonitorPage(QWidget *parent = nullptr, const QString& label = "");
    ~ImMonitorPage();

public slots:
    void on_img_receive(QDateTime datetime);
    void on_interval_receive(float interval);

private slots:
    void on_return_btn_clicked();

private:
    Ui::ImMonitorPage *ui;
    LabelSlider* interval_slider;

    // PageWidget interface
protected:
    virtual int unlink_backend() override;
    virtual int link_backend(BackendManager *backend) override;
};

#endif // IMMONITORPAGE_H
