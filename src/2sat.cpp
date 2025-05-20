#include "../include/2sat.h"

using namespace std;

Sat2Solver::Sat2Solver(int _n_vars) : n_vars(_n_vars), 
                                    n_vertices(_n_vars * 2),
                                    adj_list(_n_vars * 2),
                                    adj_list_r(_n_vars * 2),
                                    order(),
                                    used(2 * _n_vars, false),
                                    component_num(_n_vars * 2, -1),
                                    assignment(_n_vars){

}

Sat2Solver::~Sat2Solver() {

}

void Sat2Solver::add_disjunction(int a, bool sign_a, int b, bool sign_b) {
    a = (a << 1) ^ sign_a;
    b = (b << 1) ^ sign_b;

    int op_a = a ^ 1;
    int op_b = b ^ 1;

    this -> adj_list[op_a].push_back(b);
    this -> adj_list[op_b].push_back(a);

    this -> adj_list_r[a].push_back(op_b);
    this -> adj_list_r[b].push_back(op_a);
}

vector<bool> Sat2Solver::get_assignment() {
    return this -> assignment;
}

void Sat2Solver::dfs1(int v) {
    used[v] = true;
    for(int u : adj_list[v]) {
        if(!used[u]) {
            dfs1(u);
        }
    }
    order.push_back(v);
}

void Sat2Solver::dfs2(int v, int m) {
    component_num[v] = m;
    for(int u : adj_list_r[v]) {
        if(component_num[u] == -1) {
            dfs2(u, m);
        }
    }
}

bool Sat2Solver::solve() {
    this -> order.clear();
    this -> used.assign(this -> n_vertices, false);
    
    // dfs1 to topologically sort the graph
    for(int i = 0; i < this -> n_vertices; ++i) {
        if(!used[i]) {
            dfs1(i);
        }
    }

    #ifdef PRINT_TOPO_SORTED 
        for(int i = n_vertices - 1; i >= 0; --i) {
            cout << this -> order[i] << " ";
        }

        cout << '\n';
    #endif // PRINT_TOPO_SORTED
    
    // dfs2 to find all the strongly connected components
    this -> component_num.assign(this -> n_vertices, -1);
    for(int i = 0, j = 0; i < this -> n_vertices; ++i) {
        int v = this -> order[this -> n_vertices - i - 1];
        if(this -> component_num[v] == -1) {
            dfs2(v, j++);
        }
    }

    #ifdef PRINT_SCCS
        for(int i = 0; i < n_vertices; ++i) {
            cout << "Vertex : " << i << " Component number : " << component_num[i] << '\n';
        }
    #endif // PRINT_SCCS

    this -> assignment.assign(this -> n_vars, false);
    for(int i = 0; i < n_vertices; i += 2) {
        if(this -> component_num[i] == this -> component_num[i + 1]) {
            return false;
        }
        this -> assignment[i / 2] = this -> component_num[i] > this -> component_num[i + 1];
    }

    return true;
}