This program simulates a basic course enrollment system, allowing the user to build and cancel courses, enroll and drop students from courses, and view a course roster or student schedule.

The program uses two structs, Course and Student, to represent a course and a student, respectively. A Course has a CRN, department, course number, and name, while a Student has a B-number, user ID, first name, last name, and a dynamic array of pointers to courses. The array of courses is dynamically allocated so that a Student can be enrolled in any number of courses.

The main function of the program repeatedly prompts the user for a command and executes the corresponding action until the user enters "quit". The program uses several helper functions to perform input validation and search for elements within the Course and Student arrays.

The "build" command allows the user to add a new Course to the array. The user must enter a valid CRN, department, course number, and name, and the program checks that the CRN does not already exist before adding the new Course to the array.

The "cancel" command allows the user to remove a Course from the array by its CRN. If the CRN is not found in the array, the program prints a failure message.

The "enroll" command allows the user to add a new Student to the array and enroll them in one or more Courses. The user must enter a valid B-number, user ID, first name, and last name, and the program dynamically allocates a new array of pointers to courses for the new Student. The program then prompts the user to enter the CRNs of the Courses to enroll the Student in, and adds the corresponding Course pointers to the Student's array.

The "add" command allows the user to enroll an existing Student in an additional Course. The user must enter a valid B-number and CRN, and the program searches for the Student and Course in the arrays before adding the Course pointer to the Student's array.

The "drop" command allows the user to remove a Course from an existing Student's array. The user must enter a valid B-number and CRN, and the program searches for the Student and Course in the arrays before removing the Course pointer from the Student's array.

The "roster" command allows the user to view a list of Students enrolled in a specific Course. The user must enter a valid CRN, and the program searches for the Course in the array before printing the list of Students.

The "schedule" command allows the user to view a list of Courses that an existing Student is enrolled in. The user must enter a valid B-number, and the program searches for the Student in the array before printing the list of Courses.

Overall, this program provides a basic implementation of a course enrollment system, with functionality to add and remove Courses and Students, enroll and drop Students from Courses, and view rosters and schedules.
