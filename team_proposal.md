# Leading Question 

Given the underlying assembly instructions of a program, which blocks of code dominate other blocks of code? In other words, which control flows must be processed in order to reach certain other processes? How do we determine shortest paths between two blocks of code? We will generate our dataset from written C++ programs which will be converted into LLVM assembly code and stored into .s files which will be parsed into our graph data structure. To determine the shortest path between two blocks of code, we will be implementing a Djikstra’s Algorithm to solve this problem. To determine weights of the blocks and if a certain block of code dominates another block, we will be implementing the Lengauer-Tarjan algorithm to determine weights. Because of the Lengauer-Tarjan algorithm, our graph data structure will produce a dominator tree depicting the dominating relationships in our control flow graph. We will then use the properties of this tree to determine relationships between blocks of code and determine their shortest paths. We will also implement DFS traversal to traverse through the entire graph. 

# Dataset Acquisition
## Data Format

For our data, we will curate our own C++ programs and then we will make use of the LLVM compiler to generate assembly instructions from these programs. The format of the data will simply be source code files of ASM instructions assuming ARM architecture. We will only be using small subsets of our data so that we can narrow the focus of our algorithms on specific control flows and processes.


## Data Correction
When parsing our data, we will be constructing a control-flow graph data structure. So, we will read the lines of our assembly instruction data and process each instruction as a basic block containing an entry point and exit point. We will then apply the contents of the instruction to the weights of the outgoing edges of the node. Possible errors that could occur when parsing this data are syntactic ones. For instance, if a specific instruction contains a comment, the parsing for that line may result in unexpected behavior. Furthermore, if our method of emitting LLVM assembly instructions results in a defective file and we are unable to verify its correctness, this would also result in unexpected behavior.

## Data Storage

For our data storage it seems like going with a vector data type will be our best bet. We will make it a 2-D vector, as it will be easiest to store in a decent fashion after parsing our data. We believe an adjacency list will best represent a graph that we can traverse easily. We will not need any auxiliary data structures, or any pre-processed tables, as we will be parsing the data already. Lastly, we estimate that our storage cost for our data will be O(N), as we do not need to reorder an adjacency list, we just add all the data in.

# Algorithm 

Dijkstra: 
* Inputs: For our Dijkstra’s algorithm, our function inputs will be our graph and our source vertex that we will want to find the shortest paths from. We are expecting to make our input into a graph with nodes being modeled as blocks of code and our edges to be the jump instructions that allow the jump from one block of code to another. We will be using an adjacency list structure to model as our graph. 
* Outputs: We will output the shortest paths between each node connected to our source vertex in the form of a standard vector that contains the distance between each node. We can use this to answer the “shortest path between two blocks of code” question in our leading question. 
* Function efficiency: For Dijkstra’s, the Big O would be O(ElogV) where E is the number of edges and V is the number of vertices so hopefully we would target something similar to that. For space complexity, since we are using an adjacency list, we are targeting something around O(V + E) space as that is the theoretical for the adjacency list implementations. 

DFS: 
* Inputs: For the Depth First Search traversal, our function inputs will be a random Node from our basic block graph which will be used to start our traversal. Because of memory concerns, we will be using an iterative DFS implementation, with a stack to traverse through the graph and an adjacency list implementation using a 2d vector to track visited nodes and its neighbors. 
* Outputs: For the DFS, we will be outputting nothing as we plan to have the function be a void function. We will be using our DFS for the first step of our Lengauer-Tarjan algorithm to order the nodes from 1 to n, where n is the number of vertices/nodes in our graph. 
* Function efficiency: For DFS, the Big O would be O(V) where V is the number of vertices/nodes in our graph, which we are looking to match with our traversal implementation. In terms of space complexity, we are targeting O(V + E) where V is still the total number of vertices/nodes and E is the total number of edges. 

Lengauer-Tarjan: 
* Inputs: For the Lengauer-Tarjan algorithm, we will be using DFS to go through each vertex to calculate the semi dominators to create our spanning dominator tree so our inputs will be a set of all vertices V, and the set of all edges E. 
* Outputs: For the output, we will output a pointer, r, that points to the root of our newly created dominator tree so that we can depict the dominating relationships between the blocks of code as asked in our leading questions. 
* Function efficiency: A sophisticated implementation of the Lengauer-Tarjan algorithm runs in O(ma(m,n)) time, where a(m, n) is a functional inverse of Ackermann’s function but we are looking to do a simple implementation that runs in O(mlogn) where m is the number of edges and n is the number of vertices in the graph. 


#Timeline
Week of the nov 4th 
complete proposal, research necessary components and assess best options.

Week of the nov 11th 
start on the Data parsing pipeline, our data storage, and our data acquisition, and either finish or make notable progress on it.

Week of the nov 18th 
mid project check-in, will have Data parsing done. Start Dijkstra’s algorithm as well.

Week of the nov 25th 
Break – if needed catch up work will be completed asynchronously.
 
Week of the dec 2nd 
Implement our Floyd’s cycle, and our BFS algorithms. Finish our functional code base, upload everything on github.


Week of dec 9th
Create the README, Written report, and presentation video.
Finalize our project and turn it in.
