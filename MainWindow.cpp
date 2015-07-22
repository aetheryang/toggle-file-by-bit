/*************************************************************************
    > File Name: MainWindow.cpp
    > Author: aetheryang
    > Mail: aetheryang@gmail.com
    > Created Time: Sun 05 Jan 2014 09:33:27 PM CST
 ************************************************************************/
#include "MainWindow.h"
#include"toggle_file.cpp"
using namespace std;

void MainWindow::s_add_dir() {
  QFileDialog *dialog = new QFileDialog( this);
  dialog->setFileMode( QFileDialog::Directory);
  QStringList filenames;
  if (dialog->exec())
    filenames = dialog->selectedFiles();
  QString path;
  path = filenames.join("");
  if(path == "")
    return;
  QStringList list = showfile(path);
  list_left->addItems( list );
}

void MainWindow::s_add_file() {
  QFileDialog *dialog = new QFileDialog( this);
  dialog->setFileMode( QFileDialog::ExistingFiles);
  QStringList filenames;
  if (dialog->exec())
    filenames = dialog->selectedFiles();
  list_right->addItems(filenames);
}

void MainWindow::s_set_output() {
  QFileDialog *dialog = new QFileDialog( this);
  dialog->setFileMode( QFileDialog::Directory);
  //dialog->show();
  QStringList filenames;
  if (dialog->exec())
    filenames = dialog->selectedFiles();
  output = filenames.join("");
  if(output == QDir::currentPath()) {
    c_suffix->setChecked(1);
    c_suffix->setEnabled(0);
  }
  if(output == "") {
    pb_toggle->setEnabled(0);
    label->setText("output not seted");
  }
  else
    pb_toggle->setEnabled(1);
  label->setText(output);
}

void MainWindow::s_4gb_checked(int state) {
  if(state) {
    c_suffix->setChecked(1);
    c_suffix->setEnabled(0);
  }
  else
    return;
    //c_suffix->setEnabled(1);
}

void MainWindow::s_toggle() {
  int i;
  for( i = 0; i < list_right->count(); i++) {
    QString filename(list_right->item(i)->text());
    choose_mode(filename);
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

void MainWindow::s_about() {}
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
  QPushButton *pb_add_dir    = new QPushButton("Add &dir", this);
  QPushButton *pb_add_file   = new QPushButton("Add &file", this);
  //QPushButton *run     = new QPushButton("&Run", this);
  QPushButton *pb_about     = new QPushButton("&About", this);
  QPushButton *pb_set_output  = new QPushButton("Set output", this);
  pb_toggle = new QPushButton("&Toggle", this);
  //pb_toggle->setEnabled(0);
  label = new QLabel("file out to:");
  c_suffix = new QCheckBox("suffix", this);
  c_4gb = new QCheckBox("4gblimt", this);
  c_suffix->setChecked(0);
  c_4gb->setChecked(0);
  c_suffix->setEnabled(0);
  c_4gb->setEnabled(0);
  list_right = new QListWidget;
  list_left = new QListWidget;
  QStringList list = showfile(QDir::currentPath());
  list_left->addItems( list );


  mainlayout->addWidget (pb_add_dir,      0, 0, 1, 1, 0);
  mainlayout->addWidget (pb_add_file,     0, 1, 1, 1, 0);
  //mainlayout->addWidget (run,       0, 1, 1, 1, 0);
  mainlayout->addWidget (pb_about,       0, 2, 1, 1, 0);
  mainlayout->addWidget (pb_set_output,    0, 3, 1, 1, 0);
  mainlayout->addWidget (pb_toggle, 0, 4, 1, 1, 0);
  mainlayout->addWidget (c_suffix,  1, 1, 1, 1, 0);
  mainlayout->addWidget (c_4gb,  1, 2, 1, 1, 0);
  mainlayout->addWidget (list_left, 1, 0, 1, 1, 0);
  mainlayout->addWidget (list_right,1, 4, 1, 1, 0);
  mainlayout->addWidget (label,    7, 0, 1, 1, 0);
  mainlayout->addWidget (progress,  7, 4, 1, 1, 0);
  //QObject::connect( scan, SIGNAL( clicked()), this, SLOT(s_scan()));
  //QObject::connect( run, SIGNAL( clicked()), this, SLOT(s_run()));
  QObject::connect( pb_add_dir, SIGNAL( clicked()), this, SLOT(s_add_dir()));
  QObject::connect( pb_add_file, SIGNAL( clicked()), this, SLOT(s_add_file()));
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
