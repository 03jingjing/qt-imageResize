/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *INlineEdit;
    QPushButton *selectButton;
    QLabel *roislabel;
    QVBoxLayout *verticalLayout;
    QLineEdit *ROI1;
    QLineEdit *ROI2;
    QLineEdit *ROI3;
    QLineEdit *ROI4;
    QLineEdit *ROI5;
    QLabel *Resizelabel;
    QHBoxLayout *horizontalLayout_2;
    QProgressBar *progressBar;
    QPushButton *pushButton;
    QLineEdit *ResizeROI;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(395, 406);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 13, 372, 328));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        INlineEdit = new QLineEdit(widget);
        INlineEdit->setObjectName("INlineEdit");

        horizontalLayout->addWidget(INlineEdit);

        selectButton = new QPushButton(widget);
        selectButton->setObjectName("selectButton");

        horizontalLayout->addWidget(selectButton);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 2);

        roislabel = new QLabel(widget);
        roislabel->setObjectName("roislabel");

        gridLayout->addWidget(roislabel, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        ROI1 = new QLineEdit(widget);
        ROI1->setObjectName("ROI1");

        verticalLayout->addWidget(ROI1);

        ROI2 = new QLineEdit(widget);
        ROI2->setObjectName("ROI2");

        verticalLayout->addWidget(ROI2);

        ROI3 = new QLineEdit(widget);
        ROI3->setObjectName("ROI3");

        verticalLayout->addWidget(ROI3);

        ROI4 = new QLineEdit(widget);
        ROI4->setObjectName("ROI4");

        verticalLayout->addWidget(ROI4);

        ROI5 = new QLineEdit(widget);
        ROI5->setObjectName("ROI5");

        verticalLayout->addWidget(ROI5);


        gridLayout->addLayout(verticalLayout, 1, 1, 1, 1);

        Resizelabel = new QLabel(widget);
        Resizelabel->setObjectName("Resizelabel");

        gridLayout->addWidget(Resizelabel, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        progressBar = new QProgressBar(widget);
        progressBar->setObjectName("progressBar");
        progressBar->setMaximumSize(QSize(411, 31));
        progressBar->setValue(24);

        horizontalLayout_2->addWidget(progressBar);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(71, 41));

        horizontalLayout_2->addWidget(pushButton);


        gridLayout->addLayout(horizontalLayout_2, 3, 0, 1, 2);

        ResizeROI = new QLineEdit(widget);
        ResizeROI->setObjectName("ResizeROI");

        gridLayout->addWidget(ResizeROI, 2, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 395, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        selectButton->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\346\226\207\344\273\266\345\244\271", nullptr));
        roislabel->setText(QCoreApplication::translate("MainWindow", "rois:\n"
"\345\206\231\344\272\206\345\207\240\344\270\252\350\243\201\345\207\240\351\201\215", nullptr));
        Resizelabel->setText(QCoreApplication::translate("MainWindow", "Resize\345\200\215\346\225\260", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
