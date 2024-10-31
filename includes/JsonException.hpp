#ifndef JSONEXCEPTION_HPP
# define JSONEXCEPTION_HPP

#include "JsonHandler.hpp"

// 1. Class Declaration
class JsonException : public std::exception {
	private:
	// M. Member Variables
    	std::string	message;

	public:
		virtual ~JsonException() throw() {}
	// C. Constructors
		// CC. Common Contructors
    	JsonException(const std::string& msg) : message(msg) {}
		// 0. Member Functions
    	virtual const char* what() const throw() {
        	return message.c_str();
    	}
};

#endif