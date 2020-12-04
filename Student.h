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

#pragma once
#include <string>
#include <array>

#include "Degree.h"

typedef unsigned int AGE;
typedef unsigned int DAYS;

class Student {
public:
	//"constructor using all  of the input parameters provided in the table"
		//i.e. including DegreeType
	//"Note: Degree type should be populated in subclasses only."
	//Passing daysInCourse as an array, even though project specs call for each
		//day to be passed individually, because it would make it easier to change
		//the number of courses allowed, and I wanted to work with passing an
		//array object.
	//I am cognizant that this would require approval in a team environment.
	Student(std::string sId, std::string firstName, std::string lastName,
		std::string email, AGE age, std::array<DAYS, 3> daysInCourse,
		const Degree degreeType);
	Student(const Student& obj);
	~Student();
	const std::string GetSId();
	const std::string GetFirstName();
	const std::string GetLastName();
	const std::string GetEmail();
	const AGE GetAge();
	const DAYS GetDaysInCourse(const int course);

	//"2.  Create each of the following functions in the Student class :
		//"a.an accessor(i.e., getter) for *each*  instance variable from part D1
		//"a mutator(i.e., setter) for *each* instance variable from part D1"
		//(i.e. even DegreeType)
	//"Note: Leave the implementation of the getDegreeProgram() function empty."
		//Making base abstract (via pure virtual SetDegreeType()) to fulfill this,
		//but leaving GetDegreeType() not pure so that it can be inherited.
		//One might consider making the base class instantiable to cover
		//undecided students, if your school allows that, but creating an 
		//undecided derived class would work just as well and maintain an 
		//abstract base class.
	const virtual Degree GetDegreeType() = 0;
	std::string GetDegreeStr();
	void SetSId(const std::string& sId);
	void SetFirstName(const std::string& firstName);
	void SetLastName(const std::string& lastName);
	void SetEmail(const std::string& email);
	void SetAge(const AGE age);
	//Using array object here to try it out, even though a simple array would 
		//allow you to pass different lengths in case policy changed that allowed students to have more than 3 courses.
	void SetDaysInCourse(const std::array<DAYS, 3> daysInCourse);
	//"a mutator(i.e., setter) for each instance variable" (even DegreeType)
	//"Note: Degree type should be populated in subclasses only."
	void SetDegreeType(const Degree degreeType);
	void SetAll(const std::string& sId, const std::string& firstName,
		const std::string& lastName, const std::string& email, const AGE age,
		const std::array<DAYS, 3> daysInCourse, const Degree degreeType);
	virtual void Print();

private:
	//PK, required. No robust input validation included in this program, though.
	std::string SId;
	std::string FirstName;
	std::string LastName;
	std::string Email;
	AGE Age;
	//I'm assuming a fixed number of courses for simplicity's sake,
		//and because stored data implies this fixed number.
		//However, we could set a higher max number of courses and accept data
		//with varying structures.
	std::array<DAYS, 3> DaysInCourse;

protected:
	Degree DegreeType; //"populated in subclasses only"
};