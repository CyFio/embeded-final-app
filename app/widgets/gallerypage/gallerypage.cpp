/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:19:06 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: gallerypage.cpp
 * Project: embeded final supervisor
 * Description: 
 */

#include "gallerypage.h"
#include "ui_gallerypage.h"
#include "fromtoedit/fromtoedit.h"
#include "backend/backendmanager.h"
#include "backend/local/localmanager.h"
#include "backend/local/imgdatamanager.h"
#include <QFileDialog>
#include <QPixmap>

GalleryPage::GalleryPage(QWidget *parent, const QString& label) :
    PageWidget(parent, label),
    ui(new Ui::GalleryPage), from_to_edit(new FromToEdit)
{
    ui->setupUi(this);
    ui->top_layout->insertWidget(1, from_to_edit);
    connect(from_to_edit, &FromToEdit::from_to_apply, this, &GalleryPage::on_from_to_apply);
}

GalleryPage::~GalleryPage()
{
    delete ui;
}

void GalleryPage::on_from_to_apply(QDateTime from, QDateTime to)
{
    if(this->ui->image_list)
    {
        emit query_img_list(from, to , *(this->ui->image_list));
    }
}

void GalleryPage::on_return_btn_clicked()
{
    emit PopRequest();
}


int GalleryPage::unlink_backend()
{
    PageWidget::unlink_backend();
    if(this->_backend)
    {
        LocalManager* local = this->_backend->GetLocal();
        ImgDataManager* img_data = local->Get_ImgDataManager();
        disconnect(this, &GalleryPage::query_img_list, img_data, &ImgDataManager::on_list_filter_query);
    }
//    LocalManager* local = this->_backend->GetLocal();
    return 1;
}

int GalleryPage::link_backend(BackendManager *backend)
{
    if(backend == nullptr)
        return PageWidget::link_backend(backend);
    this->_backend = backend;
    if(backend)
    {
        LocalManager* local = this->_backend->GetLocal();
        ImgDataManager* img_data = local->Get_ImgDataManager();
        connect(this, &GalleryPage::query_img_list, img_data, &ImgDataManager::on_list_filter_query);
        return 1;
    }
    return 0;
}

void GalleryPage::on_image_list_currentRowChanged(int currentRow)
{
    QListWidgetItem* item = this->ui->image_list->item(currentRow);
    if(item)
    {
        QPixmap image = QPixmap(item->text());
        if(!image.isNull())
        {
            this->ui->image_lbl->setPixmap(image);
        }
    }
}

void GalleryPage::on_prev_btn_clicked()
{
    int current = this->ui->image_list->currentRow();
    if(current > 0)
        this->ui->image_list->setCurrentRow(current - 1);
}

void GalleryPage::on_next_btn_clicked()
{
    int current = this->ui->image_list->currentRow();
    if(current < this->ui->image_list->count() - 1)
        this->ui->image_list->setCurrentRow(current + 1);
}

void GalleryPage::on_export_btn_clicked()
{
    QListWidgetItem* item = this->ui->image_list->currentItem();
    if(item)
    {
        QString filename = QFileDialog::getSaveFileName(this, tr("导出图片"),"",tr("Images(*png *.jpg"));
        QPixmap img(item->text());
        if(!img.isNull())
        {
            img.save(filename);
        }
    }
}
