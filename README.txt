Para compilar o código use o seguinte comando:
	g++ main.cpp cLib/structures.cpp -o exe

Uma vez compilado execute o código usando o seguinte comando:
	./exe ARG

onde ARG é uma das seguinte opções:
 bfs (para resolver as instâncias usando Breadth-first search)
 ids (para resolver as instâncias usando Iterative deepening search)
 ucs (para resolver os instâncias usando Uniform-cost search)
 greedy_bfs_sd  (para resolver as instâncias usando Greedy best-first search com a heurística de distância simples)
 greedy_bfs_cb  (para resolver as instâncias usando Greedy best-first search com a heurística de distância de manhattan)
 a_star_sd  (para resolver as instâncias usando A* search com a heurística de distância simples)
 a_star_cb  (para resolver as instâncias usando A* search com a heurística de distância de manhattan)
 local_search_sd  (para resolver as instâncias usando Busca Local com a heurística de distância simples)
 local_search_cb  (para resolver as instâncias usando Busca Local com a heurística de distância de manhattan)


Para gera instâncias aleatórias (sem garantia de solução) use o seguinte comando
	pytho3 gera_insta.py ARG1 ARG2

onde ARG1 é o tamanho n da instancia (n^2-Puzzle, tabuleiro nxn) e ARG2 o número de instâncias.
Um arquivo na pasta instâncias será gerado com nome n-m.txt. 



