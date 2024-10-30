#include "JsonHandler.hpp"

// D. Destructor
JsonObject::~JsonObject(void) {
	std::cout << "JsonObject Destructed" << std::endl;
}
// CC. Common Constructors
JsonObject::JsonObject(void) {
	this->OriginalString = "";
	this->RawString = "";
	std::cout << "JsonObject Default Constructor Called!" << std::endl;
}
JsonObject::JsonObject(const JsonObject& src) {
	this->OriginalString = src.OriginalString;
	this->RawString = src.RawString;
}
JsonObject& JsonObject::operator=(const JsonObject& src) {
	this->OriginalString = src.OriginalString;
	this->RawString = src.RawString;
	return (*this);
}

// OC. Other Contructors
JsonObject::JsonObject(std::string jsonString) {
	this->OriginalString = jsonString;
	std::cout << "JsonObject String Constructor Called!" << std::endl;
}

// G. Getters
std::string	JsonObject::GetOriginalString(void) {
	return (this->OriginalString);
}
std::string	JsonObject::GetRawString(void) {
	return (this->RawString);
}
std::string	JsonObject::TryGetValue(std::string objectName) {
	(void)objectName;
	return ("");
}

// S. Setters

// 0. Member Functions