#include "JsonHandler.hpp"

// 0. Static Functions Protorypes
bool		IsNumber(const char& character);
std::string	ProcessEscapes(const std::string& sourceString);

// D. Destructor
JsonParser::~JsonParser(void) {}
// CC. Common Constructors
JsonParser::JsonParser(const std::string& jsonString) {
	this->ParsingString = jsonString;
	this->GlobalIndex = 0;
}

// 0. Member Functions
JsonNode	JsonParser::ReadJson(void) {
	if (this->ParsingString.empty() == true || this->DoGlobalBrakets(this->ParsingString) == false)
		throw (JsonException("ReadJson..: Not a valid JSON."));
	JsonNode	buildingJsonNode;
	while (this->GlobalIndex < this->ParsingString.size())
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
	this->ParsingString = this->ParsingString.substr(openingBracket.Position + 1, closingBracket.Position - openingBracket.Position - 1);
	return (true);
}
void		JsonParser::DoNextElement(JsonNode& jsonNode) {
	this->DoElementName();
	TokenInfo colon = this->GetNextToken(this->ParsingString, this->GlobalIndex + 1);
	if (colon.Type != ':')
		throw (JsonException("ReadJson..: Not a valid JSON."));
	this->GlobalIndex = colon.Position + 1;
	this->DoElementValue(jsonNode);
}
void		JsonParser::DoElementName(void) {
	TokenInfo startOfQuotes = this->GetNextToken(this->ParsingString, this->GlobalIndex);
	if (startOfQuotes.Type != '"')
		throw (JsonException("ReadJson..: Not a valid JSON."));
	this->GlobalIndex = this->GetNextDoubleQuotes(this->ParsingString, startOfQuotes.Position + 1);
	if (this->GlobalIndex == std::string::npos)
		throw (JsonException("ReadJson..: Not a valid JSON."));
	this->ElementName = this->ParsingString.substr(startOfQuotes.Position + 1, this->GlobalIndex - startOfQuotes.Position - 1);
	if (this->ElementName.empty() == true || this->ElementName.find('.') != std::string::npos)
		throw (JsonException("ReadJson..: Not a valid JSON."));
}
void		JsonParser::DoElementValue(JsonNode& jsonNode) {
	TokenInfo elementStart = this->GetNextToken(this->ParsingString, this->GlobalIndex);
	this->GlobalIndex = elementStart.Position;
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
		case ('['):
			this->PushChildrenElement(jsonNode);
		break;
		default:
			if (IsNumber(elementStart.Type) == true)
				this->PushNumberElement(jsonNode);
			else
				throw (JsonException("ReadJson..: Not a valid JSON."));
		break;
	}
}
void		JsonParser::PushStringElement(JsonNode& jsonNode) {
	size_t endOfString = this->GetNextDoubleQuotes(this->ParsingString, this->GlobalIndex + 1);
	if (endOfString == std::string::npos)
		throw (JsonException("ReadJson..: Not a valid JSON."));
	std::string value = this->ParsingString.substr(this->GlobalIndex + 1, endOfString - this->GlobalIndex - 1);
	this->GlobalIndex = this->GetNextElementIndex(this->ParsingString, endOfString + 1);
	jsonNode.TryPushData(this->ElementName, ProcessEscapes(value));
}
void		JsonParser::PushBoolElement(JsonNode& jsonNode, const bool& type) {
	switch (type) {
		case (true):
			if (this->ParsingString.substr(this->GlobalIndex, 4) != "true")
				throw (JsonException("ReadJson..: Not a valid JSON."));
			this->GlobalIndex += 4;
		break;
		case (false):
			if (this->ParsingString.substr(this->GlobalIndex, 5) != "false")
				throw (JsonException("ReadJson..: Not a valid JSON."));
			this->GlobalIndex += 5;
		break;
	}
	this->GlobalIndex = this->GetNextElementIndex(this->ParsingString, this->GlobalIndex);
	jsonNode.TryPushData(this->ElementName, type);
}
void		JsonParser::PushNumberElement(JsonNode& jsonNode) {
	std::string numberString;
	size_t	comma = this->ParsingString.find(',', this->GlobalIndex);
	if (comma != std::string::npos) {
		numberString = this->ParsingString.substr(this->GlobalIndex, comma - this->GlobalIndex);
		this->GlobalIndex = comma + 1;
	}
	else {
		numberString = this->ParsingString.substr(this->GlobalIndex);
		this->GlobalIndex = this->ParsingString.size();
	}
	std::pair<DataValue, DataType>	numberData = this->GetNumberDataFromString(numberString);
	jsonNode.TryPushData(JsonData(this->ElementName, numberData.first, numberData.second));
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
	size_t	closingBracket = this->GetClosingCurlyBraket(this->ParsingString, this->GlobalIndex + 1);
	if (closingBracket == std::string::npos)
		throw (JsonException("ReadJson..: Not a valid JSON."));
	std::string	childJsonString = this->ParsingString.substr(this->GlobalIndex, closingBracket - this->GlobalIndex + 1);
	this->GlobalIndex = this->GetNextElementIndex(this->ParsingString, closingBracket + 1);
	jsonNode.TryPushData(this->ElementName, JsonNode::TryParseJsonFromString(childJsonString));
}
void		JsonParser::PushChildrenElement(JsonNode& jsonNode) {
	size_t	closingBracket = this->GetClosingSquareBraket(this->ParsingString, this->GlobalIndex + 1);
	if (closingBracket == std::string::npos)
		throw (JsonException("ReadJson..: Not a valid JSON."));
	JsonChildren	jsonChildren(this->ElementName);
	std::string		childenParsingString = this->ParsingString.substr(this->GlobalIndex + 1, closingBracket - this->GlobalIndex - 1);
	for (size_t childIndex = 0; childIndex < childenParsingString.size();) {
		TokenInfo	openingChildBraket = this->GetNextToken(childenParsingString, childIndex);
		if (openingChildBraket.Type != '{')
			throw (JsonException("ReadJson..: Not a valid JSON."));
		size_t	closingChildBraket = this->GetClosingCurlyBraket(childenParsingString, openingChildBraket.Position + 1);
		if (closingChildBraket == std::string::npos)
			throw (JsonException("ReadJson..: Not a valid JSON."));
		JsonNode	childNode = JsonNode::TryParseJsonFromString(childenParsingString.substr(openingChildBraket.Position, closingChildBraket - openingChildBraket.Position + 1));
		jsonChildren.PushChild(childNode);
		childIndex = this->GetNextElementIndex(childenParsingString, closingChildBraket + 1);
	}
	this->GlobalIndex = this->GetNextElementIndex(this->ParsingString, closingBracket + 1);
	jsonNode.TryPushData(this->ElementName, jsonChildren);
}
size_t		JsonParser::GetNextElementIndex(const std::string& parsingString, const size_t& currentIndex) {
	TokenInfo	comma = this->GetNextToken(parsingString, currentIndex);
	if (comma.Type != ',' && comma.Type != '\0')
		throw (JsonException("ReadJson..: Not a valid JSON."));
	if (comma.Type == '\0')
		return (parsingString.size());
	return (comma.Position + 1);
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
size_t		JsonParser::GetClosingCurlyBraket(const std::string& bracketString, size_t currentIndex) {
	while (currentIndex < bracketString.size()) {
		switch (bracketString[currentIndex]) {
			case ('}'):
				return (currentIndex);
			break;
			case ('['):
				currentIndex = this->GetClosingSquareBraket(bracketString, currentIndex + 1);
				if (currentIndex == std::string::npos)
					return (std::string::npos);
			break;
			case ('{'):
				currentIndex = this->GetClosingCurlyBraket(bracketString, currentIndex + 1);
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
size_t		JsonParser::GetClosingSquareBraket(const std::string& bracketString, size_t currentIndex) {
	while (currentIndex < bracketString.size()) {
		switch (bracketString[currentIndex]) {
			case (']'):
				return (currentIndex);
			break;
			case ('['):
				currentIndex = this->GetClosingSquareBraket(bracketString, currentIndex + 1);
				if (currentIndex == std::string::npos)
					return (std::string::npos);
			break;
			case ('{'):
				currentIndex = this->GetClosingCurlyBraket(bracketString, currentIndex + 1);
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
bool		IsNumber(const char& character) {
	return (character >= '0' && character <= '9');
}
std::string	ProcessEscapes(const std::string& sourceString) {
    std::string	result;
    result.reserve(sourceString.size());
    for (size_t i = 0; i < sourceString.size(); ++i) {
        if (sourceString[i] == '\\' && i + 1 < sourceString.size()) {
            switch (sourceString[i + 1]) {
                case ('n'):
					result.push_back('\n');
					++i;
				break;
                case ('t'):
					result.push_back('\t');
					++i;
				break;
                case ('r'):
					result.push_back('\r');
					++i;
				break;
                case ('\\'):
					result.push_back('\\');
					++i;
				break;
                case ('"'):
					result.push_back('\"');
					++i;
				break;
                default:
					result.push_back(sourceString[i]);
				break;
            }
        } else
            result.push_back(sourceString[i]);
    }
    return result;
}