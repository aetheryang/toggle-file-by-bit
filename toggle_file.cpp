
void MainWindow::toggle_burst(QString filename)
{
    char readbyte,readbuff[1024];
    int burst_len = 1024;
    qint64 file_size, i, loc = 0,stream_len = 1;
    QFile qfile(filename);
    qfile.open( QIODevice::ReadWrite);
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
