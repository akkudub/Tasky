#include "taskydesign.h"
#include <QPalette>

const QString TaskyDesign::ADD_COMPLETE_WORD                 = "add";
const QString TaskyDesign::DISPLAY_COMPLETE_WORD             = "display";
const QString TaskyDesign::REMOVE_COMPLETE_WORD              = "remove";
const QString TaskyDesign::RENAME_COMPLETE_WORD              = "rename";
const QString TaskyDesign::RESCHEDULE_COMPLETE_WORD          = "reschedule";
const QString TaskyDesign::SEARCH_COMPLETE_WORD              = "search";
const QString TaskyDesign::MARK_COMPLETE_WORD                = "mark";
const QString TaskyDesign::UNDO_COMPLETE_WORD                = "undo";
const QString TaskyDesign::REDO_COMPLETE_WORD                = "redo";
const QString TaskyDesign::HELP_COMPLETE_WORD                = "help";
const QString TaskyDesign::HIDE_COMPLETE_WORD                = "hide";
const QString TaskyDesign::EXIT_COMPLETE_WORD                = "exit";

const QString TaskyDesign::ADD_OPERATION_REMINDER            = "Add: help -add for more information";
const QString TaskyDesign::DISPLAY_OPERATION_REMINDER        = "Display: try one of these:"
	                                                           " all/today/pending or done";
const QString TaskyDesign::REMOVE_OPERATION_REMINDER         = "Remove: remove a task by title";
const QString TaskyDesign::RENAME_OPERATION_REMINDER         = "Rename: change the title and the comment";
const QString TaskyDesign::RESCHEDULE_OPERATION_REMINDER     = "Reschedule: change the time domain of a task";
const QString TaskyDesign::SEARCH_OPERATION_REMINDER         = "Search: search by keywords+status+time domain"
	                                                            " or search empty slots";
const QString TaskyDesign::MARK_OPERATION_REMINDER           = "Mark: mark a task done or pending";
const QString TaskyDesign::UNDO_OPERATION_REMINDER           = "Undo: undo one or multiple times";
const QString TaskyDesign::REDO_OPERATION_REMINDER           = "Redo: redo one or multiple times";
const QString TaskyDesign::HELP_OPERATION_REMINDER           = "Help: learn how to better use this software";
const QString TaskyDesign::HIDE_OPERATION_REMIDER            = "Hide: Tasky will be hidden and runs in background";
const QString TaskyDesign::EXIT_OPERATION_REMINDER           = "Exit: have a nice day";
const QString TaskyDesign::OTHER_OPERATION_REMINDER          = "Attention: invalid command type";

const QString TaskyDesign::TRAY_MSG_TITLE                    = "Tasky message";
const QString TaskyDesign::TRAY_MSG_CONTENT                  = "Tasky is now hiding";

const QString TaskyDesign::ICON_STRING                       = "logo.ico";

TaskyDesign::TaskyDesign(QWidget *parent): QMainWindow(parent){
	_logic=new Processor();
	ui.setupUi(this);
	overallSetUp();
	setUpConnections();
	setUpUI();
}

//////////////////////////////////////////////////////////////////////////
//private slots definitions                                             //
//////////////////////////////////////////////////////////////////////////
void TaskyDesign::trayIconActivated(QSystemTrayIcon::ActivationReason){
	this->show();
	ui.InputBox->setFocus();
}

void TaskyDesign::showMainWindow(){
	this->show();
	ui.InputBox->setFocus();
}

void TaskyDesign::processInputString(){
	QString input=ui.InputBox->text();
	ui.InputBox->clear();
	if(equalsToKeywordWithoutCase(input, EXIT_COMPLETE_WORD)){
        exitProgram();
    }else if(equalsToKeywordWithoutCase(input, HIDE_COMPLETE_WORD)){
		hideWindow();
    }else{
		sendStdStringToBackEnd(input);
	}
}

