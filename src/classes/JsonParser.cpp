#include "JsonHandler.hpp"

// D. Destructor
JsonParser::~JsonParser(void) {
	this->NullFreeTotalParts();
	std::cout << "Json Reader Destructed" << std::endl;
}
// CC. Common Constructors
JsonParser::JsonParser(const std::string& jsonString) {
	this->parsingString = jsonString;
	this->totalParts = NULL;
	std::cout << "Json Reader Constructed" << std::endl;
}

// 0. Member Functions
JsonNode	JsonParser::ReadJson(void) {
	if (this->parsingString.empty() == true || this->DoGlobalBrakets(this->parsingString) == false)
		throw (JsonException("ReadJson..: Not a valid JSON."));
	// std::cout << "|" << this->parsingString << "|" << std::endl;
	JsonNode	buildingJsonNode;
	for (size_t globalIndex = 0; globalIndex != std::string::npos; globalIndex = std::string::npos) { //AQUIIIIIIIIIIIIIIIIIIIIII ESSE INCREMENTO QUEBRADO
		TokenInfo token = this->GetNextToken(this->parsingString, 0);
		if (token.Type != '"')
			throw (JsonException("ReadJson..: Not a valid JSON."));
		globalIndex = this->DoNextElement(token.Position, buildingJsonNode);
	}
	return (buildingJsonNode);
}

// 1. Private Functions
bool		JsonParser::DoGlobalBrakets(const std::string& jsonString) {
	TokenInfo	openingBracket = this->GetNextToken(jsonString, 0);
	if (openingBracket.Type != '{')
		return (false);
	TokenInfo	closingBracket = this->GetReverseNextToken(jsonString, jsonString.size() - 1);
	if (closingBracket.Type != '}')
		return (false);
	this->parsingString = this->parsingString.substr(openingBracket.Position + 1, closingBracket.Position - openingBracket.Position - 1);
	return (true);
}
size_t		JsonParser::DoNextElement(const size_t& startOfQuotes, JsonNode& jsonNode) {
	size_t endOfQuotes = this->GetNextDoubleQuotes(this->parsingString, startOfQuotes + 1);
	if (endOfQuotes == std::string::npos)
		throw (JsonException("ReadJson..: Not a valid JSON."));
	std::string	name = this->parsingString.substr(startOfQuotes + 1, endOfQuotes - startOfQuotes - 1);
	std::cout << "|" << name << "|\n";
	TokenInfo colon = this->GetNextToken(this->parsingString, endOfQuotes + 1);
	if (colon.Type != ':')
		throw (JsonException("ReadJson..: Not a valid JSON."));
	TokenInfo conma = this->GetNextToken(this->parsingString, colon.Position + 1);
	std::cout << "|Checkpoint|\n";
	if (colon.Type != ',' && colon.Type != '\0')
		throw (JsonException("ReadJson..: Not a valid JSON."));
	std::string	value = this->parsingString.substr(colon.Position + 1, conma.Position - colon.Position - 1);
	std::cout << "|" << value << "|\n";

	/*
	std::pair<DataValue, DataType>	rawData;
	try	{
		jsonNode.TryPushData(JsonData(name, rawData.first, rawData.second));
	} catch(JsonException ex) {
		throw (JsonException(ex));
	}
	*/
(void)jsonNode;
	return (conma.Position);
}
TokenInfo	JsonParser::GetNextToken(const std::string& srcString, size_t startingPos) const {
	for (size_t i = startingPos; i < srcString.size(); ++i) {
		switch (srcString[i]) {
			case ('"'):
				if (i == 0 || srcString[i - 1] != '\\')
					return (TokenInfo('"', i));
				continue;
			break;
			case (':'):
				return (TokenInfo(':', i));
			break;
			case ('{'):
				return (TokenInfo('{', i));
			break;
			case ('}'):
				return (TokenInfo('}', i));
			break;
			case ('\t'):
				continue;
			break;
			case (' '):
				continue;
			break;
			case ('\n'):
				continue;
			break;
			default:
				return (TokenInfo(srcString[i], i));
			break;
		}
	}
	return (TokenInfo('\0', std::string::npos));
}
TokenInfo	JsonParser::GetReverseNextToken(const std::string& srcString, size_t startingPos) const {
	for (short i = startingPos; i >= 0; --i) {
		switch (srcString[i]) {
			case ('"'):
				if (i == 0 || srcString[i - 1] != '\\')
					return (TokenInfo('"', i));
				continue;
			break;
			case (':'):
				return (TokenInfo(':', i));
			break;
			case ('{'):
				return (TokenInfo('{', i));
			break;
			case ('}'):
				return (TokenInfo('}', i));
			break;
			case ('\t'):
				continue;
			break;
			case (' '):
				continue;
			break;
			case ('\n'):
				continue;
			break;
			default:
				return (TokenInfo(srcString[i], i));
			break;
		}
	}
	return (TokenInfo('\0', std::string::npos));
}
size_t		JsonParser::GetNextDoubleQuotes(const std::string& srcString, size_t startingPos) const {
	for (size_t i = startingPos; i < srcString.size(); ++i) {
		if (srcString[i] == '"' && (i == 0 || srcString[i - 1] != '\\'))
			return (i);
	}
	return (std::string::npos);
}



void	JsonParser::NullFreeTotalParts(void) {
	if (this->totalParts != NULL) {
		delete this->totalParts;
		this->totalParts = NULL;
	}
}