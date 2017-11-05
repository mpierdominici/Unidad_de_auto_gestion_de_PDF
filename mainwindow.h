#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<vector>
#include <iterator>
#include <QMainWindow>
#include "alumno.h"
#include <QListWidgetItem>

enum{NO_TAG,TAG_SHOW,TAG_SHOW_PEOPLE,EMPRESAS_SELECT};


namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  std::vector<Alumno *> myList;
  std::vector<std::string>tagList;
  std::vector<std::string>empresas;
  std::vector<std::string>serchTag;

private slots:

  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_3_clicked();

  void on_listWidget_clicked(const QModelIndex &index);

  void on_pushButton_4_clicked();

private:
  int selectItems;
  int state;
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