void TaskyDesign::updateStatusBar(QString text){
	QPalette mypalette;
	mypalette.setColor(QPalette::WindowText, Qt::white);
	ui.statusBar->setPalette(mypalette);
	if (startWithCaseInsensitive(text, ADD_COMPLETE_WORD)){
		showStatusBarMsg(ADD_OPERATION_REMINDER);
	}else if(startWithCaseInsensitive(text, DISPLAY_COMPLETE_WORD)){
		showStatusBarMsg(DISPLAY_OPERATION_REMINDER);
	}else if(startWithCaseInsensitive(text, REMOVE_COMPLETE_WORD)){
		showStatusBarMsg(REMOVE_OPERATION_REMINDER);
	}else if(startWithCaseInsensitive(text, RENAME_COMPLETE_WORD)){
		showStatusBarMsg(RENAME_OPERATION_REMINDER);
	}else if(startWithCaseInsensitive(text, RESCHEDULE_COMPLETE_WORD)){
		showStatusBarMsg(RESCHEDULE_OPERATION_REMINDER);
	}else if(startWithCaseInsensitive(text, SEARCH_COMPLETE_WORD)){
		showStatusBarMsg(SEARCH_OPERATION_REMINDER);
	}else if(startWithCaseInsensitive(text, MARK_COMPLETE_WORD)){
		showStatusBarMsg(MARK_OPERATION_REMINDER);
	}else if(startWithCaseInsensitive(text, UNDO_COMPLETE_WORD)){
		showStatusBarMsg(UNDO_OPERATION_REMINDER);
	}else if(startWithCaseInsensitive(text, REDO_COMPLETE_WORD)){
		showStatusBarMsg(REDO_OPERATION_REMINDER);
	}else if(startWithCaseInsensitive(text, HELP_COMPLETE_WORD)){
		showStatusBarMsg(HELP_OPERATION_REMINDER);
	}else if (startWithCaseInsensitive(text, HIDE_COMPLETE_WORD)){
		showStatusBarMsg(HIDE_OPERATION_REMIDER);
    }else if(startWithCaseInsensitive(text, EXIT_COMPLETE_WORD)){
		showStatusBarMsg(EXIT_OPERATION_REMINDER);
	}else{
		showStatusBarMsg(OTHER_OPERATION_REMINDER);
	}
}

void TaskyDesign::checkMinimize(){
	QTimer::singleShot(0, this, SLOT(hide()));
	trayHiddenMsg();
}

void TaskyDesign::checkExit(){
	delete _logic;
	this->close();
}

//////////////////////////////////////////////////////////////////////////
//set up the main window utilities                                      //
//////////////////////////////////////////////////////////////////////////
void TaskyDesign::overallSetUp(){
    setUpTrayIcon();
	setUpCompleter();
}

void TaskyDesign::setUpTrayIcon(){
	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setIcon(QIcon(ICON_STRING));
	trayIcon->show();
}

void TaskyDesign::setUpCompleter(){
	fillUpWordList();
	QCompleter *completer=new QCompleter(wordlist, this->ui.InputBox);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	completer->setCompletionMode(QCompleter::InlineCompletion);
	ui.InputBox->setCompleter(completer);
}

void TaskyDesign::fillUpWordList(){
	wordlist<<ADD_COMPLETE_WORD<<DISPLAY_COMPLETE_WORD<<REMOVE_COMPLETE_WORD
		<<RENAME_COMPLETE_WORD<<RESCHEDULE_COMPLETE_WORD<<SEARCH_COMPLETE_WORD
		<<MARK_COMPLETE_WORD<<UNDO_COMPLETE_WORD<<REDO_COMPLETE_WORD
		<<HELP_COMPLETE_WORD<<HIDE_COMPLETE_WORD<<EXIT_COMPLETE_WORD;
}

void TaskyDesign::setUpGlobalShortCutKey(){
	QxtGlobalShortcut* scOpenMainWin = new QxtGlobalShortcut(QKeySequence("Ctrl+Alt+t"), this);
	connect(scOpenMainWin, SIGNAL(activated()),this, SLOT(showWindow()));
}

void TaskyDesign::setUpConnections(){
	connect(ui.InputBox, SIGNAL(textChanged(QString)), this, SLOT(updateStatusBar(QString)));
	connect(ui.InputBox, SIGNAL(returnPressed()), this, SLOT(processInputString()));
	connect(ui.CloseButton, SIGNAL(clicked()), this, SLOT(checkExit()));
	connect(ui.MinimizeButton, SIGNAL(clicked()), this, SLOT(checkMinimize()));
	connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this,
		SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
	connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(showMainWindow()));
}

