# CS225 Final Project: OpenFlights

### Team member: Boyuan Zheng, Jeff Zou, Kaiwen Ren, Lingxiang Cai

## Project Summary

Our project uses the "openflight" datasets to calculate the shortest path traveling between two airports and generates a visualization of our result.

## Deliverables
- [Presentation](https://www.youtube.com/watch?v=dQw4w9WgXcQ)
- [Report](https://docs.google.com/document/d/1UQiLYt6gcJrWr5xuSKkuioCOHEaB_xroA0EShy5fWwg/edit?usp=sharing)

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

- Airline: /* TBD */

- Airpots: /* TBD */

- CsvReader: /* TBD */

- Graph: /* TBD */

- Route: /* TBD */

## Data

Our test data was taken using /* TBD */, stored in the `data/` directory.

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
We are using Cmake to test our code, before you run the test, you should complete following process in your terminal:
```
mkdir build
cd build
```
This process will create a build folder, and you should enter the build directory, you should run cmake under the build:
```
cmake ..
```

## Test
`test.cpp` is the file taht contains our test cases. To use the full test:
```
make test
./test
```
Test case can also be partially tested：
```
./test [Graph]
./test [Dijkstra]
./test [Astar]
```

## Documents

Our signed contract and development log can be found in the `documents/` directory.

## Feedback

All feedback from our project mentor can be found in the `feedback/` directory.
