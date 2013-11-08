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
	int _msgType;
	QStringList wordlist;

private:
	static const QString STYLE_SHEET_DISPLAY_PANEL;
	static const QString STYLE_SHEET_WINDOW;
	static const QString STYLE_SHEET_INPUT_BOX;

	static const QString KEYWORD_HELP;
	static const QString KEYWORD_ABOUT;
	static const QString KEYWORD_EXIT;
	static const QString KEYWORD_MINIMIZE;

	static const QString ICON_STRING;

private slots:
	void processInputString();
	void updateStatusBar(QString text);

private:
	void setUpCompleter();
	void changeUIStyle();
	void minimizeWindow();
	void exit();
	bool equalsToKeywordWithoutCase(const QString& input, const QString& keyword);
	void sendStdStringToBackEnd(QString input);
	QString formatString(int num);
	QString combineOutput(int size);

private:
	Ui::TaskyDesign1Class ui;
};

#endif // TASKYDESIGN1_H
