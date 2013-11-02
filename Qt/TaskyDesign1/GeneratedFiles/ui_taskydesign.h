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
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TaskyDesign1Class
{
public:
    QWidget *MainPart;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *InputLabel;
    QLineEdit *InputBox;
    QListWidget *DisplayPanel;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TaskyDesign1Class)
    {
        if (TaskyDesign1Class->objectName().isEmpty())
            TaskyDesign1Class->setObjectName(QStringLiteral("TaskyDesign1Class"));
        TaskyDesign1Class->resize(460, 315);
        TaskyDesign1Class->setMinimumSize(QSize(460, 315));
        TaskyDesign1Class->setMaximumSize(QSize(460, 315));
        MainPart = new QWidget(TaskyDesign1Class);
        MainPart->setObjectName(QStringLiteral("MainPart"));
        layoutWidget = new QWidget(MainPart);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 20, 421, 261));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, -1, 15);
        InputLabel = new QLabel(layoutWidget);
        InputLabel->setObjectName(QStringLiteral("InputLabel"));
        QFont font;
        font.setFamily(QStringLiteral("Verdana"));
        font.setPointSize(12);
        font.setBold(false);
        font.setWeight(50);
        InputLabel->setFont(font);

        horizontalLayout->addWidget(InputLabel);

        InputBox = new QLineEdit(layoutWidget);
        InputBox->setObjectName(QStringLiteral("InputBox"));
        QFont font1;
        font1.setPointSize(10);
        InputBox->setFont(font1);

        horizontalLayout->addWidget(InputBox);


        verticalLayout->addLayout(horizontalLayout);

        DisplayPanel = new QListWidget(layoutWidget);
        DisplayPanel->setObjectName(QStringLiteral("DisplayPanel"));
        DisplayPanel->setFont(font1);

        verticalLayout->addWidget(DisplayPanel);

        TaskyDesign1Class->setCentralWidget(MainPart);
        statusBar = new QStatusBar(TaskyDesign1Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TaskyDesign1Class->setStatusBar(statusBar);

        retranslateUi(TaskyDesign1Class);

        QMetaObject::connectSlotsByName(TaskyDesign1Class);
    } // setupUi

    void retranslateUi(QMainWindow *TaskyDesign1Class)
    {
        TaskyDesign1Class->setWindowTitle(QApplication::translate("TaskyDesign1Class", "TaskyDesign1", 0));
        InputLabel->setText(QApplication::translate("TaskyDesign1Class", "Input ", 0));
    } // retranslateUi

};

namespace Ui {
    class TaskyDesign1Class: public Ui_TaskyDesign1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKYDESIGN_H
