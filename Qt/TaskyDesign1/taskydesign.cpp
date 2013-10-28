#include <qmessagebox.h>
#include "taskydesign.h"

const QString TaskyDesign::STYLE_SHEET_TASK_DETAILS = "QWidget#TaskDetails{background-color:#c4eafc;}";
const QString TaskyDesign::STYLE_SHEET_DISPLAY_PANEL = "QListWidget#DisplayPanel{background-color: #F1FFFF;}\n"
	                                                   "QListView#DisplayPanel::item:selected {background-color: #5CE6E6;}";
const QString TaskyDesign::STYLE_SHEET_UI = "QWidget#centralWidget {background-color: #CCFF99;}";

const QString TaskyDesign::KEYWORD_ABOUT = "about";
const QString TaskyDesign::KEYWORD_EXIT = "exit";
const QString TaskyDesign::KEYWORD_HELP = "help";
const QString TaskyDesign::KEYWORD_MINIMIZE = "minimize";

const QString TaskyDesign::ICON_STRING = "tasky_icon.ico";

TaskyDesign::TaskyDesign(QWidget *parent): QMainWindow(parent){
	ui.setupUi(this);

	timer=new QTimer(this);
	animation=new QPropertyAnimation(this);

	changeUIStyle();
	ui.TaskDetails->setStyleSheet(STYLE_SHEET_TASK_DETAILS);
	ui.DisplayPanel->setStyleSheet(STYLE_SHEET_DISPLAY_PANEL);

	connect(ui.InputBox, SIGNAL(returnPressed()), this, SLOT(processInputString()));
}

void TaskyDesign::processInputString(){
	QString input=ui.InputBox->text();
	ui.InputBox->clear();
	if (equalsToKeywordWithoutCase(input, KEYWORD_HELP)){
		help();
	}else if(equalsToKeywordWithoutCase(input, KEYWORD_ABOUT)){
		about();
	}else if(equalsToKeywordWithoutCase(input, KEYWORD_MINIMIZE)){
		minimizeWindow();
    }else if(equalsToKeywordWithoutCase(input, KEYWORD_EXIT)){
        exit();
    }else{
		sendStdStringToBackEnd(input);
	}
}

void TaskyDesign::changeBGColor(int type){
}

void TaskyDesign::changeUIStyle(){
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setStyleSheet(STYLE_SHEET_UI);
	this->setWindowIcon(QIcon(ICON_STRING));
}

void TaskyDesign::blink(int colorType){
	
}

void TaskyDesign::help(){
	QMessageBox help;
	help.setText("help here");
	help.exec();
}

void TaskyDesign::about(){
	QMessageBox about;
	about.setText("about us");
	about.exec();
}

void TaskyDesign::minimizeWindow(){
	showMinimized();
}

void TaskyDesign::exit(){
	this->close();
}

bool TaskyDesign::equalsToKeywordWithoutCase(const QString& input, const QString& keyword){
	return input.toLower()==keyword;
}

void TaskyDesign::sendStdStringToBackEnd(QString input){
	ui.TaskDetails->clear();
	ui.TaskDetails->setStyleSheet("QWidget#TaskDetails{background-color:#c4eafc;}");
	_logic.UImainProcessor(input.toStdString(), _msg, _vec);
	ui.DisplayPanel->setStyleSheet("QListWidget#DisplayPanel{background-color: #F1FFFF;}\n"
			" QListView#DisplayPanel::item:selected {background-color: #5CE6E6;}");
	ui.TaskDetails->setText(QString::fromStdString(_msg));
}

TaskyDesign::~TaskyDesign(){
}
