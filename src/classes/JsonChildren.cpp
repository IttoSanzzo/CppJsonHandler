#include "JsonHandler.hpp"

// D. Destructor
JsonChildren::~JsonChildren(void) {
	if (this->Childs != NULL)
		delete this->Childs;
}
// CC. Common Constructors
JsonChildren::JsonChildren(void) {
	this->Name = "Children";
	this->Size = 0;
	this->Childs = NULL;
}
JsonChildren::JsonChildren(const JsonChildren& src) {
	this->DeepCopy(src);
}
JsonChildren& JsonChildren::operator=(const JsonChildren& src) {
	this->DeepCopy(src);
	return (*this);
}

// OC. Other Contructors
JsonChildren::JsonChildren(std::string name) {
	this->Name = name;
	this->Size = 0;
	this->Childs = NULL;
}

// S. Setters
void	JsonChildren::SetName(std::string name) {
	this->Name = name;
}

// G. Getters
std::string	JsonChildren::GetName(void) const {
	return (this->Name);
}
size_t		JsonChildren::GetSize(void) const {
	return (this->Size);
}
JsonData	JsonChildren::GetChild(const size_t& position) const {
	if (position >= this->Size)
		return (JsonData());
	return (*this->Childs->GetPos(position)->Data);
}

// 0. Member Functions
void		JsonChildren::DeleteChild(const size_t& targetPosition) {
	if (targetPosition >= this->Size || this->Size == 0)
		return ;
	--this->Size;
	this->DestroyChildNode(this->Childs->GetPos(targetPosition));
}
JsonData*	JsonChildren::PushChild(const JsonNode& child) {
	this->Size++;
	if (this->Childs == NULL) {
		this->Childs = new DataNode(new JsonData(child.Name, child));
		return (this->Childs->Data);
	}
	DataNode* childNode = this->Childs->AddBack(new JsonData(child.Name, child));
	return (childNode->Data);
}
JsonData*	JsonChildren::PushChild(const JsonNode& child, const size_t& targetPosition) {
	if (targetPosition >= this->Size)
		return (NULL);
	DataNode* targetChild = this->Childs->GetPos(targetPosition);
	if (targetChild->Data != NULL)
		delete targetChild->Data;
	targetChild->Data = new JsonData(child.Name, child);
}

// P. Private Functions
void		JsonChildren::DeepCopy(const JsonChildren& src) {
	this->Name = src.Name;
	this->Size = src.Size;
	if (src.Childs != NULL)
		this->Childs = src.Childs->GetFirst()->ListCopy();
	else
		this->Childs = NULL;
}
void		JsonChildren::DestroyChildNode(DataNode* childNode) {
	if (childNode->Previous != NULL)
		childNode->Previous->Next = childNode->Next;
	else
		this->Childs = childNode->Next;
	childNode->Next = NULL;
	delete childNode;
}