#include "taskydesign.h"
#include <QCompleter>

const QString TaskyDesign::STYLE_SHEET_WINDOW = "background-color: #CCFF99; border-radius: 10px;";
const QString TaskyDesign::STYLE_SHEET_DISPLAY_PANEL = "QTextEdit#DisplayPanel{background-color: #ECFFF9; border-radius: 7px; margin-bottom: 20px;}";
const QString TaskyDesign::STYLE_SHEET_INPUT_BOX = "QLineEdit#InputBox{background-color: #FFFFFF;}";

const QString TaskyDesign::KEYWORD_EXIT = "exit";
const QString TaskyDesign::KEYWORD_MINIMIZE = "minimize";

const QString TaskyDesign::ICON_STRING = "tasky_icon.ico";

TaskyDesign::TaskyDesign(QWidget *parent): QMainWindow(parent){
	_logic=new Processor();
	ui.setupUi(this);
	setUpCompleter();
	changeUIStyle();

	connect(ui.InputBox, SIGNAL(textChanged(QString)), this, SLOT(updateStatusBar(QString)));
	connect(ui.InputBox, SIGNAL(returnPressed()), this, SLOT(processInputString()));
}

void TaskyDesign::processInputString(){
	QString input=ui.InputBox->text();
	ui.InputBox->clear();
	if(equalsToKeywordWithoutCase(input, KEYWORD_MINIMIZE)){
		minimizeWindow();
    }else if(equalsToKeywordWithoutCase(input, KEYWORD_EXIT)){
        exit();
    }else{
		sendStdStringToBackEnd(input);
	}
}

void TaskyDesign::updateStatusBar(QString text){
	QString input=text;
	if (input=="add" || input=="ad" || input=="a"){
		ui.statusBar->showMessage("add operation: you can type help -add for more information.");
	}
}

void TaskyDesign::setUpCompleter(){
	wordlist<<"add"<<"rename"<<"reschedule"<<"display"<<"remove"<<"rename"<<"help"<<"exit";
	QCompleter *completer=new QCompleter(wordlist, this->ui.InputBox);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	completer->setCompletionMode(QCompleter::InlineCompletion);
	ui.InputBox->setCompleter(completer);
}

void TaskyDesign::changeUIStyle(){
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setStyleSheet(STYLE_SHEET_WINDOW);
	this->setWindowIcon(QIcon(ICON_STRING));
	ui.DisplayPanel->setStyleSheet(STYLE_SHEET_DISPLAY_PANEL);
	ui.InputBox->setStyleSheet(STYLE_SHEET_INPUT_BOX);
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
	_msgType=_logic->UImainProcessor(input.toStdString(), _msg, _vec);
	ui.DisplayPanel->clear();
	ui.statusBar->clearMessage();
	ui.statusBar->showMessage(QString::fromStdString(_msg), 0);
	int size=_vec.size();
	ui.DisplayPanel->setHtml(combineOutput(size));
}

QString TaskyDesign::formatString(int num){
	QString iniStr="";
	std::string str=_vec.at(num);
	int pos1=0;
	int pos2=str.find('\n');
	iniStr.append("<font color='DeepPink'>" + QString::fromStdString(str.substr(pos1,pos2)) + "<br/></font>");
	return iniStr;
}

QString TaskyDesign::combineOutput( int size ){
	QString initStr="";
	for (unsigned int i=0;i<size;i++){
		initStr.append(formatString(i));
	}
	return initStr;
}

TaskyDesign::~TaskyDesign(){
}
