/*************************************************************************
    > File Name: MainWindow.cpp
    > Author: aetheryang
    > Mail: aetheryang@gmail.com
    > Created Time: Sun 05 Jan 2014 09:33:27 PM CST
 ************************************************************************/
#include "MainWindow.h"
#include"toggle_file.cpp"
using namespace std;

QStringList MainWindow::showfile() {
  QDir dir;
  dir.setFilter( QDir::Files | QDir::Hidden | QDir::NoSymLinks );
  dir.setSorting( QDir::Name | QDir::Reversed );
  QStringList list = dir.entryList();
  return list;
}

void MainWindow::toggle(QString filename)
{
  toggle_burst(filename);
  return;
}


void MainWindow::s_scan(QListWidgetItem *item) {
}

void MainWindow::s_set_output() {
  QFileDialog *dialog = new QFileDialog( this);
  dialog->setFileMode( QFileDialog::Directory);
  //dialog->show();
  QStringList filenames;
  if (dialog->exec())
    filenames = dialog->selectedFiles();
  output = filenames.join("");
  label->setText(output);
  cout << output.toStdString() << endl;
}

void MainWindow::s_4gb_checked(int state) {
  if(state) {
    c_suffix->setChecked(1);
    c_suffix->setEnabled(0);
  }
  else
    c_suffix->setEnabled(1);
}

void MainWindow::s_toggle() {
  int i;
  for( i = 0; i < list_right->count(); i++) {
    QString filename(list_right->item(i)->text());
    toggle(filename);
  }
  cout << "toggle finished" << endl;
}

void MainWindow::slot_left_to_right(QListWidgetItem *item) {
  item = list_left->takeItem(list_left->row(item));
  list_right->addItem(item);
}

void MainWindow::slot_right_to_left(QListWidgetItem *item) {
  item = list_right->takeItem(list_right->row(item));
  list_left->addItem(item);
}

void MainWindow::s_run() {}
void MainWindow::pfresh ()
{
}

MainWindow::~MainWindow ()
{
}

MainWindow::MainWindow ()
{
  QGridLayout *mainlayout  = new QGridLayout ();
  progress   = new QProgressBar;
  QSlider *slider          = new QSlider (Qt::Horizontal);
  setLayout (mainlayout);
  progress->setValue (0);
  resize (1200, 1200);
  slider->setRange (1, 1000);
  slider->setValue (100);
  QPushButton *scan    = new QPushButton("&Scan", this);
  QPushButton *run     = new QPushButton("&Run", this);
  QPushButton *end     = new QPushButton("&End", this);
  QPushButton *pb_set_output  = new QPushButton("Set output", this);
  QPushButton *pb_toggle = new QPushButton("&Toggle", this);
  label = new QLabel("file out to:");
  c_suffix = new QCheckBox("suffix", this);
  c_4gb = new QCheckBox("4gblimt", this);
  c_suffix->setChecked(0);
  list_right = new QListWidget;
  list_left = new QListWidget;
  QStringList list = showfile();
  list_left->addItems( list );


  mainlayout->addWidget (scan,      0, 0, 1, 1, 0);
  mainlayout->addWidget (run,       0, 1, 1, 1, 0);
  mainlayout->addWidget (end,       0, 2, 1, 1, 0);
  mainlayout->addWidget (pb_set_output,    0, 3, 1, 1, 0);
  mainlayout->addWidget (pb_toggle, 0, 4, 1, 1, 0);
  mainlayout->addWidget (c_suffix,  1, 1, 1, 1, 0);
  mainlayout->addWidget (c_4gb,  1, 2, 1, 1, 0);
  mainlayout->addWidget (list_left, 1, 0, 1, 1, 0);
  mainlayout->addWidget (list_right,1, 4, 1, 1, 0);
  mainlayout->addWidget (label,    7, 0, 1, 1, 0);
  mainlayout->addWidget (progress,  7, 4, 1, 1, 0);
  //QObject::connect( scan, SIGNAL( clicked()), this, SLOT(s_scan()));
  QObject::connect( run, SIGNAL( clicked()), this, SLOT(s_run()));
  QObject::connect( pb_set_output, SIGNAL( clicked()), this, SLOT(s_set_output()));
  QObject::connect( pb_toggle, SIGNAL( clicked()), this, SLOT(s_toggle()));
  QObject::connect( c_4gb, SIGNAL(stateChanged(int)), this, SLOT(s_4gb_checked(int)));
  QObject::connect( list_right,
                    SIGNAL( itemDoubleClicked(QListWidgetItem *)),
                    this,
                    SLOT(slot_right_to_left(QListWidgetItem *)));
  QObject::connect( list_left,
                    SIGNAL( itemDoubleClicked(QListWidgetItem *)),
                    this,
                    SLOT(slot_left_to_right(QListWidgetItem *)));
}
