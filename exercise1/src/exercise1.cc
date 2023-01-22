#include "exercise1_utils.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

using namespace std;

void split_by_commas(string &line, vector<string> &items);
int load_data(Node* node_data, const std::string &path);
void push(Node* heap, Node push_data, int size);
void pop(Node* heap_data, int size);
void top(int size, Node* heap);
void up(Node* node, int size);
void down(int index, Node* &node, int size );

int main(int argc, char** argv) {

    string path = argv[1];
   // cout << "path = " << path << endl;

    int k = atoi(argv[2]);

    //cout << "k = " << k << endl;
    int heap_capacity = 28;
    Node* player_data =  new Node[heap_capacity];
    int a = load_data(player_data, path);

    for (int i = 0; i<k;i++){
        top(a, player_data);
        pop(player_data,a);

    }

    return 0;
}

void split_by_commas(string &line, vector<string> &items){
    items.clear();

    // while there are commas in the line, split and push the first part
    // into items vector
    size_t comma_pos = line.find(',');
    while (comma_pos != std::string::npos) {
        items.push_back(line.substr(0, comma_pos));
        line = line.substr(comma_pos+1, line.size());
        comma_pos = line.find(',');
    }
    // push the remaining last item
    items.push_back(line);
}
int load_data(Node* player_data, const std::string &path) {

    ifstream fin(path);
    if (!fin.good()) {
        cerr << "Error opening data file: " << path << endl;
        exit(EXIT_FAILURE);
    }
    string line;
    vector<string> items;
    getline(fin, line);
    split_by_commas(line, items);
    int counter =0;

    while (getline(fin, line)) {

        split_by_commas(line, items);

        if ( line.empty()) {break;}

        Node pd;

        if (items[0] == "H") {pd.is_home = true;}
        else {pd.is_home = false ;}

        pd.shirt_no = stoi(items[1]);
        pd.score = stoi(items[2]);
        counter+=1;
        push(player_data, pd, counter);

        print_complete_binary_tree( player_data,counter);
    }
    fin.close();
    return counter;
}
void up(Node* heap, int size){
  for (int j = 0 ; j< log1p(size); j++) {
      for (int i = 0; i < size; i++) {
          int parent = i;
          int left = 2 * i + 1;
          int right = 2 * i + 2;
          if (heap[parent].score < heap[left].score) {
              swap(heap[parent], heap[left]);
          } else if (heap[parent].score < heap[right].score) {
              swap(heap[parent], heap[right]);
          }
      }
  }
}
void push(Node* heap, Node push_data, int size){
    int index= size-1;
    heap[index]= push_data;
    up(heap, size);

}
void down(int index,Node* &heap, int size )
{
    if (size%2 == 0){
        index= (size/2)-1;
    }
    int largest = index;
    int left = 2*index ;
    int right = 2*index + 1;
    if ( heap[left].score > heap[largest].score ){
        largest = 2*index;
    }
    if (index < size && heap[left].score > heap[index].score) {
        largest = 2*index;
    }
    if (index < size && heap[right].score > heap[index].score) {
        largest = 2*index +1;
    }
    if (largest != index)
    {
        swap(heap[index], heap[largest]);
        down(size, heap, largest);
    }
}
void pop(Node* heap_data, int size){
    try {
        // if there is no data to pop, throw an exception
        if (size == 0)
        {
            throw out_of_range("Vector<X>::at() : "
                               "index is out of range(Heap underflow)");
        }
        heap_data[0] = heap_data[size-1];
        up(heap_data,size);
    }
    catch (const out_of_range &oor) {
        cout << endl << oor.what();
    }
}
void top(int size, Node* heap)
{
    try {
        // if the heap has no elements, throw an exception
        if (size == 0)
        {
            throw out_of_range("Vector<X>::at() : "
                               "index is out of range(Heap underflow)");
        }
        cout << heap[0].score << heap[0].shirt_no << heap[0].is_home<< endl;
    }
    catch (const out_of_range &oor) {
        cout << endl << oor.what();
    }
}
