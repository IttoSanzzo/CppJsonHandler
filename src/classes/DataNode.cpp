#include "JsonHandler.hpp"

// D. Destructor
DataNode::~DataNode(void) {
	if (this->Data != NULL)
		delete this->Data;
	if (this->Next != NULL)
		delete this->Next;
	// std::cout << "DataNode " << " Destructed" << std::endl;
}
// CC. Common Constructors
DataNode::DataNode(void) {
	this->Previous = NULL;
	this->Next = NULL;
	this->Data = NULL;
	// std::cout << "DataNode " << " Default Constructor Called!" << std::endl;
}
DataNode::DataNode(const DataNode& src) {
	this->DeepCopy(src);
}
DataNode& DataNode::operator=(const DataNode& src) {
	if (this != &src) {
		if (this->Data != NULL)
			delete this->Data;
		this->DeepCopy(src);
	}
	return (*this);
}

// OC. Other Contructors
DataNode::DataNode(JsonData* data) {
	this->Previous = NULL;
	this->Next = NULL;
	this->Data = data;
}

// S. Setters
void	DataNode::SetPrevious(DataNode* previous) {
    this->Previous = previous;
}
void	DataNode::SetNext(DataNode* next) {
    this->Next = next;
}
void	DataNode::SetData(JsonData* data) {
    this->Data = data;
}

// G. Getters
DataNode*	DataNode::GetPrevious(void) const {
    return (this->Previous);
}
DataNode*	DataNode::GetNext(void) const {
    return (this->Next);
}
JsonData*	DataNode::GetData(void) const {
    return (this->Data);
}
DataNode*	DataNode::GetPos(size_t pos) {
	DataNode* node = this;
	for (size_t i = 0; i < pos; i++) {
		if (node->Next == NULL)
			return (NULL);
		node = node->Next;
	}
	return (node);
}
DataNode*	DataNode::GetFirst(void) {
	DataNode*	finder = this;
	while (finder->Previous != NULL)
		finder = finder->Previous;
	return (finder);
}
DataNode*	DataNode::GetLast(void) {
	DataNode*	finder = this;
	while (finder->Next != NULL)
		finder = finder->Next;
	return (finder);
}

// 0. Member Functions
std::string	DataNode::ToString(const bool& withLineBreaks) {

}
DataNode*	DataNode::FindNode(const std::string& name) {
	DataNode*	finder = this;
	do {
		if (finder->Data != NULL && finder->Data->Name == name)
			return (finder);
		finder = finder->Next;
	} while (finder != NULL);
	return (NULL);
}

// 1. Private Functions
void	DataNode::DeepCopy(const DataNode& src) {
	if (src.Data != NULL)
		this->Data = new JsonData(*src.Data);
	else
		this->Data = NULL;
	this->Previous = NULL;
	this->Next = NULL;
}
DataNode*	DataNode::AddBack(JsonData* data) {
	DataNode*	node = this->GetLast();
	node->Next = new DataNode(data);
	node->Next->Previous = node;
	return (node->Next);
}
DataNode*	DataNode::AddBegin(JsonData* data) {
	DataNode*	node = this->GetFirst();
	node->Previous = new DataNode(data);
	node->Previous->Next = node;
	return (node->Previous);
}
DataNode*	DataNode::ListCopy() {
	DataNode*	node = new DataNode();
	if (this->Data != NULL)
		node->Data = new JsonData(*this->Data);
	if (this->Next != NULL) {
		node->Next = this->Next->ListCopy();
		node->Next->Previous = this;
	}
	return (node);
}