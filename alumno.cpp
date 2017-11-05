#include "alumno.h"

Alumno::Alumno(std::string name,std::string surname,std::string idNumber,std::string company,std::string title,std::string tags,std::string path)
{
    dataToShow=NULL;
    this->name=name;
    this->surname=surname;
    this->idNumber=idNumber;
    this->company=company;
    this->tags=tags;
    this->path=path;
    this->title=title;
}

Alumno::~Alumno()
{

}

void Alumno:: setDataToShow(MODE sohwData)
{
  std::string temp("HOLA");


   // delete dataToShow;


    switch (sohwData) {
    case NAME_SURNAME:
        temp =this->idNumber+" "+this->surname+" "+this->name;
        break;
    case TAGS:
        temp=this->idNumber+" "+this->tags;
        break;
    case COMPANY:
        temp=this->title+" ("+this->surname+")";
        break;
    default:
        break;
    }

    this->dataToShow=new QListWidgetItem(temp.c_str());

}
