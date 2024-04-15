#include "LinkedInNetwork.hpp"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

void LinkedInNetwork::addProfessional(string name){
    vector<Professional*>& professionals = getProfessionals();

    for(int i = 0; i < professionals.size(); i++){

        if(professionals[i]->name == name){
            cout << name << " found." << endl;
            return;
        }
    }
    
    Professional* professionalToAdd = new Professional;
    professionalToAdd->name = name;
    professionals.push_back(professionalToAdd);
}

void LinkedInNetwork::addConnection(string v1, string v2){
    vector<Professional*> professionals = getProfessionals();

    Professional* p1;
    neighbor n1;
    
    Professional* p2;
    neighbor n2;

    for(int i = 0; i < professionals.size(); i++){
        if(professionals[i]->name == v1) p1 = professionals[i];

        if(professionals[i]->name == v2) p2 = professionals[i];
    }

    n1.v = p1;
    n2.v = p2;

    p1->neighbors.push_back(n2);
    p2->neighbors.push_back(n1);
}

void LinkedInNetwork::displayConnections(){
    vector<Professional*> professionals = getProfessionals();

    for(int i = 0; i < professionals.size(); i++){
        cout << professionals[i]->name << " --> ";

        for(int j = 0; j < professionals[i]->neighbors.size(); j++){
            cout << professionals[i]->neighbors[j].v->name << " ";
        }

        cout << endl;
    }
}

void bfs_reset(vector<Professional*> &professionals){
    for(int i = 0; i < professionals.size(); i++){
        professionals[i]->visited = false;
        professionals[i]->connectionOrder = 0;
    }
}

void bfs_helper(Professional* src, vector<Professional*> &professionals){
}

void LinkedInNetwork::breadthFirstTraverse(string sourceProfessional){
    vector<Professional*> professionals = getProfessionals();
    Professional* src;
    
    for(int i = 0; i < professionals.size(); i++){
        if(sourceProfessional == professionals[i]->name){
            src = professionals[i];
            break;
        }
    }

    if(src){
        bfs_reset(professionals);
        
        queue<Professional*> qq;
        src->visited = true;

        cout << "Starting Professional (root): " << sourceProfessional << "-> ";
        qq.push(src);

        while(!qq.empty()){
            Professional* u = qq.front();

            qq.pop();

            for(auto edge: u->neighbors){
                if(!edge.v->visited){
                    edge.v->visited = true;
                    edge.v->connectionOrder = u->connectionOrder + 1;

                    cout << edge.v->name << "(" << edge.v->connectionOrder << ") ";
                    qq.push(edge.v);
                }
            }
        }
    }
    // cout << endl;
}

vector<Professional*> suggestProfessionalsHelper(string sourceProfessional, vector<Professional*> &professionals){
    vector<Professional*> result;
    Professional* src;
    
    for(int i = 0; i < professionals.size(); i++){
        if(sourceProfessional == professionals[i]->name){
            src = professionals[i];
            break;
        }
    }

    if(src){
        bfs_reset(professionals);
        
        queue<Professional*> qq;
        src->visited = true;

        qq.push(src);

        while(!qq.empty()){
            Professional* u = qq.front();

            qq.pop();

            for(auto edge: u->neighbors){
                if(!edge.v->visited){
                    edge.v->visited = true;
                    edge.v->connectionOrder = u->connectionOrder + 1;

                    result.push_back(edge.v);

                    qq.push(edge.v);
                }
            }
        }
    }
    return result;
}

vector<string> LinkedInNetwork::suggestProfessionalsWithinKthOrder(string professionalName, int k){
    vector<Professional*> professionals = getProfessionals();
    vector<Professional*> traverse = suggestProfessionalsHelper(professionalName, professionals);
    vector<string> professionalsWithinK;

    for(auto node : professionals){
        if(node->connectionOrder <= k && node->connectionOrder > 0) professionalsWithinK.push_back(node->name);
    }
    
    return professionalsWithinK;
}