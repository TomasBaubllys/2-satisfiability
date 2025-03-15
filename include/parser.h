#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <unordered_map>

#define ERR_EMPTY_DISJUNCTION "Invalid argument: A disjunction cannot be empty"
#define CLAUSE_DELIMITER '&'

#define DISJUNCTION_START_CHAR '('
#define DISJUNCTION_END_CHAR ')'
#define ERR_MISSING_DISJUNCTION_PARENS "Invalid argument: A disjunction must be wrapped in parentheses"

#define LITERAL_DISJUNCTION_JOIN 'V'
#define ERR_MISSING_DISJUNCTION_LITERAL_JOIN "Invalid argument: A disjunction must contain exactly two literals that are joined with \"V\"" 

#define LITERAL_START_CHAR 'x'
#define ERR_LITERAL_START_CHAR "Invalid argument: Literal name must start with a \"x\""
#define ERR_LITERAL_TOO_SHORT "Invalid argument: Literal must contain atleast 2 characters"
#define ERR_INVALID_LITERAL_NAMING "Invalid argument: Literal must start with 'x' followed by a number"

using literal = std::pair<int, bool>;

// splits an expression to seperate disjunctions represented by pairs
std::vector<std::pair<std::string, std::string>> split_to_disjunctions(std::string &expr);

// splits a string representing a disjunction to seperate literals
std::pair<std::string, std::string> split_literals(std::string &disj);

// assigns a number and a sign to represent a literal, based on existing map
literal assign_num_and_sign(std::string literal, std::unordered_map<std::string, int> &map);

#endif // PARSER_H_INCLUDED