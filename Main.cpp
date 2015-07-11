/*************************************************************************
    > File Name: Main.cpp
    > Author: aetheryang
    > Mail: aetheryang@gmail.com
    > Created Time: Sun 05 Jan 2014 09:23:17 PM CST
 ************************************************************************/

#include<QApplication>
#include"MainWindow.cpp"
int main (int argc, char **argv)
{
	QApplication a (argc, argv);
	MainWindow *window = new MainWindow ();
	window->show ();
	return a.exec ();
}
