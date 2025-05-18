//
// Created by gking on 25-5-17.
//
/**
 * Copyright © 2025-2025 Gking,All Rights Reserved.
 * https://github.com/Gking-a/BH3-QT-GUtils
 * Mozilla Public License Version 2.0
 */
#ifndef GSCALERESIZABLE_H
#define GSCALERESIZABLE_H
#include <iostream>
#include <QWidget>

#include "GUtil.h"
namespace  GUtil {
    class GScaleResizable : public QWidget {
    Q_OBJECT

public:
    explicit GScaleResizable(QWidget *parent = nullptr,bool reload=false,bool always_reload=false):QWidget(parent){
        setReload(reload);
        set_gui_gsr_always_reload(always_reload);
    };
    ~GScaleResizable() override =default;

        struct RelativePos {
            double relX;
            double relY;
            double relWidth;
            double relHeight;
        };
        std::map<QWidget*,RelativePos> positions;

protected:

    void resizeEvent(QResizeEvent *event) override {
        // printf("resizeEvent\n");
        QWidget::resizeEvent(event);
        auto nsize = event->size();
        if (!_gui_gsr_firstload_) {
            auto widgets = findChildren<QWidget*>();
            auto fsize = event->oldSize();

            if (_gui_gsr_always_reload_||_gui_gsr_reload_) {
                for (auto ewidget : widgets) {
                    auto spoint = ewidget->pos();
                    auto ssize = ewidget->size();
                    positions[ewidget]={static_cast<double>(spoint.x()) / fsize.width(),
                            static_cast<double>(spoint.y()) / fsize.height(),
                            static_cast<double>(ssize.width()) / fsize.width(),
                            static_cast<double>(ssize.height()) / fsize.height()};
                }
                _gui_gsr_reload_=false;
            }
            handleResize(nsize);
        }else if (!(_gui_gsr_reload_&&_gui_gsr_always_reload_)) {
            handleResize(this->size());
        }
        else _gui_gsr_firstload_=false;
    }
public:
        // void setFilledBackgroundColor(const std::string& color) {
        //
        //     setStyleSheet(("background-color: "+color+";").data());
        //     QPalette palette = this->palette();
        //     palette.setColor(QPalette::Window, Qt::black);
        //     setPalette(palette);
        //     setAutoFillBackground(true);
        // };
        void handleResize() {
            handleResize(this->size());
        }
        void handleResize(QSize nsize) {
            // printf("handleResize\n");
            for (auto eposition : positions)  {
                if (eposition.first==nullptr)continue;
                auto relative_pos = positions[eposition.first];
                eposition.first->setGeometry(relative_pos.relX*nsize.width(),relative_pos.relY*nsize.height(),relative_pos.relWidth*nsize.width(),relative_pos.relHeight*nsize.height());
                // printf("%s %s %f %f %f %f\n",objectName().toStdString().c_str(),eposition.first->objectName().toStdString().c_str(),relative_pos.relX,relative_pos.relY,relative_pos.relWidth,relative_pos.relHeight);
                // printf("%s %s %f %f %f %f\n",objectName().toStdString().c_str(),eposition.first->objectName().toStdString().c_str(),relative_pos.relX*nsize.width(),relative_pos.relY*nsize.height(),relative_pos.relWidth*nsize.width(),relative_pos.relHeight*nsize.height());
            }
        }
    void setReload(bool gui_gsr_reload);
        void set_gui_gsr_always_reload(bool gui_gsr_always_reload);

private:
    bool _gui_gsr_always_reload_=false;
    bool _gui_gsr_firstload_=true;
    bool _gui_gsr_reload_=true;
};

inline void GScaleResizable::set_gui_gsr_always_reload(bool gui_gsr_always_reload) {
    _gui_gsr_always_reload_ = gui_gsr_always_reload;
}

inline void GScaleResizable::setReload(bool gui_gsr_reload) {
    _gui_gsr_reload_ = gui_gsr_reload;
}
}


#endif //GSCALERESIZABLE_H
