#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <utility>
#include <optional>

using namespace std;

struct Node
{
    bool has_child;

    // we use the key attribute to compare the two branches
    unsigned key;

    // here, we store the frequencies of each character
    pair<char, unsigned> data;
};

struct Tree
{
    Node node;
    Tree* left;
    Tree* right;
    Tree* parent;
};

class huffman_encoding
{
    public:
        huffman_encoding(string input_string);

    // private:

        // this function may fail; upgrade it with optional if possible
        pair<char, unsigned> find_least_erase();
        Tree create_parent(Tree left_branch, Tree right_branch);
        void create_tree();

    
    // private:
        map<char, unsigned> frequency_;
        vector<Tree> tree;
        vector<bool> huffman_code_;
};

huffman_encoding::huffman_encoding(string input_string) {
    for (char& c : input_string) {
        frequency_[c]++;
    }
}

pair<char, unsigned> huffman_encoding::find_least_erase() {

    // find the iterator for the least frequent occurrence
    auto iter = min_element(begin(frequency_), end(frequency_), [](const auto& a, const auto& b) -> bool {
        return a.second < b.second;
    });

    // save the found pair before we erase and return
    pair<char, unsigned> least = make_pair(iter -> first, iter -> second);
    frequency_.erase(iter);
    return least;
}


// (T_T) binary tree is too hard
void huffman_encoding::create_tree() {
    // find the two most infrequent letters
    pair<char, unsigned> very_least = find_least_erase();
    pair<char, unsigned> second_least = find_least_erase();

    // create a node for each of them
    Tree *left_branch;
    left_branch->node = {false, very_least.second, very_least};

    Tree *right_branch;
    right_branch->node = {false, second_least.second, second_least};
    
    Tree *parent_branch;
    parent_branch->node.key = very_least.second + second_least.second;
    parent_branch->left = left_branch;
    parent_branch->right = right_branch;

    left_branch->parent = parent_branch;
    right_branch->parent = parent_branch;
}

int main(){
    const string random_string = "Two households, both alike in dignity, \nIn fair Verona, where we lay our scene, \nFrom ancient grudge break to new mutiny, \nWhere civil blood makes civil hands unclean. \nFrom forth the fatal loins of these two foes \nA pair of star-cross'd lovers take their life; \nWhose misadventured piteous overthrows \nDo with their death bury their parents' strife. \nThe fearful passage of their death-mark'd love, \nAnd the continuance of their parents' rage, \nWhich, but their children's end, nought could remove, \nIs now the two hours' traffic of our stage; \nThe which if you with patient ears attend, \nWhat here shall miss, our toil shall strive to mend.";
    huffman_encoding new_obj(random_string);

    return 0;
}
