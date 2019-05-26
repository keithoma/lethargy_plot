#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

class HuffmanCoding
{
    public:
        HuffmanCoding(string text);
    
    // private:
    	typedef function<bool(pair<char, unsigned>, pair<char, unsigned>)> Comparator;
	    Comparator compFunctor = [](pair<char, unsigned> elem1, pair<char, unsigned> elem2) {
		    return elem1.second > elem2.second;
	    };
        map<char, unsigned> huffman_map_; // ordered by keys
        set<pair<char, unsigned>, Comparator> huffman_set_; // ordered by value

        void create_encoding_map();

        unsigned cumulative_frequency_(unsigned n);
        map<char, vector<bool>> encoding_map_;
};

HuffmanCoding::HuffmanCoding(string text) {

    // create a map with characters as keys and the frequencies as values
    for (char& c : text) {
        huffman_map_[c]++;
    }

    // order the above map with value and save it as "huffman_set_"
	huffman_set_ = {huffman_map_.begin(), huffman_map_.end(), compFunctor};
}

// TODO: somehow this does not work
/**
 * She returns the cumulative frequency of the characters in "huffman_set_" from the end of the set to n
 * (i.e. she should count the ascending frequencies n times). Be careful when piloting her; "huffman_set_"
 * is in descending order, but we want to count the cumulative total from the least frequent character.
 * 
 * Args:
 *  unsigned n: the "upper bound" (or in this case the lower bound) of the summation
 * 
 * Returns:
 *  unsigned total: the cumulative frequency up to "n"
 */
unsigned HuffmanCoding::cumulative_frequency_(unsigned n) {
    unsigned total;
    // can certainly be optimized
    for (unsigned i = huffman_set_.size(); i > n; --i) {
        total += next(huffman_set_.begin(), i).second;
        cout << total << "\n";
    }
    return total;
}

// TODO: hope this works, but she needs the function above
/**
 * She populates "encoding_map_" which contains the isomorphic map between the characters and binary.
 */
void HuffmanCoding::create_encoding_map() {
    vector<bool> recycle;
    for (pair<char, unsigned> element : huffman_set_) {
        unsigned n = 0;
        unsigned cum = cumulative_frequency_(n);
        ++n;
        if (element.second < cum) {
            recycle.push_back(0);
            encoding_map_.insert(pair<char, vector<bool>>(element.first, recycle));
        } else {
            recycle.push_back(1);
            encoding_map_.insert(pair<char, vector<bool>>(element.first, recycle));
        }
    }

}

int main() {
    const string random_string = "Two households, both alike in dignity, \nIn fair Verona, where we lay our scene, \nFrom ancient grudge break to new mutiny, \nWhere civil blood makes civil hands unclean. \nFrom forth the fatal loins of these two foes \nA pair of star-cross'd lovers take their life; \nWhose misadventured piteous overthrows \nDo with their death bury their parents' strife. \nThe fearful passage of their death-mark'd love, \nAnd the continuance of their parents' rage, \nWhich, but their children's end, nought could remove, \nIs now the two hours' traffic of our stage; \nThe which if you with patient ears attend, \nWhat here shall miss, our toil shall strive to mend.";

    HuffmanCoding evariste_galois(random_string);

    for (pair<char, unsigned> element : evariste_galois.huffman_set_) {
        int n = 0;
		cout << "char: " << element.first << " freq: " << element.second << " cum: " << evariste_galois.cumulative_frequency_(n) << "\n";
        ++n;
    }

    return 0;
}
