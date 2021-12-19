#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

//https://contest.yandex.ru/contest/32613/run-report/61418779/

struct BinNode {
    int Key;
    BinNode *Left;
    BinNode *Right;

    explicit BinNode(int key) : Key(key), Left(nullptr), Right(nullptr) {}
};

struct TreapNode {
    int Key;
    int Priority;
    TreapNode *Left;
    TreapNode *Right;

    explicit TreapNode(int key, int priority) : Key(key), Priority(priority), Left(nullptr), Right(nullptr) {}
};

std::pair<TreapNode *, TreapNode *> Split(int key, TreapNode *node) {
    if (!node) {
        return std::pair(nullptr, nullptr);
    }
    if (node->Key < key) {
        TreapNode *a = node;
        std::pair<TreapNode *, TreapNode *> p = Split(key, node->Right);
        a->Right = p.first;
        TreapNode *b = p.second;
        return std::pair(a, b);
    } else {
        TreapNode *b = node;
        std::pair<TreapNode *, TreapNode *> p = Split(key, node->Left);
        b->Left = p.second;
        TreapNode *a = p.first;
        return std::pair(a, b);
    }
}

void Add(int key, int priority, TreapNode *&node) {
    if (!node) {
        node = new TreapNode(key, priority);
        return;
    } else if (node->Priority < priority) {
        std::pair<TreapNode *, TreapNode *> pair_node = Split(key, node);
        TreapNode *root = new TreapNode(key, priority);
        root->Left = pair_node.first;
        root->Right = pair_node.second;
        node = root;
        return;
    }
    if (node->Key <= key) Add(key, priority, node->Right);
    else if (node->Key > key) Add(key, priority, node->Left);

}

void Add(int key, BinNode *&node) {
    if (!node) {
        node = new BinNode(key);
        return;
    }
    if (node->Key < key) Add(key, node->Right);
    else Add(key, node->Left);
}

void Width(BinNode *node, std::vector<int> &v, int k) {
    if (node) {
        v[k] += 1;
        Width(node->Left, v, k + 1);
        Width(node->Right, v, k + 1);
    }
}

void Width(TreapNode *node, std::vector<int> &v, int k) {
    if (node) {
        v[k] += 1;
        Width(node->Left, v, k + 1);
        Width(node->Right, v, k + 1);
    }
}

int MaxHeigt(TreapNode *node) {
    if (!node) {
        return 0;
    } else {
        return std::max(MaxHeigt(node->Left), MaxHeigt(node->Right)) + 1;
    }
}

int MaxHeigt(BinNode *node) {
    if (!node) {
        return 0;
    } else {
        return std::max(MaxHeigt(node->Left), MaxHeigt(node->Right)) + 1;
    }
}

void DeleTed(TreapNode *rot) {
    std::stack<TreapNode *> stack_node;
    stack_node.push(rot);
    while (!stack_node.empty()) {
        TreapNode *root = stack_node.top();
        stack_node.pop();
        if (root) {
            stack_node.push(root->Left);
            stack_node.push(root->Right);
            delete root;
        }
    }
}

void DeleTed(BinNode *rot) {
    std::stack<BinNode *> stack_node;
    stack_node.push(rot);
    while (!stack_node.empty()) {
        BinNode *root = stack_node.top();
        stack_node.pop();
        if (root) {
            stack_node.push(root->Left);
            stack_node.push(root->Right);
            delete root;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n = 0;
    std::cin >> n;
    BinNode *Bin_root = new BinNode(0);
    TreapNode *Treap_root = new TreapNode(0, 0);
    std::vector<int> v(n * 2);
    for (int i = 0; i < n * 2; i++) {
        std::cin >> v[i];
    }
    Bin_root->Key = v[0];
    for (int i = 2; i < n * 2; i += 2) {
        Add(v[i], Bin_root);
    }
    int a = 0;
    int h = MaxHeigt(Bin_root);
    {
        std::vector<int> v2(h);
        Width(Bin_root, v2, 0);
        sort(v2.begin(), v2.end());
        a = v2[h - 1];
    }
    DeleTed(Bin_root);

    Treap_root->Key = v[0];
    Treap_root->Priority = v[1];
    for (int i = 2; i < n * 2; i += 2) {
        Add(v[i], v[i + 1], Treap_root);
    }
    h = MaxHeigt(Treap_root);
    std::vector<int> v2(h);
    Width(Treap_root, v2, 0);
    sort(v2.begin(), v2.end());
    int b = v2[h - 1];
    std::cout << b - a;

    DeleTed(Treap_root);
    return 0;
}
