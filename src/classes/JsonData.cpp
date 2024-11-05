#include "JsonHandler.hpp"

// D. Destructor
JsonData::~JsonData(void) {
	switch (this->Type) {
		case (String):
			if (this->Value.StringValue != NULL)
				delete this->Value.StringValue;
		break;
		case (Child):
			if (this->Value.ChildValue != NULL)
				delete this->Value.ChildValue;
		break;
		case (Children):
			if (this->Value.ChildrenValue != NULL)
				delete this->Value.ChildrenValue;
		break;
		default:
		break;
	}
}
// CC. Common Constructors
JsonData::JsonData(void) {
	this->Name = "data";
	this->Type = None;
}
JsonData::JsonData(const JsonData& src) {
	this->DeepCopy(src);
}
JsonData& JsonData::operator=(const JsonData& src) {
	this->DeepCopy(src);
	return (*this);
}
// OC. Other Contructors
JsonData::JsonData(const std::string& name, const DataValue& value, const DataType& type) {
	this->Name = name;
	this->Type = type;
	this->Value = value;
}
JsonData::JsonData(const std::string& name, const bool& value) {
	this->Name = name;
	this->SetValue(value);
}
JsonData::JsonData(const std::string& name, const int& value) {
	this->Name = name;
	this->SetValue(value);
}
JsonData::JsonData(const std::string& name, const double& value) {
	this->Name = name;
	this->SetValue(value);
}
JsonData::JsonData(const std::string& name, const std::string& value) {
	this->Name = name;
	this->Type = None;
	this->SetValue(value);
}
JsonData::JsonData(const std::string& name, const JsonNode& value) {
	this->Name = name;
	this->Type = None;
	this->SetValue(value);
}
JsonData::JsonData(const std::string& name, const JsonNode* value) {
	this->Name = name;
	this->Type = None;
	this->SetValue(value);
}

// S. Setters
void	JsonData::SetName(const std::string& name) {
	this->Name = name;
}
void	JsonData::SetValue(const DataValue& value, const DataType& type) {
	if (this->Type == String && this->Value.StringValue != NULL)
		delete this->Value.StringValue;
	else if (this->Type == Child && this->Value.ChildValue != NULL)
		delete this->Value.ChildValue;
	this->Type = type;
	this->Value = value;
}
void	JsonData::SetValue(const bool& value) {
	this->Type = Bool;
	this->Value.BoolValue = value;
}
void	JsonData::SetValue(const int& value) {
	this->Type = Int;
	this->Value.IntValue = value;
}
void	JsonData::SetValue(const double& value) {
	this->Type = Double;
	this->Value.DoubleValue = value;
}
void	JsonData::SetValue(const std::string& value) {
	if (this->Type == String && this->Value.StringValue != NULL)
		delete this->Value.StringValue;
	this->Type = String;
	this->Value.StringValue = new std::string(value);
}
void	JsonData::SetValue(const JsonNode& value) {
	if (this->Type == Child && this->Value.ChildValue != NULL)
		delete this->Value.ChildValue;
	this->Type = Child;
	this->Value.ChildValue = new JsonNode(value);
}
void	JsonData::SetValue(const JsonNode* value) {
	if (this->Type == Child && this->Value.ChildValue != NULL)
		delete this->Value.ChildValue;
	this->Type = Child;
	this->Value.ChildValue = (JsonNode*)value;
}

// G. Getters
std::string		JsonData::GetName(void) const {
	return (this->Name);
}
DataType		JsonData::GetType(void) const {
	return (this->Type);
}
DataValue		JsonData::GetValue(void) const {
	return (this->Value);
}
bool			JsonData::TryGetBool(void) {
	if (this->Type == Bool)
		return (this->Value.BoolValue);
	throw JsonException("TryGetBool..: Not this type, the correct one is: '" + this->DataTypeName() + "'.");
}
int				JsonData::TryGetInt(void) {
	if (this->Type == Int)
		return (this->Value.IntValue);
	throw JsonException("TryGetInt..: Not this type, the correct one is: '" + this->DataTypeName() + "'.");
}
double			JsonData::TryGetDouble(void) {
	if (this->Type == Double)
		return (this->Value.DoubleValue);
	throw JsonException("TryGetDouble..: Not this type, the correct one is: '" + this->DataTypeName() + "'.");
}
std::string		JsonData::TryGetString(void) {
	if (this->Type == String)
		return (*this->Value.StringValue);
	throw JsonException("TryGetString..: Not this type, the correct one is: '" + this->DataTypeName() + "'.");
}
JsonNode		JsonData::TryGetChild(void) {
	if (this->Type == Child)
		return (*this->Value.ChildValue);
	throw JsonException("TryGetChild..: Not this type, the correct one is: '" + this->DataTypeName() + "'.");
}
JsonChildren	JsonData::TryGetChildren(void) {
	if (this->Type == Children)
		return (*this->Value.ChildrenValue);
	throw JsonException("TryGetChildren..: Not this type, the correct one is: '" + this->DataTypeName() + "'.");
}
// 0. Member Functions
std::string	JsonData::ToString(const bool& withLineBreaks, const size_t& depth) const {
	switch (this->Type) {
		case (Bool):
			return (this->ToString(this->Value.BoolValue));
		break;
		case (Int):
			return (this->ToString(this->Value.IntValue));
		break;
		case (Double):
			return (this->ToString(this->Value.DoubleValue));
		break;
		case (String):
			return (this->ToString(this->Value.StringValue));
		break;
		case (Child):
			return (this->ToString(this->Value.ChildValue, withLineBreaks, depth));
		break;
		case (Children):
			return (this->ToString(this->Value.ChildrenValue, withLineBreaks, depth));
		break;
		default:
			return ("UNKNOWN ERROR");
		break;
	}
}

