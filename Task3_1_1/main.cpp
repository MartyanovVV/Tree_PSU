#include <iostream>
#include <stack>
#include <vector>
//https://contest.yandex.ru/contest/32613/run-report/61418943/

//https://contest.yandex.ru/contest/32613/run-report/62316511/
struct AVLNode {
    int Key;
    int Height;
    int Count;
    AVLNode *Left;
    AVLNode *Right;

    explicit AVLNode(int key) : Key(key), Height(1), Count(1), Left(nullptr), Right(nullptr) {}
};

int Count(AVLNode *&node) {
    return node ? node->Count : 0;
}
int Height(AVLNode *&node) {
    return node ? node->Height : 0;
}
void FixCount(AVLNode *&node) {
    node->Count = Count(node->Right) + Count(node->Left) + 1;
}
void FixHeight(AVLNode *&node) {
    node->Height = std::max(Height(node->Left), Height(node->Right)) + 1;
}
int Balance(AVLNode *&node) {
    if (!node) return 0;
    return Height(node->Left) - Height(node->Right);
}
void RotateLeft2(AVLNode *&root) {
    AVLNode *right = root->Right;
    root->Right = root->Right->Left;
    right->Left = root;
    root = right;
    FixHeight(root->Left);
    FixHeight(root);
    FixCount(root->Left);
    FixCount(root);
}
void RotateRight2(AVLNode *&root) {
    AVLNode *left = root->Left;
    root->Left = root->Left->Right;
    left->Right = root;
    root = left;
    FixHeight(root->Right);
    FixHeight(root);
    FixCount(root->Right);
    FixCount(root);
}
void BigRotateLeft2(AVLNode *&root) {
    if (Balance(root->Right) > 0) {
        RotateRight2(root->Right);
        RotateLeft2(root);
    } else {
        RotateLeft2(root);
    }
}
void BigRotateRight2(AVLNode *&root) {
    if (Balance(root->Left) < 0) {
        RotateLeft2(root->Left);
        RotateRight2(root);
    } else {
        RotateRight2(root);
    }
}
void FixTree(AVLNode *&node) {
    if (Balance(node) == -2) {
        BigRotateLeft2(node);
    } else if (Balance(node) == 2) {
        BigRotateRight2(node);
    } else {
        FixHeight(node);
        FixCount(node);
    }
}
void Add(int key, AVLNode *&node) {
    if (!node) {
        node = new AVLNode(key);
        return;
    }
    if (node->Key < key) Add(key, node->Right);
    else Add(key, node->Left);
    FixTree(node);
}
AVLNode *MinRight(AVLNode *root,AVLNode*& node) {
    if(root->Left) {
        root->Left = MinRight(root->Left,node);
    }else{
        node=root;
        return root->Right;
    }
    FixTree(root);
    return root;
}
void DeleTed(AVLNode *rot) {
    std::stack<AVLNode *> stack_node;
    stack_node.push(rot);
    while (!stack_node.empty()) {
        AVLNode *root = stack_node.top();
        stack_node.pop();
        if (root) {
            stack_node.push(root->Left);
            stack_node.push(root->Right);
            delete root;
        }
    }
}
int Kstat(int kstat, AVLNode *root) {
    int statistic = Count(root->Right);
    while (statistic != kstat) {
        if (kstat < statistic) {
            root = root->Right;
            statistic = statistic - (1 + Count(root->Left));
        } else {
            root = root->Left;
            statistic = statistic + (1 + Count(root->Right));
        }
    }
    return root->Key;
}
AVLNode *DeleteElem(int k, AVLNode *&root) {
    if (root->Key < k) {
        root->Right = DeleteElem(k, root->Right);
    } else if (k < root->Key) {
        root->Left = DeleteElem(k, root->Left);
    } else {
        if (!root->Left || !root->Right) {
            AVLNode *child = root->Left ? root->Left : root->Right;
            delete root;
            return child;
        } else {
            AVLNode *min_node = new AVLNode(0);
            root->Right = MinRight(root->Right, min_node);
            root->Key = min_node->Key;
            delete min_node;
        }
    }
    FixTree(root);
    return root;
}
int KstatKey(int key, AVLNode *node, int k) {
    while (node->Key != key) {
        if (node->Key < key) {
            node = node->Right;
        } else {
            k += Count(node->Right) + 1;
            node = node->Left;
        }
    }
    if (!node->Right && !node->Left) {
        return k;
    } else {
        return k + Count(node->Right);
    }
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    int n = 0;
    std::cin >> n;
    AVLNode *root = new AVLNode(0);
    std::vector<int> v(n * 2);
    for (int i = 0; i < n * 2; i += 2) {
        std::cin >> v[i] >> v[i + 1];
    }
    root->Key = v[1];
    std::cout << KstatKey(v[1], root, 0) << " ";
    for (int i = 2; i < n * 2; i += 2) {
        if (v[i] == 1) {
            Add(v[i + 1], root);
            std::cout << KstatKey(v[i + 1], root, 0) << " ";
        } else if (v[i] == 2) {
            root = DeleteElem(Kstat(v[i + 1], root), root);
        }
    }
    DeleTed(root);
    return 0;
}
