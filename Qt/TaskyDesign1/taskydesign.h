#ifndef TASKYDESIGN1_H
#define TASKYDESIGN1_H

#include <QtWidgets/QMainWindow>
#include <QListWidget>
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
	Processor* _logic;
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
	void showFullTextOfSelected();

private:
	void changeUIStyle();
	void help();
	void about();
	void minimizeWindow();
	void exit();
	bool equalsToKeywordWithoutCase(const QString& input, const QString& keyword);
	void sendStdStringToBackEnd(QString input);
	std::string preserveFirstString(int num);
	std::string fullString(int num);

private:
	Ui::TaskyDesign1Class ui;
};

#endif // TASKYDESIGN1_H
