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
	// std::cout << "JsonData " << this->Name << " Destructed!" << std::endl;
}
// CC. Common Constructors
JsonData::JsonData(void) {
	this->Name = "data";
	this->Type = None;
	// std::cout << "JsonData " << this->Name << " Default Constructed!" << std::endl;
}
JsonData::JsonData(const JsonData& src) {
	this->DeepCopy(src);
	// std::cout << "JsonData " << this->Name << " Source Constructed!" << std::endl;
}
JsonData& JsonData::operator=(const JsonData& src) {
	this->DeepCopy(src);
	// std::cout << "JsonData " << this->Name << " Operator= Constructed!" << std::endl;
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
	// std::cout << "JsonData " << this->Name << " Bool Constructed!" << std::endl;
}
JsonData::JsonData(const std::string& name, const int& value) {
	this->Name = name;
	this->SetValue(value);
	// std::cout << "JsonData " << this->Name << " Int Constructed!" << std::endl;
}
JsonData::JsonData(const std::string& name, const double& value) {
	this->Name = name;
	this->SetValue(value);
	// std::cout << "JsonData " << this->Name << " Double Constructed!" << std::endl;
}
JsonData::JsonData(const std::string& name, const std::string& value) {
	this->Name = name;
	this->Type = None;
	this->SetValue(value);
	// std::cout << "JsonData " << this->Name << " String Constructed!" << std::endl;
}
JsonData::JsonData(const std::string& name, const JsonNode& value) {
	this->Name = name;
	this->Type = None;
	this->SetValue(value);
	// std::cout << "JsonData " << this->Name << " Child Constructed!" << std::endl;
}
JsonData::JsonData(const std::string& name, const JsonNode* value) {
	this->Name = name;
	this->Type = None;
	this->SetValue(value);
	// std::cout << "JsonData " << this->Name << " Child Constructed!" << std::endl;
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
std::string	JsonData::GetName(void) const {
	return (this->Name);
}
DataType	JsonData::GetType(void) const {
	return (this->Type);
}
DataValue	JsonData::GetValue(void) const {
	return (this->Value);
}
bool		JsonData::TryGetBool(void) {
	if (this->Type == Bool)
		return (this->Value.BoolValue);
	throw JsonException("TryGetBool..: Not this type, the correct one is: '" + this->DataTypeName() + "'.");
}
int			JsonData::TryGetInt(void) {
	if (this->Type == Int)
		return (this->Value.IntValue);
	throw JsonException("TryGetInt..: Not this type, the correct one is: '" + this->DataTypeName() + "'.");
}
double		JsonData::TryGetDouble(void) {
	if (this->Type == Double)
		return (this->Value.DoubleValue);
	throw JsonException("TryGetDouble..: Not this type, the correct one is: '" + this->DataTypeName() + "'.");
}
std::string	JsonData::TryGetString(void) {
	if (this->Type == String)
		return (*this->Value.StringValue);
	throw JsonException("TryGetString..: Not this type, the correct one is: '" + this->DataTypeName() + "'.");
}
JsonNode	JsonData::TryGetChild(void) {
	if (this->Type == Child)
		return (*this->Value.ChildValue);
	throw JsonException("TryGetChild..: Not this type, the correct one is: '" + this->DataTypeName() + "'.");
}

// 0. Private Functions
void		JsonData::DeepCopy(const JsonData& src) {
	this->Name = src.Name;
	this->Type = src.Type;
	this->Value = src.Value;
	if (this->Type == String)
		this->Value.StringValue = new std::string(*src.Value.StringValue);
	if (this->Type == Child)
		this->Value.ChildValue = new JsonNode(*src.Value.ChildValue);
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