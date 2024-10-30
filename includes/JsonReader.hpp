#ifndef JSONREADER_HPP
# define JSONREADER_HPP

// 0. Includes
#include "JsonHandler.hpp"

// 1. Class Declaration
class JsonReader {
	private:
	// M. Member Variables

	public:
	// C. Constructors
		~JsonReader(void);
		JsonReader(void);
		JsonReader(JsonReader& src);
		JsonReader&	operator=(JsonReader& src);
		JsonReader(std::string jsonString);
	// S. Setters
	// G. Getters

	public:
	// 0. Member Functions

		void	test(void);

	private:
	// 0. Private Functions

};

#endif