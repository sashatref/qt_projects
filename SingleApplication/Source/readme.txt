#include "singleapplication.h"

int main(int argc, char *argv[])
{
	SingleApplication a(argc, argv, "UniqueName");
	if(a.isRunning()) { return 0;}
	
	MainWindow w;
	QObject::connect(&a, SIGNAL(onAnotherInstanceLaunch()), &w, SLOT(anotherAppInstanceLaunch()));
	w.show;
	
	return a.exec();
}

� MainWindow �������� ���� anotherAppInstanceLaunch, � ������� ���������� ��� ��������� �� �������� ���� ����