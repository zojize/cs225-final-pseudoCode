## Leading Question

- A* search algorithm | Iterative DFS | BFS
- Graph visualization

Our project uses the "openflight" datasets to calculate the shortest path traveling between two airports using the A\* search algorithm, using the euclidean distance as the weights of our edges and as the approximated distance to destination in our A* search procedure. We will also try different approaches such as Dijkstra's and BFS to compare the trade-offs between different algorithms, as well as generating a visualization of our result.

## Dataset Acquisition

Data of airport and route:

- <https://openflights.org/data.html> will be our main source of data
- <https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports.dat>
- <https://raw.githubusercontent.com/jpatokal/openflights/master/data/routes.dat>

## Data Format

- <https://openflights.org/data.html>
  - comma separated entries in `.csv` format containing data about airline information, routes, airports, etc.
- [Airports](https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports.dat)
  - `.csv` format data containing information about airports
  - Entries: `Airport ID, Name, City, Country, IATA, ICAO, Latitude, Longitude, Altitude, Timezone, DST, Tz database time zone, Type, Source` 
- [Routes](https://raw.githubusercontent.com/jpatokal/openflights/master/data/routes.dat)
  - `.csv` format data containing information about routes
  - Entries: `Airline, Airline ID, Source airport, Source airport ID, Destination airport, Destination airport ID, Codeshare, Stops, Equipment`
- We will be using the airports' data as the vertices for our graph. It will be storing the airport's `Airport ID, Name, City, Country, Longitude, Altitude`. The routes data will be use as edges for our graph, and the euclidean distance between the source and destination will be used as the weight on our edges.

## Data Correction

- Invalid or unreachable source / destination pairs should provide an accurate and clear error message to the user
- If the source dataset contains invalid routes (e.g. non-existent id), that entry will be discarded
- If an airport is unreachable, it will also be discarded
- Me might collect, fix and store all the data in a single `.json` file for the ease of usage.
- The two inputs will be the departure and landing airport. First, we will use the airport data to check if airports exist in both areas. If the departure or landing airport does not exist, we will return a message like "No departure airport found" or "No landing airport found". If both airports exist, we will use the route data to check if a route exists between the two airports. If there is no direct route, we will compare the number of stops, etc. of different connecting routes to select the best route

## Data Storage

- The airline data will be stored internally by a graph where each vertex contains the information of the airport and airlines. With each weighted edge representing the routes for the flights and the approximate distance between them.
- The estimated space efficiency is $O(|\text{airports}| + |\text{routes}|)$

## Algorithm

- `optional<vector<route>> find_shortest_path(airport_id source, airport_id destination);`
  - `@returns` A sequence of routes to take to reach the designated airport from the source airport if the viable path is found, otherwise an empty value is return.
  - `@param source` A starting airport id
  - `@param destination` Destination airport id
  - `@implementation` This function uses the A* search algorithm and has the worst case time complexity of $O(|E|)$ and worst case space complexity of $O(|V|)$. (where $|V|$ is the number of airports and $V$)

- `void draw_path(canvas c, vector<route> path);`
  - `@implementation` Projects the given path on to a world map on a designated canvas. Its time complexity is $O(n)$.

## Timeline (Approximate)

- [ ] 11/11 Data acquisition and processing
- [ ] 11/13 Makefiles, finish project setup
- [ ] 11/20 Algorithm MVP finish
- [ ] 11/27 Polishing code and complete test cases
- [ ] 12/04 Finish README
- [ ] 12/08 Presentation
