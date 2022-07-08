## AED_T06_G60 - STCP Public Transport Navigation

> **2021/2022** - 2nd Year, 1st Semester
> 
> **Course** - AED (Algoritmos e Estruturas de Dados)
> 
> **Project developed by**
> - Isabel Amaral (up202006677)
> - Milena Gouveia (up202008862)
> - Sofia Moura (up201907201)

### Project Description

The purpose of this project was to implement a series of algorithms to calculate several versions of what would be considered a "best path", in order to help anyone who would want to use the STCP Public Transport Navigation System (Sociedade de Transportes Colectivos do
Porto). 

For testing purposes, we had access to a detailed dataset containing real data about all the STCP lines and stops, as well as the location (latitude and longitide) of these, which we were able to use to create several graphs. Using the given coordinates of each stop and the Haversine formula, we were able to calculate the distance between two consecutive stops, which we used as the weight of a graph's edge.

### Implemented Features

The different definitions of "best path" we considered, given a source stop and a destination stop, were listed in the project's description (pt) - [here](./docs/project-description.pdf):

- **Minimum number of stops** - Path that passes by the lower number of stops, disregarding the number of times the user would have to change buses.
- **Minimum number of stops without changing lines** - Path that passes by the lower number of stops without ever changing lines. This scenario may not be able to find a solution, given that sometimes it may not exist one single line that connects two locations.
- **Shortest Path** - Path that can be used to travel the lowest distance, disregarding the number of times the user would have to change buses.
- **Cheapest Path** - Path that can be taken in order to pass by the lowest number of "city zones" and, therefore, would require a least expensive ticket.

Other implemented features:

- **Interactive Menu** - In order to test and demonstrate the many features developed, we created a simple menu. This allows the user to either view a listing of all the bus stops near a given location or explore the different "best path" deffinitions given a start and end location.
- **Code documentation** - All the implemented classes were documented using doxygen. The complete generated documentation can be checked in the [docs directory](./docs/output/html/). Alternatively just open the [index.html](./docs/output/html/index.html) in your browser.

### Program Development State

Overall all the scenarios implemented seemed to be working properly. We learned in which contexts it makes sense to use some commonly used graph algorithms, such as DFS, BFS and Dijkstra's Algorithm.

Some details regarding implementation:

- For all our scenarios, it's considered the possibility that the user may need to walk a certain distance (defined by input) between stops. This also means that the input start and end coordinates may not correspond to the coordinates of an actual stop.
- We used two different types of graphs to represent the dataset:
    - One object of the class Graph, which represented the overall STCP network, containing every stop from every line and the connections between consecutive stops from the same line.
    - A list of obejcts of the class LineGraph, similar to the Graph class, but each object only containing the information regarding the stops and connections between stops of a specific line.
- In the Graph object we also added extra edges between stops that did not belong to the same line or which were not consecutive, but that were close enough so that the user had the possibility of walking between those two stops in case this contributed to a better path.

For a more detailed project report (pt) check out ppt presentation [here](./docs/presentation.pdf).