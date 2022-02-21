#include <iostream>
#include <string>
#include "../include/linkedlist.hpp"
#include "../include/arraylist.hpp"
#include "../include/hashmap.hpp"

using namespace std;

//int argc, char** argv
int main(){

    HashMap<string, string> map;
    
    map["Nome"] = "Thales";
    map["Idade"] = "25";
    map["Cidade"] = "Mantena";

    //cout << map << endl;

    cout << map["Ola"] << endl;

    map.printStructure();
    
    return 0;
}