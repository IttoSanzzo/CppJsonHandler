#include "JsonHandler.hpp"

// D. Destructor
JsonObject::~JsonObject(void) {
	std::cout << "JsonObject Destructed" << std::endl;
}
// CC. Common Constructors
JsonObject::JsonObject(void) {
	std::cout << "JsonObject Default Constructor Called!" << std::endl;
}
JsonObject::JsonObject(const JsonObject& src) {
	(void)src;
}
JsonObject& JsonObject::operator=(const JsonObject& src) {
	(void)src;
	return (*this);
}

// OC. Other Contructors

// G. Getters
std::string	JsonObject::TryGetValue(std::string objectName) {
	(void)objectName;
	return ("");
}

// S. Setters

// 0. Member Functions