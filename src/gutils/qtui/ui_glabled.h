/********************************************************************************
** Form generated from reading UI file 'glabled.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLABLED_H
#define UI_GLABLED_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GLabled
{
public:
    QLabel *label;

    void setupUi(QWidget *GLabled)
    {
        if (GLabled->objectName().isEmpty())
            GLabled->setObjectName("GLabled");
        GLabled->resize(400, 400);
        label = new QLabel(GLabled);
        label->setObjectName("label");
        label->setGeometry(QRect(6, 16, 381, 381));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        retranslateUi(GLabled);

        QMetaObject::connectSlotsByName(GLabled);
    } // setupUi

    void retranslateUi(QWidget *GLabled)
    {
        GLabled->setWindowTitle(QCoreApplication::translate("GLabled", "GLabled", nullptr));
        label->setText(QCoreApplication::translate("GLabled", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GLabled: public Ui_GLabled {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLABLED_H
