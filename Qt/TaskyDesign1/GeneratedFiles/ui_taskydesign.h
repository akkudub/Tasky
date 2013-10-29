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
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TaskyDesign1Class
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QHBoxLayout *MainHLayout;
    QVBoxLayout *LeftVLayout;
    QHBoxLayout *CmdHLayout;
    QLabel *InputLabel;
    QLineEdit *InputBox;
    QTextEdit *TaskDetails;
    QCalendarWidget *calendar;
    QListWidget *DisplayPanel;

    void setupUi(QMainWindow *TaskyDesign1Class)
    {
        if (TaskyDesign1Class->objectName().isEmpty())
            TaskyDesign1Class->setObjectName(QStringLiteral("TaskyDesign1Class"));
        TaskyDesign1Class->resize(650, 340);
        TaskyDesign1Class->setMinimumSize(QSize(650, 340));
        TaskyDesign1Class->setMaximumSize(QSize(650, 340));
        centralWidget = new QWidget(TaskyDesign1Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 20, 611, 291));
        MainHLayout = new QHBoxLayout(layoutWidget);
        MainHLayout->setSpacing(6);
        MainHLayout->setContentsMargins(11, 11, 11, 11);
        MainHLayout->setObjectName(QStringLiteral("MainHLayout"));
        MainHLayout->setContentsMargins(0, 0, 0, 0);
        LeftVLayout = new QVBoxLayout();
        LeftVLayout->setSpacing(6);
        LeftVLayout->setObjectName(QStringLiteral("LeftVLayout"));
        LeftVLayout->setContentsMargins(-1, -1, 20, -1);
        CmdHLayout = new QHBoxLayout();
        CmdHLayout->setSpacing(6);
        CmdHLayout->setObjectName(QStringLiteral("CmdHLayout"));
        InputLabel = new QLabel(layoutWidget);
        InputLabel->setObjectName(QStringLiteral("InputLabel"));
        InputLabel->setStyleSheet(QStringLiteral("bg-color=rgb(255, 254, 221)"));
        InputLabel->setWordWrap(false);

        CmdHLayout->addWidget(InputLabel);

        InputBox = new QLineEdit(layoutWidget);
        InputBox->setObjectName(QStringLiteral("InputBox"));
        InputBox->setEnabled(true);
        InputBox->setMinimumSize(QSize(200, 25));
        InputBox->setMaximumSize(QSize(220, 25));

        CmdHLayout->addWidget(InputBox);


        LeftVLayout->addLayout(CmdHLayout);

        TaskDetails = new QTextEdit(layoutWidget);
        TaskDetails->setObjectName(QStringLiteral("TaskDetails"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TaskDetails->sizePolicy().hasHeightForWidth());
        TaskDetails->setSizePolicy(sizePolicy);
        TaskDetails->setMinimumSize(QSize(300, 60));
        TaskDetails->setMaximumSize(QSize(300, 60));
        TaskDetails->setFocusPolicy(Qt::NoFocus);
        TaskDetails->setFrameShape(QFrame::NoFrame);
        TaskDetails->setReadOnly(true);

        LeftVLayout->addWidget(TaskDetails);

        calendar = new QCalendarWidget(layoutWidget);
        calendar->setObjectName(QStringLiteral("calendar"));
        calendar->setMinimumSize(QSize(300, 160));
        calendar->setMaximumSize(QSize(300, 160));
        calendar->setCursor(QCursor(Qt::PointingHandCursor));

        LeftVLayout->addWidget(calendar);


        MainHLayout->addLayout(LeftVLayout);

        DisplayPanel = new QListWidget(layoutWidget);
        DisplayPanel->setObjectName(QStringLiteral("DisplayPanel"));
        DisplayPanel->setFrameShape(QFrame::NoFrame);
        DisplayPanel->setEditTriggers(QAbstractItemView::NoEditTriggers);

        MainHLayout->addWidget(DisplayPanel);

        TaskyDesign1Class->setCentralWidget(centralWidget);
        QWidget::setTabOrder(InputBox, TaskDetails);
        QWidget::setTabOrder(TaskDetails, calendar);
        QWidget::setTabOrder(calendar, DisplayPanel);

        retranslateUi(TaskyDesign1Class);

        QMetaObject::connectSlotsByName(TaskyDesign1Class);
    } // setupUi

    void retranslateUi(QMainWindow *TaskyDesign1Class)
    {
        TaskyDesign1Class->setWindowTitle(QApplication::translate("TaskyDesign1Class", "TaskyDesign1", 0));
        InputLabel->setText(QApplication::translate("TaskyDesign1Class", "Command", 0));
        InputBox->setPlaceholderText(QApplication::translate("TaskyDesign1Class", "Type your command here", 0));
        TaskDetails->setHtml(QApplication::translate("TaskyDesign1Class", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\" bgcolor=\"#c4eafc\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class TaskyDesign1Class: public Ui_TaskyDesign1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKYDESIGN_H
