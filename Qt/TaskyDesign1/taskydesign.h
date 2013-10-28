#ifndef TASKYDESIGN1_H
#define TASKYDESIGN1_H

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include <QPropertyAnimation>
#include <vector>
#include "ui_taskydesign.h"
#include "Processor.h"

class TaskyDesign : public QMainWindow
{
	Q_OBJECT

public:
	TaskyDesign(QWidget *parent = 0);
	~TaskyDesign();

private:
	Processor _logic;
	std::string _msg;
	std::vector<std::string> _vec;

private:
	static const QString STYLE_SHEET_TASK_DETAILS;
	static const QString STYLE_SHEET_DISPLAY_PANEL;
	static const QString STYLE_SHEET_UI;

	static const QString KEYWORD_HELP;
	static const QString KEYWORD_ABOUT;
	static const QString KEYWORD_EXIT;
	static const QString KEYWORD_MINIMIZE;

	static const QString ICON_STRING;

private slots:
	void processInputString();
	void changeBGColor(int type);

private:
	void changeUIStyle();
	void help();
	void about();
	void blink(int colorType);
	void minimizeWindow();
	void exit();
	bool equalsToKeywordWithoutCase(const QString& input, const QString& keyword);
	void sendStdStringToBackEnd(QString input);

private:
	Ui::TaskyDesign1Class ui;
	QTimer* timer;
	QPropertyAnimation* animation;
};

#endif // TASKYDESIGN1_H
