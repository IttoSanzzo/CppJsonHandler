#ifndef DATANODE_HPP
# define DATANODE_HPP

// 0. Includes
#include "JsonHandler.hpp"

// 1. Class Declaration
class DataNode {
	friend class JsonNode;
	friend class JsonChildren;
	friend class JsonData;
	private:
	// M. Member Variables
		DataNode*	Previous;
		DataNode*	Next;
		JsonData*	Data;
	public:
		~DataNode(void);
	// C. Constructors
		// CC. Common Contructors
		DataNode(void);
		DataNode(const DataNode& src);
		DataNode&	operator=(const DataNode& src);
		// OC. Other Contructors
		DataNode(JsonData* data);
	// S. Setters
		void		SetPrevious(DataNode* previous);
		void		SetNext(DataNode* next);
		void		SetData(JsonData* data);

	// G. Getters
		DataNode*	GetPrevious(void) const;
		DataNode*	GetNext(void) const;
		JsonData*	GetData(void) const;
		DataNode*	GetPos(size_t pos);
		DataNode*	GetFirst(void);
		DataNode*	GetLast(void);
	// 0. Member Functions
		DataNode*	FindNode(const std::string& name);

	private:
	// 0. Private Functions
		void		DeepCopy(const DataNode& src);
		DataNode*	AddBack(JsonData* data);
		DataNode*	AddBegin(JsonData* data);
		DataNode*	ListCopy();
};

#endif