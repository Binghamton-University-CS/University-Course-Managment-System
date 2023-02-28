#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Course {
  int crn;
  string department;
  int number;
  string name;

};

struct Student {
  string bNumber;
  string userID;
  string firstName;
  string lastName;
};

bool isValidBNumber(string str) {
  if (str.length() != 9 || str[0] != 'B') {
    return false;
  }
  for (int i = 1; i < 9; i++) {
    if (!isdigit(str[i])) {
      return false;
    }
  }
  return true;
}

bool isValidUserID(string str) {
  if (str.empty() || !isalpha(str[0])) {
    return false;
  }
  for (char c : str) {
    if (!isalnum(c)) {
      return false;
    }
  }
  return true;
}

void enroll(Student *&students, int &numStudents, string bNumber, string userID,
            string firstName, string lastName) {

  if (bNumber.empty() || userID.empty() || firstName.empty() ||
      lastName.empty()) {
    cout << "Input Error: too few arguments" << endl;
    return;
  }
  // Check if the B Number already exists
  for (int i = 0; i < numStudents; i++) {
    if (students[i].bNumber == bNumber) {
      cout << "Fail: cannot enroll student, B Number exists" << endl;
      return;
    }
  }

  // Check if the input arguments are valid
  if (!isValidBNumber(bNumber) || !isValidUserID(userID) || firstName.empty() ||
      lastName.empty()) {
    cout << "Input Error: invalid arguments" << endl;
    return;
  }

  // Create a new student and add it to the dynamic array
  Student newStudent = {bNumber, userID, firstName, lastName};
  Student *newStudents = new Student[numStudents + 1];
  for (int i = 0; i < numStudents; i++) {
    newStudents[i] = students[i];
  }
  newStudents[numStudents] = newStudent;
  numStudents++;
  delete[] students;
  students = newStudents;
  cout << "Success: enrolled student " << newStudent.bNumber << " ("
       << newStudent.userID << ") " << newStudent.lastName << ", "
       << newStudent.firstName << endl;
}

bool isValidCRN(int crn) {
  return (crn >= 100000 && crn <= 999999);
}

int findStudentIndex(Student *students, int numStudents, string bNumber) {
  for (int i = 0; i < numStudents; i++) {
    if (students[i].bNumber == bNumber) {
      return i;
    }
  }
  return -1;
}

int findCourseIndex(Course *courses, int numCourses, int crn) {
  for (int i = 0; i < numCourses; i++) {
    if (courses[i].crn == crn) {
      return i;
    }
  }
  return -1;
}








void showPrompt() {
  cout << "Enter [\"build <crn> <department> <number> <name>\"" << endl
       << "       \"cancel <crn>\"" << endl
       << "       \"enroll <bnumber> <userid> <first> <last>\"" << endl
       << "       \"add <bnumber> <crn>\"" << endl
       << "       \"drop <bnumber> <crn>\"" << endl
       << "       \"roster <crn>\"" << endl
       << "       \"schedule <bnumber>\"" << endl
       << "       \"quit\"]" << endl
       << ": ";
}

int main() {
  Course *courses = nullptr;
  Student *students = nullptr;
  int numStudents = 0;
  int num_courses = 0;
  int max_courses = 0;

  showPrompt();

  while (true) {
    string command;
    cin >> command;

    if (command == "build") {
      int crn;
      string department;
      int number;
      string name;

      cin >> crn >> department >> number;
      getline(cin, name);

      // Make sure CRN is 6 digits
      if (crn < 100000 || crn > 999999) {
        cout << "Invalid CRN" << endl;
        continue;
      }

      // Make sure department is 2-4 characters
      if (department.length() < 2 || department.length() > 4) {
        cout << "Invalid department code" << endl;
        continue;
      }

      // Make sure number is between 100 and 700
      if (number < 100 || number > 700) {
        cout << "Invalid course number" << endl;
        continue;
      }

      // Add course to array
      if (num_courses == max_courses) {
        max_courses = max(max_courses * 2, 1);
        Course *new_courses = new Course[max_courses];
        for (int i = 0; i < num_courses; i++) {
          new_courses[i] = courses[i];
        }
        delete[] courses;
        courses = new_courses;
      }

      courses[num_courses].crn = crn;
      courses[num_courses].department = department;
      courses[num_courses].number = number;
      courses[num_courses].name = name;
      num_courses++;
      cout << "Success: built course " << department << number
           << " (CRN: " << crn << ")" << endl;
    }

    else if (command == "cancel") {
      int crn;
      cin >> crn;

      // Make sure CRN is 6 digits
      if (crn < 100000 || crn > 999999) {
        cout << "Input Error: illegal CRN" << endl;
        continue;
      }

      // Search for course with given CRN
      bool found = false;
      for (int i = 0; i < num_courses; i++) {
        if (courses[i].crn == crn) {
          // Shift courses after the removed course down in the array
          for (int j = i; j < num_courses - 1; j++) {
            courses[j] = courses[j + 1];
          }
          num_courses--;
          found = true;
          break;
        }
      }

      if (found) {
        cout << "Success: cancelled course " << crn << endl;
      } else {
        cout << "Fail: cannot cancel course, CRN does not exist" << endl;
      }

    } else if (command == "enroll") {
      string bNumber, userID, firstName, lastName;
      cin >> bNumber >> userID >> firstName >> lastName;
      enroll(students, numStudents, bNumber, userID, firstName, lastName);

    }

    else if (command == "add") {


      }

    
    else if(command == "drop"){

      
      
    }

    else if(command == "roster"){

      
    }

    else if(command == "schedule"){


      
    }
       else if (command == "quit") {

      break;
    }

    else {

      cout << "Input Error: command not recognized, please try again." << endl;
      continue;
    }
  }

  delete[] courses;
  delete[] students;
  return 0;
}
