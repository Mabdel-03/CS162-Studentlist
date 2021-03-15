/*
This program was written by Mahmoud Abdelmoneum on 3/14/2021
This program was written to be a Student List program
This Student List program allows for the storage of student names, IDs, and GPAs
It allows for the addition of students, as well as the deletion of students
It also allows the viewer to output all of the students
 */

#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>

using namespace std;

struct student {
  char first[30];
  char last[30];
  int studentID;
  float GPA;
};

void addStudent(vector<student> *vptr);
void deleteStudent(vector<student> *vptr, int studentID);
void printStudent(vector<student> *vptr);
bool isNew(vector<student> *vptr, int id);
bool isLegal(char*command);
void quit();

bool isNew(vector<student> *vptr, int id) {
  //checks to see if the student entered is new or not
  for(vector<student>::iterator index = vptr->begin(); index != vptr->end(); ++index) {
    if(index->studentID == id) {
      return false;
    }
  }
  return true; 
}

//function to add a new student
void addStudent(vector<student> *vptr) {

  student *Student = new student;
  char first[30];
  char last[30];
  int id = 0;
  float gpa = 0.00;

  //input first name
  cout << "Enter the student's FIRST name: " << endl;
  cin.get(first, 30);
  cin.get();
  strcpy(Student->first, first);

  //input last name
  cout << "Enter the student's LAST name: " << endl;
  cin.get(last, 30);
  cin.get();
  strcpy(Student->last, last);

  //input Student ID
  cout << "Enter the student's student ID: " << endl;
  cin >> id;
  cin.get();
  bool unique = isNew(vptr, id);
  if(unique == true) {
    Student->studentID = id;
  }
  else { //error, invalid input
    cout << "Student ID Already Exists... Try Again" << endl;
    delete Student;
    return;
  }

  //input GPA
  cout << "Enter student's GPA: " << endl;
  cin >> gpa;
  cin.get();
  Student->GPA = gpa;

  //add Student to vector point
  vptr->push_back(*Student);

  return;

}

//function to print the student struct (all student info outputted)
void printStudent(vector<student> *vptr) {
  //set GPA precision to 2 decimal points
  cout << fixed;
  cout << setprecision(2);

  //iterator
  for(vector<student>::iterator index = vptr->begin(); index != vptr->end(); ++index) {

    cout << "\n" << index->first << " " << index->last << ", " << index->studentID << ", " << index->GPA << endl;

  }

  return;

}

//delete a student that already exists
void deleteStudent(vector <student> *vptr, int studentID) {

  for(vector<student>::iterator index = vptr->begin(); index != vptr->end(); ++index) {

    if(index->studentID == studentID) {
      vptr->erase(index);
      return;
    }

  }
  return;

}

//quit program function
void quit() {

  cout << "Thank you for using the Studentlist program! Goodbye!" << endl;
  return;
  
}

//check if the command given is one of the 4 legal commands
bool isLegal(char*command) {

  //compares the string to the legal commands
  if(strcmp(command, "ADD") == 0) {
    return true;
  }
  if(strcmp(command, "DELETE") == 0) {
    return true;
  }
  if(strcmp(command, "QUIT") == 0) {
    return true;
  }
  if(strcmp(command, "PRINT") == 0) {
    return true;
  }

  return false;
  
}


int main() {

  //make the vectors
  vector<student> structVtr; //struct vector
  vector<student> *vptr = &structVtr; //pointer to struct vector

  char command[7];

  cout << "Welcome to the Studentlist program!" << endl;
  cout << "To add a student, type ADD. To delete a student, type DELETE." << endl;
  cout << "To print an existing student, type PRINT. To quit, type QUIT." << endl;
  int idnum = 0; //variable for student ID

  while(strcmp(command, "QUIT") != 0) {

    //user input
    cout << "Please enter a command" << endl;
    cin.get(command, 7);
    cin.get();
    //convert all letter to uppercase
    for(int i = 0; i < strlen(command); i++) {
      command[i] = toupper(command[i]);
    }

    //check legality of input
    bool legal = isLegal(command);
    if(legal == true) {

      if(strcmp(command, "ADD") == 0) { //ADD
	addStudent(vptr); 
      }
      else if(strcmp(command, "PRINT") == 0) { //PRINT
	printStudent(vptr);
      }
      else if(strcmp(command, "DELETE") == 0) { //DELETE
	cout << "Enter ID number of the desired student to delete" << endl;
	cin >> idnum;
	cin.get();
	deleteStudent(vptr, idnum);
      }
    }
  }
  //end program
  quit();
  return 0;

}
