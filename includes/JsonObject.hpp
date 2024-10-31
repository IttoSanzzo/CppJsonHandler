#ifndef JSONOBJECT_HPP
# define JSONOBJECT_HPP

// 0. Includes
#include "JsonHandler.hpp"

// 1. Class Declaration
class JsonObject {
	private:
	// M. Member Variables

	public:
	// C. Constructors
		~JsonObject(void);
		JsonObject(void);
		JsonObject(const JsonObject& src);
		JsonObject&	operator=(const JsonObject& src);
		JsonObject(std::string jsonString);

	public:
	// S. Setters
	// G. Getters
		std::string	TryGetValue(std::string objectName);

	public:
	// 0. Member Functions

	private:
	// 0. Private Functions

};

#endif