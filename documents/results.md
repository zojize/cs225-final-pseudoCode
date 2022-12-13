- Airline:

- Airpots: vertex class. Used for graph construction vertex class
    - stored airport id, name, itat, icao, latitude, and longitude
    - latitude and longitude are used for edge weight calculation
    - constructor:
        - default constructor: no input
        - constructor with vector as input: construct using information in the vector
        - constructor with corresponding inputs as class variables: assign inputs to the class variables
    - overwritten operators are used for algorithms in Algorithms.hpp (dijkstra, A*, prims)

- CsvReader: convert data in the csv file into the data structure that is applicable for graph construction

- Graph: using adjacency list and unordered map to construct the graph
    - default constructor
    - vertex:
        - add_vertex
        - remove_vertex
        - get_all_vertices
        - contains_vertex
    - edge:
        - struct Edge
            - default constructor
            - constructor with input: source, destination, weight
            - stored source, destination, weight
            - overwritten operator== for comparison with other edge
        - add_edge
        - remove_edge
        - get_all_edges
        - get_edge_weight
        - contains_edge
    - other algorithm:
        - get_adjacent: get all adjacent vertices according to the input vertex
        - bfs_walk: bfs walk through the graph

- Route: used in build graph method for edge construction
    - stored airline_id, source_airport_id, destination_airport_id
    - rewrite operator to use in build graph method
    - constructor: accept the input listed above and assign them to the class
    variables

- Algorithm:

    - BFS:
        Using the Labels to determine the weight of edges, after set the label of       edges. Using queue to travesal the graph and find the shortest way.
        - get_label
        - set_label
        - bfs_walk_impl
        - bfs_init

    - A* search algorithm：

    - Since dijkstra is the basic algorithm of A*, so we implant the A* on the basis of dijkstra.

    - for dijkstra, we using PriorityQueue to find the shoortest way between nodes, and caclulate the weight(from src to dst) each steep. we will get the node weight as total distance and find the shortest path.

    - for A*, we are doing most of the part same, but we need to estimate the Euclidean distance from the current point to the end point, which help algorithm find the shortest path more accurate.
  
        - find_shortest_path_dijkstra
        - find_shortest_path_A_star

    - Prims

    - Using the prims algorithm in MST, we only need to know the weight of edges(distance between nodes). By using PriorityQueue to find the shortest path in each nodes, by adding up we can find the shortest path between the src node to dst node.
        - prims

- Canvas: Visualize the route between the two airports by building a canvas
    - default constructor
    - line
    - fill_rect
    - writeToFile
    - _plot
    - _mix
