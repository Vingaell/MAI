#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>

const int MAX_PRIORITY = 1000000;
const int MIN_PRIORITY = 0;

struct TreeNode {
    int priority;
    std::string key;
    std::string value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const std::string& key, const std::string& value)
        : key(key), value(value), priority(MIN_PRIORITY + rand() % MAX_PRIORITY), left(nullptr), right(nullptr) {}
};

TreeNode* combine(TreeNode* leftTree, TreeNode* rightTree) {
    if (!leftTree) return rightTree;
    if (!rightTree) return leftTree;
    if (leftTree->priority > rightTree->priority) {
        leftTree->right = combine(leftTree->right, rightTree);
        return leftTree;
    } else {
        rightTree->left = combine(leftTree, rightTree->left);
        return rightTree;
    }
}

void partition(TreeNode* current, const std::string& key, TreeNode*& left, TreeNode*& right) {
    if (!current) {
        left = right = nullptr;
        return;
    }
    if (current->key < key) {
        partition(current->right, key, current->right, right);
        left = current;
    } else {
        partition(current->left, key, left, current->left);
        right = current;
    }
}

std::string toLowerCase(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

TreeNode* addNode(TreeNode* root, const std::string& key, const std::string& value) {
    TreeNode* newNode = new TreeNode(key, value);
    if (!root) return newNode;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    partition(root, key, left, right);
    TreeNode* tempTree = combine(left, newNode);

    return combine(tempTree, right);
}

TreeNode* findNode(TreeNode* root, const std::string& key) {
    if (!root) return nullptr;
    if (root->key == key) return root;
    if (root->key < key) {
        return findNode(root->right, key);
    }
    return findNode(root->left, key);
}

TreeNode* deleteNode(TreeNode* root, const std::string& key) {
    if (!root) return nullptr;
    if (root->key == key) {
        TreeNode* temp = combine(root->left, root->right);
        delete root;
        return temp;
    }
    if (root->key < key) {
        root->right = deleteNode(root->right, key);
    } else {
        root->left = deleteNode(root->left, key);
    }
    return root;
}

void printTree(TreeNode* root, int level = 0, char dir = '-') {
    if (root) {
        printTree(root->right, level + 1, 'R');
        for (int i = 0; i < level; ++i) std::cout << "   ";
        std::cout << dir << ":" << root->key << "(" << root->priority << ")" << std::endl;
        printTree(root->left, level + 1, 'L');
    }
}

class Treap {
    TreeNode* root;

    void destroyTree(TreeNode* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    Treap() : root(nullptr) {
        srand(time(0));
    }

    ~Treap() {
        destroyTree(root);
    }

    void insert(const std::string& key, const std::string& value) {
        std::string lowerKey = toLowerCase(key);
        if (findNode(root, lowerKey)) {
            std::cout << "Exist" << std::endl;
            return;
        }
        root = addNode(root, lowerKey, value);
        std::cout << "OK" << std::endl;
    }

    void remove(const std::string& key) {
        std::string lowerKey = toLowerCase(key);
        if (!findNode(root, lowerKey)) {
            std::cout << "NoSuchWord" << std::endl;
            return;
        }
        root = deleteNode(root, lowerKey);
        std::cout << "OK" << std::endl;
    }

    void find(const std::string& key) {
        std::string lowerKey = toLowerCase(key);
        TreeNode* node = findNode(root, lowerKey);
        if (!node) {
            std::cout << "NoSuchWord" << std::endl;
            return;
        }
        std::cout << "OK: " << node->value << std::endl;
    }

    void print() {
        printTree(root);
    }
};

int main() {
    std::string input;
    Treap treap;
    while (std::getline(std::cin, input)) {
        if (input[0] == '+') {
            auto spacePos = input.find(' ', 2);
            std::string key = input.substr(2, spacePos - 2);
            std::string value = input.substr(spacePos + 1);
            treap.insert(key, value);
        } else if (input[0] == '-') {
            std::string key = input.substr(2);
            treap.remove(key);
        } else if (input == "print") {
            treap.print();
        } else {
            treap.find(input);
        }
    }
    return 0;
}