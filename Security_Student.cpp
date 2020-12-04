//"Each subclass should override the getDegreeProgram() function.
//"Each subclass should have a data member to hold the enumerated type for the degree program using the types defined in part C."
#include <string>
#include <array>
#include <iostream>
//using namespace std

#include "Security_Student.h"

SecurityStudent::SecurityStudent(std::string sId, std::string firstName,
	std::string lastName, std::string email, AGE age,
	std::array<DAYS, 3> daysInCourse, Degree degreeType)
	: Student(sId, firstName, lastName, email, age, daysInCourse, degreeType) {
	return;
}

SecurityStudent::SecurityStudent(const SecurityStudent& obj) : Student(obj) {
	return;
}

SecurityStudent::~SecurityStudent() {
	return;
}

const Degree SecurityStudent::GetDegreeType() {
	return this->DegreeType;
}