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
  
  void build(Course *&courses,int num_courses,int crn,string department, int number,string name ){  
     
  
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

void drop(Student *students, int numStudents, string bNumber, int crn) {
   
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
  
         string crn_string;
      string number_string;
      stringstream ss1;
      stringstream ss2;
      ss1<<crn;
      ss1>>crn_string;
      ss2<<number;
      ss2>>number_string;
  
  
        if (crn_string.empty() || department.empty() || number_string.empty() ||
        name.empty()) {
      cout << "Input Error: too few arguments" << endl;
      continue;
    }
    
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
        string bNumber, crn;
      cin >> bNumber >> crn;
      
      // Check if the bNumber is valid
      if (bNumber.length() != 9 || bNumber[0] != 'B') {
          cout << "Fail: invalid bNumber" << endl;
          continue;
      }
      
      // Check if the crn is valid
      if (crn.length() != 6) {
          cout << "Fail: invalid CRN" << endl;
          continue;
      }
      
      // Check if the student is already enrolled in the course
      for (int i = 0; i < numStudents; i++) {
          if (students[i].bNumber == bNumber) {
              for (int j = 0; j < students[i].num_courses; j++) {
                  if (students[i].courses[j]->crn == stoi(crn)) {
                      cout << "Fail: cannot add, student " << bNumber << " already enrolled in course " << crn << endl;
                      continue;
                  }
              }
          }
      }
      
      
      // Find the course with the matching CRN
      //Course* course = nullptr;
      for (int i = 0; i < num_courses; i++) {
          if (courses[i].crn == stoi(crn)) {
              courses = &courses[i];
              
          }
      }
      if (courses == nullptr) {
          cout << "Fail: course not found" << endl;
          continue;
      }
      
      // Add the course to the student's course list
      Course** new_courses = new Course*[students->num_courses + 1];
      for (int i = 0; i < students->num_courses; i++) {
          new_courses[i] = students->courses[i];
      }
      new_courses[students->num_courses] = courses;
      delete[] students->courses;
      students->courses = new_courses;
      students->num_courses++;
      
      cout << "Success: added student " << bNumber << " into course " << crn << endl;
  
      }
  
      else if (command == "drop") {
        string bNumber;
        int crn;
        cin>>bNumber>>crn;
        
         int studentIndex = findStudentIndex(students, numStudents, bNumber);
    if (studentIndex == -1) {
        cout << "Fail: student " << bNumber << " not found" << endl;
        continue;;
    }
    int courseIndex = findCourseIndex(courses,num_courses, crn);
    if (courseIndex == -1) {
        cout << "Fail: course " << crn << " not found for student " << bNumber << endl;
        continue;
    }
    Course **newCourses = new Course *[students[studentIndex].num_courses - 1];
    int j = 0;
    for (int i = 0; i < students[studentIndex].num_courses; i++) {
        if (students[studentIndex].courses[i]->crn != crn) {
            newCourses[j++] = students[studentIndex].courses[i];
        }
    }
    students[studentIndex].num_courses--;
    delete[] students[studentIndex].courses;
    students[studentIndex].courses = newCourses;
    cout << "Success: course " << crn << " dropped for student " << bNumber << endl;
  
      }
  
      else if (command == "roster") {
  
      }
  
      else if (command == "schedule") {
  
      } else if (command == "quit") {
  
        break;
      }
  
      else {
  
        cout << "Input Error: command not recognized, please try again." << endl;
        continue;
      }
    }
  
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
