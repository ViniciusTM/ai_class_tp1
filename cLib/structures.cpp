#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <sstream>
#include <ctime>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include "structures.h"

// Internal functions
int simple_dist(const State& s) {
    int side = static_cast<int>(std::sqrt(s.config.size()));
    int dist = 0;

    for (int i=0; i<s.config.size(); i++) {
        int right_pos = s.config[i] - 1;
        int pos = i;

        if (right_pos == -2) {
            right_pos = 8;
        }

        if (right_pos != pos) {
            dist += 1;
        }
    }

    return dist;
}

int city_block_dist(const State& s) {
    int side = static_cast<int>(std::sqrt(s.config.size()));
    int dist = 0;

    for (int i=0; i<s.config.size(); i++) {
        int right_pos = s.config[i] - 1;
        int pos = i;

        if (right_pos == -2) {
            right_pos = 8;
        }

        dist += std::abs(right_pos / side - (pos) / side) + std::abs(right_pos % side - (pos) % side);
    }

    return dist;
}


// Node
Node::Node(int n) {
    for (int i=0; i<n; i++) {
        children.push_back(NULL);
    }
}

TabuList::TabuList(int n) {
    root = new Node(n);
    size = 0;
}

TabuList::~TabuList() {
    clear_tree(root);
}

void TabuList::clear_tree(Node *node) {
    if (node != NULL) {
        for (Node* n : node->children) {
            clear_tree(n);
        }
        delete node;
    }
}

bool TabuList::find(State s) {
    Node *current;

    current = root;
    for (int i : s.config) {
        bool stop = true;

        if (i == -1) {
            if (current->children[0]) {
                current = current->children[0];
                stop = false;
            }
        }
        else {
            if (current->children[i]) {
                current = current->children[i];
                stop = false;
            }
        }

        if (stop) {
            return false;
        }
    }

    return true;
}

bool TabuList::find_and_add(State s) {
    Node *current;

    current = root;
    for (int i : s.config) {
        bool stop = true;

        if (i == -1) {
            if (current->children[0]) {
                current = current->children[0];
                stop = false;
            }
        }
        else {
            if (current->children[i]) {
                current = current->children[i];
                stop = false;
            }
        }

        if (stop) {
            this->add(s);
            return false;
        }
    }

    if (current->depth > s.steps.size()) {
        current->depth = s.steps.size();
        return false;
    }
    else {
        return true;
    }    
}

void TabuList::add(State s) {
    int i = 0;
    int n = s.config.size();
    Node *current;

    current = root;
    while(current && i<n) {
        bool stop = true;
        int idx = s.config[i];

        if (idx == -1) {
            if (current->children[0]) {
                current = current->children[0];
                i++;
                stop = false;
            }
        }
        else {
            if (current->children[idx]) {
                current = current->children[idx];
                i++;
                stop = false;
            }
        }

        if (stop) {
            break;
        }
    }

    for (int k=i; k<n; k++) {
        int j = s.config[k];

        if (j == -1) {
            current->children[0] = new Node(n);
            current = current->children[0];
        }

        else {
            current->children[j] = new Node(n);
            current = current->children[j];
        }         
    }
    current->depth = s.steps.size();
    size ++;
}


// State
State::State(State *s) {
    config = s->config;
    steps = s->steps;
    emptyPos = s->emptyPos;
    n = s->n;
}

State::State(int size) {
    n = size;

    config.resize(size);
    for (int i=0; i<size; i++) {
        config[i] = -1;
    }
}

State::State() {}


State State::make_move(int i, int j, int move) {
    State s(this);

    std::swap(s.config[i], s.config[j]);
    s.emptyPos = j;
    s.steps.push_back(move);

    return s;
}

