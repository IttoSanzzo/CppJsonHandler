#ifndef JSONNODE_HPP
# define JSONNODE_HPP

// 0. Includes
#include "JsonHandler.hpp"

// 1. Class Declaration
class JsonNode {
	friend class JsonData;
	friend class JsonChildren;
	private:
	// M. Member Variables
		std::string	Name;
		size_t		Size;
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
	// G. Getters
		std::string	GetName(void) const;
		size_t		GetSize(void) const;
		JsonData*	FindData(const std::string& name) const;
	// 0. Member Functions
		std::string	ToString(const bool& withLineBreaks = true) const;
		void		DeleteData(std::string name);
		JsonData*	TryPushData(const JsonData& data);
		JsonData*	TryPushData(const std::string& name, bool value);
		JsonData*	TryPushData(const std::string& name, int value);
		JsonData*	TryPushData(const std::string& name, double value);
		JsonData*	TryPushData(const std::string& name, const std::string& value);
		JsonData*	TryPushData(const std::string& name, const JsonNode& value);
		JsonData*	TryPushData(const std::string& name, const JsonChildren& value);
		bool			TryGetBool(const std::string& name) const;
		int				TryGetInt(const std::string& name) const;
		double			TryGetDouble(const std::string& name) const;
		std::string		TryGetString(const std::string& name) const;
		JsonNode		TryGetChild(const std::string& name) const;
		JsonChildren	TryGetChildren(const std::string& name) const;
	// 1. Readers
		static JsonNode	TryParseJsonFromString(const std::string& jsonString);
		static JsonNode	TryParseJsonFromFile(const std::string& pathToFile);

	private:
	// P. Private Functions
		void	DeepCopy(const JsonNode& src);
		void	DestroyDataNode(DataNode* node);
		JsonData*	PushDataDoor(const std::string& name, const DataValue& value, const DataType& type);
		DataNode*	TryCreateDataNode(JsonData* data, const std::string* targetName, size_t targetSize);
		DataNode*	CreateSimpleDataNode(JsonData* data);
		JsonData*	FindData(const std::string* name) const;
		std::string	ToString(const bool& withLineBreaks, const size_t& depth) const;
		std::string	ToStringTab(const bool& withTabs, const bool& withBreak, short depth) const;
};

#endif