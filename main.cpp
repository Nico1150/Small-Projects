#include <iostream>
#include <vector>
#include <utility>

using Tuple = std::pair<unsigned int, int>;

bool res = false;
std::vector<bool> visited; // Has the vertex in the position given by its number already been visited?
std::vector<unsigned int> path; // The path we are currently building
int accumulated = 0; // How much weight does the partial path have
unsigned int vertices;
std::vector<std::vector<Tuple>> adj;
int maximum;
bool negative = false; // Are there any negative edges?


void Hamilton(unsigned int current, int partialLength){
    if ((!negative) && (accumulated > maximum)) return;
    path.push_back(current);
    visited[current] = true;
    if (partialLength == (vertices - 1)){
        if (partialLength <= maximum) res = true;
        return;
    }
    else{
        for (Tuple t : adj[current]) if (!visited[t.first]){
            accumulated += t.second;
            Hamilton(t.first, partialLength + 1);
            if (res) return;
            accumulated -= t.second;
        }
    }
    visited[current] = false;
    path.pop_back();
}


int main(){
    std::cout << "How many vertices will the graph have?" << std::endl;
    std::cin >> vertices;
    adj.insert(adj.end(), vertices, std::vector<std::pair<unsigned int, int>>());
    visited.insert(visited.end(), vertices, false);
    std::cout << "Each vertex will be represented by a number from 1 to the amount submitted." << std::endl;
    int v, w, weight;
    while (true){
        std::cout << "What 2 vertices will the next edge connect? (0 if you don't want to add more edges)" << std::endl;
        std::cin >> v >> w;
        if ((v <= 0) || (w <= 0)) break;
        std::cout << "What will its weight be?" << std::endl;
        std::cin >> weight;
        adj[v-1].push_back(std::make_pair(w-1, weight));
        adj[v-1].push_back(std::make_pair(w-1, weight));
        if (weight < 0) negative = true;
    }
    std::cout << "What's the maximum length the path should have?" << std::endl;
    std::cin >> maximum;
    unsigned int iterations = 0;
    while ((iterations < vertices) && !res){
        Hamilton(iterations, 0);
        iterations++;
    }
    if (res) {
        std::cout << "There is a path that visits every vertex of the graph of total weight " << accumulated << "." << std::endl;
        std::cout << "It goes as it follows:" << std::endl;
        for (unsigned int vertex : path) std::cout << vertex << std::endl;
    }
    else std::cout << "There exists no path that satisfies the conditions given." << std::endl;
    return 0;
}
