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
		JsonData*	FindData(std::string name);
	// 0. Member Functions
		DataNode*	TryPushData(const JsonData& data);
		DataNode*	TryPushData(std::string name, bool value);
		DataNode*	TryPushData(std::string name, int value);
		DataNode*	TryPushData(std::string name, double value);
		DataNode*	TryPushData(std::string name, const std::string& value);
		DataNode*	TryPushData(std::string name, const JsonNode& value);
		void	DeleteData(std::string name);
		bool		TryGetBool(const std::string& name);
		int			TryGetInt(const std::string& name);
		double		TryGetDouble(const std::string& name);
		std::string	TryGetString(const std::string& name);
		JsonNode	TryGetChild(const std::string& name);

	private:
	// 0. Private Functions
		void	DeepCopy(const JsonNode& src);
		void	DestroyDataNode(DataNode* node);
		DataNode*	TryCreateDataNode(JsonData* data, std::string* targetName, size_t targetSize);
		DataNode*	CreateSimpleDataNode(JsonData* data);
		JsonData*	FindData(std::string* name);
};

#endif