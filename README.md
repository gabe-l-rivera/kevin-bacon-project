# KevinBaconProject
This project was inspired by my professor, Dr. Yi Pike, from the University of Kentucky. In my software engineering course, this program was my solution to our third project of the semester, the "Six Degrees of Kevin Bacon" project. A copy of the description is as follows:  Six Degrees of Kevin Bacon is a parlor game based on the "six degrees of separation" concept, which posits that any two people on Earth are six or fewer acquaintance links apart. Movie buffs challenge each other to find the shortest path between an arbitrary actor and prolific character actor Kevin Bacon.  The “Six Degrees of Kevin Bacon” game is based on graphs. If you assign each actor to a vertex, and add an edge between two actors if they have appeared together in a movie, then you have a graph that represents the data for this game. Then the problem of finding a trail of actors to Kevin Bacon becomes a traditional graph problem: that of finding a path between two vertices. Since we wish to find a shortest path, one might think to apply Dijkstra's shortest path algorithm to this problem, but that would be overkill since Dijkstra's algorithm is meant for situations when each edge has an associated length (or weight) and the goal is to find the path with the shortest cumulative length. Since we are only concerned with finding the shortest paths in terms of the number of edges, the Breadth-First Search (BFS) algorithm will solve the problem (and use less time than Dijkstra's). BFS builds a tree of shortest paths from every actor who can reach Kevin Bacon back to Kevin Bacon. Or more generally, given a root, BFS builds a shortest-path tree from every vertex that can reach the root back to the root.  In this problem you will write a C++ program to generate the Bacon Number for any actor input by the user. The vertices in this graph problem are actors and the edge relationship is "appeared together in a movie". The goal is to find the shortest path to Kevin Bacon.