std::vector<State> State::generate_actions() {
    std::vector<State> results;
    int side = static_cast<int>(std::sqrt(n));

    if (this->emptyPos / side == (this->emptyPos - 1) / side && (this->emptyPos - 1 >= 0)) {
        results.push_back(this->make_move(this->emptyPos, this->emptyPos - 1, LEFT));
    }

    if (this->emptyPos / side == (this->emptyPos + 1) / side && (this->emptyPos + 1 < this->config.size())) {
        results.push_back(this->make_move(this->emptyPos, this->emptyPos + 1, RIGHT));
    }

    if (this->emptyPos - side >= 0) {
        results.push_back(this->make_move(this->emptyPos, this->emptyPos - side, UP));
    }

    if (this->emptyPos + side < this->config.size()) {
        results.push_back(this->make_move(this->emptyPos, this->emptyPos + side, DOWN));
    }

    return results;
}

bool State::check() {
    for (int i=1; i<9; i++) {
        if (config[i-1] != i) {
            return false;
        }
    }
    return true;
}

void State::print_steps() {
    for (int i : this->steps) {
        switch(i) {
            case UP: 
                std::cout << "UP ";
                continue;

            case DOWN:
                std::cout << "DOWN ";
                continue;

            case LEFT:
                std::cout << "LEFT ";
                continue;

            case RIGHT:
                std::cout << "RIGHT ";
                continue;

            default: ;
        }
    }
    std::cout << std::endl;
}

