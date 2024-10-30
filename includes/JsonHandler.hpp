#ifndef JSONHANDLER_HPP
# define JSONHANDLER_HPP

// 0. External Includes
# include "iostream"
# include "typeinfo"
# include "vector"
# include "list"

// 1. Data Structures

class JsonNode;
class JsonData;
enum DataType {
	None,
	Bool,
	Int,
	Double,
	String,
	Child,
	Children
};
union DataValue {
	bool			BoolValue;
	int				IntValue;
	double			DoubleValue;
	std::string*	StringValue;
	JsonNode*		ChildValue;
};

// 3. Internal Classes
# include "JsonNode.hpp"
# include "JsonData.hpp"
# include "JsonReader.hpp"
# include "JsonObject.hpp"

#endif