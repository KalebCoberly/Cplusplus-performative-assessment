/*
"1.  Create the base class Student in the files student.h and student.cpp, which includes each  of the following variables :

•   student ID

•   first name

•   last name

•   email address

•   age

•   array of number of days to complete each course

•   degree types


Note : Degree type should be populated in subclasses only.


	2.  Create each of the following functions in the Student class :

	a.an accessor(i.e., getter) for each  instance variable from part D1

	b.a mutator(i.e., setter) for each instance variable from part D1


	Note : All access and changes to the instance variables of the Student class should be done through the accessor and mutator functions.


	c.constructor using all  of the input parameters provided in the table

	d.  virtual print() to print specific student data

	e.destructor

	f.  virtual getDegreeProgram()


	Note: Leave the implementation of the getDegreeProgram() function empty."
*/

#include <string>
#include <array>
#include <iomanip>
#include <iostream>
#include <stdexcept>

#include "Student.h"

Student::Student(std::string sId, std::string firstName, std::string lastName,
	std::string email, AGE age, std::array<DAYS, 3> daysInCourse,
	const Degree degreeType) {
	//"constructor using all  of the input parameters provided in the table"
		//i.e. including DegreeType
	//"Note: Degree type should be populated in subclasses only."	
		//Choosing to exclude degree parameter in base constructor because:
			//1. Project specs don't allow for a NULLDEGREE enumerator value.
			//2. Project specs prohibit degree member value from being populated
				//in base class.
			//3. Even though it seems redundant in derived classes as well
				//(as they are defined by their degree type),
				//it's an opportunity to demonstrate using the base constructor
				//to handle the common parameters in the derived constructor.

	//Using direct access here rather than accessors, to save compute.
	this->SId = sId;
	this->FirstName = firstName;
	this->LastName = lastName;
	this->Email = email;
	this->Age = age;
	for (int i = 0; i < daysInCourse.size(); i++) {
		if (daysInCourse[i] < 0) {
			throw std::runtime_error(
				"Invalid number of days in course in Student::SetDaysInCourse. Must be >= 0.");
		}
		this->DaysInCourse[i] = daysInCourse[i];
	}
	this->DegreeType = degreeType; 

	return;
}

Student::Student(const Student& obj) {
	this->SId = obj.SId;
	this->FirstName = obj.FirstName;
	this->LastName = obj.LastName;
	this->Email = obj.Email;
	this->Age = obj.Age;
	for (int i = 0; i < this->DaysInCourse.size(); i++) {
		this->DaysInCourse[i] = obj.DaysInCourse[i];
	}
	this->DegreeType = obj.DegreeType;
}

Student::~Student() {
	return;
}

const std::string Student::GetSId() {
	return this->SId;
}
const std::string Student::GetFirstName() {
	return this->FirstName;
}
const std::string Student::GetLastName() {
	return this->LastName;
}
const std::string Student::GetEmail() {
	return this->Email;
}
const AGE Student::GetAge() {
	return this->Age;
}
const DAYS Student::GetDaysInCourse(const int course) {
	return this->DaysInCourse[course];
}

std::string Student::GetDegreeStr() {
	//Would like to use static function DegToStr(), but it's not accessible in
		//main() unless declared there? Probably something I'm missing, but moving on.
	DegMapToStr degMapToStr; //Or strMapToDeg? Which is said to be mapped to which?
	degMapToStr[Degree::SECURITY] = "SECURITY";
	degMapToStr[Degree::NETWORK] = "NETWORK";
	degMapToStr[Degree::SOFTWARE] = "SOFTWARE";

	return degMapToStr[this->GetDegreeType()];
}

void Student::SetSId(const std::string& sId) {
	this->SId = sId;
	return;
}
void Student::SetFirstName(const std::string& firstName) {
	this->FirstName = firstName;
	return;
}
void Student::SetLastName(const std::string& lastName) {
	this->LastName = lastName;
	return;
}
void Student::SetEmail(const std::string& email) {
	this->Email = email;
	return;
}
void Student::SetAge(const AGE age) {
	this->Age = age;
	return;
}

//Using array object here to try it out, even though a simple array would
	//allow you to pass different lengths in case policy changed that allowed
	//students to have more than 3 courses.
void Student::SetDaysInCourse(const std::array<DAYS, 3> daysInCourse) {
	for (int i = 0; i < daysInCourse.size(); i++) {
		if (daysInCourse[i] < 0) {
			throw std::runtime_error(
				"Invalid number of days in course in Student::SetDaysInCourse. Must be >= 0.");
		}
		this->DaysInCourse[i] = daysInCourse[i];
	}

	return;
}

void Student::SetDegreeType(Degree degreeType) {
	this->DegreeType = degreeType;
}

void Student::SetAll(const std::string& sId, const std::string& firstName,
	const std::string& lastName, const std::string& email, const AGE age,
	const std::array<DAYS, 3> daysInCourse, const Degree degreeType) {

	for (int i = 0; i < daysInCourse.size(); i++) {
		if (daysInCourse[i] < 0) {
			throw std::runtime_error(
				"Invalid number of days in course in Student::SetAll. Must be >= 0.");
		}
	}
	this->SId = sId;
	this->FirstName = firstName;
	this->LastName = lastName;
	this->Email = email;
	this->Age = age;
	this->SetDaysInCourse(daysInCourse);
	this->DegreeType = degreeType;
	return;
}

void Student::Print() {
	//"1 [tab] First Name: John [tab] Last Name: Smith [tab] Age: 20 [tab]daysInCourse: {35, 40, 55} Degree Program: Security."
	//Missing [tab] in Degree field, but I verified that this was not intentional.
	//I would include the student ID, since it's the PK,
		//but the project specs call for this report format.
	std::cout << "First Name: " << this->GetFirstName() << "\tLast Name: "
		<< this->GetLastName() << "\tAge: " << this->GetAge() << std::setw(20)
		<< "\tDays in course: {" << this->GetDaysInCourse(0) << ", "
		<< this->GetDaysInCourse(1) << ", " << this->GetDaysInCourse(2)
		<< "}\tDegree Program: " << this->GetDegreeStr() << std::endl;

	return;
}