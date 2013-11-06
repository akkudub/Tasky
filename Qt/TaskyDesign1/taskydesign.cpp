#include <qmessagebox.h>
#include "taskydesign.h"
#include <qdebug.h>

const QString TaskyDesign::STYLE_SHEET_WINDOW = "background-color: #CCFF99; border-radius: 10px;";
const QString TaskyDesign::STYLE_SHEET_DISPLAY_PANEL = "QListWidget#DisplayPanel{background-color: #F1FFFF; border-radius: 5px;}\n"
	                                                   "QListView#DisplayPanel::item {margin-bottom: 5px; border-radius: 5px;}\n"
	                                                   "QListView#DisplayPanel::item:selected {background-color: #5CE6E6;}";
const QString TaskyDesign::STYLE_SHEET_INPUT_BOX = "QLineEdit#InputBox{background-color: #FFFFFF;}";

const QString TaskyDesign::KEYWORD_ABOUT = "about";
const QString TaskyDesign::KEYWORD_EXIT = "exit";
const QString TaskyDesign::KEYWORD_HELP = "help";
const QString TaskyDesign::KEYWORD_MINIMIZE = "minimize";

const QString TaskyDesign::ICON_STRING = "tasky_icon.ico";

TaskyDesign::TaskyDesign(QWidget *parent): QMainWindow(parent){
	ui.setupUi(this);
	_logic=new Processor();

	changeUIStyle();

	connect(ui.InputBox, SIGNAL(returnPressed()), this, SLOT(processInputString()));
	connect(ui.DisplayPanel, SIGNAL(itemSelectionChanged()), this, SLOT(showFullTextOfSelected()));
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

void TaskyDesign::showFullTextOfSelected(){
	int size=_vec.size();
	//int size=ui.DisplayPanel->count();
	for (int i=0;i<size;i++){
		if (i>=ui.DisplayPanel->count()){
			continue;
		}else if (ui.DisplayPanel->item(i)->isSelected()){
			ui.DisplayPanel->item(i)->setText(QString::fromStdString(fullString(i)));
		}else{
			ui.DisplayPanel->item(i)->setText(QString::fromStdString(preserveFirstString(i)));
	    }
	}
}

void TaskyDesign::changeUIStyle(){
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setStyleSheet(STYLE_SHEET_WINDOW);
	this->setWindowIcon(QIcon(ICON_STRING));
	ui.DisplayPanel->setStyleSheet(STYLE_SHEET_DISPLAY_PANEL);
	ui.InputBox->setStyleSheet(STYLE_SHEET_INPUT_BOX);
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
	delete _logic;
	this->close();
}

bool TaskyDesign::equalsToKeywordWithoutCase(const QString& input, const QString& keyword){
	return input.toLower()==keyword;
}

void TaskyDesign::sendStdStringToBackEnd(QString input){
	_logic->UImainProcessor(input.toStdString(), _msg, _vec);
	ui.DisplayPanel->clear();
	ui.statusBar->clearMessage();
	ui.statusBar->showMessage(QString::fromStdString(_msg), 0);
	int size=_vec.size();
	for (unsigned int i=0;i<size;i++){
		ui.DisplayPanel->addItem(QString::fromStdString(preserveFirstString(i)));
	}
	if (ui.DisplayPanel->count()>=1){
		ui.DisplayPanel->item(0)->setSelected(true);
	}
}

std::string TaskyDesign::preserveFirstString(int num){
	std::string str= _vec.at(num);
	return str.substr(0, str.find_first_of('\n'));
}

std::string TaskyDesign::fullString(int num){
	return _vec.at(num);
}

TaskyDesign::~TaskyDesign(){
}
