#ifndef JSONNODE_HPP
# define JSONNODE_HPP

// 0. Includes
#include "JsonHandler.hpp"

// 1. Class Declaration
class JsonNode {
	private:
	// M. Member Variables
		std::string	Name;
		JsonNode*	Parent;
		size_t		Size;
	public:
		DataNode*	DataNodes;
	public:
	// C. Constructors
		~JsonNode(void);
		JsonNode(void);
		JsonNode(const JsonNode& src);
		JsonNode&	operator=(const JsonNode& src);
		JsonNode(std::string name);
	// S. Setters
		void	SetName(std::string name);
		void	SetParent(JsonNode* parent);
	// G. Getters
		std::string	GetName(void) const;
		JsonNode*	GetParent(void) const;
		size_t		GetSize(void) const;
		JsonData*	FindData(const std::string& name);
	// 0. Member Functions
		std::string	ToString(const bool& withLineBreaks = true);
		void		DeleteData(std::string name);
		JsonData*	TryPushData(const JsonData& data);
		JsonData*	TryPushData(const std::string& name, bool value);
		JsonData*	TryPushData(const std::string& name, int value);
		JsonData*	TryPushData(const std::string& name, double value);
		JsonData*	TryPushData(const std::string& name, const std::string& value);
		JsonData*	TryPushData(const std::string& name, const JsonNode& value);
		bool		TryGetBool(const std::string& name);
		int			TryGetInt(const std::string& name);
		double		TryGetDouble(const std::string& name);
		std::string	TryGetString(const std::string& name);
		JsonNode	TryGetChild(const std::string& name);

	private:
	// 0. Private Functions
		void	DeepCopy(const JsonNode& src);
		void	DestroyDataNode(DataNode* node);
		JsonData*	PushDataDoor(const std::string& name, const DataValue& value, const DataType& type);
		DataNode*	TryCreateDataNode(JsonData* data, const std::string* targetName, size_t targetSize);
		DataNode*	CreateSimpleDataNode(JsonData* data);
		JsonData*	FindData(const std::string* name);
};

#endif