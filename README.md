# Virus-Detection-Isolation
Detect and isolate individuals ,represented as vertices and edges in a graph, using C++.

# How it works
The program will receive a config file (json) as an input, which includes the description of the
social network graph and a list of agents (viruses and contact tracers).

The program receives the path of the config file as the first command line argument. After the
program is initialized, the function simulate() would trigger. The simulate() function runs in a
loop, until the termination conditions (Which are detailed *below*) are satisfied.
In each iteration of the loop (Called a cycle), each agent in the session acts on the graph. The
two types of agents which operate on the graph are contact tracers and viruses. Viruses infect
the node they occupy, and spread themselves (By creating new viruses) into adjacent nodes.
Contact tracers attempt to break the chain of infection by disconnecting a node from the graph.
The choice of the node to disconnect, is according to three types of pre-defined logic :

1) RootTree – Simply disconnects the root of the tree.

2) MaxRankTree – Disconnects the node in the tree with the highest number of children.
In case of a tie, the node with the smallest depth in the tree would be picked. If there is still a
tie, then the left-most node in that tree would be picked.

3) CycleTree - Starts traversing the tree from the root, picking always the left-most child. Returns
the c'th node in this trip, where c is the cycle in which the tree was created. If the trip is less
than c nodes long, returns the last node in it.

*The program terminates when each connected component of the graph is either fully infected,
or doesn't contain a virus in it*

# Examples
There three diffrent running configurations and expected outputs (config1.json / output1.json , config2...).

