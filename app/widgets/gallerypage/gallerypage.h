/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:19:08 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: gallerypage.h
 * Project: embeded final supervisor
 * Description: 
 */

#ifndef GALLERYPAGE_H
#define GALLERYPAGE_H

#include "pagewidget/pagewidget.h"
#include <QDateTime>
#include <QListWidget>

class FromToEdit;

namespace Ui {
class GalleryPage;
}

class GalleryPage : public PageWidget
{
    Q_OBJECT

public:
    explicit GalleryPage(QWidget *parent = nullptr, const QString& label = "");
    ~GalleryPage();

signals:
    void query_img_list(QDateTime from, QDateTime to, QListWidget& list);

private slots:
    void on_from_to_apply(QDateTime from, QDateTime to);

    void on_return_btn_clicked();

    void on_image_list_currentRowChanged(int currentRow);

    void on_prev_btn_clicked();

    void on_next_btn_clicked();

    void on_export_btn_clicked();

private:
    Ui::GalleryPage *ui;
    FromToEdit* from_to_edit;

    // PageWidget interface
protected:
    virtual int unlink_backend() override;
    virtual int link_backend(BackendManager *backend) override;
};

#endif // GALLERYPAGE_H
