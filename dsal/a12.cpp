//============================================================================
// Name        : a12_sequentialFileHandling.cpp
// Author      : 21132 Shreyash Halge
// Date        : 16 May 2022
// Copyright   : Your copyright notice
// Description : Department maintains a student information. The file contains roll number, name, division and address. Allow user to add, delete information of student. Display information of particular employee. If record of student does not exist an appropriate message is displayed. If it is, then the system displays the student details. Use sequential file to main the data.
//============================================================================

#include <iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
using namespace std;
const int MAX=20;
class Student
{
 int rollno;
 char name[20],city[20];

public:
 Student()
{
  strcpy(name,"");
  strcpy(city,"");
  rollno=0;
}
 Student(int rollno,char name[MAX], char city[MAX])
 {
  strcpy(this->name,name);
  strcpy(this->city,city);
  this->rollno=rollno;
 }
 int getRollNo()
 {
  return rollno;
 }
 void displayRecord()
 {

  cout<<endl<<setw(5)<<rollno<<setw(20)<<name<<setw(5)<<setw(5)<<setw(20)<<city;
 }
};
//==========File Operations ===========
class FileOperations
{
 fstream file;
public:
 FileOperations(char* filename)
{
file.open(filename,ios::in|ios::out|ios::ate|ios::binary);
}
 void insertRecord(int rollno, char name[MAX],char city[MAX])
 {
  Student s1(rollno,name,city);
  file.seekp(0,ios::end);
  file.write((char *)&s1,sizeof(Student));
  file.clear();
 }
 void displayAll()
 {
  Student s1;
  file.seekg(0,ios::beg);
  while(file.read((char *)&s1, sizeof(Student)))
  {
   s1.displayRecord();
  }
  file.clear();
 }
 void displayRecord(int rollNo)
 {
  Student s1;
  file.seekg(0,ios::beg);
  bool flag=false;
  while(file.read((char*)&s1,sizeof(Student)))
  {
   if(s1.getRollNo()==rollNo)
   {
    s1.displayRecord();
    flag=true;
    break;
   }
  }
  if(flag==false)
  {
   cout<<"\nRecord of "<<rollNo<<"is not present.";
  }
  file.clear();
 }
 void deleteRecord(int rollno)
 {
  ofstream outFile("new.dat",ios::binary);
  file.seekg(0,ios::beg);
  bool flag=false;
  Student s1;

  while(file.read((char *)&s1, sizeof(Student)))
  {
   if(s1.getRollNo()==rollno)
   {
    flag=true;
    continue;
   }
   outFile.write((char *)&s1, sizeof(Student));
  }
  if(!flag)
  {
   cout<<"\nRecord of "<<rollno<<" is not present.";
  }
  file.close();
  outFile.close();
  remove("student.dat");
  rename("new.dat","student.dat");
  file.open("student.dat",ios::in|ios::out|ios::ate|ios::binary);
 }
 ~FileOperations()
 {
  file.close();
  cout<<"\nFile Closed.";
 }
};
int main() {
 ofstream newFile("student.dat",ios::app|ios::binary);
  newFile.close();
  FileOperations file((char*)"student.dat");
     int rollNo,year,choice=0;
     char div;
     char name[MAX],address[MAX];
     while(choice!=5)
     {
         //clrscr();
         cout<<"\n\n------Student Database-----\n";
         cout<<"1) Add New Student\n";
         cout<<"2) Display All Students\n";
         cout<<"3) Search\n";
         cout<<"4) Delete\n";
         cout<<"5) Exit\n";
         cout<<"Choose your choice : ";
         cin>>choice;
         switch(choice)
         {
             case 1 : //New Record
               cout<<endl<<"Enter RollNo and name : \n";
               cin>>rollNo>>name;
               cout<<"Enter City : \n";
               cin.ignore();
               cin.getline(address,20);
               file.insertRecord(rollNo,name,address);
               cout<<"\nRecord Inserted.";
               break;
             case 2 :
              cout<<endl<<setw(5)<<"ROLL"<<setw(20)<<"NAME"<<setw(5)<<"CITY";
               file.displayAll();
               break;
             case 3 :
               cout<<"Enter Roll number to search: ";
               cin>>rollNo;
                file.displayRecord(rollNo);

               break;
             case 4:
               cout<<"Enter roll no you want to delete:";
               cin>>rollNo;
               file.deleteRecord(rollNo);
               break;
            case 5 :break;
         }

     }

 return 0;
}

/*

------Student Database-----
1) Add New Student
2) Display All Students
3) Search
4) Delete
5) Exit
Choose your choice : 1

Enter RollNo and name : 
21132 Shreyash
Enter City : 
Pune

Record Inserted.

------Student Database-----
1) Add New Student
2) Display All Students
3) Search
4) Delete
5) Exit
Choose your choice : 1

Enter RollNo and name :
21111 Aditya
Enter City : 
Mumbai

Record Inserted.

------Student Database-----
1) Add New Student
2) Display All Students
3) Search
4) Delete
5) Exit
Choose your choice : 2

 ROLL                NAME CITY
21132            Shreyash                Pune
21111              Aditya              Mumbai

------Student Database-----
1) Add New Student
2) Display All Students
3) Search
4) Delete
5) Exit
Choose your choice : 3
Enter Roll number to search: 21132

21132            Shreyash                Pune

------Student Database-----
1) Add New Student
2) Display All Students
3) Search
4) Delete
5) Exit
Choose your choice : 4
Enter roll no you want to delete:21111


------Student Database-----
1) Add New Student
2) Display All Students
3) Search
4) Delete
5) Exit
Choose your choice : 2

 ROLL                NAME CITY
21132            Shreyash                Pune

------Student Database-----
1) Add New Student
2) Display All Students
3) Search
4) Delete
5) Exit
Choose your choice : 5

File Closed.
*/