void State::print_state() {
    int side = static_cast<int>(std::sqrt(n));

    for (int i=0; i<n; i++) {
        std::cout << config[i] << " ";
        if (i % side == side-1) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

void State::print_steps(std::ofstream& file) {
    for (int i : this->steps) {
        switch(i) {
            case UP: 
                file << "UP ";
                continue;

            case DOWN:
                file << "DOWN ";
                continue;

            case LEFT:
                file << "LEFT ";
                continue;

            case RIGHT:
                file << "RIGHT ";
                continue;

            default: ;
        }
    }
    file << std::endl; 
}


// Solution
Solution::Solution() {
    nStatesVisited = 0;
    stopWatch =  clock();
}

void Solution::print_output(std::ofstream& file) {
    if (!solvable) {
        file << "SOLUTION NOT FOUND" << std::endl;
        file << std::endl;
        return ;
    }
    else {
        state.print_steps(file);
    }
    
    file << state.steps.size() << " " << nStatesVisited << " " << elapsedTime << std::endl;
    file << std::endl;
}


// Game
Game::Game(State &config) {
    state.config = config.config;
    n = state.config.size();
    state.n = n;
}

Game::Game(std::string& config, int size) {
    n = static_cast<int>(pow(size, 2));
    state.config.reserve(n);
    state.n = n;

    std::stringstream line(config);
    int value;

    while(line >> value) {
        state.config.push_back(value);

        if (value == -1) {
            state.emptyPos = state.config.size() - 1;
        }
    }
}

Solution Game::bfs() {
    std::queue<State> q;
    TabuList tabu(this->n);
    Solution sol;

    if (this->state.check()) {
        sol.elapsedTime = static_cast<double>(clock() - sol.stopWatch) / CLOCKS_PER_SEC;
        sol.solvable = true;
        sol.state = State(&this->state);
        return sol;
    }

    for (State state : this->state.generate_actions()) {
        q.push(state);
        tabu.add(state);
    }

    while (q.size() != 0) {
        State s = q.front();
        q.pop();

        sol.nStatesVisited += 1;

        if (s.check()) {
            sol.elapsedTime = static_cast<double>(clock() - sol.stopWatch) / CLOCKS_PER_SEC;
            sol.solvable = true;
            sol.state = State(&s);
            return sol;
        }

        if (s.steps.size() > 31) {
            sol.elapsedTime = static_cast<double>(clock() - sol.stopWatch) / CLOCKS_PER_SEC;
            sol.solvable = false;
            return sol;
        }

        for (State state : s.generate_actions()) {
            if (tabu.find(state)) {
                continue;
            }
            else {
                q.push(state);                
                tabu.add(state);
            }        
        }
    }

    std::cout << "algo deu bem errado" << std::endl;
}

void Game::dfs(int k, Solution& sol) {
    TabuList tabu(this->n);

    if (this->state.check()) {
        sol.elapsedTime = static_cast<double>(clock() - sol.stopWatch) / CLOCKS_PER_SEC;
        sol.solvable = true;
        sol.state = State(&this->state);
        return ;
    }

    std::stack<State> stack;
    for (State state : this->state.generate_actions()) {
        stack.push(state);
        tabu.add(state);
    }

    while (stack.size() > 0) {
        State s = stack.top();
        stack.pop();

        //s.print_steps();

        sol.nStatesVisited += 1;

        if (s.check()) {
            sol.elapsedTime = static_cast<double>(clock() - sol.stopWatch) / CLOCKS_PER_SEC;
            sol.solvable = true;
            sol.state = State(&s);
            return ;
        }

        for (State state : s.generate_actions()) {
            if (state.steps.size() > k) {
                continue;
            }

            if (tabu.find_and_add(state)) {
                continue;
            }
            stack.push(state);                       
        }
    }
    //std::cout << "size: " << tabu.size << std::endl;
}

Solution Game::ids() {
    Solution sol;
    sol.solvable = false;

    for (int k=1; k<=31; k++) {
        this->dfs(k, sol);

        if (sol.solvable) {
            return sol;
        }
    }

    return sol;
}

Solution Game::ucs() {
    TabuList tabu(this->n);
    Solution sol;
    
    auto comp = [](State a, State b) {return a.steps.size() > b.steps.size(); };    
    std::priority_queue<State, std::vector<State>, decltype(comp)> queue(comp);

    if (this->state.check()) {
        sol.elapsedTime = static_cast<double>(clock() - sol.stopWatch) / CLOCKS_PER_SEC;
        sol.solvable = true;
        sol.state = State(&this->state);
        return sol;
    }

    for (State state : this->state.generate_actions()) {
        queue.push(state);
        tabu.add(state);
    }

    while (queue.size() != 0) {
        State s = queue.top();
        queue.pop();

        sol.nStatesVisited += 1;

        if (s.check()) {
            sol.elapsedTime = static_cast<double>(clock() - sol.stopWatch) / CLOCKS_PER_SEC;
            sol.solvable = true;
            sol.state = State(&s);
            return sol;
        }

        if (s.steps.size() > 31) {
            sol.elapsedTime = static_cast<double>(clock() - sol.stopWatch) / CLOCKS_PER_SEC;
            sol.solvable = false;
            return sol;
        }

        for (State state : s.generate_actions()) {
            if (tabu.find(state)) {
                continue;
            }
            else {
                queue.push(state);                
                tabu.add(state);
            }        
        }
    }
}

Solution Game::greedy_bfs(std::string heuristic) {
    Solution sol;
    
    if (std::strcmp(heuristic.c_str(),"city block") != 0 && std::strcmp(heuristic.c_str(),"simple dist") != 0) {
        std::cout << "Invalid heuristic" << std::endl;
        return sol; 
    }

    TabuList tabu(this->n);
    
    auto comp = [](State a, State b) {return a.heuristic_dist > b.heuristic_dist; };    
    std::priority_queue<State, std::vector<State>, decltype(comp)> queue(comp);

    if (this->state.check()) {
        sol.elapsedTime = static_cast<double>(clock() - sol.stopWatch) / CLOCKS_PER_SEC;
        sol.solvable = true;
        sol.state = State(&this->state);
        return sol;
    }

    for (State state : this->state.generate_actions()) {
        if (std::strcmp(heuristic.c_str(),"city block") == 0) {
            state.heuristic_dist = city_block_dist(state);
        }
        else {
            state.heuristic_dist = simple_dist(state);
        }
        
        queue.push(state);
        tabu.add(state);
    }

    while (queue.size() != 0) {
        State s = queue.top();
        queue.pop();

        sol.nStatesVisited += 1;

        if (s.check()) {
            sol.elapsedTime = static_cast<double>(clock() - sol.stopWatch) / CLOCKS_PER_SEC;
            sol.solvable = true;
            sol.state = State(&s);
            return sol;
        }

        for (State state : s.generate_actions()) {
            if (tabu.find_and_add(state)) {
                continue;
            }
        
            if (std::strcmp(heuristic.c_str(),"city block") == 0) {
                state.heuristic_dist = city_block_dist(state);
            }
            else {
                state.heuristic_dist = simple_dist(state);
            }
    
            queue.push(state);                
                  
        }
    }
}

Solution Game::a_star(std::string heuristic) {
    Solution sol;
    
    if (std::strcmp(heuristic.c_str(),"city block") != 0 && std::strcmp(heuristic.c_str(),"simple dist") != 0) {
        std::cout << "Invalid heuristic" << std::endl;
        return sol; 
    }

    TabuList tabu(this->n);
    
    auto comp = [](State a, State b) {return a.heuristic_dist > b.heuristic_dist; };    
    std::priority_queue<State, std::vector<State>, decltype(comp)> queue(comp);

    if (this->state.check()) {
        sol.elapsedTime = static_cast<double>(clock() - sol.stopWatch) / CLOCKS_PER_SEC;
        sol.solvable = true;
        sol.state = State(&this->state);
        return sol;
    }

    for (State state : this->state.generate_actions()) {
        if (std::strcmp(heuristic.c_str(),"city block") == 0) {
            state.heuristic_dist = city_block_dist(state);
        }
        else {
            state.heuristic_dist = simple_dist(state);
        }
        
        queue.push(state);
        tabu.add(state);
    }

    while (queue.size() != 0) {
        State s = queue.top();
        queue.pop();

        sol.nStatesVisited += 1;

        if (s.check()) {
            sol.elapsedTime = static_cast<double>(clock() - sol.stopWatch) / CLOCKS_PER_SEC;
            sol.solvable = true;
            sol.state = State(&s);
            return sol;
        }

        // if (s.steps.size() > 31) {
        //     sol.elapsedTime = static_cast<double>(clock() - sol.stopWatch) / CLOCKS_PER_SEC;
        //     sol.solvable = false;
        //     return sol;
        // }

        for (State state : s.generate_actions()) {
            if (tabu.find_and_add(state)) {
                continue;
            }
            else {
                if (std::strcmp(heuristic.c_str(),"city block") == 0) {
                    state.heuristic_dist = s.steps.size() + city_block_dist(state);
                }
                else {
                    state.heuristic_dist = s.steps.size() + simple_dist(state);
                }
        
                queue.push(state);                
            }        
        }
    }
}

Solution Game::local_search(std::string heuristic) {
    Solution sol;
    
    if (std::strcmp(heuristic.c_str(),"city block") != 0 && std::strcmp(heuristic.c_str(),"simple dist") != 0) {
        std::cout << "Invalid heuristic" << std::endl;
        return sol; 
    }

    TabuList tabu(this->n);
    
    auto comp = [](State a, State b) {return a.heuristic_dist > b.heuristic_dist; };    

    State current(&this->state);

    if (std::strcmp(heuristic.c_str(),"city block") == 0) {
        current.heuristic_dist = city_block_dist(state);
    }
    else {
        current.heuristic_dist = simple_dist(state);
    }

    while (true) {
        if (current.check()) {
            sol.elapsedTime = static_cast<double>(clock() - sol.stopWatch) / CLOCKS_PER_SEC;
            sol.solvable = true;
            sol.state = State(&current);
            return sol;
        }
        sol.nStatesVisited += 1;

        State best;
        best.heuristic_dist = 1000;
        bool stop = true;
        for (State state : current.generate_actions()) {
            if (tabu.find(state)) {
                continue;
            }
        
            if (std::strcmp(heuristic.c_str(),"city block") == 0) {
                state.heuristic_dist = city_block_dist(state);
            }
            else {
                state.heuristic_dist = simple_dist(state);
            }

            if (state.heuristic_dist <= current.heuristic_dist) {
                if (state.heuristic_dist < best.heuristic_dist) {
                    tabu.add(state);
                    best = state;
                    stop = false;
                }
            }    
        }

        if (stop) {
            sol.elapsedTime = static_cast<double>(clock() - sol.stopWatch) / CLOCKS_PER_SEC;
            sol.solvable = false;
            return sol;
        }
        current = best;
    }
}


