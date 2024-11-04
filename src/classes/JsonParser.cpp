#include "JsonHandler.hpp"

// 0. Static Functions Protorypes
bool	IsNumber(const char& character);

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
	JsonNode	buildingJsonNode;
	while (this->globalIndex < this->parsingString.size())
		this->DoNextElement(buildingJsonNode);
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
	std::cout << "|" << this->elementName << "|\n";
	TokenInfo colon = this->GetNextToken(this->parsingString, this->globalIndex + 1);
	if (colon.Type != ':')
		throw (JsonException("ReadJson..: Not a valid JSON."));
	this->globalIndex = colon.Position + 1;
	this->DoElementValue(jsonNode);
	if (this->globalIndex == this->parsingString.size())
		std::cout << "LASTONE HERE" << std::endl;
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
			this->PushChildElement(jsonNode);
		break;
		// case ('['):
			// this->PushChildrenElement(jsonNode);
		// break;
		default:
			if (IsNumber(elementStart.Type) == true)
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
	this->globalIndex = this->GetNextElementIndex(endOfString);
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
	this->globalIndex = this->GetNextElementIndex(this->globalIndex);
	jsonNode.TryPushData(this->elementName, type);
}
void		JsonParser::PushNumberElement(JsonNode& jsonNode) {
	std::string numberString;
	size_t	comma = this->parsingString.find(',', this->globalIndex);
	if (comma != std::string::npos) {
		numberString = this->parsingString.substr(this->globalIndex, comma - this->globalIndex);
		this->globalIndex = comma + 1;
	}
	else {
		numberString = this->parsingString.substr(this->globalIndex);
		this->globalIndex = this->parsingString.size();
	}
	std::pair<DataValue, DataType>	numberData = this->GetNumberDataFromString(numberString);
	jsonNode.TryPushData(JsonData(this->elementName, numberData.first, numberData.second));
}
std::pair<DataValue, DataType>	JsonParser::GetNumberDataFromString(const std::string& numberString) {
	DataValue	value;
	bool		dots = false;
	size_t		lastNumberIndex = -1;
	while (++lastNumberIndex < numberString.size() && (IsNumber(numberString[lastNumberIndex]) == true || numberString[lastNumberIndex] == '.')) {
		if (numberString[lastNumberIndex] == '.' && ((dots = !dots ) != true || lastNumberIndex + 1 == numberString.size()))
			throw (JsonException("ReadJson..: Not a valid JSON."));
	}
	TokenInfo	checkRemainingCharacters = this->GetNextToken(numberString, lastNumberIndex);
	if (checkRemainingCharacters.Type != '\0')
		throw (JsonException("ReadJson..: Not a valid JSON."));
	if (dots == true) {
		std::stringstream(numberString.substr(0, lastNumberIndex)) >> value.DoubleValue;
		return (std::make_pair(value, Double));
	}
	std::stringstream(numberString.substr(0, lastNumberIndex)) >> value.IntValue;
	return (std::make_pair(value, Int));
}
void		JsonParser::PushChildElement(JsonNode& jsonNode) {
	std::string	childJsonString;

	size_t	closingBracket = this->GetClosingBraket(this->parsingString, this->globalIndex + 1);
	if (closingBracket == std::string::npos)
		throw (JsonException("ReadJson..: Not a valid JSON."));
	childJsonString = this->parsingString.substr(this->globalIndex, closingBracket - this->globalIndex + 1);
	this->globalIndex = this->GetNextElementIndex(closingBracket);
	jsonNode.TryPushData(this->elementName, JsonNode::TryParseJsonFromString(childJsonString));
}
size_t		JsonParser::GetNextElementIndex(size_t currentIndex) {
	TokenInfo	colon = this->GetNextToken(this->parsingString, currentIndex);
	if (colon.Type != ',' && colon.Type != '\0')
		throw (JsonException("ReadJson..: Not a valid JSON."));
	if (colon.Type == '\0')
		return (this->parsingString.size());
	return (colon.Position + 1);
}
TokenInfo	JsonParser::GetNextToken(const std::string& srcString, size_t startingPos) const {
	for (size_t i = startingPos; i < srcString.size(); ++i)
		switch (srcString[i]) {
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
size_t		JsonParser::GetClosingBraket(const std::string& bracketString, size_t currentIndex) {
	while (currentIndex < bracketString.size()) {
		switch (bracketString[currentIndex]) {
			case ('}'):
				return (currentIndex);
			break;
			case ('{'):
				currentIndex = this->GetClosingBraket(bracketString, currentIndex + 1);
				if (currentIndex == std::string::npos)
					return (std::string::npos);
			break;
			case ('"'):
				currentIndex = this->GetNextDoubleQuotes(bracketString, currentIndex + 1);
				if (currentIndex == std::string::npos)
					return (std::string::npos);
			break;
		}
		currentIndex++;
	}
	return (std::string::npos);
}

// 2. Static Functions
bool	IsNumber(const char& character) {
	return (character >= '0' && character <= '9');
}