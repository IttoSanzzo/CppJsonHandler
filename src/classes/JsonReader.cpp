#include "JsonHandler.hpp"

// D. Destructor
JsonReader::~JsonReader(void) {
	std::cout << "Json Reader Destructed" << std::endl;
}
// CC. Common Constructors
JsonReader::JsonReader(void) {
	std::cout << "Json Reader Constructed" << std::endl;
}
JsonReader::JsonReader(JsonReader& src) {
	(void)src;
}
JsonReader& JsonReader::operator=(JsonReader& src) {
	(void)src;
	return (*this);
}

// OC. Other Contructors

// G. Getters

// S. Setters

// 0. Member Functions
void	JsonReader::test(void) {
	std::cout << "Skyreach" << std::endl;
}