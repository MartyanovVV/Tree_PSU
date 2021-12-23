#include <iostream>
#include <stack>

//https://contest.yandex.ru/contest/32613/run-report/61427409/

//https://contest.yandex.ru/contest/32613/run-report/61970567/

//https://contest.yandex.ru/contest/32613/run-report/62560224/

struct Node {
    int Key;
    Node *Left;
    Node *Right;

    explicit Node(int key) : Key(key), Right(nullptr), Left(nullptr) {}
};

class Tree {
public:
    Tree() : root(nullptr) {}

    ~Tree() { DeleTed(root); }

    void Add(int key);

    void Print();

private:
    Node *root;

    void DeleTed(Node *rot) {
        std::stack<Node *> stack_node;
        stack_node.push(rot);
        while (!stack_node.empty()) {
            Node *root = stack_node.top();
            stack_node.pop();
            if (root) {
                if(root->Left){
                    stack_node.push(root->Left);
                }
                if(root->Right){
                    stack_node.push(root->Right);
                }
                delete root;
            }
        }
    }

};

void Tree::Print() {
    std::stack<Node *> stackNode;
    stackNode.push(root);
    Node *lastElement = nullptr;
    while (!stackNode.empty()) {
        Node *Element = stackNode.top();
        if (lastElement == nullptr || lastElement != Element->Right && lastElement != Element->Left) {
            if (Element->Right) {
                stackNode.push(Element->Right);
            }
            if (Element->Left) {
                stackNode.push(Element->Left);
            }
            if (!Element->Left && !Element->Right) {
                lastElement = Element;
                std::cout << Element->Key << " ";
                stackNode.pop();
            }
        } else {
            lastElement = Element;
            std::cout << Element->Key << " ";
            stackNode.pop();
        }
    }
}

void Tree::Add(int key) {
    if (root == nullptr) {
        root = new Node(key);
    } else {
        Node *node = root;
        while (true) {
            if (key < node->Key) {
                if (node->Left) {
                    node = node->Left;
                } else {
                    node->Left = new Node(key);
                    break;
                }
            } else {
                if (node->Right) {
                    node = node->Right;
                } else {
                    node->Right = new Node(key);
                    break;
                }
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    int n = 0;
    std::cin >> n;
    Tree tree;
    for (int i = 0; i < n; i++) {
        int a = 0;
        std::cin >> a;
        tree.Add(a);
    }
    tree.Print();
    return 0;
}