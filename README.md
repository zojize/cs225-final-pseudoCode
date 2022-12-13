# CS225 Final Project: OpenFlights

### Team member: Boyuan Zheng, Jeff Zou, Kaiwen Ren, Lingxiang Cai

![preview](documents/assets/finalPic.png "finalPic")

## Project Summary

Our project uses the "openflight" datasets to calculate the shortest path traveling between two airports and generates a visualization of our result.

We use the A\* search algorithm, using the euclidean distance as the weights of our edges and as the approximated distance to destination in our A\* search procedure. We also use Prim's algorithm as a main search algorithm, by using PriorityQueue to find the best path for each two nodes.

We also try different approaches such as Dijkstra's and BFS to compare the trade-offs between different algorithms.

And we use prim's algorithm to optimize our image.

## Deliverables

- [Presentation video](https://www.youtube.com/watch?v=dQw4w9WgXcQ)
- [Presentation slides](https://docs.google.com/presentation/d/1DUc7WUnn43Rt1Ul_V4eLH_oWoyoy5Mtpffktlazd7Zg/edit#slide=id.g1b506828009_1_7)
- [Report](documents/results.md)

## File Structure

- `cs225-final-pseudoCode`
    - `data/`
        - `.csv` data file
    - `documents/`
        - team contract and team proposal
    - `entry/`
        - `main.cpp` location
    - `feedback/`
        - feedback
    - `lib/`
        - classes provided by the course
    - `src/`
        - All code files can be found in the `src/` directory. To run the code:

        1. Compile using `g++ main.cpp`

        2. Run using `./a.out`

        3. Insert any entropy value (as long as it is an integer!)
    - `tests/`
        - `test.cpp` and three `.csv` file which contain all test cases

## Code description

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

## Data

Our data was stored in the `data/` directory.

1. [Airlines](https://openflights.org/data.html)
    - comma separated entries in `.csv` format containing data about airline information, routes, airports, etc.

2. [Airports](https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports.dat)
    - `.csv` format data containing information about airports
    - Entries: `Airport ID, Name, City, Country, IATA, ICAO, Latitude, Longitude, Altitude, Timezone, DST, Tz database time zone, Type, Source`

3. [Routes](https://raw.githubusercontent.com/jpatokal/openflights/master/data/routes.dat)
    - `.csv` format data containing information about routes
    - Entries: `Airline, Airline ID, Source airport, Source airport ID, Destination airport, Destination airport ID, Codeshare, Stops, Equipment`

- The airports' data is used as the vertices for the graph. It will be storing the airport's `Airport ID, Name, City, Country, Longitude, Altitude`. The routes data is used as edges for our graph, and the euclidean distance between the source and destination is used as the weight on the edges.

## Preparing Your Code for Testing

We are using CMake to test our code, before you run the test, you should complete following process in your terminal:

```
mkdir build
cd build
```

This process will create a build folder, and you should enter the build directory, you should run CMake under the build:

```
cmake ..
```

## Test

`test.cpp` is the file that contains our test cases. To use the full test:

```
make test
./test
```

Test case can also be partially tested:

```
./test [Graph]
./test [Dijkstra]
./test [Astar]
```

## Documents

Our signed contract and development log can be found in the `documents/` directory.

## Feedback

All feedback from our project mentor can be found in the `feedback/` directory.
