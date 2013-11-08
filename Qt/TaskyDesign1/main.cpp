#include "taskydesign.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TaskyDesign w;
	w.show();
	return a.exec();
}
