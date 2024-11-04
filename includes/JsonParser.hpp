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
		std::string		elementName;
		size_t			globalIndex;
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
		void		DoNextElement(JsonNode& jsonNode);
		void		DoElementName(void);
		void		DoElementValue(JsonNode& jsonNode);
		void		PushStringElement(JsonNode& jsonNode);
		void		PushBoolElement(JsonNode& jsonNode, const bool& type);
		void		PushNumberElement(JsonNode& jsonNode);
		std::pair<DataValue, DataType>	GetNumberDataFromString(const std::string& numberString);
		void		PushChildElement(JsonNode& jsonNode);
		size_t		GetNextElementIndex(size_t currentIndex);
		TokenInfo	GetNextToken(const std::string& srcString, size_t startingPos) const;
		TokenInfo	GetReverseNextToken(const std::string& srcString, size_t startingPos) const;
		size_t		GetNextDoubleQuotes(const std::string& srcString, size_t startingPos) const;
		size_t		GetClosingBraket(const std::string& bracketString, size_t currentIndex);
};

#endif