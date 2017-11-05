#include "mainwindow.h"
#include <QApplication>
#include "alumno.h"
#include <QListWidgetItem>
#include "csv.h"
int main(int argc, char *argv[])
{
//  if (argc!=2)
//    {
//      printf("falta path");
//      return 1;
//    }
  std::string ruta("C:/Users/Sony/Documents/practicas_laborales");
//  std::string ruta(argv[1]);
  io::CSVReader<7> in((ruta+"/db.csv").c_str());
  io::LineReader lr((ruta+"/tags.txt").c_str());
  in.read_header(io::ignore_extra_column,"Legajo","Apellido","Nombre","Empresa","Titulo","TAGS","Nombre archivo");
  std::string completePath=ruta+"/PDF/";
  std::string legajo;
  std::string apellido;
  std::string nombre;
  std::string tags;
  std::string empresa;
  std::string path;
  std::string title;


  QApplication a(argc, argv);
  MainWindow w;
  std::vector<std::string>::iterator startStrinList;
  std::vector<std::string>::iterator endStringList;

  while(in.read_row(legajo,apellido,nombre,empresa,title,tags,path))//cargo todo lo que contiene el csv
    {
      w.myList.push_back(new Alumno(nombre,apellido,legajo,empresa,title,tags,completePath+path));
      std::cout<<completePath+path<<std::endl;
      if(w.empresas.empty())
        {
          w.empresas.push_back(empresa);
        }
      else
        {
          startStrinList=w.empresas.begin();
          endStringList=w.empresas.end();
          for(startStrinList;startStrinList!=endStringList;startStrinList++)//me fijo si la empresa ya estava abregada
            {
              if((*startStrinList)==empresa)
                {
                  break;
                }

            }
          if(startStrinList==endStringList)//como no pertenece a la lista lo agrego
            {
              w.empresas.push_back(empresa);
            }
          
        }
      
    }

  startStrinList=w.empresas.begin();
  endStringList=w.empresas.end();
  for(startStrinList;startStrinList!=endStringList;startStrinList++)//me fijo si la empresa ya estava abregada
    {

      std::cout<<(*startStrinList)<<std::endl;

    }
  std::string loadToTagList;
  char * lineRead=NULL;
  while((lineRead=lr.next_line())!=NULL)
    {
      loadToTagList=lineRead;
      w.tagList.push_back(loadToTagList);
    }


  w.show();

  return a.exec();
}
