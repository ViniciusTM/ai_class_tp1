#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include "cLib/structures.h"


int main(int argc, char *argv[]) {
    std::ifstream file("instancias/g1.txt");
    std::ofstream out("solucoes/saida.txt");
    std::string line;


    while(std::getline(file, line)) {
        Game game(line, 3);
        Solution sol;

        if (std::strcmp(argv[1], "bfs") == 0) {
            sol = game.bfs();
        }
        else if (std::strcmp(argv[1], "ids") == 0) {
            sol = game.ids();
        }
        else if (std::strcmp(argv[1], "ucs") == 0) {
            sol = game.ucs();
        }
        else if (std::strcmp(argv[1], "greedy_bfs_sd") == 0) {
            sol = game.greedy_bfs("simple dist");
        }
        else if (std::strcmp(argv[1], "greedy_bfs_cb") == 0) {
            sol = game.greedy_bfs("city block");
        }
        else if (std::strcmp(argv[1], "a_star_sd") == 0) {
            sol = game.a_star("simple dist");
        }
        else if (std::strcmp(argv[1], "a_star_cb") == 0) {
            sol = game.a_star("city block");
        }
        else if (std::strcmp(argv[1], "local_search_sd") == 0) {
            sol = game.local_search("simple dist");
        }
        else if (std::strcmp(argv[1], "local_search_cb") == 0) {
            sol = game.local_search("city block");
        }
        else {
            std::cout << "Invalid argv" << std::endl;
            return 0;
        }

        sol.print_output(out);
    }
    out.close();
    file.close();
}