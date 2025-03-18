#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <cassert>
#include <algorithm>

#include "../include/2sat.h"
#include "../include/parser.h"

#define GREEN "\033[1;92m"  // Bright neon green
#define RED "\033[1;91m"    // Bright neon red
#define RESET "\033[0m"     // Reset to default terminal color

// example usage 2sat (x1Vx2)&(nx1Vx2)&(x3Vx4)
using namespace std;

int main(int argc, char *argv[]) {
    try {
        if(argc != 2) {
            cerr << "Invalid usage! Try: ./2sat <expression>\n";
        }

        unordered_map<string, int> literal_map;

        string expr(argv[1]);

        vector<pair<string, string>> disj_str = split_to_disjunctions(expr);

        vector<pair<literal, literal>> disj;

        for_each(disj_str.begin(), disj_str.end(), [&](pair<string, string> d){
            literal literal1 = assign_num_and_sign(d.first, literal_map);
            literal literal2 = assign_num_and_sign(d.second, literal_map);

            disj.push_back({literal1, literal2});
        });
        
        #ifdef DEBUG
            cout << "Map size: " << literal_map.size() << '\n';
        #endif // DEBUG

        Sat2Solver solver(literal_map.size());

        for_each(disj.begin(), disj.end(), [&](pair<literal, literal> d){
            // cout << d.first.first << "  " << d.first.second << " s " << d.second.first << " "  << d.second.second <<  endl;
            solver.add_disjunction(d.first.first, d.first.second, d.second.first, d.second.second);
        });

        bool is_solved = solver.solve();

        cout << "The given CNF is " << (is_solved? GREEN "satisfiable" : RED "unsatisfiable") << RESET << '\n';

        if(is_solved) {
            cout << "Assignments in order that they appeared in CNF:\n";

            vector<bool> assign = solver.get_assignment();
            for(size_t i = 0; i < assign.size(); ++i) {
                cout << (assign[i]? GREEN "true" : RED "false") << RESET << '\n';
            }
        }

    }
    catch(exception &e) {
        cerr << e.what() << '\n';    
    }

    return 0;
}