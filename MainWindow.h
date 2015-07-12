/*************************************************************************
    > File Name: MainWindow.h
    > Author: aetheryang
    > Mail: aetheryang@gmail.com 
    > Created Time: Sun 05 Jan 2014 09:26:15 PM CST
 ************************************************************************/
#include<QProgressBar>
#include<QListWidget>
#include<QWidget>
#include<qmainwindow.h>
#include<QObject>
#include<QDir>
#include<QCheckBox>
#include <QAction>
#include <QIcon>
#include <QToolBar>
#include <QMenuBar>
#include <QMenu>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include<QSlider>
#include<QSpinBox>
#include<QPushButton>
#include<QGridLayout>
#include<iostream>
#include<QPainter>
#include<QCheckBox>
#include<QFileDialog>
class MainWindow:public QWidget
{
  Q_OBJECT public:
	  MainWindow ();
	 ~MainWindow ();
	void pfresh ();
  public:
  QListWidget *list_right, *list_left;
  QCheckBox *c_suffix, *c_4gb;
  QProgressBar *progress;
  QLabel* label;
  QString output;
  QStringList showfile();
  void toggle(QString filename);
  void toggle_burst(QString filename);
  public slots:
  void s_scan(QListWidgetItem *item);
  void s_toggle();
  void s_run();
  void s_4gb_checked(int state);
  void s_set_output();
  void slot_left_to_right(QListWidgetItem *item);
  void slot_right_to_left(QListWidgetItem *item);
};
