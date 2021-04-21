/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:20:07 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: mytabwidget.h
 * Project: embeded final supervisor
 * Description: 
 */

#ifndef MYTABWIDGET_H
#define MYTABWIDGET_H

#include <QWidget>

class PageWidget;

namespace Ui {
class MyTabWidget;
}

class MyTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyTabWidget(QWidget *parent = nullptr);
    bool SetDefaultTabWidget(PageWidget* widget);
    bool Clear(void);
    bool AddWidget(PageWidget* new_widget=nullptr, int index = -1);
    bool RemoveWidget(int index = -1);
    ~MyTabWidget();

private slots:
    void on_addTab_btn_clicked();

    void on_tabWidget_tabCloseRequested(int index);

    void on_tabWidget_labelChanged(const QString& new_label);

private:
    Ui::MyTabWidget *ui;
    PageWidget* default_page;
};

#endif // MYTABWIDGET_H
