#include <iostream>
#include <vector>
#include "../code/LinkedInNetwork.hpp"
#include <string>
using namespace std;

int main(int argc, char** argv)
{
    LinkedInNetwork graph;

    graph.addProfessional("Jackson");
    graph.addProfessional("Marley");
    graph.addProfessional("Presley");
    graph.addProfessional("Dylan");
    graph.addProfessional("Lennon");
    graph.addProfessional("McCartney");
    

    graph.addConnection("Marley", "Dylan");
    graph.addConnection("Dylan", "Lennon");
    graph.addConnection("McCartney", "Lennon");
    graph.addConnection("Lennon", "Presley");
    graph.addConnection("Presley", "Dylan");

    graph.displayConnections();

    graph.breadthFirstTraverse("Jackson");
    getchar();

    vector<string> result = graph.suggestProfessionalsWithinKthOrder("Jackson", 3);
    for(auto node : result){
        cout << node << " ";
    }
    cout << endl;
    getchar();

    result = graph.suggestProfessionalsWithinKthOrder("Presley", 3);
    for(auto node : result){
        cout << node << " ";
    }
    cout << endl;
    getchar();
    
    result = graph.suggestProfessionalsWithinKthOrder("Presley", 1);
    for(auto node : result){
        cout << node << " ";
    }
    cout << endl;
    getchar();

    cout << endl;


    return 0;
}
