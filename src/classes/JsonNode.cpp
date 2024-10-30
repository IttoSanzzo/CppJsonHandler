#include "JsonHandler.hpp"

// D. Destructor
JsonNode::~JsonNode(void) {
	std::cout << "JsonNode Destructed" << std::endl;
}
// CC. Common Constructors
JsonNode::JsonNode(void) {
	this->Name = "node";
	this->Parent = NULL;
	std::cout << "JsonNode Default Constructor Called!" << std::endl;
}
JsonNode::JsonNode(const JsonNode& src) {
	this->Name = src.Name;
	this->Parent = src.Parent;
}
JsonNode& JsonNode::operator=(const JsonNode& src) {
	this->Name = src.Name;
	this->Parent = src.Parent;
	return (*this);
}

// OC. Other Contructors
// S. Setters
void	JsonNode::SetName(std::string name) {
	this->Name = name;
}
void	JsonNode::SetParent(JsonNode* parent) {
	this->Parent = parent;
}

// G. Getters
std::string	JsonNode::GetName(void) {
	return (this->Name);
}
JsonNode*	JsonNode::GetParent(void) {
	return (this->Parent);
}

// 0. Member Functions
void	JsonNode::CreateData(JsonData data) {
	this->Data.push_back(data);
}
void	JsonNode::CreateData(std::string name, bool value) {
	this->Data.push_back(JsonData(name, value));
}
void	JsonNode::CreateData(std::string name, std::string value) {
	this->Data.push_back(JsonData(name, value));
}