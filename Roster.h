/*
"E.Create a Roster class (roster.cpp) by doing the following :

1.  Create an array of pointers, classRosterArray, to hold the data provided in the studentData table.

2.  Create a student object for each  student in the data table by using the subclasses NetworkStudent, SecurityStudent, and SoftwareStudent, and populate classRosterArray.

a.Apply pointer operations when parsing each  set of data identified in the studentData table.

b.Add each student object to classRosterArray.

3.  Define the following functions :

a.  public void add(string studentID, string firstName, string lastName, string emailAddress, int age, int daysInCourse1, int daysInCourse2, int daysInCourse3, < degree program >) that sets the instance variables from part D1 and updates the roster.

b.  public void remove(string studentID) that removes students from the roster by student ID.If the student ID does not exist, the function prints an error message indicating that the student was not found.


c.  public void printAll() that prints a complete tab - separated list of student data using accessor functions with the provided format : 1[tab] First Name : John[tab] Last Name : Smith[tab] Age : 20[tab]daysInCourse : {35, 40, 55} Degree Program : Security.The printAll() function should loop through all  the students in classRosterArrayand call the print() function for each student.

d.  public void printDaysInCourse(string studentID) that correctly prints a student’s average number of days in the three courses.The student is identified by the studentID parameter.

e.  public void printInvalidEmails() that verifies student email addressesand displays all invalid email addresses to the user


Note : A valid email should include an at sign('@') and period('.') and should not include a space(' ').


	f.  public void printByDegreeProgram(int degreeProgram) that prints out student information for a degree program specified by an enumerated type"
*/

#pragma once
#include <string>
#include <array>
#include <vector>
#include <iostream>

#include "Degree.h"
#include "Student.h"

class Roster {
public:
	//Initialzes roster, given a string array of properly formatted
		//comma-separated records, the number of fields in each record,
		//and a maximum roster length.
	Roster(const std::string srcArr[] = nullptr, unsigned int srcArrLen = 0,
		unsigned int numOfFields = 9, unsigned int maxRostLen = 63);
	Roster(const Roster& obj);
	~Roster();

	const int GetMaxRostLen();

	void SetMaxRostLen(const unsigned int maxRostLen);
	//Initializes roster, given a string array of properly formatted
		//comma-separated records, the number of fields in each record,
		//and a maximum roster length.
		//Can use to reset roster without destructing the object.
		//Be sure to call DeconRoster() first if using outside of Roster().
	void SetRoster(const std::string srcArr[] = nullptr, unsigned int srcArrLen = 0,
		unsigned int numOfFields = 9, unsigned int maxRostLen = 63);
	//Deconstructs StudentRoster. Extant Students detructed, pointers set to
		//nullptr, array deleted.
	void DeconRoster();
	//Populates roster, given a string array of properly formatted
		//comma-separated records and the number of fields in each record.
	void AddByStrArr(const std::string srcArr[], const unsigned int srcArrLen,
		const unsigned int numOfFields);

	//Removes student from roster. Destructs student, and points roster element to null.
	void Remove(const std::string& sId);

	//Prints all students' data from roster.
		//Passing true requires user to press enter to continue after the end of
		//the list, using EndList().
	void PrintAll(bool holdWindow = false);
	//Prints the average days in course for all students in roster.
	void PrintAllAvDays(bool holdWindow = false);
	//Prints the average days in course for a single student, given student ID.
	void PrintAvDaysInCourse(const std::string& sId);
	//Prints student ID and email addresses of all students in roster with invalid
		//email addresses..
	//Passing true requires the user to press enter to continue after the end of
		//the list, using EndList().
	void PrintInvalidEmails(bool holdWindow = false);
	//Prints data of all students in roster in a degree program, given the degree type.
		//Passing true requires user to press enter to continue after the end of
			//the list, using EndList().
	void PrintByDegreeProgram(const Degree degreeType, bool holdWindow = false);

private:
	int MaxRostLen;
	Student** StudentRoster; //Dynamic array of pointers, per project specs.

	//Returns pointer to Student* array.
	Student** GetRoster();
	//Returns the roster index of a student, given ID.
	const int FindStudIdxBySId(const std::string& sId);
	//Returns student pointer, given roster index.
	Student* GetStudPtrByIdx(const unsigned int idx);

	//Adds a student to roster, given a properly formatted comma-separated record
		//as a string, and the number of fields.
	void AddByRecordStr(const std::string& record, const unsigned int numOfFields);
	//Adds a student to roster from properly typed data. This is where the
		//student finally gets constructed.
	void AddByField(const std::string& sId, const std::string& firstName,
		const std::string& lastName, const std::string& email, AGE age,
		const std::array<DAYS, 3> daysInCourse, const Degree degreeType);

	//Validates a single email address, given roster index.
	bool IsValidEmail(const unsigned int studIdx);
};

//Used at end of list outputs, to either hold the window open and require user to
	//press enter, or to continue automatically.
	//Allows function to be used independently of current use case,
	//i.e. to leave window open.	
//Would like to include in separate file (as I would like to give main()
	//its own file), but project specs explicitly require only the files included.
void EndList(const bool holdWindow);

//Maps Degree enum to string equivalent.
std::string DegToStr(const Degree degreeType);