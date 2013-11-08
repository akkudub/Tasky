/********************************************************************************
** Form generated from reading UI file 'taskydesign.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKYDESIGN_H
#define UI_TASKYDESIGN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TaskyDesign1Class
{
public:
    QWidget *MainPart;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *DisplayPanel;
    QHBoxLayout *horizontalLayout;
    QLabel *InputLabel;
    QLineEdit *InputBox;
    QWidget *BG1;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TaskyDesign1Class)
    {
        if (TaskyDesign1Class->objectName().isEmpty())
            TaskyDesign1Class->setObjectName(QStringLiteral("TaskyDesign1Class"));
        TaskyDesign1Class->resize(500, 387);
        TaskyDesign1Class->setMinimumSize(QSize(460, 315));
        TaskyDesign1Class->setMaximumSize(QSize(500, 400));
        MainPart = new QWidget(TaskyDesign1Class);
        MainPart->setObjectName(QStringLiteral("MainPart"));
        layoutWidget = new QWidget(MainPart);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 20, 461, 321));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        DisplayPanel = new QTextEdit(layoutWidget);
        DisplayPanel->setObjectName(QStringLiteral("DisplayPanel"));
        QFont font;
        font.setFamily(QStringLiteral("Segoe UI"));
        font.setPointSize(10);
        DisplayPanel->setFont(font);
        DisplayPanel->setReadOnly(true);

        verticalLayout->addWidget(DisplayPanel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        InputLabel = new QLabel(layoutWidget);
        InputLabel->setObjectName(QStringLiteral("InputLabel"));
        QFont font1;
        font1.setFamily(QStringLiteral("Segoe Print"));
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setWeight(50);
        InputLabel->setFont(font1);

        horizontalLayout->addWidget(InputLabel);

        InputBox = new QLineEdit(layoutWidget);
        InputBox->setObjectName(QStringLiteral("InputBox"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(InputBox->sizePolicy().hasHeightForWidth());
        InputBox->setSizePolicy(sizePolicy);
        InputBox->setMinimumSize(QSize(400, 25));
        InputBox->setMaximumSize(QSize(16777215, 30));
        QFont font2;
        font2.setFamily(QStringLiteral("Segoe Print"));
        font2.setPointSize(11);
        InputBox->setFont(font2);

        horizontalLayout->addWidget(InputBox);


        verticalLayout->addLayout(horizontalLayout);

        BG1 = new QWidget(MainPart);
        BG1->setObjectName(QStringLiteral("BG1"));
        BG1->setGeometry(QRect(0, -11, 500, 401));
        BG1->setStyleSheet(QStringLiteral("background-color:rgb(255, 131, 74);"));
        TaskyDesign1Class->setCentralWidget(MainPart);
        BG1->raise();
        layoutWidget->raise();
        statusBar = new QStatusBar(TaskyDesign1Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(statusBar->sizePolicy().hasHeightForWidth());
        statusBar->setSizePolicy(sizePolicy1);
        statusBar->setMinimumSize(QSize(400, 25));
        QFont font3;
        font3.setPointSize(11);
        statusBar->setFont(font3);
        TaskyDesign1Class->setStatusBar(statusBar);

        retranslateUi(TaskyDesign1Class);

        QMetaObject::connectSlotsByName(TaskyDesign1Class);
    } // setupUi

    void retranslateUi(QMainWindow *TaskyDesign1Class)
    {
        TaskyDesign1Class->setWindowTitle(QApplication::translate("TaskyDesign1Class", "TaskyDesign1", 0));
        DisplayPanel->setHtml(QApplication::translate("TaskyDesign1Class", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p></body></html>", 0));
        InputLabel->setText(QApplication::translate("TaskyDesign1Class", "Input ", 0));
        InputBox->setPlaceholderText(QApplication::translate("TaskyDesign1Class", "input your commend here", 0));
    } // retranslateUi

};

namespace Ui {
    class TaskyDesign1Class: public Ui_TaskyDesign1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKYDESIGN_H
