//"C.Define an enumerated data type Degree for the degree programs containing
	//the following data elements SECURITY, NETWORKING and SOFTWARE."
#pragma once
#include <string>
#include <array>
#include <map>
//Changed "NETWORKING" to "NETWORK" since input data array uses "NETWORK."
//Base class "constructor using all  of the input parameters provided in the table"
	//i.e. including DegreeType
	//"Note: Degree type should be populated in subclasses only."
enum class Degree : char { SECURITY, NETWORK, SOFTWARE };

using DegMapToStr = std::map<Degree, std::string>;