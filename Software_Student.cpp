//"Each subclass should override the getDegreeProgram() function.
//"Each subclass should have a data member to hold the enumerated type for the
	//degree program using the types defined in part C."
#include <string>
#include <array>
#include <iostream>

#include "Software_Student.h"

SoftwareStudent::SoftwareStudent(std::string sId, std::string firstName,
	std::string lastName, std::string email, AGE age,
	std::array<DAYS, 3> daysInCourse, Degree degreeType)
	: Student(sId, firstName, lastName, email, age, daysInCourse, degreeType) {
	return;
}

SoftwareStudent::SoftwareStudent(const SoftwareStudent& obj) : Student(obj) {
	return;
}

SoftwareStudent::~SoftwareStudent() {
	return;
}

const Degree SoftwareStudent::GetDegreeType() {
	return this->DegreeType;
}