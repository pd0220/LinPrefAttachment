// linear preferential attachment system simulation

// used headers and/or libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>

// size of tree
int const N{(int)1e6};
// file name to save results
std::string const fileName{"data.txt"};

// choose a random integer from given [0, high] interval uniformly --> choose a node from given set of nodes
auto Rand = [](int const &high) {
    // check given parameter
    if (high <= 0 || std::abs(std::floor(high) - high) > 1e-15)
    {
        std::cout << "Invalid higher boundary for random number generation." << std::endl;
        std::exit(-1);
    }
    // generate random uniform integer
    std::random_device rd{};
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> Uni(0, high);
    return Uni(gen);
};

// addig a new node to the system --> according to the probability of given degree
auto AddNode = [&](std::vector<int> &Nodes) {
    // number of nodes
    int numOfNodes{static_cast<int>(Nodes.size())};
    // determine normalization factor --> sum of degrees (now: 2 * N - 2)
    int norm{2 * numOfNodes - 2};
    // connect new node --> repeat until a new node is added
    int stop{0};
    while (stop == 0)
    {
        // choose node uniformly
        int node{Rand(static_cast<int>(Nodes.size()))};
        int k{Nodes[node]};
        // determine probability of connection
        double p{(double)(k / norm)};
        // to connect, or not to connect... this is the question
        if (p < Rand(1))
        {
            // increase degree
            Nodes[node] += 1;
            // new node
            Nodes.push_back(1);
            // exit loop
            stop++;
        }
    }
};

// write final graph to file
auto WriteToFile = [&](std::vector<int> const &Nodes) {
    std::ofstream data;
    data.open(fileName);
    for (int i{0}; i < N; i++)
        data << Nodes[i] << std::endl;
    data.close();
};

// main funcion
int main(int, char **)
{
    // number of starters nodes
    int starter{2};
    // container for nodes
    // initialization with given initial condition
    // from two nodes (equivalent to one node)
    std::vector<int> Nodes(starter, 1);

    // simulate node dynamics
    for (int i{starter}; i < N; i++)
        AddNode(Nodes);

    // write to file final graph
    WriteToFile(Nodes);
}
