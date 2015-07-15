using namespace std;

QStringList MainWindow::showfile(QString path) {
  QDir dir(path);
  dir.setFilter( QDir::Files | QDir::Hidden | QDir::NoSymLinks );
  dir.setSorting( QDir::Name | QDir::Reversed );
  QStringList list = dir.entryList();
  return list;
}

QString MainWindow::set_suffix(QString filename) {
  QString suffix[16] = { ".t0", ".t1", ".t2", ".t3", ".t4", ".t5", ".t6", ".t7"\
                         ".t8", ".t9", ".ta", ".tb", ".tc", ".td", ".te", ".tf"};
  QString dot_t = ".t";
  if(filename.lastIndexOf(dot_t) == 1)
    filename.remove( -3, 3);
  else
    filename.append( ".t0");
  return filename;
}
void MainWindow::toggle_burst(QString filename)
{
    toggle_4gb(filename);
    return;
    char readbyte,readbuff[1024];
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
void MainWindow::toggle_out(QString filename)
{
  char readbyte,readbuff[1024];
  int burst_len = 1024;
  qint64 file_size, i, loc = 0,stream_len = 1;
  QFile qin(filename);
  if(!qin.open( QIODevice::ReadOnly)) {
    ERRORLIST << filename + " open failed";
    return;
  }
  QFile qout(output + filename);
  if(!qout.open( QIODevice::WriteOnly)) {
    ERRORLIST << filename + " open failed";
    return;
  }
  file_size = qin.size();
  cout<< "ok" << endl;
  cout << set_suffix(filename).toStdString() << endl;
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
    QFile qout(output + filename + suffix[file_num]);
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
