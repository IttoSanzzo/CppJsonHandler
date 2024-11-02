#include "JsonHandler.hpp"

// 01. Static Funcion Prototypes
static std::string*	split(const std::string& inputString, char delimiter);
static size_t		StringArrayLength(const std::string* str);

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
	// std::cout << "JsonNode " << this->Name << " Default Constructor Called!" << std::endl;
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
	// std::cout << "JsonNode " << this->Name << " Default Constructor Called!" << std::endl;
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
JsonData*	JsonNode::FindData(const std::string& name) {
	std::string* targetName = split(name, '.');
	JsonData* targetData = this->FindData(targetName);
	delete[] targetName;
	return (targetData);
}

// 0. Member Functions
// 0.1 Others
void		JsonNode::DeleteData(std::string name) {
	JsonNode*	jsonNode = this;
	if (name.find('.') != std::string::npos) {
		std::string* targetName = split(name, '.');
		size_t targetSize = StringArrayLength(targetName) - 1;
		JsonData* data;
		for (size_t targetIndex = 0; targetIndex < targetSize; targetIndex++) {
			data = jsonNode->FindData(targetName[targetIndex]);
			if (data == NULL || data->Type != Child) {
				delete[] targetName;
				return ;
			}
			jsonNode = data->Value.ChildValue;
		}
		name = targetName[targetSize];
		delete[] targetName;
	}
	if (jsonNode != NULL && jsonNode->DataNodes != NULL) {
		DataNode*	dataNode = jsonNode->DataNodes->FindNode(name);
		if (dataNode != NULL) {
			jsonNode->DestroyDataNode(dataNode);
			jsonNode->Size--;
		}
	}
}
std::string	JsonNode::ToString(const bool& withLineBreaks) {
	(void)withLineBreaks;
	std::string jsonString = "{";
	DataNode*	dataNode = this->DataNodes;
	while (dataNode != NULL) {
		jsonString += dataNode->ToString(withLineBreaks);
		if (dataNode->Next != NULL)
			switch (withLineBreaks) {
				case (true):
					jsonString =+ ",\n";
				break;
				case (false):
					jsonString =+ ",";
				break;
			}
		dataNode = dataNode->Next;
	}
	return (jsonString + "}");
}

// 0.1 TryPushes
JsonData*	JsonNode::TryPushData(const JsonData& src) {
	JsonData* data = this->FindData(src.Name);
	if (data != NULL) {
		switch (src.Type) {
			case (Bool):
				data->SetValue(src.Value.BoolValue);
			break;
			case (Int):
				data->SetValue(src.Value.IntValue);
			break;
			case (Double):
				data->SetValue(src.Value.DoubleValue);
			break;
			case (String):
				data->SetValue(src.Value.StringValue);
			break;
			case (Child):
				data->SetValue(src.Value.ChildValue);
			break;
			default:
				return (NULL);
			break;
		}
		return (data);
	}
	return (this->CreateSimpleDataNode(new JsonData(src))->Data);
}
JsonData*	JsonNode::TryPushData(const std::string& name, bool value) {
	DataValue	dataValue;
	dataValue.BoolValue = value;
	return (this->PushDataDoor(name, dataValue, Bool));
}
JsonData*	JsonNode::TryPushData(const std::string& name, int value) {
	DataValue	dataValue;
	dataValue.IntValue = value;
	return (this->PushDataDoor(name, dataValue, Int));
}
JsonData*	JsonNode::TryPushData(const std::string& name, double value) {
	DataValue	dataValue;
	dataValue.DoubleValue = value;
	return (this->PushDataDoor(name, dataValue, Double));
}
JsonData*	JsonNode::TryPushData(const std::string& name, const std::string& value) {
	DataValue	dataValue;
	dataValue.StringValue = new std::string(value);
	return (this->PushDataDoor(name, dataValue, String));
}
JsonData*	JsonNode::TryPushData(const std::string& name, const JsonNode& value) {
	DataValue	dataValue;
	dataValue.ChildValue = new JsonNode(value);
	return (this->PushDataDoor(name, dataValue, Child));
}
// 0.1 TryGets
bool		JsonNode::TryGetBool(const std::string& name) {
	JsonData* data = this->FindData(name);
	if (data == NULL)
		throw JsonException("TryGetBool..: '" + name + "' Not Found.");
	return (data->TryGetBool());
}
int			JsonNode::TryGetInt(const std::string& name) {
	JsonData* data = this->FindData(name);
	if (data == NULL)
		throw JsonException("TryGetInt..: '" + name + "' Not Found.");
	return (data->TryGetInt());
}
double		JsonNode::TryGetDouble(const std::string& name) {
	JsonData* data = this->FindData(name);
	if (data == NULL)
		throw JsonException("TryGetDouble..: '" + name + "' Not Found.");
	return (data->TryGetDouble());
}
std::string	JsonNode::TryGetString(const std::string& name) {
	JsonData* data = this->FindData(name);
	if (data == NULL)
		throw JsonException("TryGetString..: '" + name + "' Not Found.");
	return (data->TryGetString());
}
JsonNode	JsonNode::TryGetChild(const std::string& name) {
	JsonData* data = this->FindData(name);
	if (data == NULL)
		throw JsonException("TryGetChild..: '" + name + "' Not Found.");
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
JsonData*	JsonNode::PushDataDoor(const std::string& name, const DataValue& value, const DataType& type) {
	JsonData* data = this->FindData(name);
	if (data != NULL) {
		data->SetValue(value, type);
		return (data);
	}
	std::string* targetName = split(name, '.');
	size_t targetSize = StringArrayLength(targetName) - 1;
	DataNode* newNode = this->TryCreateDataNode(new JsonData(targetName[targetSize], value, type), targetName, targetSize);
	delete[] targetName;
	return (newNode->Data);
}
DataNode*	JsonNode::TryCreateDataNode(JsonData* data, const std::string* targetName, size_t targetSize) {
	JsonNode* jsonNode = this;
	JsonData* jsonData;
	for (size_t targetIndex = 0; targetIndex < targetSize; targetIndex++) {
		jsonData = jsonNode->FindData(targetName[targetIndex]);
		if (jsonData != NULL) {
			if (jsonData->Type != Child) {
				delete[] targetName;
				throw JsonException("Trying to push through a non-child node");
			}
			jsonNode = jsonData->Value.ChildValue;
		}
		else
			jsonNode = (jsonNode->CreateSimpleDataNode(new JsonData( targetName[targetIndex], new JsonNode(targetName[targetIndex]))))->Data->Value.ChildValue;
	}
	jsonNode->Size++;
	return (jsonNode->CreateSimpleDataNode(data));
}
DataNode*	JsonNode::CreateSimpleDataNode(JsonData* data) {
	if (this->DataNodes == NULL)
		return (this->DataNodes = new DataNode(data));
	return (this->DataNodes->AddBack(data));
}
JsonData*	JsonNode::FindData(const std::string* targetName) {
	if (targetName[0].empty() || this->DataNodes == NULL)
		return (NULL);
	DataNode* node = this->DataNodes->FindNode(targetName[0]);
	if (node == NULL)
		return (NULL);
	else if (targetName[1].empty())
		return (node->Data);
	else if (node->Data == NULL || node->Data->Type != Child)
		return (NULL);
	JsonData* targetData = node->Data->Value.ChildValue->FindData(targetName + 1);
	return (targetData);
}

// 3. Static Util Functions
static size_t		StringArrayLength(const std::string* str) {
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