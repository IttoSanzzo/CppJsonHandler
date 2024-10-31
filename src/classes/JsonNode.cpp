#include "JsonHandler.hpp"

// 01. Static Funcion Prototypes
static std::string*	split(const std::string& inputString, char delimiter);
static size_t		StringArrayLength(std::string* str);

// D. Destructor
JsonNode::~JsonNode(void) {
	if (this->DataNodes != NULL)
		delete this->DataNodes;
	// std::cout << "JsonNode " << this->Name << " Destructed" << std::endl;
}
// CC. Common Constructors
JsonNode::JsonNode(void) {
	this->Name = "JsonObject";
	this->Parent = NULL;
	this->Size = 0;
	this->DataNodes = NULL;
	std::cout << "JsonNode " << this->Name << " Default Constructor Called!" << std::endl;
}
JsonNode::JsonNode(const JsonNode& src) {
	this->DeepCopy(src);
}
JsonNode& JsonNode::operator=(const JsonNode& src) {
	this->DeepCopy(src);
	return (*this);
}

// OC. Other Contructors
JsonNode::JsonNode(std::string name) {
	this->Name = name;
	this->Parent = NULL;
	this->Size = 0;
	this->DataNodes = NULL;
	std::cout << "JsonNode " << this->Name << " Default Constructor Called!" << std::endl;
}

// S. Setters
void	JsonNode::SetName(std::string name) {
	this->Name = name;
}
void	JsonNode::SetParent(JsonNode* parent) {
	this->Parent = parent;
}

// G. Getters
std::string	JsonNode::GetName(void) const {
	return (this->Name);
}
JsonNode*	JsonNode::GetParent(void) const {
	return (this->Parent);
}
size_t		JsonNode::GetSize(void) const {
	return (this->Size);
}
JsonData*	JsonNode::FindData(std::string name) {
	std::string* targetName = split(name, '.');
	if (StringArrayLength(targetName) == 0) {
		delete[]	targetName;
		return (NULL);
	}
	DataNode* node = this->DataNodes->FindNode(targetName[0]);
	if (node == NULL) {
		delete[]	targetName;
		return (NULL);
	}
	if (StringArrayLength(targetName) == 1) {
		delete[]	targetName;
		return (node->Data);
	}
	if (node->Data->Type != Child) {
		delete[]	targetName;
		return (NULL);
	}
	JsonNode* child = node->Data->Value.ChildValue;
	JsonData* targetData = child->FindData(targetName + 1);
	delete[] targetName;
	return (targetData);
}

// 0. Member Functions
DataNode*	JsonNode::TryPushData(const JsonData& src) {
	DataNode* node = this->DataNodes->FindNode(src.Name);
	if (node != NULL) {
		if (node->Data == NULL) {
			node->Data = new JsonData(src);
			return (node);
		}
		switch (src.Type) {
			case (Bool):
				node->Data->SetValue(src.Value.BoolValue);
			break;
			case (Int):
				node->Data->SetValue(src.Value.IntValue);
			break;
			case (Double):
				node->Data->SetValue(src.Value.DoubleValue);
			break;
			case (String):
				node->Data->SetValue(src.Value.StringValue);
			break;
			case (Child):
				node->Data->SetValue(src.Value.ChildValue);
			break;
			default:
				return (NULL);
			break;
		}
		return (node);
	}
	return (this->CreateSimpleDataNode(new JsonData(src)));
}
DataNode*	JsonNode::TryPushData(std::string name, bool value) {
	JsonData* data = this->FindData(name);
	if (data != NULL) {
		data->SetValue(value);
		return (data);
	}
	std::string* targetName = split(name, '.');
	size_t targetSize = StringArrayLength(targetName);
	DataNode* newNode = this->TryCreateDataNode(new JsonData(targetName[targetSize - 1], value), targetName, targetSize);
	delete[] targetName;
	return (newNode);
}

/*

		VOCE ESTAJA PENSANDO EM TROCAR O RESTORNO DO TRYPUSHDATA DE DATANODE* PARA JSONDATA*, TALVEZ PELOS RETORNOS DAS PROPRIAS FUNCOES.

*/