// 1. Private Functions
void		JsonData::DeepCopy(const JsonData& src) {
	this->Name = src.Name;
	this->Type = src.Type;
	switch (src.Type) {
		case (String):
			this->Value.StringValue = new std::string(*src.Value.StringValue);
		break;
		case (Child):
			this->Value.ChildValue = new JsonNode(*src.Value.ChildValue);
		break;
		case (Children):
			this->Value.ChildrenValue = new JsonChildren(*src.Value.ChildrenValue);
		break;
		default:
			this->Value = src.Value;
		break;
	}
}
std::string	JsonData::DataTypeName() {
	switch (this->Type) {
		case (Bool):
			return "Bool";
		case (Int):
			return "Int";
		case (Double):
			return "Double";
		case (String):
			return "String";
		case (Child):
			return "Child";
		case (Children):
			return "Children";
		default:
			return "Unknown";
	}
}
std::string	JsonData::DataTypeName(const DataType& type) {
	switch (type) {
		case (Bool):
			return "Bool";
		case (Int):
			return "Int";
		case (Double):
			return "Double";
		case (String):
			return "String";
		case (Child):
			return "Child";
		case (Children):
			return "Children";
		default:
			return "Unknown";
	}
}
std::string	JsonData::ToString(const bool& value) const {
	std::string	jsonString = "\"";
	jsonString += this->Name;
	jsonString += "\": ";
	if (value == true)
		jsonString += "true";
	else
		jsonString += "false";
	return (jsonString);
}
std::string	JsonData::ToString(const int& value) const {
	std::ostringstream	oss;
	oss << value;
	std::string	jsonString = "\"";
	jsonString += this->Name;
	jsonString += "\": ";
	jsonString += oss.str();
	return (jsonString);
}
std::string	JsonData::ToString(const double& value) const {
	std::ostringstream	oss;
	oss << value;
	std::string	jsonString = "\"";
	jsonString += this->Name;
	jsonString += "\": ";
	jsonString += oss.str();
	return (jsonString);
}
std::string	JsonData::ToString(const std::string* value) const {
	std::string	jsonString = "\"";
	jsonString += this->Name;
	jsonString += "\": \"";
	jsonString += *value;
	jsonString += "\"";
	return (jsonString);
}
std::string	JsonData::ToString(const JsonNode* value, const bool& withLineBreaks, const size_t& depth) const {
	std::string	jsonString = "\"";
	jsonString += this->Name;
	jsonString += "\": ";
	jsonString += value->ToString(withLineBreaks, depth);
	return (jsonString);
}
std::string	JsonData::ToString(const JsonChildren* value, const bool& withLineBreaks, const size_t& depth) const {
	std::string	jsonString = "\"";
	jsonString += this->Name;
	jsonString += "\": [";
	if (value->Size == 0)
		return (jsonString + ']');
	if (withLineBreaks == true)
		jsonString += '\n';
	for (size_t childIndex = 0; childIndex < value->Size; ++childIndex) {
		if (withLineBreaks == true)
			for (size_t tabs = 0; tabs < depth; ++tabs)
				jsonString += '\t';
		jsonString += value->Childs->GetPos(childIndex)->Data->Value.ChildValue->ToString(withLineBreaks, depth + 1);
		if (childIndex < value->Size - 1) {
			if (withLineBreaks == true)
				jsonString += ",\n";
			else
				jsonString += ", ";
		}
	}
	if (withLineBreaks == true) {
		jsonString += '\n';
		for (size_t tabs = 1; tabs < depth; ++tabs)
			jsonString += '\t';
	}
	return (jsonString + ']');
}