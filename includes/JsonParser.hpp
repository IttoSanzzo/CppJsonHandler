#ifndef JSONPARSER_HPP
# define JSONPARSER_HPP

// 0. Includes
#include "JsonHandler.hpp"

// 1. Class Declaration
class JsonParser {
	friend class JsonNode;
	private:
	// M. Member Variables
		std::string		parsingString;
		std::string		refinedString;
		std::string*	totalParts;
		JsonParser(const std::string& jsonString);
		~JsonParser(void);
	public:
	// C. Constructors
	// S. Setters
	// G. Getters

	public:
	// 0. Member Functions
		JsonNode	ReadJson(void);

	private:
	// 0. Private Functions
		bool		DoGlobalBrakets(const std::string& jsonString);
		size_t		DoNextElement(const size_t& startOfQuotes, JsonNode& jsonNode);
		TokenInfo	GetNextToken(const std::string& srcString, size_t startingPos = 0) const;
		TokenInfo	GetReverseNextToken(const std::string& srcString, size_t startingPos) const;
		size_t		GetNextDoubleQuotes(const std::string& srcString, size_t startingPos) const;
		void		NullFreeTotalParts(void);

};

#endif