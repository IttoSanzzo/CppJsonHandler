#ifndef JSONCHILDREN_HPP
# define JSONCHILDREN_HPP

// 0. Includes
#include "JsonHandler.hpp"

// 1. Class Declaration
class JsonChildren {
	friend class JsonData;
	private:
	// M. Member Variables
		std::string 	Name;
		size_t			Size;
		DataNode*		Childs;
	public:
	// C. Constructors
		~JsonChildren(void);
		// CC. Common Constructors
		JsonChildren(void);
		JsonChildren(const JsonChildren& src);
		JsonChildren&	operator=(const JsonChildren& src);
		// OC. Other Contructors
		JsonChildren(std::string name);
	// S. Setters
		void	SetName(std::string name);
	// G. Getters
		std::string	GetName(void) const;
		size_t		GetSize(void) const;
		JsonData	GetChild(const size_t& position) const;
	// 0. Member Functions
		void		DeleteChild(const size_t& targetPosition);
		JsonData*	PushChild(const JsonNode& child);
		JsonData*	PushChild(const JsonNode& child, const size_t& pos);

	private:
	// P. Private Functions
		void		DeepCopy(const JsonChildren& src);
		void		DestroyChildNode(DataNode* childNode);
};

#endif