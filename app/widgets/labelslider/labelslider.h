/*
 * embeded final supervisor CopyRight (C) 2020 CyFio
 * This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
 * This is free software, and you are welcome to redistribute it under certain conditions; type `show c' for details.
 * Created Time: Wednesday, 21st April 2021 9:47:34 pm
 * Author: CyFio
 * E-mail: cyfio@foxmail.com
 * ------------------------------------------------
 * Last Modified: Wednesday, 21st April 2021 10:19:30 pm
 * Modified By CyFio(cyfio@foxmail.com)
 * ------------------------------------------------
 * Filename: labelslider.h
 * Project: embeded final supervisor
 * Description: 
 */

#ifndef LABELSLIDER_H
#define LABELSLIDER_H

#include <QWidget>

namespace Ui {
class LabelSlider;
}

class LabelSlider : public QWidget
{
    Q_OBJECT

public:
    struct config_t
    {
        QString title;
        QString unit;
        int min = 50;
        int max = 1;
        int value = 10;
        float base = 0.1f;
    };
    static inline float clamp(float value, float min, float max){
        return value < min ? min : (value > max ? max : value);
    }
    static inline float alpha(float value, float min, float max){
        return (clamp(value, min, max) - min)/(max - min);
    }
    static inline float lerp(float a, float b, float alpha){
        return a + (b - a) * alpha;
    }
    explicit LabelSlider(QWidget *parent, const config_t& cfg);
    ~LabelSlider();
    inline float GetValue(){return value * base;}

//public slots:
    void SetValue(float raw_value);

signals:
    void ValueChanged(float);


private slots:
    void on_slider_valueChanged(int value);

    void on_slider_sliderReleased();

    void on_slider_actionTriggered(int action);

private:
    Ui::LabelSlider *ui;
    int min;
    int max;
    int value;
    float base;
    bool pending_for_change;
    QString title;
    QString unit;
};

#endif // LABELSLIDER_H
