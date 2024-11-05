#ifndef JSONHANDLER_HPP
# define JSONHANDLER_HPP

// 0. External Includes
# include "iostream"
# include "sstream"
# include "fstream"
# include "typeinfo"
# include "exception"

// 1. Class Declarations
class JsonNode;
class JsonData;
class DataNode;
class JsonChildren;

// 2. Data Structures
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
	JsonChildren*	ChildrenValue;
};
struct TokenInfo {
	char	Type;
	size_t	Position;
	TokenInfo(char token, size_t position) : Type(token), Position(position) {};
};

// 3. Internal Classes
# include "JsonException.hpp"
# include "JsonNode.hpp"
# include "JsonData.hpp"
# include "DataNode.hpp"
# include "JsonChildren.hpp"
# include "JsonParser.hpp"

#endif