void TaskyDesign::setUpUI(){
	this->setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	this->setWindowIcon(QIcon(ICON_STRING));
	ui.InputBox->setFocus();
}

//////////////////////////////////////////////////////////////////////////
//UI special functionality handling functions                           //
//////////////////////////////////////////////////////////////////////////
bool TaskyDesign::eventFilter(QObject* watched, QEvent* event){
	return false;
}

void TaskyDesign::mousePressEvent(QMouseEvent *event){
	this->windowPosition = this->pos();
	this->mousePressPosition = event->globalPos();
}

void TaskyDesign::mouseMoveEvent(QMouseEvent *event){
	this->mouseMovePosition = event->globalPos();
	QPoint distanceToMove = this->mouseMovePosition - this->mousePressPosition + 
		this->windowPosition;
	this->move(distanceToMove);   
}

void TaskyDesign::trayHiddenMsg(){
	trayIcon->showMessage(TRAY_MSG_TITLE, TRAY_MSG_CONTENT);
}

void TaskyDesign::showStatusBarMsg(QString content){
	ui.statusBar->showMessage(content);
}

void TaskyDesign::hideWindow(){
	QTimer::singleShot(0, this, SLOT(hide()));
	trayHiddenMsg();
}

void TaskyDesign::exitProgram(){
	delete _logic;
	this->close();
}

//////////////////////////////////////////////////////////////////////////
//UI logic parts                                                        //
//////////////////////////////////////////////////////////////////////////
void TaskyDesign::sendStdStringToBackEnd(QString input){
	_msgType=_logic->UImainProcessor(input.toStdString(), _msg, _vec);
	int size=_vec.size();
	ui.DisplayPanel->clear();
	ui.statusBar->clearMessage();
	setStatusBarMsgAndColor();
	ui.DisplayPanel->setHtml(combineOutput(size));
}

void TaskyDesign::setStatusBarMsgAndColor(){
	QPalette mypalette;
	if (_msg.find("Success!")!=std::string::npos){
		mypalette.setColor(QPalette::WindowText, Qt::green);
	}else if(_msg.find("Error!")!=std::string::npos){
		mypalette.setColor(QPalette::WindowText, Qt::red);
	}else if(_msg.find("Warning!")!=std::string::npos){
		mypalette.setColor(QPalette::WindowText, Qt::yellow);
	}else{
		mypalette.setColor(QPalette::WindowText, Qt::white);
	}
	ui.statusBar->setPalette(mypalette);
	ui.statusBar->showMessage(QString::fromStdString(_msg));
}

bool TaskyDesign::equalsToKeywordWithoutCase(const QString& input, const QString& keyword){
	return input.toLower()==keyword;
}

bool TaskyDesign::startWithCaseInsensitive(QString text, const QString& keyword){
	return text.startsWith(keyword, Qt::CaseInsensitive);
}

QString TaskyDesign::combineOutput( int size ){
	QString initStr="";
	for (unsigned int i=0;i<size;i++){
		initStr.append(formatString(i));
	}
	return initStr;
}

QString TaskyDesign::formatString(int num){
	std::string str=_vec.at(num);
	
	if (str.find('\n')==std::string::npos){
		return singleLineInDisplayPanel(str);
	}else{
		return multipleLinesInDisplayPanel(str);		
	}
}

QString TaskyDesign::singleLineInDisplayPanel(std::string str){
	return "<font color=\"Red\">"+QString::fromStdString(str)+"</font><br/>";
}

QString TaskyDesign::multipleLinesInDisplayPanel(std::string str){
	QString initStr="";

	initStr.append("<pre>");
	initStr.append(QString::fromStdString(str));
	initStr.replace(" ", "&nbsp;");
	initStr.replace(QString("\n"), QString("<br/>"));
	initStr.append("<br/><br/>");
	initStr.append("</pre>");
	return initStr;
}

TaskyDesign::~TaskyDesign(){
}
