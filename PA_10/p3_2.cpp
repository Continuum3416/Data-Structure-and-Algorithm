#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <iomanip>
#include <list>

// Uses smart pointer
template <typename T>
class heapPQ {
public:
    heapPQ() {
        PQ.push_back(nullptr);
    }

    void insert(std::shared_ptr<T> item) {
        PQ.push_back(item);
        upHeap(PQ.size() - 1);
    }

    void removeMin() {
        if (PQ.size() < 2)
            return;
        std::swap(PQ[1], PQ[PQ.size() - 1]);
        PQ.pop_back();
        downHeap(1);
    }

    std::shared_ptr<T> min() {
        if (PQ.size() < 2)
            throw std::runtime_error("PQ is empty");
        return PQ[1];
    }

    bool empty() {
        return PQ.size() < 2;
    }

    size_t size() {
        return PQ.size() - 1;
    }

private:
    std::vector<std::shared_ptr<T>> PQ;

    void upHeap(int index) {
        int parentIndex = index / 2;
        while (index > 1 && *PQ[index] < *PQ[parentIndex]) {
            std::swap(PQ[index], PQ[parentIndex]);
            index = parentIndex;
            parentIndex = index / 2;
        }
    }

    void downHeap(int index) {
        int leftChildIndex = 2 * index, rightChildIndex = 2 * index + 1, smallest = index;

        if (leftChildIndex <= PQ.size() - 1 && *PQ[leftChildIndex] < *PQ[smallest])
            smallest = leftChildIndex;
        if (rightChildIndex <= PQ.size() - 1 && *PQ[rightChildIndex] < *PQ[smallest])
            smallest = rightChildIndex;
        if (smallest != index) {
            std::swap(PQ[index], PQ[smallest]);
            downHeap(smallest);
        }
    }
};



template <typename Elem> class BinaryTree {
protected:
    struct Node {
        Elem elt;
        Node *par;
        Node *left;
        Node *right;
        Node() : elt(), par(NULL), left(NULL), right(NULL) {}
    };

public:
    class Position {
    private:
        Node *v;

    public:
        Position(Node *_v = NULL) : v(_v) {}
        Elem &operator*() { return v->elt; }
        const Elem &operator*() const { return v->elt; }
        Position left() const { return Position(v->left); }
        Position right() const { return Position(v->right); }
        Position parent() const { return Position(v->par); }
        bool isRoot() const { return v->par == NULL; }
        bool isExternal() const { return v->left == NULL && v->right == NULL; }
        bool operator==(const Position &p) const { return v == p.v; }
        bool operator!=(const Position &p) const { return v != p.v; }
        friend class BinaryTree;
    };

    typedef std::list<Position> PositionList;

public:
    BinaryTree() : _root(NULL), n(0) {}
    int size() const { return n; }
    bool empty() const { return size() == 0; }
    Position root() const { return Position(_root); }

    PositionList positions() const {
        PositionList pl;
        preorder(_root, pl);
        return PositionList(pl);
    }

    void addRoot() {
        _root = new Node;
        n = 1;
    }

    void expandExternal(const Position &p) {
        Node *v = p.v;
        v->left = new Node;
        v->left->par = v;
        v->right = new Node;
        v->right->par = v;
        n += 2;
    }

    void attach(const Position &p, Position p1, int n1, Position p2, int n2) {
        Node *v = p.v;
        v->left = p1.v;
        v->left->par = v;
        v->right = p2.v;
        v->right->par = v;
        n = n + n1 + n2;
    }

    Position removeAboveExternal(const Position &p) {
        Node *w = p.v;
        Node *v = w->par;
        Node *sib = (w == v->left ? v->right : v->left);
        if (v == _root) {
            _root = sib;
            sib->par = NULL;
        } else {
            Node *gpar = v->par;
            if (v == gpar->left)
                gpar->left = sib;
            else
                gpar->right = sib;
            sib->par = gpar;
        }
        delete w;
        delete v;
        n -= 2;
        return Position(sib);
    }

protected:
    void preorder(Node *v, PositionList &pl) const {
        pl.push_back(Position(v));
        if (v->left != NULL)
            preorder(v->left, pl);
        if (v->right != NULL)
            preorder(v->right, pl);
    }

    void relink(Node *parent, Node *child, bool makeLeftChild) {
        child->par = parent;
        if (makeLeftChild)
            parent->left = child;
        else
            parent->right = child;
    }

public:
    void rotate(const Position &p) {
        Node *x = p.v;
        Node *y = x->par;
        Node *z = y->par;
        if (z == NULL) {
            _root = x;
            x->par = NULL;
        } else
            relink(z, x, y == z->left);
        if (x == y->left) {
            relink(y, x->right, true);
            relink(x, y, false);
        } else {
            relink(y, x->left, false);
            relink(x, y, true);
        }
    }

private:
    Node *_root;
    int n;
};

