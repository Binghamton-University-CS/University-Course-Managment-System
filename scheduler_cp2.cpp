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
  int num_courses;
  Course **courses = nullptr;
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

bool isValidCRN(int crn) { return (crn >= 100000 && crn <= 999999); }

int findStudentIndex(Student *students, int numStudents, string bNumber) {
  for (int i = 0; i < numStudents; i++) {
    if (students[i].bNumber == bNumber) {
      return i;
    }
  }
  return -1;
}

int findCourseIndex(Course *courses, int num_courses, int crn) {
  for (int i = 0; i < num_courses; i++) {
    if (courses[i].crn == crn) {
      return i;
    }
  }
  return -1;
}

void add(Student *students, int numStudents, Course *courses, int num_courses,
         string bNumber, int crn) {

  int courseIndex = findCourseIndex(courses, num_courses, crn);
  if (courseIndex == -1) {
    cout << "Fail: course " << crn << " not found" << endl;
    return;
  }
  // Find the student
  int studentIndex = findStudentIndex(students, numStudents, bNumber);
  if (studentIndex == -1) {
    cout << "Fail: student " << bNumber << " not found" << endl;
    return;
  }

  // Find the course

  // Check if the student is already enrolled in the course
  for (int i = 0; i < students[studentIndex].num_courses; i++) {
    if (students[studentIndex].courses[i]->crn == crn) {
      cout << "Fail: student " << bNumber << " is already enrolled in course "
           << crn << endl;
      return;
    }
  }

  // Create a new array of course pointers with space for one more course
  Course **newCourseList = new Course *[students[studentIndex].num_courses + 1];

  // Copy over the old course pointers
  for (int i = 0; i < students[studentIndex].num_courses; i++) {
    newCourseList[i] = students[studentIndex].courses[i];
  }

  // Add the new course pointer to the end of the array
  newCourseList[students[studentIndex].num_courses] = &courses[courseIndex];

  // Deallocate the old course pointer array
  delete[] students[studentIndex].courses;

  // Update the student's course pointer array to point to the new array
  students[studentIndex].courses = newCourseList;

  // Increment the student's number of courses
  students[studentIndex].num_courses++;

  cout << "Success: added course " << crn << " for student " << bNumber << endl;
  return;
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

      for (int i = 0; i < num_courses; i++) {
        if (courses[i].crn == crn) {
          cout << "Fail: cannot build course" << name << "(CRN:" << crn
               << "): CRN exists" << endl;
          continue;
        }
      }
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
  Course newCourse = {crn,department,number,name};
  Course *newCourses = new Course[num_courses + 1];
  for (int i = 0; i < num_courses; i++) {
    newCourses[i] = courses[i];
  }
  newCourses[num_courses] = newCourse;
  num_courses++;
  delete[] courses;
  courses = newCourses;
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
      int crn;
      string bNumber;
      cin >> crn >> bNumber;
      add(students, numStudents, courses, num_courses, bNumber, crn);

    }

    else if (command == "drop") {

    }

    else if (command == "roster") {

    }

    else if (command == "schedule") {

    } else if (command == "quit") {

      break;
    }

    else {

      cout << "Input Error: command not recognized, please try again." << endl;
    }
  }

  delete[] courses;
  delete[] students;
  return 0;
}

/*#include <iostream>
using namespace std;

class CourseInfo {
        private:
                string crn;
                string department;
                int number;
                string name;
                // No roster
};

class StudentInfo {
        private:
                string bnumber;
                string first, last;
                // No  schedule
};

class CourseInfoList {
        private:
                CourseInfo *infoList;
                int num_courses;
                int capacity;
};

class StudentInfoList {
        private:
                StudentInfo *infoList;
                int num_students;
                int capacity;
};

class Course {
        private:
                CourseInfo info;
                StudentInfoList roster;
};

class Student {
        private:
                StudentInfo student;
                CourseInfoList schedule;

};

class CourseList {
        private:
                Course *courses;
                int num_courses;
                int capacity;
};

class StudentList {
        private:
                Student *students;
                int num_students;
                int capacity;
};

int main() {
        StudentList all_students;
        CourseList all_courses;
}
*/
