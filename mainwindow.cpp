#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <iostream>
#include <Windows.h>
#include <string>

#define MAX_SELECTED_ITEMS 3



MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  selectItems=0;
  state=NO_TAG;
  ui->setupUi(this);
  ui->pushButton_4->setHidden(true);
  ui->label_3->show();

 }

MainWindow::~MainWindow()
{
  delete ui;
}
void MainWindow::on_pushButton_clicked()
{
  state=NO_TAG;
  Alumno * temp=NULL;
  ui->pushButton_4->setHidden(true);//apago el boton buscar
  ui->listWidget->clear();//hace el destroy de cada elemento
  std::vector<Alumno *>::iterator startList= myList.begin();
  std::vector<Alumno *>::iterator endList= myList.end();

  for(startList;startList!=endList;startList++)
    {
    temp=(*startList);
    temp->setDataToShow(NAME_SURNAME);
    ui->listWidget->addItem(temp->dataToShow);
    }

}
void open_file_windows(const char* mypath);

void MainWindow::on_pushButton_2_clicked()//tag Button
{
  selectItems=0;
  ui->pushButton_4->setHidden(true);//apago el boton buscar
  std::string temp;
  state =TAG_SHOW;
  ui->listWidget->clear();//hace el destroy de cada elemento
  std::vector<std::string>::iterator startList =tagList.begin();
  std::vector<std::string>::iterator endList =tagList.end();

  for(startList;startList!=endList;startList++)
    {
      temp=(*startList);
      ui->listWidget->addItem(temp.c_str());
    }


}

void MainWindow::on_pushButton_3_clicked()//empresa
{
  state=NO_TAG;
 // Alumno * temp=NULL;
  ui->pushButton_4->setHidden(true);//apago el boton buscar
  ui->listWidget->clear();//hace el destroy de cada elemento
  std::string nombreEmpresa;
  std::vector<std::string>::iterator startStrinList=empresas.begin();
  std::vector<std::string>::iterator endStringList=empresas.end();
    for(startStrinList;startStrinList!=endStringList;startStrinList++)
      {
        nombreEmpresa=(*startStrinList);

      ui->listWidget->addItem(nombreEmpresa.c_str());
      }
    state=EMPRESAS_SELECT;
//  std::vector<Alumno *>::iterator startList= myList.begin();
//  std::vector<Alumno *>::iterator endList= myList.end();

//  for(startList;startList!=endList;startList++)
//    {
//    temp=(*startList);
//    temp->setDataToShow(COMPANY);
//    ui->listWidget->addItem(temp->dataToShow);
//    }
}

void open_file_windows(const char* mypath) {
	std::string path = mypath;
	std::string code = "start \"\" /max " + path;

	system(code.c_str());
}


void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{

  Alumno * temp=NULL;
  std::vector<Alumno *>::iterator startList= myList.begin();
  std::vector<Alumno *>::iterator endList= myList.end();
  std::vector<std::string>::iterator startTagListSelected=serchTag.begin();
  std::vector<std::string>::iterator endTagListSelected=serchTag.end();
  QListWidgetItem * tempPointer =NULL;
  std::string TagToFind;
  std::string empresaSelccionada;
  switch(state)
    {
      case TAG_SHOW:

      tempPointer=ui->listWidget->currentItem();
      if(tempPointer->background().color()==Qt::blue)
        {
          selectItems--;
          tempPointer->setSelected(false);
          tempPointer->setBackgroundColor(Qt::white);
          //borrar todo y despues recargarlo

          std::string tempString;
           for(startTagListSelected;startTagListSelected!=endTagListSelected;startTagListSelected++)
             {
               tempString= *startTagListSelected;
               if((tempString.find(tempPointer->text().toStdString()))!=std::string::npos)
                 {
                   serchTag.erase(startTagListSelected);
                   break;

                 }

             }
        }
      else if(selectItems<MAX_SELECTED_ITEMS)
        {
          selectItems++;
          tempPointer->setSelected(true);
          tempPointer->setBackgroundColor(Qt::blue);
          //push to list
          serchTag.push_back(tempPointer->text().toStdString());//agrego los elementos a la lista
        }
      if(selectItems)
        {
          ui->pushButton_4->setHidden(false);
        }
      else
        {
          ui->pushButton_4->setHidden(true);
        }




      break;
    case EMPRESAS_SELECT:
      startList=myList.begin();
      endList=myList.end();
      empresaSelccionada=(((ui->listWidget->currentItem())->text().toStdString()));
      ui->listWidget->clear();
      for(startList;(startList!=endList);startList++)
        {
          temp=(*startList);
          temp->setDataToShow(COMPANY);
          if(empresaSelccionada==(temp->company))
            {
              temp->setDataToShow(COMPANY);
              ui->listWidget->addItem(temp->dataToShow);
            }

        }


      state=NO_TAG;
      break;


    case NO_TAG:

      startList= myList.begin();

      endList= myList.end();
      ui->listWidget->currentItem()->setSelected(true);
      for(startList;(startList!=endList);startList++)
        {
        temp=(*startList);
        if(temp->dataToShow->isSelected())
          {
            std::cout<<temp->path<<std::endl;
            open_file_windows(temp->path.c_str());
            break;
          }

        }
      ui->listWidget->currentItem()->setSelected(false);
      break;

    }//end switch case

    }//end lista widget



void MainWindow::on_pushButton_4_clicked()//boton buscar
{
  state=NO_TAG;
  ui->pushButton_4->setHidden(true);
  Alumno * temp=NULL;
  std::vector<Alumno *>::iterator startList= myList.begin();
  std::vector<Alumno *>::iterator endList= myList.end();

  std::string tempString;

  for(startList=myList.begin();(startList!=endList);startList++)//paso todo los elemntos de la lista a selected
    {
    temp=(*startList);
    temp->setDataToShow(NAME_SURNAME);
    temp->dataToShow->setBackgroundColor(Qt::blue);
    }


  while(!serchTag.empty())
    {
      tempString=serchTag.back();
      for(startList=myList.begin();(startList!=endList);startList++)//aplico el criteriode busqueda sobre la lista
        {
          temp=(*startList);

          if((temp->tags.find(tempString))==std::string::npos)//si el tag indicado no esta lo marco en la lista
            {
              temp->dataToShow->setBackgroundColor(Qt::white);

            }

        }
      serchTag.pop_back();
    }


  ui->listWidget->clear();
  for(startList=myList.begin();(startList!=endList);startList++)
    {
      temp=(*startList);
      if(temp->dataToShow->background().color()==Qt::blue)
        {
          temp->dataToShow->setBackgroundColor(Qt::white);
          ui->listWidget->addItem(temp->dataToShow);

        }


    }

}
