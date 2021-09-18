#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    // TODO 2: Use the m_Model.FindClosestNode method to find the closest nodes to the starting and ending coordinates.
    // Store the nodes you find in the RoutePlanner's start_node and end_node attributes.
    //Node &FindClosestNode(float x, float y); // this function returns an address
    start_node = &m_Model.FindClosestNode(start_x,start_y); // initializes the start_node pointer variable
    end_node = &m_Model.FindClosestNode(end_x,end_y);

}


// TODO 3: Implement the CalculateHValue method.
// Tips:
// - You can use the distance to the end_node for the h value.
// - Node objects have a distance method to determine the distance to another node.

float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
  //float distance(Node other) function returns a float
  return node->distance(*end_node); // use * operator to dereference the end_node pointer to give access to the value it points at
}


// TODO 4: Complete the AddNeighbors method to expand the current node by adding all unvisited neighbors to the open list.
// Tips:
// - Use the FindNeighbors() method of the current_node to populate current_node.neighbors vector with all the neighbors.
// - For each node in current_node.neighbors, set the parent, the h_value, the g_value.
// - Use CalculateHValue below to implement the h-Value calculation.
// - For each node in current_node.neighbors, add the neighbor to open_list and set the node's visited attribute to true.

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {

  current_node->FindNeighbors();
  for(auto current_neighbor : current_node->neighbors){
    current_neighbor->parent = current_node;// initialize the parent pointer with the current node pointer
    current_neighbor->h_value = CalculateHValue(current_neighbor);
    current_neighbor->g_value = current_node->g_value + current_node->distance(*current_neighbor);
    this->open_list.push_back(current_neighbor); // open list is a vector of node pointer variables
    current_neighbor->visited = true;
  }

}


// TODO 5: Complete the NextNode method to sort the open list and return the next node.
// Tips:
// - Sort the open_list according to the sum of the h value and g value.
// - Create a pointer to the node in the list with the lowest sum.
// - Remove that node from the open_list.
// - Return the pointer.

// ** my_sort_function takes two pointer variables of type RouteModel::Node
// and returns true if the first input (xx) has smaller g+h values than
// the second input (yy).
// To be used with the sort function which will then sort
// the vector of open_list with g+h values from low to high
// open_list[0] contains the node with lowest sum
bool my_sort_function(const RouteModel::Node *xx,const RouteModel::Node *yy){
    return (xx->g_value+xx->h_value) < (yy->g_value+yy->h_value);
}

RouteModel::Node *RoutePlanner::NextNode() {

    //std::vector<RouteModel::Node*> open_list;
    std::sort(open_list.begin(),open_list.end(),my_sort_function);
    RouteModel::Node *next_node = open_list[0]; // creat a pointer to the node with the lowest sum

    return next_node; // return the next node
}


// TODO 6: Complete the ConstructFinalPath method to return the final path found from your A* search.
// Tips:
// - This method should take the current (final) node as an argument and iteratively follow the
//   chain of parents of nodes until the starting node is found.
// - For each node in the chain, add the distance from the node to its parent to the distance variable.
// - The returned vector should be in the correct order: the start node should be the first element
//   of the vector, the end node should be the last element.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    // TODO: Implement your solution here.

    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;

}


// TODO 7: Write the A* Search algorithm here.
// Tips:
// - Use the AddNeighbors method to add all of the neighbors of the current node to the open_list.
// - Use the NextNode() method to sort the open_list and return the next node.
// - When the search has reached the end_node, use the ConstructFinalPath method to return the final path that was found.
// - Store the final path in the m_Model.path attribute before the method exits. This path will then be displayed on the map tile.

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;

    // TODO: Implement your solution here.

}
