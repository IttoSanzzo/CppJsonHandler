#ifndef JSONDATA_HPP
# define JSONDATA_HPP

// 0. Includes
#include "JsonHandler.hpp"

// 1. Class Declaration
class JsonData {
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
		JsonData(std::string name, bool value);
		JsonData(std::string name, int value);
		JsonData(std::string name, double value);
		JsonData(std::string name, std::string value);
		JsonData(std::string name, JsonNode value);
	// S. Setters
		void	SetName(std::string name);
		void	SetValue(bool value);
		void	SetValue(int value);
		void	SetValue(double value);
		void	SetValue(std::string value);
		void	SetValue(JsonNode value);
	// G. Getters
		std::string		GetName(void) const;
		DataType		GetType(void) const;
		DataValue		GetValue(void) const;
		bool			TryGetBool(void) const;
		int				TryGetInt(void) const;
		double			TryGetDouble(void) const;
		std::string		TryGetString(void) const;
		JsonNode		TryGetChild(void) const;
};

#endif