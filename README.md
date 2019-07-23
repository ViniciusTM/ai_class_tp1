# AI for solving the 9-puzzle game

This work is the result of a project developed for a Artificial Intelligence class conducted at Universidade Federal de Minas Gerais. The objective is to use classical algorithms for solving the 9-Puzzle game.

## Running the program:

Tun the following comand for compiling:

`g++ main.cpp cLib/structures.cpp -o exe`

Then execute with the sollowing command:
`./exe ARG`

where ARG is one of the folling options:
- bfs (solve with Breadth-first search)
- ids (solve with Iterative deepening search)
- ucs (solve with Uniform-cost search)
- greedy_bfs_sd  (solve with Greedy best-first search using simple distance heuristic)
- greedy_bfs_cb  (solve with Greedy best-first search using manhattan distance heuristic)
- a_star_sd  (solve with A* search using simple distance heuristic)
- a_star_cb  (solve with A* search using manhattan distance heuristic)
- local_search_sd  (solve with Local Search using simple distance heuristic)
- local_search_cb  (solve with Local Search using manhattan distance heuristic)

For generating random instances use the python script "gera_insta.py":

`pytho3 gera_insta.py ARG1 ARG2`

Where ARG1 is the size of the instance (n^2-Puzzle, board n x n) and ARG2 is the number of instances.
