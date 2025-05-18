//
// Created by gking on 25-5-17.
//
/**
 * Copyright © 2025-2025 Gking,All Rights Reserved.
 * https://github.com/Gking-a/BH3-QT-GUtils
 * Mozilla Public License Version 2.0
 */
#ifndef GRIGHTCLICKBUTTON_H
#define GRIGHTCLICKBUTTON_H
#include <qevent.h>
#include <QPushButton>

#include "GScaleResizable.h"


namespace GUtil {
    class GRightClickable : public GUtil::GScaleResizable{
        Q_OBJECT
    public:
        void** msg=nullptr;
    public:
        explicit GRightClickable(QWidget *parent = nullptr):GScaleResizable(parent){}
        ~GRightClickable() override =default;
        virtual void mousePressEvent(QMouseEvent *event) override {
            if (event->button()==Qt::LeftButton) {
                emit guiLeftClick(msg);
            }else if (event->button()==Qt::RightButton) {
                emit guiRightClick(msg);
            }
        };
        signals:
            void guiLeftClick(void**);
            void guiRightClick(void**);
    };
}
#endif //GRIGHTCLICKBUTTON_H