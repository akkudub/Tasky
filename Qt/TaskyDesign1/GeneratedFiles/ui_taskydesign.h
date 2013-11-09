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
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TaskyDesignClass
{
public:
    QWidget *MainPart;
    QWidget *layoutWidget;
    QVBoxLayout *VerticalLayout;
    QTextEdit *DisplayPanel;
    QHBoxLayout *HorizontalLayout;
    QLabel *InputLabel;
    QLineEdit *InputBox;
    QToolButton *CloseButton;
    QToolButton *MinimizeButton;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TaskyDesignClass)
    {
        if (TaskyDesignClass->objectName().isEmpty())
            TaskyDesignClass->setObjectName(QStringLiteral("TaskyDesignClass"));
        TaskyDesignClass->resize(580, 430);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TaskyDesignClass->sizePolicy().hasHeightForWidth());
        TaskyDesignClass->setSizePolicy(sizePolicy);
        TaskyDesignClass->setMinimumSize(QSize(580, 430));
        TaskyDesignClass->setMaximumSize(QSize(580, 430));
        QIcon icon;
        icon.addFile(QStringLiteral(":/TaskyDesign1/Resources/logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        TaskyDesignClass->setWindowIcon(icon);
        TaskyDesignClass->setStyleSheet(QLatin1String("QMainWindow#TaskyDesignClass{\n"
"background-color: transparent; \n"
"padding: 0px 0px 5px 0px;\n"
"}"));
        MainPart = new QWidget(TaskyDesignClass);
        MainPart->setObjectName(QStringLiteral("MainPart"));
        sizePolicy.setHeightForWidth(MainPart->sizePolicy().hasHeightForWidth());
        MainPart->setSizePolicy(sizePolicy);
        MainPart->setMinimumSize(QSize(580, 375));
        MainPart->setMaximumSize(QSize(580, 430));
        MainPart->setStyleSheet(QLatin1String("QWidget#MainPart{\n"
"background-color: #2E534C; \n"
"border-radius: 2px;\n"
"}"));
        layoutWidget = new QWidget(MainPart);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 30, 541, 351));
        VerticalLayout = new QVBoxLayout(layoutWidget);
        VerticalLayout->setSpacing(6);
        VerticalLayout->setContentsMargins(11, 11, 11, 11);
        VerticalLayout->setObjectName(QStringLiteral("VerticalLayout"));
        VerticalLayout->setContentsMargins(0, 0, 0, 0);
        DisplayPanel = new QTextEdit(layoutWidget);
        DisplayPanel->setObjectName(QStringLiteral("DisplayPanel"));
        QFont font;
        font.setFamily(QStringLiteral("Segoe UI"));
        font.setPointSize(10);
        DisplayPanel->setFont(font);
        DisplayPanel->setAutoFillBackground(false);
        DisplayPanel->setStyleSheet(QLatin1String("QTextEdit#DisplayPanel{\n"
"background-color: #2E534C;\n"
"color: #FFFFFF;\n"
"box-shadow: 2px 2px 2px 2px #FFFFFF;\n"
"border-radius: 7px;\n"
"padding: 10px 5px 18px 0px;\n"
"}\n"
"QTextEdit#DisplatPanel:hover{\n"
"background-color: black;\n"
"}\n"
"QTextEdit#DisplayPanel QScrollBar:vertical{\n"
"background-color: #233333;\n"
"width: 5px;\n"
"}\n"
"QTextEdit#DisplayPanel QScrollBar::handle:vertical{\n"
"height:200px;\n"
"background-color: #2E334C;\n"
"}\n"
""));
        DisplayPanel->setFrameShape(QFrame::Box);
        DisplayPanel->setFrameShadow(QFrame::Sunken);
        DisplayPanel->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        DisplayPanel->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        DisplayPanel->setReadOnly(true);

        VerticalLayout->addWidget(DisplayPanel);

        HorizontalLayout = new QHBoxLayout();
        HorizontalLayout->setSpacing(6);
        HorizontalLayout->setObjectName(QStringLiteral("HorizontalLayout"));
        HorizontalLayout->setContentsMargins(-1, 15, -1, -1);
        InputLabel = new QLabel(layoutWidget);
        InputLabel->setObjectName(QStringLiteral("InputLabel"));
        QFont font1;
        font1.setFamily(QStringLiteral("Calibri"));
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        InputLabel->setFont(font1);
        InputLabel->setStyleSheet(QLatin1String("color: #FFFF00;\n"
"border: 0px solid white;"));

        HorizontalLayout->addWidget(InputLabel);

        InputBox = new QLineEdit(layoutWidget);
        InputBox->setObjectName(QStringLiteral("InputBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(InputBox->sizePolicy().hasHeightForWidth());
        InputBox->setSizePolicy(sizePolicy1);
        InputBox->setMinimumSize(QSize(400, 25));
        InputBox->setMaximumSize(QSize(16777215, 30));
        QFont font2;
        font2.setFamily(QStringLiteral("Calibri"));
        font2.setPointSize(11);
        InputBox->setFont(font2);
        InputBox->setStyleSheet(QLatin1String("QLineEdit#InputBox{\n"
"color: #FFFFFF;\n"
"border: 1px solid #FFFFFF;\n"
"border-radius: 2px;\n"
"background-color: #2E534C;\n"
"}"));
        InputBox->setCursorMoveStyle(Qt::VisualMoveStyle);

        HorizontalLayout->addWidget(InputBox);


        VerticalLayout->addLayout(HorizontalLayout);

        CloseButton = new QToolButton(MainPart);
        CloseButton->setObjectName(QStringLiteral("CloseButton"));
        CloseButton->setGeometry(QRect(550, 0, 31, 31));
        CloseButton->setFocusPolicy(Qt::NoFocus);
        CloseButton->setStyleSheet(QLatin1String("QToolButton#CloseButton{	\n"
"border-style:flat;\n"
"}\n"
""));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/TaskyDesign1/Resources/button_close100.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QStringLiteral(":/TaskyDesign1/Resources/button_close100.png"), QSize(), QIcon::Normal, QIcon::On);
        CloseButton->setIcon(icon1);
        CloseButton->setIconSize(QSize(25, 25));
        MinimizeButton = new QToolButton(MainPart);
        MinimizeButton->setObjectName(QStringLiteral("MinimizeButton"));
        MinimizeButton->setGeometry(QRect(530, 0, 31, 31));
        MinimizeButton->setFocusPolicy(Qt::NoFocus);
        MinimizeButton->setStyleSheet(QLatin1String("QToolButton#MinimizeButton{\n"
"border-style: flat;\n"
"}"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/TaskyDesign1/Resources/button_minimize100.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QStringLiteral(":/TaskyDesign1/Resources/button_minimize100.png"), QSize(), QIcon::Normal, QIcon::On);
        MinimizeButton->setIcon(icon2);
        MinimizeButton->setIconSize(QSize(25, 25));
        TaskyDesignClass->setCentralWidget(MainPart);
        statusBar = new QStatusBar(TaskyDesignClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(statusBar->sizePolicy().hasHeightForWidth());
        statusBar->setSizePolicy(sizePolicy2);
        statusBar->setMinimumSize(QSize(580, 35));
        QFont font3;
        font3.setPointSize(11);
        font3.setBold(false);
        font3.setWeight(50);
        statusBar->setFont(font3);
        statusBar->setStyleSheet(QLatin1String("background-color: #003329;\n"
"border-radius: 2px;\n"
"color: #FFFFFF;\n"
"margin: 0px 0px 0px 0px;\n"
"padding: 2px 10px 10px 10px;\n"
""));
        statusBar->setSizeGripEnabled(true);
        TaskyDesignClass->setStatusBar(statusBar);
        QWidget::setTabOrder(InputBox, DisplayPanel);

        retranslateUi(TaskyDesignClass);

        QMetaObject::connectSlotsByName(TaskyDesignClass);
    } // setupUi

    void retranslateUi(QMainWindow *TaskyDesignClass)
    {
        TaskyDesignClass->setWindowTitle(QApplication::translate("TaskyDesignClass", "Tasky", 0));
        DisplayPanel->setHtml(QApplication::translate("TaskyDesignClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p></body></html>", 0));
        InputLabel->setText(QApplication::translate("TaskyDesignClass", "  > ", 0));
        InputBox->setPlaceholderText(QApplication::translate("TaskyDesignClass", "input your command here", 0));
        CloseButton->setText(QString());
        MinimizeButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TaskyDesignClass: public Ui_TaskyDesignClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKYDESIGN_H
