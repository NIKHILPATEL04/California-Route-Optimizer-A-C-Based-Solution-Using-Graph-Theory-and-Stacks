**Efficient Pathfinding Using Graph Theory and Data Structures**


Nikhil Patel



**Purpose**


I developed this program to calculate the most efficient path between multiple locations, ensuring that every location is visited exactly once and the total distance is minimized. By applying graph theory, depth-first search (DFS), and abstract data structures such as stacks and adjacency matrices, I created a solution capable of determining the optimal route while balancing computational efficiency and accuracy.

**Graph Data Structures and Their Applications**


The foundation of my program lies in its use of graphs, represented through adjacency matrices and adjacency lists.

**Adjacency Lists:**


I chose adjacency lists for their simplicity and memory efficiency, especially for sparse graphs. They allowed me to represent direct relationships between locations (vertices) with minimal overhead. This approach was particularly useful when storing vertex names and working with smaller datasets.

**Adjacency Matrices:**
For quick access to edge weights and efficient operations on dense graphs, I implemented adjacency matrices. Their row-column structure enabled me to store all possible connections between locations, even when some edges didn’t exist. This dual approach of using both representations ensured a balance between memory efficiency and computational speed.

**Algorithmic Approach and Path Search**


The problem of finding the shortest path across all locations was addressed using depth-first search (DFS). This algorithm allowed me to explore every potential path recursively while keeping track of the shortest one.

I initialized a variable to store the shortest path and its distance.
During each traversal, the program calculated the total distance and compared it with the current shortest distance.
Paths exceeding the current shortest distance were pruned to save computation time.
This method ensured that I identified the optimal route while avoiding redundant calculations. If multiple paths had the same weight, the algorithm deterministically selected the first one encountered.

**Program Design and Modular Implementation**


To ensure maintainability and clarity, I structured the program into multiple modules, each with a specific responsibility.

**Graph Module:**


I implemented this module to manage vertices, edges, and their weights. Using a combination of adjacency matrices and adjacency lists, I was able to efficiently store and retrieve graph data.

**Key Functions:**


graph_create: Allocates and initializes the graph structure.
graph_add_vertex: Assigns names to vertices.
graph_add_edge: Adds weighted edges to the adjacency matrix.
graph_get_weight: Retrieves the weight of a specific edge.
Stack Module:
The stack was essential for tracking the traversal order during DFS. I implemented it as a dynamic, last-in, first-out (LIFO) structure.

**Key Functions:**



stack_create: Initializes the stack.
stack_push and stack_pop: Manage stack operations for traversal.
stack_print: Outputs stack contents for debugging.
Path Module:
I designed this module to track the total distance and sequence of vertices in a given path. It worked in conjunction with the graph and stack modules to calculate and compare paths.

**Key Functions:**



path_create: Initializes a path structure.
path_add and path_remove: Modify the path and update its total distance.
path_copy: Copies paths for comparison and updates.
DFS and TSP Implementation:
The core algorithm for finding the shortest path was implemented using DFS. By iterating through all possible paths and comparing their distances, I was able to identify the optimal route.

**DFS Process:**



Initialize the shortest path variable with a large initial value.
Recursively traverse all vertices, updating the path and total distance.
Use pruning to eliminate suboptimal paths early.
Skills and Techniques Employed
This project allowed me to apply and deepen my understanding of key programming concepts:

**Graph Theory:**


I implemented and analyzed undirected, weighted graphs to solve real-world pathfinding problems.
Recursive Algorithms: DFS was used to explore all paths exhaustively while maintaining efficiency.
Dynamic Memory Management: I carefully allocated and freed memory for graphs, stacks, and paths to ensure no leaks occurred.
Abstract Data Types (ADTs): I created reusable, modular data structures to simplify the implementation of complex algorithms.
Performance Optimization: By pruning paths and leveraging adjacency matrices, I minimized unnecessary computations.
Testing and Debugging: I employed extensive testing strategies, including edge cases and automated scripts, to validate the program’s functionality.

**Testing Methodology**


I conducted rigorous testing at every stage of development to ensure reliability and correctness:

**Unit Testing:**


Each function was tested independently using assertions and print statements to verify logical correctness.

**Integration Testing:**


After combining modules, I tested the complete program with various graph inputs, including edge cases like malformed files, non-integer weights, and large datasets.

**Automated Scripts:**


I wrote shell scripts to simulate user inputs and validate outputs against expected results, ensuring consistent performance.

**Memory Checks:**


Using Valgrind, I confirmed that all dynamically allocated memory was freed properly and that no memory leaks occurred.

**Final Reflections**


This project was an invaluable learning experience that showcased the power of combining theoretical concepts like graph theory with practical programming skills. By modularizing my implementation and optimizing the underlying algorithms, I was able to create a robust and efficient solution for determining the shortest path across multiple locations. The process of debugging and testing further honed my ability to write reliable and scalable code, which I look forward to applying in future projects.
