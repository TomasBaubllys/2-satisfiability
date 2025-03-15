#ifndef SAT2_H_INCLUDED
#define SAT2_H_INCLUDED

#include <vector>
#include <cstdlib>
#include "not_implemented.h"
#include "parser.h"

#define POSITIVE true;
#define NEGATIVE false;

class Sat2Solver {
private:
    // number of variables
    int n_vars;

    // number of vertices
    int n_vertices;

    // adjecency lists
    std::vector<std::vector<int>> adj_list;
    std::vector<std::vector<int>> adj_list_r;

    std::vector<int> component_num;
    std::vector<int> order;
    std::vector<bool> used;

    // variable assignment list
    std::vector<bool> assignment;

public:
    // creates a 2-sat solver object for _n_vars different variables
    Sat2Solver(int _n_vars);

    ~Sat2Solver();

    // adds sign_a a |/ sign_b b to the graph
    void add_disjunction(int a, bool sign_a, int b, bool sign_b);

    // returns a vector of variable assigments
    std::vector<bool> get_assignment();

    // dfs search to order nodes in finishing order
    void dfs1(int v);

    // dfs search to find all reachable nodes from a vertex and mark it with m
    void dfs2(int v, int m);

    // solves the 2-sat problem based on the current object
    bool solve();

    void assign_to_2sat(std::vector<std::pair<std::string, std::string>> &disjs);
};

#endif // SAT2_H_INCLUDED