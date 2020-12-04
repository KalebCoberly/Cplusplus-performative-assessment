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


	f.  public void printByDegreeProgram(int degreeProgram) that prints out student information for a degree program specified by an enumerated type


	F.Demonstrate the program’s required functionality by adding a void main() function to roster.cpp, which will contain the required function calls to achieve the following results :

1.  Print out to the screen, via your application, the course title, the programming language used, your student ID, and your name.

2.  Create an instance of the Roster class called classRoster.

3.  Add each student to classRoster.

4.  Convert the following pseudo code to complete the rest of the main() function :
	classRoster.printAll();
classRoster.printInvalidEmails();
Loop through classRosterArray and for each element:
classRoster.printAverageDaysInCourse(current_object's student id);
classRoster.printByDegreeProgram(SOFTWARE);
classRoster.remove("A3");
classRoster.remove("A3");
Expected: the above line should print a message saying such a student with this ID was not found.

5.  Call the destructor to release the Roster memory."
*/

#define _WIN32_WINNT 0x0500

#include <array>
#include <iomanip>
#include <ios>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#include <windows.h>

#include "Degree.h"
#include "Network_Student.h"
#include "Roster.h"
#include "Security_Student.h"
#include "Software_Student.h"
#include "Student.h"

//Constructs roster, given a string array of properly formatted comma-separated
	//records, the number of fields in each record, and a maximum roster length.
Roster::Roster(const std::string srcArr[], unsigned int srcArrLen,
	unsigned int numOfFields, unsigned int maxRostLen) {
	//"Create an array of pointers, classRosterArray, to hold the data provided
		//in the studentData table."
	//"2.  Create an instance of the Roster class called classRoster.
	//"3.  Add each student to classRoster."

	/*My plan*/
		//Construct roster, passing studentData.
			//Inside construction, iterate through array, calling AddByRecordStr() for each element.
				//Inside AddByRecordStr(), parse the record into proper data types, and pass to AddByField().
					//Inside AddByField(), construct students, and add pointers to roster member array.

	//Using mutator here to save lines of code, assuming this isn't processing a
		//huge load of rosters.
	this->SetRoster(srcArr, srcArrLen, numOfFields, maxRostLen);

	return;
}

Roster::Roster(const Roster& obj) {
	this->MaxRostLen = obj.MaxRostLen;
	**this->StudentRoster = **obj.StudentRoster;
	return;
}

Roster::~Roster() {
	//Destruct students and delete array.
	this->DeconRoster();
	return;
}

const int Roster::GetMaxRostLen() {
	return this->MaxRostLen;
}

void Roster::SetRoster(const std::string srcArr[], unsigned int srcArrLen,
	unsigned int numOfFields, unsigned int maxRostLen) {
	//Construct roster, passing studentData (as pointer to first element).
			//Inside construction, iterate through array, calling AddByRecordStr() for each element.
				//Inside AddByRecordStr(), parse the record into proper data types, and pass to AddByField().
					//Inside AddByField(), construct students, and add pointers to roster member array.
	unsigned int mrLen = maxRostLen;
	//If needed resize max array size to fit input array.
	if (srcArrLen > mrLen) {
		std::cout << "Sizing roster array length to fit source array length: "
			<< srcArrLen << "." << std::endl << std::endl;
		mrLen = srcArrLen;
	}
	//Initialize array of student pointers.
	this->MaxRostLen = mrLen;
	this->StudentRoster = new Student * [mrLen];

	for (unsigned int i = 0; i < mrLen; i++) {
		this->StudentRoster[i] = nullptr;
	}

	//If array passed, construct Student objects from provided data, and load
		//their pointers into the array.
	if (srcArrLen > 0) {
		AddByStrArr(srcArr, srcArrLen, numOfFields);
	}

	return;
}

Student** Roster::GetRoster() {
	return this->StudentRoster;
}

//Deconstructs StudentRoster. Extant Students detructed, pointers set to nullptr,
	//array deleted.
void Roster::DeconRoster() {
	for (int i = 0; i < this->GetMaxRostLen(); i++) {
		if (this->StudentRoster[i] != nullptr) {
			delete this->StudentRoster[i];
			this->StudentRoster[i] = nullptr; //Necessary?
		}
	}
	delete[] this->StudentRoster;
	this->StudentRoster = nullptr;
}

//Returns the roster index of a student, given ID.
const int Roster::FindStudIdxBySId(const std::string& sId) {
	//Iterate through roster, checking ID.
	bool studFound = false;
	int i;

	for (i = 0; i < this->GetMaxRostLen(); i++) {
		if ((this->StudentRoster[i] != nullptr)
			&& (this->StudentRoster[i]->GetSId().compare(sId) == 0)) {

			studFound = true;
			break;
		}
	}

	if (!studFound) {
		i = -1;
	}

	return i;
}

//Returns student pointer, given roster index.
Student* Roster::GetStudPtrByIdx(const unsigned int idx) {
	return this->StudentRoster[idx];
}

void Roster::SetMaxRostLen(const unsigned int maxRostLen) {
	this->MaxRostLen = maxRostLen;
}

//Populates roster, given a string array of properly formatted comma-separated
	//records, the array length, and the number of fields in each record.
void Roster::AddByStrArr(const std::string srcArr[], const unsigned int srcArrLen,
	const unsigned int numOfFields = 9) {

	if ((srcArr == nullptr) && (srcArrLen > 0)) {
		throw std::runtime_error(
			"Invalid source array in Roster::AddByStrArr. Must not be nullptr if array length is set.");
	}
	if ((srcArrLen == 0) && (srcArr != nullptr)) {
		throw std::runtime_error(
			"Invalid source array length in Roster::AddByStrArr. Must be > 0 if array is passed (Match actual array length, please, and no empty arrays.)."); //No way to check if length passed matches length of array.
	}
	//Construct Student objects from each string record, and load pointers into
		//roster.
	for (unsigned int i = 0; i < srcArrLen; i++) {
		AddByRecordStr(srcArr[i], numOfFields);
	}
	return;
}

//Adds a student to roster, given a properly formatted comma-separated string
	//record as a string, and the number of fields.
void Roster::AddByRecordStr(const std::string& record,
	const unsigned int numOfFields = 9) {

	if (numOfFields < 1) {
		throw std::runtime_error("Invalid number of fields in Roster::AddByRecordStr. numOfFields must be > 0");
	}

	AGE age;
	//Assuming fixed number of courses for simplicity's sake, and to try use of
		//array object.
		//Also assuming validated input did not allow commas within fields --
		//from a csv maybe.
	//Maybe the best way we could handle a varied number of courses would be
		//by increasing the max number of courses to include all cases allowed by
		//school policy.
		//That would also require changing the number of fields in a record and
			//processing 0 values as no course.
		//We would have to reformat legacy input (e.g. the array provided in this
			//assignment) by inserting zeroed fields before age.
		//We would have to be mindful of that hack when adding later input
			//reformats that add or subtract fields after these fields,
			//and we would have to review any extant (extra)object functions 
			//in the ecos that iterate through student fields.
	std::array<DAYS, 3> daysInCourse;
	Degree degreeType;

	//Find position of commas in record.
		//Fixed number of courses makes fields fixed,
			//though we could say that all fields between the 5th field and the
			//final field are days in courses, and set the daysInCourse[],
			//recordFields[], and commasInRecord[] sizes at runtime.
			//We could use a vector and resize as needed instead if project specs
			//allowed, but resources may be limited irl, and we'd still have to
			//manage varied input strings etc.

	//No out-of-range exceptions.
	const unsigned int numOfCommas = numOfFields - 1;
	std::vector<std::string> recordFields(numOfFields, ""); //Stores separated fields from comma-separated string record.
	std::vector<unsigned int> commaPositions(numOfCommas, -1); //Stores position of commas.
	std::size_t foundPos = -1;
	unsigned int foundCommas = 0;

	do {
		foundPos = record.find(",", (foundPos + 1));
		if (foundPos != -1) {
			foundCommas++;
			if (foundCommas <= numOfCommas) {
				int comPosIdx = foundCommas - 1;
				if (comPosIdx < 0) {
					throw std::runtime_error(
						"Invalid comma index in Roster::AddByRecordStr(). When loading found comma positions into array, foundCommas - 1 must be >= 0.");
				}
				commaPositions.at(comPosIdx) = foundPos;
			}
		}
	} while (foundPos != -1); //find() will return -1 when it doesn't find a comma.

	//Validate fields, number of fields.
		//Not using throw so student entries can continue.
	if (foundCommas == numOfCommas) {

		//Use commas to find each field, and create a string array of them.
		//Set 1st substring before 1st comma.
		unsigned int startPos = 0; //Start position of substring to be field.
		std::size_t subLength = commaPositions.at(0); //Length of substring to be field.
		for (unsigned int i = 0; i < numOfCommas; i++) {
			recordFields.at(i) = record.substr(startPos, subLength);
			//Set next substring between commas.
			if (i < (numOfCommas - 1)) {
				unsigned int currentCommaIdx = commaPositions.at(i);
				unsigned int comPosIdx = i + 1;
				unsigned int nextCommaIdx = commaPositions.at(comPosIdx);
				startPos = currentCommaIdx + 1;
				unsigned int signedSubLen = nextCommaIdx - startPos;
				if (signedSubLen <= 0) {
					throw std::runtime_error(
						"Potential overflow error in Roster::AddByRecordStr. String sublength for field must be > 0.");
				}
				subLength = signedSubLen;
			}
			//Last comma: next sublength determined by string length, not next comma.
			else {
				startPos = commaPositions.at(i) + 1;
				subLength = record.length() - startPos;
				unsigned int fieldIdx = numOfFields - 1;
				recordFields.at(fieldIdx) = record.substr(startPos, subLength);
			}
		}

		//Validate degreeType, and set.
			//One might choose to validate each field in the record before
				//proceeding, rather than one at a time.
			//This would avoid the annoying scenario in which a record that has
				//multiple invalid fields gets thrown back to the user for a field
				//fix one field at a time, rather than highlighting for the user
				//all at once each invalid field in a record.
			//However, this saves compute time on all of the valid records,
				//and records with only one or two invalid fields.
			//So, if you're constructing a ton of rosters with a ton of students
				//all at once, this would save time.
			//Then, a full validation can be called if one field is found invalid,
				//but I don't include that here since any validation is above and
				//beyond the assignment.
			//However, the project specs call for PrintInvalidEmails() wherein
				//students are entered regardless and validation is done after
				//the fact.
			//This works best for string fields, and may be a good way to handle
				//the ID field.
			//But, since this is a demo, I included some preemptive validation as well.
		bool isDegValid = false;
		/*
		switch (0)
		{
		case recordFields.at(8).compare("SECURITY"):
			isDegValid = true;
			degreeType = SECURITY;
			break;
		case recordFields.at(8).compare("NETWORK"):
			isDegValid = true;
			degreeType = NETWORK;
			break;
		case recordFields.at(8).compare("SOFTWARE"):
			isDegValid = true;
			degreeType = SOFTWARE;
			break;
		default:
			std::cout << "Could not enter student. Invalid degree type:";
			for (int i = 0; i < numOfFields; i++) {
				std::cout << "    " << recordFields.at(i);
			}
			break;
		}
		*/
		//Fewer lines. Same number of computations?
		if (recordFields.at(8).compare("SECURITY") == 0) {
			isDegValid = true;
			degreeType = Degree::SECURITY;
		}
		else if (recordFields.at(8).compare("NETWORK") == 0) {
			isDegValid = true;
			degreeType = Degree::NETWORK;
		}
		else if (recordFields.at(8).compare("SOFTWARE") == 0) {
			isDegValid = true;
			degreeType = Degree::SOFTWARE;
		}
		else {
			std::cout << "Could not enter student. Invalid degree type:";
			for (unsigned int i = 0; i < numOfFields; i++) {
				std::cout << "    " << recordFields.at(i);
			}
			std::cout << std::endl;
		}

		if (isDegValid) {
			//Validate and set other fields.
			//invalid_argument and out_of_range exceptions to be handled in main()
				//try block. (Type of logical error.)
			if (std::stoi(recordFields.at(4)) < 0) {
				age = 0;
				std::cout << "Invalid age (must be >= 0): ";
				for (unsigned int i = 0; i < numOfFields; i++) {
					std::cout << "\t" << recordFields.at(i);
				}
				std::cout << std::endl;
				std::cout << "Age to be used: " << age << "." << std::endl;
			}
			else {
				age = std::stoi(recordFields.at(4));
			}

			//Construct daysInCourse as array sooner rather than later in case
				//program gets revised to accomodate students enrolled in more
				//courses.
			int fieldIdx = 5;
			for (int i = 0; i < daysInCourse.size(); i++) {
				if (std::stoi(recordFields.at(fieldIdx)) < 0) {
					daysInCourse[i] = 0;
					std::cout << "Invalid days in course " << (i + 1)
						<< " (must be >= 0): ";
					for (unsigned int j = 0; j < numOfFields; j++) {
						std::cout << "\t" << recordFields.at(j);
					}
					std::cout << std::endl;
					std::cout << "Number of days to be used: " << daysInCourse[i]
						<< "." << std::endl;
				}
				else {
					daysInCourse[i] = std::stoi(recordFields.at(fieldIdx));
				}
				fieldIdx++;
			}

			//Construct the student and add to roster.
			AddByField(recordFields.at(0), recordFields.at(1), recordFields.at(2),
				recordFields.at(3), age, daysInCourse, degreeType);
		}

	}
	else {
		std::cout << "Could not enter student. Invalid number of fields (requires "
			<< numOfFields << " fields):";
		for (unsigned int i = 0; i < numOfFields; i++) {
			std::cout << "\t" << recordFields.at(i);
		}
	}
	return;
}

//Adds a student to roster from properly typed data. This is where the student
	//finally gets constructed.
void Roster::AddByField(const std::string& sId, const std::string& firstName,
	const std::string& lastName, const std::string& email, const AGE age,
	const std::array<DAYS, 3> daysInCourse, const Degree degreeType) {
	//Validate ID (PK, required.)
		//Choosing not use exception handling for validation here so that following student entries can continue.
	int studIdx = FindStudIdxBySId(sId);
	if (studIdx != -1) {
		std::cout << "Student ID already in use: " << std::endl;
		this->StudentRoster[studIdx]->Print();
	}
	//Make sure input field is not empty string.
	else if (sId.compare("") == 0) {
		std::cout << "Student could not be entered. Invalid ID: " << std::endl;
		std::cout << firstName << "\t" << lastName << "\t" << email << "\t"
			<< age << "\t";
		for (int i = 0; i < daysInCourse.size(); i++) {
			std::cout << daysInCourse[i] << "\t";
		}
		std::cout << DegToStr(degreeType) << std::endl << std::endl;
	}
	//If ID is valid, construct and add student to roster.
	else {
		//Find first empty slot in roster, by nullptr,
			//in case we've previously removed students, and to make sure we
			//haven't exceeded class size.
		studIdx = -1;
		for (int i = 0; i < this->GetMaxRostLen(); i++) {
			if (this->StudentRoster[i] == nullptr) {
				studIdx = i;
				break;
			}
		}
		//If empty slot found in roster,
		if (studIdx != -1) {
			//point element at appropriately classified new student, and set all
				//values.
			switch (degreeType)
			{
				//Handle exception if number of courses doesn't match array length.
			case Degree::SECURITY:
				this->StudentRoster[studIdx] = new SecurityStudent(sId, firstName,
					lastName, email, age, daysInCourse);
				break;

			case Degree::NETWORK:
				this->StudentRoster[studIdx] = new NetworkStudent(sId, firstName,
					lastName, email, age, daysInCourse);
				break;

			case Degree::SOFTWARE:
				this->StudentRoster[studIdx] = new SoftwareStudent(sId, firstName,
					lastName, email, age, daysInCourse);
				break;

			default:
				break;
			}
		}
		else {
			std::cout << "No space in roster. Student not added. Student ID: "
				<< sId << "." << std::endl;
			EndList(false);
		}
	}

	return;
}


//Removes student from roster. Destructs student, and points roster element to null.
	//If the student ID does not exist, the function prints an error message
	//indicating that the student was not found.
void Roster::Remove(const std::string& sId) {
	std::cout << "Removing student " << sId << " ... " << std::flush;
	//Find student by ID.
	int idx = this->FindStudIdxBySId(sId);
	//Destruct and point roster element to empty student.
	if (idx != -1) {
		delete this->StudentRoster[idx];
		this->StudentRoster[idx] = nullptr;
		std::cout << "Student " << sId << " removed." << std::endl << std::endl;
	}

	//Or, alert not found.
	else {
		std::cout << "Student " << sId << " not found." << std::endl << std::endl;
	}

	return;
}

//Prints all students' data from roster.
	//Passing true requires user to press enter to continue after the end of the
	//list, using EndList().
	//"Prints a complete tab-separated list of student data using accessor functions with the provided format :
	//"1[tab] First Name : John[tab] Last Name : Smith[tab] Age : 20[tab]daysInCourse : {35, 40, 55} Degree Program : Security.The printAll()function should loop through all  the students in classRosterArray and call the print() function for each student."
		//(Missing tab separator ignored.)
void Roster::PrintAll(bool holdWindow) {

	std::cout << "Roster:" << std::endl;

	int listNum = 0; //Allow for empty roster slots, and output list number
						//(not index number).
	for (int i = 0; i < this->GetMaxRostLen(); i++) {
		//List only non-empty students.
		if (this->StudentRoster[i] != nullptr) {
			listNum++;
			std::cout << listNum << "\t";
			this->StudentRoster[i]->Print();
		}
	}

	//Allow function to be used independently of current use case,
		//i.e. to leave window open waiting for input.
	EndList(holdWindow);
}

void Roster::PrintAllAvDays(bool holdWindow) {
	//"loop through classRosterArray and for each element:
	std::cout << "Average days in course:" << std::endl;
	for (int i = 0; i < this->GetMaxRostLen(); i++) {
		Student* studPtr = this->GetStudPtrByIdx(i);
		if (studPtr != nullptr) {
			std::string sId = studPtr->GetSId();
			this->PrintAvDaysInCourse(sId);
		}
	}
	//End list, and leave window open.
	EndList(holdWindow);
}

//"Correctly prints a student’s average number of days in the three courses.
//"The student is identified by the studentID parameter."
void Roster::PrintAvDaysInCourse(const std::string& sId) {
	//Find student.
	std::cout << sId << ": ";
	int idx = this->FindStudIdxBySId(sId);
	if (idx != -1) {
		//Average days.
		double avDays = 0;
		for (int i = 0; i < 3; i++) {
			avDays += this->StudentRoster[idx]->GetDaysInCourse(i);
		}
		avDays = avDays / 3;
		//avDays = floor(avDays * 10) / 10;

		std::cout << std::fixed << std::setprecision(1) << std::showpoint
			<< avDays << std::endl;
	}
	else {
		std::cout << "Student not found." << std::endl << std::endl;
	}

	return;
}

//"verifies student email addresses and displays all invalid email addresses to
	//the user."
//Passing true requires the user to press enter to continue after the end of the
	//list, using EndList().
void Roster::PrintInvalidEmails(bool holdWindow) {
	std::cout << "Invalid email addresses:" << std::endl;
	//If not an empty student, validate email.
	for (int i = 0; i < this->GetMaxRostLen(); i++) {
		if (this->StudentRoster[i] != nullptr) {
			bool isValid = this->IsValidEmail(i);
			if (!isValid) {
				std::cout << this->StudentRoster[i]->GetSId() << ": "
					<< this->StudentRoster[i]->GetEmail() << std::endl;
			}
		}
	}

	//Allow function to be used independently of current use case, i.e. to leave
		//window open.
	EndList(holdWindow);

	return;
}

//Validates a single email address, given roster index.
bool Roster::IsValidEmail(const unsigned int studIdx) {
	//"Note: A valid email should include an at sign('@') and period('.')
		//and should not include a space(' ')."
	//Additional validation would include ensuring that there is only one @,
			//that everything that follows it forms a valid (sub)domain
			//(or at least a valid TLD), and any additional standard checks such
			//as for prohibited characters. Omitted here for expedience.
			//There's probably a well-known algorithm for it.
	bool isValid = false;
	std::string email = this->StudentRoster[studIdx]->GetEmail();
	if ((email.find("@") >= 0) && (email.find(".") >= 0)
		&& (email.find(" ") == -1)) {

		isValid = true;
	}

	return isValid;
}

//"Prints out student information for a degree program specified by an enumerated type."
//Prints data of all students in roster in a degree program, given the degree type.
		//Passing true requires user to press enter to continue after the end of
		//the list, using EndList().
void Roster::PrintByDegreeProgram(const Degree degreeType, bool holdWindow) {
	std::cout << "Students in " << DegToStr(degreeType) << ":" << std::endl;
	int listNum = 0;
	for (int i = 0; i < this->GetMaxRostLen(); i++) {
		if ((this->StudentRoster[i] != nullptr)
			&& (this->StudentRoster[i]->GetDegreeType() == degreeType)) {

			listNum++;
			std::cout << listNum << "\t";
			this->StudentRoster[i]->Print();
		}
	}

	//Allow function to be used independently of current use case,
		//i.e. to leave window open.
	EndList(holdWindow);

	return;
}

//Used at end of list outputs, to either hold the window open and require user to
	//press enter, or to continue automatically.
	//Allows function to be used independently of current use case, i.e. to leave
	//window open.	
//Would like to include in separate file (as I would like to give main() its own
	//file),
	//but project specs explicitly require only the files included.
void EndList(const bool holdWindow) {
	if (holdWindow) {
		std::cout << "End of list. Press enter to continue." << std::endl
			<< std::endl;
		std::cin.get();
	}
	else {
		std::cout << "End of list." << std::endl << std::endl;
	}

	return;
}

//Maps Degree enum to string equivalent.
std::string DegToStr(const Degree degreeType) {
	DegMapToStr degMapToStr; //Or strMapToDeg? Which is said to be mapped to which?
	degMapToStr[Degree::SECURITY] = "SECURITY";
	degMapToStr[Degree::NETWORK] = "NETWORK";
	degMapToStr[Degree::SOFTWARE] = "SOFTWARE";

	return degMapToStr[degreeType];
}

//Would like to include in separate file, but project specs explicitly require
	//only the files included.
int main() {
	const std::string studentData[] = {
		"A1,John,Smith,John1989@gm ail.com,20,30,35,40,SECURITY",
		"A2,Suzan,Erickson,Erickson_1990@gmailcom,19,50,30,40,NETWORK",
		"A3,Jack,Napoli,The_lawyer99yahoo.com,19,20,40,33,SOFTWARE",
		"A4,Erin,Black,Erin.black@comcast.net,22,50,58,40,SECURITY",
		"A5,Kaleb,Coberly,kcoberl@wgu.edu,38,4,10,400,SOFTWARE"
	};

	const unsigned int srcArrLen = 5;
	const unsigned int numOfFields = 9;
	const unsigned int maxRostLen = 31;

	//"1.  Print out to the screen, via your application, the course title, the programming language used, your student ID, and your name.
	//"2.  Create an instance of the Roster class called classRoster.
	//"3.  Add each student to classRoster.
	//"4.  Convert the following pseudo code to complete the rest of the main() function :
		//"classRoster.printAll();
		//"classRoster.printInvalidEmails();
		//"loop through classRosterArray and for each element:
			//"classRoster.printAverageDaysInCourse(/*current_object's student id*/);
		//"classRoster.printByDegreeProgram(SOFTWARE);
		//"classRoster.remove("A3");
		//"classRoster.remove("A3");
		//"expected: the above line should print a message saying such a student with this ID was not found.
	//"5.  Call the destructor to release the Roster memory.

	//I threw in a lot of extra stuff. There is a whole lot more I would have fun throwing in,
		//like operator overrides and recursive functions,
		//but in the interest of time, I'm submitting this as is.
		//It could use some cleaning up for readability, mostly fitting lines to the margins,
		//and maybe finding a few places where the code could be a touch more efficient.
		//That said, in addition to adding extras features to demo,
		//I spent a good deal of time considering real-life issues,
		//like where I could cut down on computational and storage overhead,
		//how to maintain data integrity, and how to handle a broad range of use cases.


	//"1.  Print out to the screen, via your application, the course title, the programming language used, your student ID, and your name.
	std::cout << "C867 Scripting and Programming - Applications (C++)"
		<< std::endl;
	std::cout << "Final project: \"Class Roster\"" << std::endl;
	std::cout << "Kaleb Coberly, SID 001114541" << std::endl << std::endl
		<< std::endl;

	//"2.  Create an instance of the Roster class called classRoster.
	//"3.  Add each student to classRoster."
		//My plan, to be handled upon instantiation (though I've designed the
			//roster object to be able to be populated after instantiation as well if needed, by additional string arrays of student records, or by single string records, or by properly typed fields):
		//Construct roster, passing studentData (as pointer to first element).
			//Inside construction, iterate through array, calling AddByRecordStr() for each element.
				//Inside AddByRecordStr(), parse the record into proper data types, and pass to AddByField().
					//Inside AddByField(), construct students, and add their pointers to roster member array.
	try {
		//Set window size, since the default window is too small to accomodate
			//formatting. Default size drops endl etc., which is not remedied upon window
			//expansion.
		HWND consWin = GetConsoleWindow();
		//MoveWindow(window_handle, x, y, width, height, redraw_window);
		MoveWindow(consWin, 0, 0, 1000, 1000, TRUE);

		Roster* classRoster = new Roster(studentData, srcArrLen, numOfFields,
			maxRostLen);

		//"4.  Convert the following pseudo code to complete the rest of the
			//main() function :
		classRoster->PrintAll(false);
		classRoster->PrintInvalidEmails(false);
		classRoster->PrintAllAvDays(false);
		classRoster->PrintByDegreeProgram(Degree::SOFTWARE, false);
		classRoster->Remove("A3");
		classRoster->Remove("A3");
		//"Expected: the above line should print a message saying such a student
			//with this ID was not found.

	//"5.  Call the destructor to release the Roster memory.
		delete classRoster;
		classRoster = nullptr; //Only necessary if main() continues after this,
			//which you are assuming it does if you're going to the trouble of
			//freeing the memory.
	}

	catch (std::runtime_error & excpt) {
		std::cout << excpt.what() << std::endl;
	}
	catch (std::invalid_argument & excpt) {
		std::cout << excpt.what() << std::endl;
	}
	catch (std::out_of_range & excpt) {
		std::cout << excpt.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unidentified exception." << std::endl;
	}

	std::cout << "End of program. Press enter to exit." << std::endl;
	std::cin.get();

	return 0;
}


/*
Create a program that converts the array of strings found in the studentData table to an array of student objects by doing the following :



A.Modify the studentData table to include your personal information as the last item.


B.Create a C++ project in your integrated development environment(IDE) with the following files :

•   degree.h

•   student.h and student.cpp

•   networkStudent.h and networkStudent.cpp

•   securityStudent.h and securityStudent.cpp

•   softwareStudent.h and softwareStudent.cpp

•   roster.h and roster.cpp


Note : There must be a total of 11 source code files.


	C.Define an enumerated data type Degree for the degree programs containing the following data elements SECURITY, NETWORKINGand SOFTWARE.


	Note : This information should be included in the degree.h file.


	D.For the Student class, do the following :

1.  Create the base class Student in the files student.h and student.cpp, which includes each  of the following variables :

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


	Note: Leave the implementation of the getDegreeProgram() function empty.


	3.  Create the three following classes as subclasses of Student, using the files created in part B :

•   SecurityStudent

•   NetworkStudent

•   SoftwareStudent

Each subclass should override the getDegreeProgram() function.Each subclass should have a data member to hold the enumerated type for the degree program using the types defined in part C.


E.Create a Roster class (roster.cpp) by doing the following :

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


	f.  public void printByDegreeProgram(int degreeProgram) that prints out student information for a degree program specified by an enumerated type


	F.Demonstrate the program’s required functionality by adding a void main() function to roster.cpp, which will contain the required function calls to achieve the following results :

1.  Print out to the screen, via your application, the course title, the programming language used, your student ID, and your name.

2.  Create an instance of the Roster class called classRoster.

3.  Add each student to classRoster.

4.  Convert the following pseudo code to complete the rest of the main() function :
	classRoster.printAll();
classRoster.printInvalidEmails();
Loop through classRosterArray and for each element:
classRoster.printAverageDaysInCourse(current_object's student id);
classRoster.printByDegreeProgram(SOFTWARE);
classRoster.remove("A3");
classRoster.remove("A3");
Expected: the above line should print a message saying such a student with this ID was not found.

5.  Call the destructor to release the Roster memory.





; gfsergfh; , ]
*/