#include "graph.h"

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

// Global Visited Variable
int *visited;
std::string temp_string;

/**
 * @brief Construct a new Graph object
 *
 * reads data in from the input file of the graph given in 
 * adjacency matrix representation and builds the graph 
 * with a adjacency list representation. This method sets 
 * the value of size, builds the vectors labels and adj_list
 * 
 * @param filename to be read in
 **********************************************************/
Graph::Graph(const char* filename) {
    // Open the file
    std::ifstream input;
    input.open(filename);

    // Read in the size of the graph
    input >> size;
    char temp[25];

    input.getline(temp, 1);
    input.getline(temp, 25);

    for (int i = 0; i < size; i++) {

        std::string line(temp);

        // Remove all spaces from the line
        std::string::iterator end = std::remove_if(line.begin(), line.end(), [](char c) { return c == ' '; });
        line.erase(end, line.end());

        // Add the label to the labels vector
        for(int i = 0; i < int(line.size()); i++) {
            labels.push_back('A' + i);
        }
    }

    // Build the adjacency list
    while(input) {
        std::list<int> values;
        input.getline(temp, 100);
        std::string line(temp);

        if(line.size() == 0) break;
        
        // Remove all spaces from the line, again
        // For some reason, the lambda function (prior) doesn't work here
        // it spits out garbage and then segfaults
        line.erase(remove_if(line.begin(),line.end(), static_cast<int(*)(int)>(isspace)), line.end());
                
        // Add the values to the list
        for(int i = 1; i < int(line.size()); i++) {
            if(line[i] == '1') {
                values.push_back(i-1);
            }
        }

        // and finally add the list to the adjacency list
        adj_list.push_back(values);
    }
}

/**
 * @brief Destroy the Graph:: Graph object
 **********************************************************/
Graph::~Graph() {
    delete visited;
}

/**
 * @brief This public function is used to traverse a graph 
 *        and evokes the Depthfirst method (below)
 **********************************************************/
void Graph::Traverse() {
    // setup the global variables
    temp_string = "";
    std::cout << std::endl << "------- traverse of graph ------" << std::endl;
    visited = new int[size];

    // initialize the visited array
    for(int i = 0 ; i< size; i++) {
        visited[i] = 0;
    }

    // call the recursive function
    for (int i = 0; i < size; i++) {
        if(visited[i] == 0)
            Depthfirst(i);
    }
    
    std::cout << std::endl << temp_string << std::endl;
    std::cout << "--------- end of traverse -------" << std::endl << std::endl;
}

/**
 * @brief private function is used to traverse a graph in 
 *        the depth-first traversal/search algorithm starting 
 *        at the vertex with the index value of v.
 * 
 * @param v 
 **********************************************************/
void Graph::Depthfirst(int v) {
    visited[v]++;
    std::cout << labels[v] << " ";

    for(int i : adj_list[v]) {
        if(visited[i] == 0) {
            temp_string = temp_string + '(' + labels[v] + ',' + ' ' + labels[i] + ')' + ' ';
            Depthfirst(i);
        }
    }
}

/**
 * @brief Returns the size of the graph
 * 
 * @return int the size of the graph
 **********************************************************/
int Graph::Getsize() const { 
    return size;
}

/**
 * @brief function to print the adjacency list for the graph.
 **********************************************************/
void Graph::Print() const {
    int i = 0;

    // print the headers for the output
    std::cout << std::endl << "Number of vertices in the graph: " << size << std::endl;
    std::cout << std::endl << "-------- graph -------" << std::endl;

    // print the labels
    for (auto it = adj_list.begin(); it != adj_list.end(); ++it) {
        std::cout << labels[i] << ": ";

        // print the adjacency list
        for (auto it2 = it->begin(); it2 != it->end(); ++it2) {

            // if end of list, don't print a comma
            if (it2 == --it->end()) {
                std::cout << labels[*it2];
            } else {
                std::cout << labels[*it2] << ", ";
            }
        }
        std::cout << std::endl;
        i++;
    }

    // print the footer for the output
    std::cout << "------- end of graph ------" << std::endl;
}