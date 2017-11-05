#ifndef ALUMNO_H
#define ALUMNO_H

#include <QListWidgetItem>
#include <iostream>
 typedef enum mode{NAME_SURNAME,TAGS,COMPANY} MODE;

class Alumno
{
public:
    Alumno(std::string name,std::string surname,std::string idNumber,std::string company,std::string title,std::string tags,std::string path);
    ~Alumno();
    void setDataToShow(MODE sohwData);
     QListWidgetItem * dataToShow;
     std::string path;
     std::string tags;
     std::string company;
     std::string title;
private:

    std::string name;
    std::string surname;
    std::string idNumber;




};


#endif // ALUMNO_H
