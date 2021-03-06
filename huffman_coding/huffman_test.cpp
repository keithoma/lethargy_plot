#include <algorithm>
#include <iterator>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

#include <iostream>

namespace ranges {

template <typename Container, typename F>
auto min_element(Container& container, F f)
{
    return std::min_element(begin(container), end(container), f);
}

}  // namespace ranges

using namespace std;

struct Branch;
struct Leaf;

using Node = variant<Branch, Leaf>;

struct Leaf {
    char ch;
    unsigned frequency;
};

struct Branch {
    unique_ptr<Node> left;
    unique_ptr<Node> right;
    unsigned frequency;
};

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
    // TODO: print edge labels (with "0" and "1")
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
    Node root = [&]() {
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
    do
    {
        auto a = ranges::min_element(freqs, smallestFreq);
        Leaf a_{a->first, a->second};
        auto const frequency = a_.frequency + get<Branch>(root).frequency;
        freqs.erase(a);
        root = a_.frequency < get<Branch>(root).frequency
                   ? Branch{make_unique<Node>(a_), make_unique<Node>(move(root)), frequency}
                   : Branch{make_unique<Node>(move(root)), make_unique<Node>(a_), frequency};
    } while (!freqs.empty());

    return move(root);
}

// -----------------------------------------------------------------------------
// Source API

class Source {
  public:
    virtual ~Source() = default;

    using Buffer = std::vector<uint8_t>;

    virtual std::size_t read(Buffer& target) = 0;
};

// reads from source without interpreting (identity)
class RawSource : public Source {
  public:
    RawSource(std::istream& source) : source_{source} {}

    std::size_t read(Buffer& target) override;

  private:
    std::istream& source_;
};

// Reads from huffman encoded source, for retrieving decoded data.
class HuffmanSource : public Source {
  public:
    std::size_t read(Buffer& target) override;
};

class ImageSource : public Source {
  public:
    virtual unsigned width() const noexcept = 0;
    virtual unsigned height() const noexcept = 0;
};

class PPMSource : public ImageSource {
  public:
    PPMSource(std::istream& source) : source_{source} {}
    unsigned width() const noexcept override;
    unsigned height() const noexcept override;
    std::size_t read(Buffer& target) override;

  private:
    std::istream& source_;
};

class RLESource : public ImageSource {
  public:
    unsigned width() const noexcept override;
    unsigned height() const noexcept override;
    std::size_t read(Buffer& target) override;
};

// -----------------------------------------------------------------------------
// Sink API

class Sink {
  public:
    virtual ~Sink() = default;

	virtual void write(uint8_t const* data, size_t count) = 0;
};

class PPMSink : public Sink {
  public:
    PPMSink(unsigned width, unsigned height, std::ostream& target);
    void write(uint8_t const* data, size_t count) override;

  private:
    std::ostream& target_;
};

class RLESink : public Sink {
  public:
    RLESink(unsigned width, unsigned height, std::ostream& target);
    void write(uint8_t const* data, size_t count) override;

  private:
    std::ostream& target_;
};

// -----------------------------------------------------------------------------
// Converter CLI

class Converter {
  public:
};

// -----------------------------------------------------------------------------
// CLI main

int main(int argc, const char* argv[])
{
	// TODO: use Flags API from klex project (maybe also AnsiColor and unit test framework)
    Node const root = huffman_encode("aaaabcadaaabbaaaacaabaadc");

    cout << to_string(root) << "\n\n";

    // print in dot file format (see graphviz)
    cout << printDotFormat(root) << "\n";

    HuffmanCodes const codes = encode(root);
    cout << to_string(codes) << "\n";

    return EXIT_SUCCESS;
}
