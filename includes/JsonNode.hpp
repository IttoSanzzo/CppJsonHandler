#ifndef JSONNODE_HPP
# define JSONNODE_HPP

// 0. Includes
#include "JsonHandler.hpp"

// 1. Class Declaration
class JsonNode {
	private:
	// M. Member Variables
		std::string				Name;
		JsonNode*				Parent;
		std::vector<JsonData>	Data;
		
	public:
	// C. Constructors
		~JsonNode(void);
		JsonNode(void);
		JsonNode(const JsonNode& src);
		JsonNode&	operator=(const JsonNode& src);
	// S. Setters
		void	SetName(std::string name);
		void	SetParent(JsonNode* parent);
	// G. Getters
		std::string	GetName(void);
		JsonNode*	GetParent(void);
	// 0. Member Functions
		void	CreateData(JsonData data);
		void	CreateData(std::string name, bool value);
		void	CreateData(std::string name, std::string value);

	private:
	// 0. Private Functions
};

#endif