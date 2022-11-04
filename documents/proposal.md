## Leading Question 

- A* search algorithm | Iterative DFS | BFS
- Graph visualization

Our project uses the openflight datasets to calculate the shortest path traveling between two airports using the A\* search algorithm, using the euclidean distance as the weights of our edges and as the approximated distance to destination in our A* search procedure. We will also try different approaches such as Dijkstra's and BFS to compare the trade offs between different algorithms, as well as generating a visualization of our result.

## Dataset Acquisition

- https://openflights.org/data.html will be our main source of data
- potentially other databases containing data for duration of the flight route which we can use for the weights instead.

## Data Format

- https://openflights.org/data.html
  - comma separated `.dat` files containing data about airline information, routes, airports, etc.

## Data Correction

- Invalid or unreachable source / destination pairs should provide an accurate and clear error message to the user
- If the source dataset contains invalid routes (e.g. non-existent id), that entry will be discarded
- If an airport is unreachable, it will also be discarded
- Me might collect, fix and store all the data in a single `.json` file for the ease of usage.

## Data Storage

- The airline data will be stored internally by a graph where each vertex contains the information of the airport and airlines. With each weighted edge representing the routes for the flights and the approximate distance between them.
- The estimated space efficiency is $O(|\text{airports}| + |\text{routes}|)$

## Algorithm 

- `optional<vector<route>> find_shortest_path(airport_id source, airport_id destination);`
  - `get_shortest_path` returns a sequence of routes to take to reach the designated airport from the source airport if the viable path is found, otherwise an empty value is return. This function uses the A* search algorithm and has a worst case time complexity of $O(|\text{airports}|)$ and worst case space complexity of $O(|\text{routes}|)$.

- `void draw_path(canvas c, vector<route> path);`
  - `draw_path` draws the flight path on a world map on a designated canvas. Its time complexity is $O(|\text{path}|)$.

## Timeline

- [ ] 11/07 Data acquisition and processing
- [ ] 11/09 Makefiles, finish project setup
- [ ] 11/13 Algorithm MVP finish
- [ ] 11/27 Polishing code and complete test cases
- [ ] 12/04 Finish README
- [ ] 12/08 Presentation