template <typename K, typename V> class Entry {
public:
    typedef K Key;
    typedef V Value;

    Entry(const K &k = K(), const V &v = V()) : _key(k), _value(v) {}

    const K &key() const { return _key; }
    const V &value() const { return _value; }
    void setKey(const K &k) { _key = k; }
    void setValue(const V &v) { _value = v; }
    bool operator<(const Entry &e) const { return _key < e.key(); }

private:
    K _key;
    V _value;
};

class Huffman {
public:
    void huffman(const std::string &X) {
        std::unordered_map<char, int> frequency;
        for (char c : X) {
            frequency[c]++;
        }

        heapPQ<Entry<int, std::pair<BinaryTree<char>, BinaryTree<int>>>> Q;
        for (const auto &pair : frequency) {
            BinaryTree<char> T;
            BinaryTree<int> F;
            T.addRoot();
            F.addRoot();
            *T.root() = pair.first;
            *F.root() = pair.second;
            auto entry = std::make_shared<Entry<int, std::pair<BinaryTree<char>, BinaryTree<int>>>>(pair.second, std::make_pair(T, F));
            Q.insert(entry);
        }

        while (Q.size() > 1) {
            auto entry1 = Q.min();
            int f1 = entry1->key();
            auto [T1, F1] = entry1->value();
            Q.removeMin();

            auto entry2 = Q.min();
            int f2 = entry2->key();
            auto [T2, F2] = entry2->value();
            Q.removeMin();

            BinaryTree<char> T;
            BinaryTree<int> F;
            T.addRoot();
            F.addRoot();
            F.attach(F.root(), F1.root(), F1.size(), F2.root(), F2.size());
            *F.root() = f1 + f2;
            T.attach(T.root(), T1.root(), T1.size(), T2.root(), T2.size());
            auto newEntry = std::make_shared<Entry<int, std::pair<BinaryTree<char>, BinaryTree<int>>>>(f1 + f2, std::make_pair(T, F));
            Q.insert(newEntry);
        }

        auto finalEntry = Q.min();
        auto [finalT, finalF] = finalEntry->value();
        std::unordered_map<char, std::string> huffmanCodes;

        std::cout << "Huffman coding tree:" << std::endl;
        printTree(finalT.root(), finalF.root());
        std::cout << "Huffman codes:" << std::endl;
        printCodes(finalT.root(), "", huffmanCodes);
    }


    void printCodes(const BinaryTree<char>::Position &pos, const std::string &code, std::unordered_map<char, std::string> &huffmanCodes) {
        if (pos.isExternal()) {
            huffmanCodes[*pos] = code;
            std::cout << *pos << ": " << code << std::endl;
        } else {
            printCodes(pos.left(), code + "0", huffmanCodes);
            printCodes(pos.right(), code + "1", huffmanCodes);
        }
    }

    void printTree(const BinaryTree<char>::Position &pos, const BinaryTree<int>::Position &freqPos, int depth = 0) {
        if (!pos.isExternal()) {
            std::cout << std::setw(depth) << ' ' << *freqPos << " *" << std::endl;
        } else {
            std::cout << std::setw(depth) << ' ' << *freqPos << " " << *pos << std::endl;
        }
        if (!pos.isExternal()) {
            printTree(pos.left(), freqPos.left(), depth + 4);
            printTree(pos.right(), freqPos.right(), depth + 4);
        }
    }
};



int main(){
    std::string text = "more money needed";
    std::cout << "Text: "<< text <<'\n';
    std::cout << "Number of characters: "<<text.length()<<'\n';
    Huffman test;
    test.huffman(text);


// Run: g++ p3_2.cpp -o p3_2.exe; ./p3_2.exe
return 0;
}