DataNode*	JsonNode::TryPushData(std::string name, int value) {
	JsonData* data = this->FindData(name);
	if (data != NULL) {
		data->SetValue(value);
		return ;
	}
	std::string* targetName = split(name, '.');
	size_t targetSize = StringArrayLength(targetName);
	DataNode* newNode = this->TryCreateDataNode(new JsonData(targetName[targetSize - 1], value), targetName, targetSize);
	delete[] targetName;
	return (newNode);
}
DataNode*	JsonNode::TryPushData(std::string name, double value) {
	JsonData* data = this->FindData(name);
	if (data != NULL) {
		data->SetValue(value);
		return ;
	}
	std::string* targetName = split(name, '.');
	size_t targetSize = StringArrayLength(targetName);
	DataNode* newNode = this->TryCreateDataNode(new JsonData(targetName[targetSize - 1], value), targetName, targetSize);
	delete[] targetName;
	return (newNode);
}
DataNode*	JsonNode::TryPushData(std::string name, const std::string& value) {
	JsonData* data = this->FindData(name);
	if (data != NULL) {
		data->SetValue(value);
		return ;
	}
	std::string* targetName = split(name, '.');
	size_t targetSize = StringArrayLength(targetName);
	DataNode* newNode = this->TryCreateDataNode(new JsonData(targetName[targetSize - 1], value), targetName, targetSize);
	delete[] targetName;
	return (newNode);
}
DataNode*	JsonNode::TryPushData(std::string name, const JsonNode& value) {
	JsonData* data = this->FindData(name);
	if (data != NULL) {
		data->SetValue(value);
		return ;
	}
	std::string* targetName = split(name, '.');
	size_t targetSize = StringArrayLength(targetName);
	DataNode* newNode = this->TryCreateDataNode(new JsonData(targetName[targetSize - 1], value), targetName, targetSize);
	delete[] targetName;
	return (newNode);
}
void	JsonNode::DeleteData(std::string name) {
	DataNode*	node = this->DataNodes->FindNode(name);
	if (node != NULL) {
		this->Size--;
		this->DestroyDataNode(node);
	}
}
bool		JsonNode::TryGetBool(const std::string& name) {
	JsonData* data = this->FindData(name);
	if (data == NULL)
		throw JsonException("Not Found");
	return (data->TryGetBool());
}
int			JsonNode::TryGetInt(const std::string& name) {
	JsonData* data = this->FindData(name);
	if (data == NULL)
		throw JsonException("Not Found");
	return (data->TryGetInt());
}
double		JsonNode::TryGetDouble(const std::string& name) {
	JsonData* data = this->FindData(name);
	if (data == NULL)
		throw JsonException("Not Found");
	return (data->TryGetDouble());
}
std::string	JsonNode::TryGetString(const std::string& name) {
	JsonData* data = this->FindData(name);
	if (data == NULL)
		throw JsonException("Not Found");
	return (data->TryGetString());
}
JsonNode	JsonNode::TryGetChild(const std::string& name) {
	JsonData* data = this->FindData(name);
	if (data == NULL)
		throw JsonException("Not Found");
	return (data->TryGetChild());
}

// 2. Private Functions
void		JsonNode::DeepCopy(const JsonNode& src) {
	this->Name = src.Name;
	this->Parent = src.Parent;
	this->Size = src.Size;
	this->DataNodes = src.DataNodes->GetFirst()->ListCopy();
}
void		JsonNode::DestroyDataNode(DataNode* node) {
	if (node->Previous != NULL)
		node->Previous->Next = node->Next;
	else
		this->DataNodes = node->Next;
	node->Next = NULL;
	delete node;
}
DataNode*	JsonNode::TryCreateDataNode(JsonData* data, std::string* targetName, size_t targetSize) {
	size_t	targetIndex = 0;
	JsonNode* node = this;
	JsonNode* nextNode = NULL;
	while (targetIndex < targetSize) {
		JsonData* data = node->FindData(targetName[targetIndex]);
		if (data == NULL)
			node = (node->CreateSimpleDataNode(new JsonData(targetName[targetIndex], JsonNode(targetName[targetIndex]))))->Data->Value.ChildValue;
		else {
			if (data->Type != Child)
				throw JsonException("Trying to push through a non-child node");
			node = data->Value.ChildValue;
		}
	}
	node->Size++;
	return (this->CreateSimpleDataNode(data));
}
DataNode*	JsonNode::CreateSimpleDataNode(JsonData* data) {
	if (this->DataNodes == NULL) {
		this->DataNodes = new DataNode(data);
		return (this->DataNodes);
	}
	else
		return (this->DataNodes->AddBack(data));
}
JsonData*	JsonNode::FindData(std::string* targetName) {
	DataNode* node = this->DataNodes->FindNode(targetName[0]);
	if (StringArrayLength(targetName) == 0)
		return (NULL);
	if (node == NULL)
		return (NULL);
	if (StringArrayLength(targetName) == 1)
		return (node->Data);
	if (node->Data->Type != Child)
		return (NULL);
	JsonNode* child = node->Data->Value.ChildValue;
	JsonData* targetData = child->FindData(targetName + 1);
	return (targetData);
}

// 3. Static Util Functions
static size_t		StringArrayLength(std::string* str) {
	size_t	lenght = 0;
	while (str[lenght] != "")
		lenght++;
	return (lenght);
}
static int			countOccurrences(const std::string& input, char delimiter) {
    int		count = 0;
	size_t	i = 0;
	while (i < (size_t)input.size() && input[i] == delimiter)
		i++;
	while (i < (size_t)input.size()) {
		if (input[i] != delimiter) {
			count++;
			while (++i < (size_t)input.size() && input[i] != delimiter)
				continue ;
			--i;
		}
		i++;
    }
    return (count);
}
static std::string*	split(const std::string& inputString, char delimiter) {
    int partsCount = countOccurrences(inputString, delimiter) + 1;
    std::string* parts = new std::string[partsCount];
	if (partsCount == 1) {
		parts[0] = std::string("");
		return (parts);
	}
    size_t	partIndex = 0;
    size_t	start = 0;
	while (inputString[start] == delimiter)
		start++;
    size_t	end = inputString.find(delimiter, start);
    while (start < inputString.size() && end != std::string::npos) {
        parts[partIndex++] = inputString.substr(start, end - start);
        start = end;
		while (start < inputString.size() && inputString[start] == delimiter)
			start++;
        end = inputString.find(delimiter, start);
    }
	if (inputString[inputString.size() - 1] != delimiter)
    	parts[partIndex++] = inputString.substr(start, inputString.size() - start);
    parts[partIndex] = "";
    return (parts);
}
