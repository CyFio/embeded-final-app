/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:20:48 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: stackedpage.h
 * Project: embeded final supervisor
 * Description: 
 */

#ifndef STACKEDPAGE_H
#define STACKEDPAGE_H

#include "pagewidget/pagewidget.h"
#include <QStack>

class QStackedWidget;

namespace Ui {
class StackedPage;
}

class StackedPage : public PageWidget
{
    Q_OBJECT

public:
    explicit StackedPage(QWidget *parent = nullptr);
    virtual ~StackedPage();
    virtual PageWidget *Clone() override;
    bool PushPage(PageWidget* page);
    bool PopPage();

public slots:
    void On_Push_Request(PageWidget* page_to_push);
    void On_Pop_Request(void);
//    bool Forward();
//    bool Backward();

private:
    Ui::StackedPage *ui;

    // PageWidget interface
protected:
    QStackedWidget* ui_stack;
    QStack<PageWidget*> page_stack;

protected slots:
    void SetLabelFromCurrentId(int id);
};

#endif // STACKEDPAGE_H
