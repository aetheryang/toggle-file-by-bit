using namespace std;

QStringList MainWindow::showfile(QString path) {
  QDir dir(path);
  dir.setFilter( QDir::Files | QDir::Hidden | QDir::NoSymLinks );
  dir.setSorting( QDir::Name | QDir::Reversed );
  QStringList list = dir.entryList();
  return list;
}

void MainWindow::choose_mode(QString filename) {
  QString dot_t = ".t";
  if(filename.lastIndexOf(dot_t) == 1)
    toggle_back(filename);
  else
    if(c_4gb->isChecked())
      toggle_4gb(filename);
    else
      toggle_transfer(filename);
  return;
}
void MainWindow::toggle(QString filename)
{
    char readbuff[1024];
    int burst_len = 1024;
    qint64 file_size, i, loc = 0,stream_len = 1;
    QFile qfile(filename);
    if(!qfile.open( QIODevice::ReadWrite)) {
      ERRORLIST << filename + " open failed";
      return;
    }
    file_size = qfile.size();
    while(stream_len) {
      stream_len = qfile.read( readbuff, burst_len);
      qfile.seek(loc);
      i = stream_len;
      while(i) { readbuff[--i] ^= 0xff;}
      loc += qfile.write( readbuff, stream_len);
      qfile.seek(loc);
      progress->setValue ((loc)*100.0/file_size);
    }
    qfile.close();
}
void MainWindow::toggle_transfer(QString filename)
{
  char readbuff[1024];
  int burst_len = 1024;
  qint64 file_size, i, loc = 0,stream_len = 1;
  QFile qin(filename);
  if(!qin.open( QIODevice::ReadOnly)) {
    ERRORLIST << filename + " open failed";
    return;
  }
  if(c_suffix->isChecked())
    filename.append(".t0");
  QFile qout(output + filename);
  if(!qout.open( QIODevice::WriteOnly)) {
    ERRORLIST << filename + " open failed";
    return;
  }
  file_size = qin.size();
  cout<< "ok" << endl;
  do {
    stream_len = qin.read( readbuff, burst_len);
    i = stream_len;
    while(i) { readbuff[--i] ^= 0xff;}
    loc += qout.write( readbuff, stream_len);
    progress->setValue ((loc)*100.0/file_size);
  } while(stream_len);
  qin.close();
  qout.close();
}

void MainWindow::toggle_4gb(QString filename)
{
  QString suffix[16] = { ".t0", ".t1", ".t2", ".t3", ".t4", ".t5", ".t6", ".t7"\
                         ".t8", ".t9", ".ta", ".tb", ".tc", ".td", ".te", ".tf"};
  char readbuff[1024];
  int burst_len = 1024;
  qint64 file_size, file_num, i, loc = 0,stream_len = 1;
  QFile qin(filename);
  if(!qin.open( QIODevice::ReadOnly)) {
    ERRORLIST << filename + " open failed";
    return;
  }
  file_size = qin.size();
  for( file_num = 0; file_num < 16; file_num ++) {
    QString file_out = output + filename + suffix[file_num];
    QFile qout(file_out);
    if(!qout.open( QIODevice::WriteOnly)) {
      ERRORLIST << filename + " open failed";
      return;
    }
    for(; stream_len;) {
      if(file_num != 15 && loc > 4000000000*(file_num+1))
        break;
      stream_len = qin.read( readbuff, burst_len);
      i = stream_len;
      while(i) { readbuff[--i] ^= 0xff;}
      loc += qout.write( readbuff, stream_len);
      progress->setValue ((loc)*100.0/file_size);
    }
    qout.close();
    if(!stream_len)
      break;
  }
  qin.close();
}

void MainWindow::toggle_back(QString filename)
{
  QString suffix[16] = { ".t0", ".t1", ".t2", ".t3", ".t4", ".t5", ".t6", ".t7"\
                         ".t8", ".t9", ".ta", ".tb", ".tc", ".td", ".te", ".tf"};
  char readbuff[1024];
  int burst_len = 1024;
  qint64 file_size = 0, file_num, i, loc = 0,stream_len = 1;
  QFile qout(output + filename.remove(-3, 3));
  if(!qout.open( QIODevice::WriteOnly)) {
    ERRORLIST << filename + " open failed";
    return;
  }
  for( file_num = 0; file_num < 16; file_num ++) {
    QFile qin(filename + suffix[file_num]);
    if(!qin.open( QIODevice::ReadOnly)) {
      ERRORLIST << filename + " open failed";
      qout.close();
      return;
    }
    file_size += qin.size();
    for(; stream_len;) {
      stream_len = qin.read( readbuff, burst_len);
      i = stream_len;
      while(i) { readbuff[--i] ^= 0xff;}
      loc += qout.write( readbuff, stream_len);
      progress->setValue ((loc)*100.0/file_size);
    }
    qin.close();
  }
  qout.close();
}
