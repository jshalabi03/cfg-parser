# 225 Final Project 
Justin Kim, Jacob Shalabi, Kenny Kim, Ben Kim 


# Organization:

Our presentation video is linked at : _____

Our team contract, Written Report, and Project Proposal can be found in the "docs" folder.

Within the includes/ directory, we have our control flow graph data structure declared in CFG.h. 
Our data parsing pipeline is contained within the constructor of our control flow graph.
Our algorithms which include Depth-First Search, Lengauer-Tarjan, and Dijkstra's are all member functions of CFG.
The data parsing functionality uses parsing utility methods declared in ParseUtil.h

The source files associated with these headers are contains in the src/ directory.

In the "data" folder you can find the assembly code examples which we use as well as the cpp code used to generate the assembly.

Lastly, our written test cases can be found in the "tests" folder.


# Running Instructions:

Installation:

1. First, locally clone this repository, at https://github.com/jshalabi03/cfg-parser

2. Open the project directory in the dev container given by the Dockerfile. 

3. Verify that you are in the root directory of the project before continuing.

3. Edit the data/index.cpp file with a compilable C++ program whose entry function is labelled main.

4. Run 'make gen' to generate data/index.s, which contains the LLVM ARM assembly generated instructions from data/index.cpp

5. Finally, run 'make' to run the command line application which will prompt various information queries on the parsed control flow graph.

Testing: 

1. To run our implemented tests, run 'make test'
