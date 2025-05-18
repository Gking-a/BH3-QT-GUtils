//
// Created by gking on 25-5-18.
//
/**
 * Copyright © 2025-2025 Gking,All Rights Reserved.
 * https://github.com/Gking-a/BH3-QT-GUtils
 * Mozilla Public License Version 2.0
 */
#ifndef GLABLED_H
#define GLABLED_H

#include <QWidget>

#include "qtui/ui_glabled.h"
#include "GScaleResizable.h"
#include "GRightClickable.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GLabled; }
QT_END_NAMESPACE
namespace GUtil {
    class GLabled : public GUtil::GRightClickable {
        Q_OBJECT
    public :
            std::string label;
            QWidget* child=nullptr;

    public:
        GLabled(const std::string& label,QWidget *parent,double x=0,double y=0,double w=0,double h=0):GUtil::GLabled(parent) {
            GScaleResizable::positions[ui->label]={x,y,w,h};
            ui->label->setAttribute(Qt::WA_TransparentForMouseEvents, true);  // 穿透鼠标事件
            ui->label->setFocusPolicy(Qt::NoFocus);                            // 禁止获取焦点
            ui->label->setAttribute(Qt::WA_InputMethodTransparent, true);       // 穿透输入法事件
            setLabel(label);
        }
        void setLabel(const std::string& slabel) {
            this->label=slabel;
            ui->label->setText(label.data());
            msg=reinterpret_cast<void **>(&this->label);
            setONuseLabel();
        }
        void setChildPosition(QWidget* child,double x=0,double y=0,double w=1,double h=1) {
            this->child=child;
            GScaleResizable::positions[child]={x,y,w,h};
            if (child!=nullptr) {
                child->stackUnder(ui->label);
            }
            handleResize(size());
        }
        ~GLabled() override {
            delete ui;
        }
        void setONuseLabel() {
            setObjectName(label);
        }
    private:
        GLabled(QWidget *parent) :
            GRightClickable(parent), ui(new Ui::GLabled) {
            ui->setupUi(this);
            setReload(false);
            set_gui_gsr_always_reload(false);
        }
        Ui::GLabled *ui;
    };
}
#ifndef AUTOLABELED_H
#define AUTOLABELED_H

// 定义一个可发送点击信号的 QLabel
class ClickableQLabel : public QLabel {
    Q_OBJECT
signals:
    void clicked();  // 自定义点击信号
public:
    using QLabel::QLabel;  // 继承 QLabel 的构造函数
protected:
    void mousePressEvent(QMouseEvent* event) override {
        QLabel::mousePressEvent(event);
        emit clicked();  // 触发点击信号
    }
};

namespace GUtil {
    class GFillLabeled : public GLabled {
        Q_OBJECT
    signals:
        // void onclick();  // 子类自身的点击信号
    public:
        // 构造函数：自动创建 QLabel 并设置位置
        explicit GFillLabeled(const std::string& label, QWidget* parent = nullptr,double x=0,double y=0,double w=0,double h=0)
            : GLabled(label, parent, x,y,w,h) {
            // 创建可点击的 QLabel
            // ClickableQLabel* clickableLabel = new ClickableQLabel(this);
            // 设置子控件位置为 0,0,1,1
            QLabel* q=new QLabel(this);
            q->setAttribute(Qt::WA_TransparentForMouseEvents, true);  // 穿透鼠标事件
            q->setFocusPolicy(Qt::NoFocus);                            // 禁止获取焦点
            q->setAttribute(Qt::WA_InputMethodTransparent, true);       // 穿透输入法事件
            setChildPosition(q, 0, 0, 1, 1);
        }
    };
}

#endif // AUTOLABELED_H
#endif //GLABLED_H
