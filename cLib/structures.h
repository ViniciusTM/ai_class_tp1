#pragma once

#include <vector>
#include <string>
#include <ctime>
#include <fstream>

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

struct State {
    std::vector<int> config;
    std::vector<int> steps;
    int emptyPos; 
    int n;
    int heuristic_dist;

    State(State*);
    State(int);
    State(void);
    // State& operator =(State&);

    State make_move(int, int, int);
    std::vector<State> generate_actions();
    bool check();
    void print_steps();
    void print_state();
    void print_steps(std::ofstream&);
};

struct Node {
    std::vector<Node*> children;
    int depth;

    Node(int);
};

struct TabuList {
    Node *root;
    int size;

    TabuList(int);
    ~TabuList();

    void clear_tree(Node*);
    bool find(State s);
    bool find_and_add(State s);
    void add(State s);
};

struct Solution {
    State state;
    
    bool solvable;
    int nStatesVisited;
    clock_t stopWatch;
    double elapsedTime;

    Solution();
    void print_output(std::ofstream&);
};

struct Game {
	int n;
	State state;

	Game(State&);
    Game(std::string&, int=3);
    
    Solution bfs();
    void dfs(int, Solution&);
    Solution ids();
    Solution ucs();

    Solution a_star(std::string);
    Solution greedy_bfs(std::string);

    Solution local_search(std::string);
};