#ifndef JSONDATA_HPP
# define JSONDATA_HPP

// 0. Includes
#include "JsonHandler.hpp"

// 1. Class Declaration
class JsonData {
	friend class DataNode;
	friend class JsonNode;
	friend class JsonChildren;
	private:
	// M. Member Variables
		std::string	Name;
		DataType	Type;
		DataValue	Value;
	public:
	// C. Constructors
		// CC. Common Contructors
		~JsonData(void);
		JsonData(void);
		JsonData(const JsonData& src);
		JsonData&	operator=(const JsonData& src);
		// OC. Other Contructors
		JsonData(const std::string& name, const DataValue& value, const DataType& type);
		JsonData(const std::string& name, const bool& value);
		JsonData(const std::string& name, const int& value);
		JsonData(const std::string& name, const double& value);
		JsonData(const std::string& name, const std::string& value);
		JsonData(const std::string& name, const JsonNode& value);
		JsonData(const std::string& name, const JsonNode* value);
	// S. Setters
		void	SetName(const std::string& name);
		void	SetValue(const DataValue& value, const DataType& type);
		void	SetValue(const bool& value);
		void	SetValue(const int& value);
		void	SetValue(const double& value);
		void	SetValue(const std::string& value);
		void	SetValue(const JsonNode& value);
		void	SetValue(const JsonNode* value);
	// G. Getters
		std::string		GetName(void) const;
		DataType		GetType(void) const;
		DataValue		GetValue(void) const;
		bool			TryGetBool(void);
		int				TryGetInt(void);
		double			TryGetDouble(void);
		std::string		TryGetString(void);
		JsonNode		TryGetChild(void);
		JsonChildren	TryGetChildren(void);
	// 0. Member Functions
		std::string	ToString(const bool& withLineBreaks, const size_t& depth) const;
	private:
	// 0. Private Functions
		void		DeepCopy(const JsonData& src);
		std::string	DataTypeName(const DataType& type);
		std::string	DataTypeName();
		std::string	ToString(const bool& value) const;
		std::string	ToString(const int& value) const;
		std::string	ToString(const double& value) const;
		std::string	ToString(const std::string* value) const;
		std::string	ToString(const JsonNode* value, const bool& withLineBreaks, const size_t& depth) const;
};

#endif