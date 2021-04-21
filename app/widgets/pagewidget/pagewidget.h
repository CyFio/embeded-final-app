/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:20:15 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: pagewidget.h
 * Project: embeded final supervisor
 * Description: 
 */

#ifndef PAGEWIDGET_H
#define PAGEWIDGET_H

#include <QWidget>
#include <backend/backendmanager.h>

class PageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PageWidget(QWidget *parent = nullptr, const QString& label = "新标签页");
    virtual ~PageWidget();
    const QString& GetLabel() const {return _label;}
    int SetBackend(BackendManager* backend);
    virtual PageWidget* Clone();
public slots:
    void SetLabel(const QString& label){_label = label; emit LabelChanged(label);}
signals:
    void LabelChanged(const QString& new_label);
    void PushRequest(PageWidget* page_to_push);
    void PopRequest(void);
private:

protected:
    QString _label;
    BackendManager* _backend = nullptr;
    virtual int unlink_backend();
    virtual int link_backend(BackendManager* backend);
};

#endif // PAGEWIDGET_H
