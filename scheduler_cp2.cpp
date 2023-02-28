 string bNumber;
    string userId;
    string firstName;
    string lastName;
    vector<int> crns; #include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;


struct Course {
    int crn;
    string department;
    int number;
    string name;
    vector<string> bNumbers;
};

struct Student {
    string bNumber;
    string userid;
    string first_name;
    string last_name;
    vector<int> crns; 
};







bool is_valid_crn(string crn) {
    if (crn.size() != 6) {
        return false;
    }
    for (char c : crn) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}


bool is_valid_department(string department) {
    if (department.size() < 2 || department.size() > 4) {
        return false;
    }
    for (char c : department) {
        if (!isupper(c)) {
            return false;
        }
    }
    return true;
}


bool is_valid_course_number(string course_number) {
    if (course_number.size() != 3) {
        return false;
    }
    for (char c : course_number) {
        if (!isdigit(c)) {
            return false;
        }
    }
    int number = stoi(course_number);
    return (number >= 100 && number <= 700);
}


bool is_valid_bnumber(string bnumber) {
    if (bnumber.size() != 9 || bnumber[0] != 'B') {
        return false;
    }
    for (char c : bnumber.substr(1)) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool isValidUserid(string userid) {
    if (userid.size() == 0 || !isalpha(userId[0])) {
        return false;
    }
    for (int i = 1; i < userid.size(); i++) {
        if (!isalnum(userid[i])) {
            return false;
        }
    }
    return true;
}


bool crn_exists(string crn) {
    return (courses.find(crn) != courses.end());
}


bool bnumber_exists(string bnumber) {
    return (students.find(bnumber) != students.end());
}

void showPrompt() {
   cout << "Enter [\"build <crn> <department> <number> <name>\"" << endl <<
                "       \"cancel <crn>\"" << endl <<
                "       \"enroll <bnumber> <userid> <first> <last>\"" << endl <<
                "       \"add <bnumber> <crn>\"" << endl <<
                "       \"drop <bnumber> <crn>\"" << endl <<
                "       \"roster <crn>\"" << endl <<
                "       \"schedule <bnumber>\"" << endl <<
                "       \"quit\"]" << endl <<
                ": ";
}


int main() {
    string command, crn, department, course_number, name, bnumber, userid, first_name, last_name;
    
    Student* students = new Student[];
    Course* courses = new Course[];
    int numStudents = 0;
    int numCourses = 0;
    
    showPrompt();
    while (true) {
                
        cin >> command;
        
        
        if (command == "build") {
            
            cin >> crn >> department >> course_number;
            getline(cin, name);
            name = name.substr(1);  
            

            if (!is_valid_crn(crn)) {
                cout << "Input Error: illegal CRN" << endl;
            }

	    else if (!is_valid_department(department)) {
                cout << "Input Error: illegal department" << endl;

	    }

	    else if (!is_valid_course_number(course_number)) {
                cout << "Input Error: illegal course number" << endl;

	    }

	    else if (crn_exists(crn)) {
	      cout << "Fail: cannot build course " << department << course_number << " (CRN: " <<crn<<")"<<endl;

	    }
	    
	    else{

	       courses[numCourses].crn = crn;
               courses[numCourses].department = department;
               courses[numCourses].number = number;
               courses[numCourses].name = name;
               numCourses++;
	       
              
	      cout << "Success: built course " << department << course_number << " (CRN: " << crn << ")" << endl;
    
	    }
	    
	}

	else if(command == "cancel"){
	  string crn;
	  cin >> crn;

	  if (!is_valid_crn(crn)) {

	    cout << "Input Error: illegal CRN" << endl;
    }
	  else if (!crn_exists(crn)) {

	    cout << "Fail: CRN " << crn << " does not exist" << endl;
    }
	  
	  else {

	    for (int i = 0; i < numCourses; i++) {
                    if (courses[i].crn == crn) {
                        for (int j = i; j < numCourses - 1; j++) {
                            courses[j] = courses[j + 1];
                        }
                        numCourses--;
		    }
	    }
	     cout << "Success: Canceled course " << crn << endl;
	  }
	}
    
	else if(command == "enroll"){

	  
	  cin >> bnumber >> userid >> first_name >> last_name;
	  
	  if (!is_valid_bnumber(bnumber)) {

	    cout << "Input Error: illegal B number" << endl;
    }
	  else if (bnumber_exists(bnumber)) {

	    cout << "Fail: student " << bnumber << " already exists" << endl;
    }

	  else {
	    
	    students[numStudents].bnumber = bnumber;
	    students[numStudents].userid = userid;
	    students[numStudents].last_name = last_name;
	    students[numStudents].first_name = first_name;
	    numStudents++;
                cout << "Success: Enroll student " << bnumber << " (" << userid << ") " << last_name << ", " << first_name << endl;
    }

	}

	else if(command == "add"){

	  cin >> bnumber >> crn;

	  if (!is_valid_bnumber(bnumber)) {

	    cout << "Input Error: illegal B number" << endl;
    }
	  else if (!is_valid_crn(crn)) {

	    cout << "Input Error: illegal CRN" << endl;
    }
	  else if (!bnumber_exists(bnumber)) {

	    cout << "Fail: student " << bnumber << " does not exist" << endl;
    }
	  else if (!crn_exists(crn)) {

	    cout << "Fail: CRN " << crn << " does not exist" << endl;
    }

	  else {
	    
	  
	cout << "Success: Added student " << bnumber << " to course " << crn << endl;

	  }
	}
    
	else if(command == "drop"){

	  cin >> bnumber >> crn;
    
    
    if (!is_valid_bnumber(bnumber)) {
        cout << "Input Error: illegal B number" << endl;
    }

    else if (!is_valid_crn(crn)) {

      cout << "Input Error: illegal CRN" << endl;
    }

    else if (!bnumber_exists(bnumber)) {

      cout << "Fail: student " << bnumber << " does not exist" << endl;
    }

    else if (!crn_exists(crn)) {

      cout << "Fail: CRN " << crn << " does not exist" << endl;
    }

    else {
       
      //vector<string>& schedule = students[bnumber].schedule;
      //schedule.erase(remove(schedule.begin(), schedule.end(), crn), schedule.end());
        
       
      //vector<string>& roster = 
	  }

	}

	else if(command == "roster"){


	}

	else if(command == "schedule"){
	   cin >> bnumber;
    if (!is_valid_bnumber(bnumber)) {
        cout << "Input Error: illegal B number" << endl;
    } else if (!bnumber_exists(bnumber)) {
        cout << "Fail: student " << bnumber << " does not exist" << endl;
    } else {
        cout << "Schedule for " << bnumber << ":" << endl;
        for (string crn : students[bnumber].schedule) {
            Course course = courses[crn];
            cout << course.department << " " << course.number << " " << course.name << endl;
        }
    }


	}

	else if(command =="quit"){


	  break;
	}

	else{

	  cout <<"Unknown command"<<endl;
	}

    }

    delete[] students;
    delete[] courses;
    return 0;
}
