#include "JsonHandler.hpp"

// D. Destructor
JsonParser::~JsonParser(void) {
	std::cout << "Json Reader Destructed" << std::endl;
}
// CC. Common Constructors
JsonParser::JsonParser(const std::string& jsonString) {
	this->parsingString = jsonString;
	this->globalIndex = 0;
	std::cout << "Json Reader Constructed" << std::endl;
}

// 0. Member Functions
JsonNode	JsonParser::ReadJson(void) {
	if (this->parsingString.empty() == true || this->DoGlobalBrakets(this->parsingString) == false)
		throw (JsonException("ReadJson..: Not a valid JSON."));
	// std::cout << "|" << this->parsingString << "|" << std::endl;
	JsonNode	buildingJsonNode;
	while (this->globalIndex != std::string::npos)//AQUIIIIIIIIIIIIIIIIIIIIII ESSE INCREMENTO QUEBRADO
	{
		this->DoNextElement(buildingJsonNode);
		this->DoNextElement(buildingJsonNode);
		this->DoNextElement(buildingJsonNode);
		this->DoNextElement(buildingJsonNode);
		this->DoNextElement(buildingJsonNode);
		this->globalIndex = std::string::npos;
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
void		JsonParser::DoNextElement(JsonNode& jsonNode) {
	this->DoElementName();
	TokenInfo colon = this->GetNextToken(this->parsingString, this->globalIndex + 1);
	if (colon.Type != ':')
		throw (JsonException("ReadJson..: Not a valid JSON."));
	this->globalIndex = colon.Position + 1;
	this->DoElementValue(jsonNode);
}
void		JsonParser::DoElementName(void) {
	TokenInfo startOfQuotes = this->GetNextToken(this->parsingString, this->globalIndex);
	if (startOfQuotes.Type != '"')
		throw (JsonException("ReadJson..: Not a valid JSON."));
	this->globalIndex = this->GetNextDoubleQuotes(this->parsingString, startOfQuotes.Position + 1);
	if (this->globalIndex == std::string::npos)
		throw (JsonException("ReadJson..: Not a valid JSON."));
	this->elementName = this->parsingString.substr(startOfQuotes.Position + 1, this->globalIndex - startOfQuotes.Position - 1);
	if (this->elementName.empty() == true || this->elementName.find('.') != std::string::npos)
		throw (JsonException("ReadJson..: Not a valid JSON."));
}
void		JsonParser::DoElementValue(JsonNode& jsonNode) {
	TokenInfo elementStart = this->GetNextToken(this->parsingString, this->globalIndex);
	this->globalIndex = elementStart.Position;
	switch (elementStart.Type) {
		case ('"'):
			this->PushStringElement(jsonNode);
		break;
		case ('t'):
			this->PushBoolElement(jsonNode, true);
		break;
		case ('f'):
			this->PushBoolElement(jsonNode, false);
		break;
		case ('{'):
			// this->PushChildElement(jsonNode);
		break;
		case ('['):
			// this->PushChildrenElement(jsonNode);
		break;
		default:
			if (elementStart.Type >= '0' && elementStart.Type <= '9')
				this->PushNumberElement(jsonNode);
			else
				throw (JsonException("ReadJson..: Not a valid JSON."));
		break;
	}
}
void		JsonParser::PushStringElement(JsonNode& jsonNode) {
	size_t endOfString = this->GetNextDoubleQuotes(this->parsingString, this->globalIndex + 1);
	if (endOfString == std::string::npos)
		throw (JsonException("ReadJson..: Not a valid JSON."));
	std::string value = this->parsingString.substr(this->globalIndex + 1, endOfString - this->globalIndex - 1); 
	this->globalIndex = this->GetNextSimpleColon(endOfString + 1);
	jsonNode.TryPushData(this->elementName, value);
}
void		JsonParser::PushBoolElement(JsonNode& jsonNode, const bool& type) {
	switch (type) {
		case (true):
			if (this->parsingString.substr(this->globalIndex, 4) != "true")
				throw (JsonException("ReadJson..: Not a valid JSON."));
			this->globalIndex += 4;
		break;
		case (false):
			if (this->parsingString.substr(this->globalIndex, 5) != "false")
				throw (JsonException("ReadJson..: Not a valid JSON."));
			this->globalIndex += 5;
		break;
	}
	this->globalIndex = this->GetNextSimpleColon(this->globalIndex);
	jsonNode.TryPushData(this->elementName, type);
}
void		JsonParser::PushNumberElement(JsonNode& jsonNode) {
	std::cout << "Push Number Entered!" << std::endl;
	std::string numberString;


	size_t	colon = this->parsingString.find(',', this->globalIndex);
	if (colon != std::string::npos)
		numberString = this->parsingString.substr(this->globalIndex, colon - this->globalIndex);
	else
		numberString = this->parsingString.substr(this->globalIndex);
	std::cout << "|" << numberString << "|" << std::endl;
	std::pair<DataValue, DataType>	numberData = this.GetNumberDataFromString(const std::string& numberString);
	jsonNode.TryPushData(JsonData(this->elementName, numberData.first, numberData.second));
	(void)jsonNode;
}
std::pair<DataValue, DataType>	JsonParser::GetNumberDataFromString(const std::string& numberString) {
	DataValue	value;
	DataType	type;
	short		dots = 0;
	for (size_t i = 0; i < numberString.size(); ++i) {
		if (numberString[i] == '.' && dots++ != 0)
			throw (JsonException("ReadJson..: Not a valid JSON."));

	}
	if (dots == 1) {
		// value.DoubleValue = ;
		return (std::make_pair(value, Double));
	}
	// value.IntValue = ;
	return (std::make_pair(value, Int));
}
size_t		JsonParser::GetNextSimpleColon(size_t currentIndex) {
	TokenInfo	colon = this->GetNextToken(this->parsingString, currentIndex);
	if (colon.Type != ',' && colon.Type != '\0')
		throw (JsonException("ReadJson..: Not a valid JSON."));
	return (colon.Position + 1);
}
TokenInfo	JsonParser::GetNextToken(const std::string& srcString, size_t startingPos) const {
	for (size_t i = startingPos; i < srcString.size(); ++i)
		switch (srcString[i]) {
			case ('"'):
				if (i == 0 || srcString[i - 1] != '\\')
					return (TokenInfo('"', i));
				continue;
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
	return (TokenInfo('\0', std::string::npos));
}
TokenInfo	JsonParser::GetReverseNextToken(const std::string& srcString, size_t startingPos) const {
	for (short i = startingPos; i >= 0; --i)
		switch (srcString[i]) {
			case ('"'):
				if (i == 0 || srcString[i - 1] != '\\')
					return (TokenInfo('"', i));
				continue;
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
	return (TokenInfo('\0', std::string::npos));
}
size_t		JsonParser::GetNextDoubleQuotes(const std::string& srcString, size_t startingPos) const {
	for (size_t i = startingPos; i < srcString.size(); ++i)
		if (srcString[i] == '"' && (i == 0 || srcString[i - 1] != '\\'))
			return (i);
	return (std::string::npos);
}