#include <iostream>
#include "../include/linkedlist.hpp"
#include "../include/arraylist.hpp"
#include "../include/hashmap.hpp"

using namespace std;

int main(int argc, char** argv){
    
    HashMap<int, char*> hash(1);
    ArrayList<char*> list;
    list.add("Ola");
    list.add("Mundo!");
    list[1] = "Mundooo!";
    cout << list << endl;

    //hash.del("nome");

    // cout << hash["nome"] << endl;
    // cout << hash["sobrenome"] << endl;
    cout << hash << endl;
    return 0;
}