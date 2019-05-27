#include <algorithm>
#include <functional>
#include <iterator>
#include <iostream>
#include <map>
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <variant>
#include <sstream>

namespace ranges
{

template <typename Container, typename F>
auto min_element(Container& container, F f)
{
	return std::min_element(begin(container), end(container), f);
}

} // namespace ranges

using namespace std;

struct Branch;
struct Leaf;

using Node = variant<Branch, Leaf>;

struct Leaf
{
	char ch;
	unsigned frequency;
};

struct Branch
{
	unique_ptr<Node> left;
	unique_ptr<Node> right;
	unsigned frequency;
	//Branch(Node a, Node b, unsigned freq): left{move(a)}, right{move(b)}, frequency{freq} {}
};

unsigned getFrequency(Node const& n)
{
	if (holds_alternative<Leaf>(n))
		return get<Leaf>(n).frequency;
	else
		return get<Branch>(n).frequency;
}

using HuffmanCodes = vector<pair<char, vector<bool>>>;

string to_string(HuffmanCodes const& codes)
{
	stringstream os;
	int i = 0;
	for (auto const& code : codes)
	{
		if (i++)
			os << ", ";
		os << '{' << code.first << ": ";
		for (bool bit : code.second)
			os << (bit ? '1' : '0');
		os << '}';
	}
	return os.str();
}

/*
 * @param root tree root of our huffman tree
 * @param state remembered bits until this root
 */
HuffmanCodes encode(Node const& root, vector<bool> state = {})
{
	vector<pair<char, vector<bool>>> result;

	if (holds_alternative<Leaf>(root))
		result.emplace_back(make_pair(get<Leaf>(root).ch, state));
	else
	{
		auto const& br = get<Branch>(root);

		state.push_back(false);
		auto x = encode(*br.left, state);
		result.insert(end(result), begin(x), end(x));

		state.back() = true;
		auto y = encode(*br.right, state);
		result.insert(end(result), begin(y), end(y));
	}

	return result;
}

void printDotFormat(ostream& os, Node const& n)
{
	if (holds_alternative<Branch>(n))
	{
		auto const& br = get<Branch>(n);

		os << "\"-(" << br.frequency << ")\" -> ";
		printDotFormat(os, *br.left);

		os << "\"-(" << br.frequency << ")\" -> ";
		printDotFormat(os, *br.right);
	}
	else
	{
		auto const& leaf = get<Leaf>(n);
		os << '"' << leaf.ch << "(" << leaf.frequency << ")\";\n";
	}
}

string printDotFormat(Node const& root)
{
	std::stringstream out;

	out << "digraph D {\n";
	printDotFormat(out, root);
	out << "}\n";

	return out.str();
}

std::string to_string(Node const& node)
{
	stringstream os;
	if (holds_alternative<Leaf>(node))
	{
		auto const& leaf = get<Leaf>(node);
		os << "{" << leaf.frequency << ": " << leaf.ch << "}";
	}
	else
	{
		auto const& br = get<Branch>(node);
		os << "{" << br.frequency << ": " << to_string(*br.left) << ", " << to_string(*br.right) << "}";
	}
	return os.str();
}

Node huffman_encode(string const& data)
{
	if (data.empty())
		return {};

	auto static const smallestFreq = [](auto const& a, auto const& b) { return a.second < b.second; };

	// collect frequencies
	map<char, unsigned> freqs;
	for_each(begin(data), end(data), [&](char c) { freqs[c]++; });

	// create initial root
	Node root = [&]()
	{
		auto a = ranges::min_element(freqs, smallestFreq);
		auto a_ = Leaf{a->first, a->second};
		freqs.erase(a);

		auto b = ranges::min_element(freqs, smallestFreq);
		if (b == end(freqs))
			return Node{a_};

		auto b_ = Leaf{b->first, b->second};
		freqs.erase(b);
		return Node{Branch{make_unique<Node>(a_), make_unique<Node>(b_), a_.frequency + b_.frequency}};
	}();

	if (freqs.empty())
		return move(root);

	// eliminate remaining frequencies and build tree bottom-up
	// NB: It is guaranteed that root is a Branch (not a Leaf).
	while (!freqs.empty())
	{
		auto a = ranges::min_element(freqs, smallestFreq);
		Leaf a_{a->first, a->second};
		freqs.erase(a);
		if (a_.frequency < getFrequency(root))
			root = Branch{make_unique<Node>(a_), make_unique<Node>(move(root)), a_.frequency + getFrequency(root)};
		else
			root = Branch{make_unique<Node>(move(root)), make_unique<Node>(a_), a_.frequency + getFrequency(root)};
	}

	return move(root);
}

int main(int argc, const char* argv[])
{
	Node const root = huffman_encode("aaaabcadaaabbaaaacaabaadc");

	cout << to_string(root) << "\n\n";

	// print in dot file format (see graphviz)
	cout << printDotFormat(root) << "\n";

	HuffmanCodes const codes = encode(root);
	cout << to_string(codes) << "\n";

	return EXIT_SUCCESS;
}
