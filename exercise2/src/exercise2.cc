#include "exercise2_utils.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


using namespace std;
void split_by_commas(string &line, vector<string> &items);
int load_data(Node* player_data, const std::string &path);
void inorder(Node* root);
Node* constructBST(Node *player_data, int counter);
Node* insert(Node* root, Node pd);



int main(int argc, char** argv) {

    string path = argv[1];
    cout << "path = " << path << endl;
    int s_min = atoi(argv[2]);

    //cout << "s_min = " << s_min << endl;

    int s_max = atoi(argv[3]);

    //cout << "s_max = " << s_max << endl;

    int capacity = 28;
    Node* player_data =  new Node[capacity];

    load_data(player_data,  path);

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

    Node& tree = *player_data;
    int counter =0;
    while (getline(fin, line)) {

        split_by_commas(line, items);

        if ( line.empty()) {break;}

        Node pd ;

        if (items[0] == "H") {pd.is_home = true;}
        else {pd.is_home = false ;}
        pd.shirt_no = stoi(items[1]);
        pd.score = stoi(items[2]);
        pd.left = nullptr;
        pd.right = nullptr;

        player_data[counter] = pd;
        counter+=1;

        Node *root = constructBST(player_data,counter);

        inorder(root);

        print_binary_tree( *root);
    }
    fin.close();
    return counter;
}

void inorder(Node* root)
{
    if (root == nullptr) {
        return;
    }
    inorder(root->left);
    inorder(root->right);
}

Node* insert(Node* root, Node pd)
{

    if (root == nullptr) {
        return new Node(pd);
    }

    if (pd.score < root->score) {
        root->left = insert(root->left, pd);
    }
    else {
        root->right = insert(root->right, pd);
    }

    return root;
}

Node* constructBST(Node *player_data, int counter)
{
    Node* root = nullptr;
    for ( int i =0; i<counter; i++){
        root = insert(root, player_data[i]);
    }
    return root;
}