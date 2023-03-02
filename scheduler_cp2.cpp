  #include <iostream>
  #include <sstream>
  #include <string>
  #include <vector>
  #include <cstring>

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
  
    
  
  
  bool isValidCRN(int crn) { return (crn >= 100000 && crn <= 999999); }
  
  int findStudent(Student *students, int numStudents, string bNumber) {
    for (int i = 0; i < numStudents; i++) {
      if (students[i].bNumber == bNumber) {
        return i;
      }
    }
    return -1;
  }
  
  int findCourse(Course *courses, int num_courses, int crn) {
    for (int i = 0; i < num_courses; i++) {
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
  
  
    
  
    while (true) {
      showPrompt();
      string command;
      cin >> command;
  
      if (command == "build") {
      int crn;
    string department;
    int number;
    string name;

    cin >> crn >> department >> number;
    getline(cin, name);

    // Check for input errors
    if (!isValidCRN(crn)) {
        cout << "Input Error: illegal CRN" << endl;
        continue;
    }
    if (department.length() < 2 || department.length() > 4 || !isalpha(department[0])) {
        cout << "Input Error: illegal department" << endl;
        continue;
    }
    if (number < 100 || number > 700) {
        cout << "Input Error: illegal course number" << endl;
        continue;
    }

    // Check if CRN already exists
    if (findCourse(courses, num_courses, crn) != -1) {
        cout << "Fail: cannot build course " << name << " (CRN:" << crn << "): CRN exists" << endl;
        continue;
    }
    //add course to array
    Course newCourse = { crn, department, number, name };
    Course* newCourses = new Course[num_courses + 1];
    for(int i =0;i<num_courses;i++){
      newCourses[i] = courses[i];
    }
    newCourses[num_courses] = newCourse;
    num_courses++;

    delete[] courses;
    courses = newCourses;

    cout << "Success: built course " << department <<" " <<number << " (CRN: " << crn << ")" << endl;
        }
  
      else if (command == "cancel") {
        int crn;
        cin >> crn;
  
        if (crn < 100000 || crn > 999999) {
          cout << "Input Error: illegal CRN" << endl;
          continue;
        }
  
        // Search for course  CRN
        bool found = false;
        for (int i = 0; i < num_courses; i++) {
          if (courses[i].crn == crn) {
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
       if (bNumber.empty() || userID.empty() || firstName.empty() ||
        lastName.empty()) {
      cout << "Input Error: too few arguments" << endl;
      continue;
    }
    // Check if the B Number already exists
    for (int i = 0; i < numStudents; i++) {
      if (students[i].bNumber == bNumber) {
        cout << "Fail: cannot enroll student, B Number exists" << endl;
        continue;
      }
    }
  
    
    if (!isValidBNumber(bNumber) || !isValidUserID(userID) || firstName.empty() ||
        lastName.empty()) {
      cout << "Input Error: invalid arguments" << endl;
      continue;
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
  
      else if (command == "add") {
        string bNumber;
        int crn;
      cin >> bNumber >> crn;
      
      if (bNumber.length() != 9 || bNumber[0] != 'B') {
          cout << "Fail: invalid bNumber" << endl;
          continue;
      }
       if (crn < 100000 || crn > 999999) {
          cout << "Input Error: illegal CRN" << endl;
          continue;
        }

      for (int i = 0; i < numStudents; i++) {
          if (students[i].bNumber == bNumber) {
              for (int j = 0; j < students[i].num_courses; j++) {
                  if (students[i].courses[j]->crn == crn) {
                      cout << "Fail: cannot add, student " << bNumber << " already enrolled in course " << crn << endl;
                      continue;
                  }
              }
          }
      }
      
      
      //Course* course = nullptr;
      /*bool crn_exists = false;
  for (int i = 0; i < num_courses; i++) {
    if (courses[i].crn != crn) {
      crn_exists = true;
      cout << "Fail: course not found"<< endl;
      break;
    }
  }
  if (crn_exists) {
    continue;
    }*/
    int studentIndex = findStudent(students, numStudents, bNumber);
  if (studentIndex == -1) {
    cout << "Fail: cannot add, student " << bNumber << " not found" << endl;
    continue;
  }

  // Search for course by crn
  int courseIndex = findCourse(courses, num_courses, crn);
  if (courseIndex == -1) {
    cout << "Fail: cannot add, course " << crn << " not found" << endl;
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
      num_courses++;
      
      cout << "Success: added student " << bNumber << " into course " << crn << endl;
  
      }
  
      else if (command == "drop") {
        string  bNumber;
        int crn;
        cin>>bNumber>>crn;
        
         int studentIndex = findStudent(students, numStudents, bNumber);
    if (studentIndex == -1) {
        cout << "Fail: student " << bNumber << " not found" << endl;
        continue;;
    }
    int courseIndex = findCourse(courses,num_courses, crn);
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
        int crn;
        cin>>crn;
            if (!isValidCRN(crn)) {
        cout << "Error: invalid CRN" << endl;
        continue;
    }

    int courseIndex = findCourse(courses, num_courses, crn);
    if (courseIndex == -1) {
        cout << "Error: CRN not found" << endl;
        continue;
    }

    cout << "CRN: " << courses[courseIndex].crn << endl;
    if(numStudents==0){
    cout << "Students: "<<numStudents<<endl;
      }
        
    int count = 0;
    for (int i = 0; i < numStudents; i++) {
        for (int j = 0; j < students[i].num_courses; j++) {
            if (students[i].courses[j]->crn == crn) {
                count++;
                cout << students[i].bNumber << " " << students[i].firstName << ", " << students[i].lastName << endl;
                
            }
        }
    }
  
      }
  
      else if (command == "schedule") {
        string bNumber;
        cin>>bNumber;
          if (!isValidBNumber(bNumber)) {
    cout << "Input Error: invalid arguments" << endl;
    continue;
  }
  
  // Find the index of the student with the given B Number
  int studentIndex = findStudent(students, numStudents, bNumber);
  if (studentIndex == -1) {
    cout << "Fail: could not find student with B Number " << bNumber << endl;
    continue;
  }
  
  Student student = students[studentIndex];
  cout << "Student: " << student.bNumber << ": " << student.firstName << " " << student.lastName << endl;
  if (student.num_courses == 0) {
    cout << "No courses" << endl;
  } else {
    for (int i = 0; i < student.num_courses; i++) {
      Course *course = student.courses[i];
      cout << course->crn << " " << course->department << " " << course->number << " " << course->name << endl;
    }
  }
  
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
