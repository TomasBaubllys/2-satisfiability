#include "../include/parser.h"

using namespace std;

vector<pair<string, string>> split_to_disjunctions(string &expr) {
    if(expr.front() == '&' || expr.back() == '&') {
        throw invalid_argument(ERR_EMPTY_DISJUNCTION);
    }
    
    vector<pair<string, string>> disj;
    
    stringstream ss(expr);
    string temp;
    char delim = CLAUSE_DELIMITER;

    while(getline(ss, temp, delim)) {
        if(temp.empty() || temp.size() <= 2) {
            throw invalid_argument(ERR_EMPTY_DISJUNCTION);
        }

        if(temp.front() != DISJUNCTION_START_CHAR || temp.back() != DISJUNCTION_END_CHAR) {
            throw invalid_argument(ERR_MISSING_DISJUNCTION_PARENS);
        }

        temp = (temp.substr(1, temp.size() - 2));
        disj.push_back(split_literals(temp));
        
        #ifdef DEBUG
            cout << " vector<string> split_to_disjunctions(string &expr): " << disj.back().first << " " <<disj.back().second << '\n';
        #endif
    }

    return disj;
}

pair<string, string> split_literals(string &disj) {
    pair<string, string> literals;
    
    size_t pos = disj.find_first_of(LITERAL_DISJUNCTION_JOIN);

    if(pos == disj.npos) {
        throw invalid_argument(ERR_MISSING_DISJUNCTION_LITERAL_JOIN);
    }

    string literal1 = disj.substr(0, pos);
    string literal2 = disj.substr(pos + 1);

    literals.first = literal1;
    literals.second = literal2;

    return literals;
}

literal assign_num_and_sign(string literal, unordered_map<string, int> &map) {
    if(literal.size() < 2) {
        throw invalid_argument(ERR_LITERAL_TOO_SHORT);
    }
    
    bool sign = literal.front() == '-'? false : true;
    int num = -1;

    if(sign) { 
        if(literal.front() != LITERAL_START_CHAR) {
            throw invalid_argument(ERR_LITERAL_START_CHAR);
        }

        if(map.find(literal) != map.end()) {
            num = map[literal];
        }
        else {
            try {
                // check if a number is valid
                num = stoi(literal.substr(1));

                // assign a new number for the literal based on the map
                num = map.size();
                map.insert(make_pair(literal, num));

            }
            catch(exception &e) {
                throw invalid_argument(ERR_INVALID_LITERAL_NAMING);
            }
        }

        return make_pair(num, sign);
    }

    // from here we know sign is negative
    if(literal[1] != LITERAL_START_CHAR) {
        throw invalid_argument(ERR_LITERAL_START_CHAR);
    }

    // remove the minus sign
    literal = literal.substr(1);

    if(map.find(literal) != map.end()) {
        num = map[literal];
    }
    else {
        try {
            stoi(literal.substr(1));

            num = map.size();
            map.insert(make_pair(literal, num));
        }
        catch(exception &e) {
            throw invalid_argument(ERR_INVALID_LITERAL_NAMING);
        }
    }

    return make_pair(num, sign);
}