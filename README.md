# NavigationSystem
 
This is a navigation system that allows the user to travel from the source node to the destination node. 

The program uses weighted and directed graph for the network. 

The program uses A* algorithm to traverse and search through the graph.
(Dijkstra algorithm can be found in the past commits)

Nodes are connected with edges and the heuristic vales are assigned with the latitude and longitude of the cities. 

Concepts: class, dynamic memory allocation, data structure, A* algorithm,  
for data set, 

The data is parsed from "Data.txt". 


Format:

if root city,
- City name | latitude | longitude

if the adjacent city,
- City name | distance from root city | latitude | longitude