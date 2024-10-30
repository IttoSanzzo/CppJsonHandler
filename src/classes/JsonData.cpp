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
	this->Name = src.Name;
	this->Type = src.Type;
	this->Value = src.Value;
	if (this->Type == String)
		this->Value.StringValue = new std::string(*src.Value.StringValue);
}
JsonData& JsonData::operator=(const JsonData& src) {
	this->Name = src.Name;
	this->Type = src.Type;
	this->Value = src.Value;
	if (this->Type == String)
		this->Value.StringValue = new std::string(*src.Value.StringValue);
	if (this->Type == Child)
		this->Value.ChildValue = new JsonNode(*src.Value.ChildValue);
	return (*this);
}
// OC. Other Contructors
JsonData::JsonData(std::string name, bool value) {
	this->Name = name;
	this->Type = Bool;
	this->Value.BoolValue = value;
}
JsonData::JsonData(std::string name, int value) {
	this->Name = name;
	this->Type = Int;
	this->Value.IntValue = value;
}
JsonData::JsonData(std::string name, double value) {
	this->Name = name;
	this->Type = Double;
	this->Value.DoubleValue = value;
}
JsonData::JsonData(std::string name, std::string value) {
	this->Name = name;
	this->Type = String;
	this->Value.StringValue = NULL;
	this->SetValue(value);
}
JsonData::JsonData(std::string name, JsonNode value) {
	this->Name = name;
	this->Type = Child;
	this->Value.ChildValue = NULL;
	this->SetValue(value);
}

// S. Setters
void	JsonData::SetName(std::string name) {
	this->Name = name;
}
void	JsonData::SetValue(bool value) {
	this->Type = Bool;
	this->Value.BoolValue = value;
}
void	JsonData::SetValue(int value) {
	this->Type = Int;
	this->Value.IntValue = value;
}
void	JsonData::SetValue(double value) {
	this->Type = Double;
	this->Value.DoubleValue = value;
}
void	JsonData::SetValue(std::string value) {
	if (this->Type == String && this->Value.StringValue != NULL)
		delete this->Value.StringValue;
	this->Type = String;
	this->Value.StringValue = new std::string(value);
}
void	JsonData::SetValue(JsonNode value) {
	if (this->Type == Child && this->Value.ChildValue != NULL)
		delete this->Value.ChildValue;
	this->Type = Child;
	this->Value.ChildValue = new JsonNode(value);
}

// G. Getters
std::string	JsonData::GetName(void) const {
	return (this->Name);
}
DataType	JsonData::GetType(void) const {
	return (this->Type);
}
DataValue	JsonData::GetValue(void) const {
	return (this->Value);
}
bool		JsonData::TryGetBool(void) const {
	if (this->Type == Bool)
		return (this->Value.BoolValue);
	throw std::bad_cast();
}
int			JsonData::TryGetInt(void) const {
	if (this->Type == Int)
		return (this->Value.IntValue);
	throw std::bad_cast();
}
double		JsonData::TryGetDouble(void) const {
	if (this->Type == Double)
		return (this->Value.DoubleValue);
	throw std::bad_cast();
}
std::string	JsonData::TryGetString(void) const {
	if (this->Type == String)
		return (*this->Value.StringValue);
	throw std::bad_cast();
}
JsonNode	JsonData::TryGetChild(void) const {
	if (this->Type == Child)
		return (*this->Value.ChildValue);
	throw std::bad_cast();
}