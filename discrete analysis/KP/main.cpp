#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <memory>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Node {
    int index;
    unique_ptr<Node> left, right;
    vector<long double> min_d, max_d;
    Node(int idx, int d) : index(idx), left(nullptr), right(nullptr), min_d(d, numeric_limits<long double>::max()), max_d(d, numeric_limits<long double>::lowest()) {}
};

class KDTree {
private:
    int d;
    vector<vector<long double>>& points;
    vector<int> indices;
    unordered_map<string, int> memo;
    
    Node* build(int left, int right, int depth) {
        if (left > right) return nullptr;
        int axis = depth % d;
        int medianIndex = left + (right - left) / 2;
        sort(indices.begin() + left, indices.begin() + right + 1, [&](int a, int b) {
            return points[a][axis] < points[b][axis];
        });
        auto node = make_unique<Node>(indices[medianIndex], d);
        node->left = unique_ptr<Node>(build(left, medianIndex - 1, depth + 1));
        node->right = unique_ptr<Node>(build(medianIndex + 1, right, depth + 1));
        for (int i = 0; i < d; ++i) {
            node->min_d[i] = node->max_d[i] = points[node->index][i];
            if (node->left) {
                node->min_d[i] = min(node->min_d[i], node->left->min_d[i]);
                node->max_d[i] = max(node->max_d[i], node->left->max_d[i]);
            }
            if (node->right) {
                node->min_d[i] = min(node->min_d[i], node->right->min_d[i]);
                node->max_d[i] = max(node->max_d[i], node->right->max_d[i]);
            }
        }
        return node.release();
    }
    
    long double squaredDistance(const vector<long double>& a, const vector<long double>& b, long double currentBest) {
        long double distance = 0;
        for (int i = 0; i < d; ++i) {
            long double diff = a[i] - b[i];
            distance += diff * diff;
            if (distance >= currentBest) return distance;
        }
        return distance;
    }
    
    long double minDistanceToBox(const vector<long double>& target, const Node* node) {
        long double distance = 0;
        for (int i = 0; i < d; ++i) {
            if (target[i] < node->min_d[i]) distance += (target[i] - node->min_d[i]) * (target[i] - node->min_d[i]);
            else if (target[i] > node->max_d[i]) distance += (target[i] - node->max_d[i]) * (target[i] - node->max_d[i]);
        }
        return distance;
    }
    
    void nearest(Node* node, const vector<long double>& target, int depth, long double& bestDistance, int& bestIndex) {
        if (!node) return;
        long double currentDistance = squaredDistance(points[node->index], target, bestDistance);
        if (currentDistance < bestDistance) {
            bestDistance = currentDistance;
            bestIndex = node->index;
        }
        int axis = depth % d;
        Node* nearChild = (target[axis] < points[node->index][axis]) ? node->left.get() : node->right.get();
        Node* farChild = (target[axis] < points[node->index][axis]) ? node->right.get() : node->left.get();
        nearest(nearChild, target, depth + 1, bestDistance, bestIndex);
        if (farChild && minDistanceToBox(target, farChild) < bestDistance) {
            nearest(farChild, target, depth + 1, bestDistance, bestIndex);
        }
    }
    
    string hashPoint(const vector<long double>& point) {
        string hash = "";
        for (auto& coord : point) {
            hash += to_string(coord) + ",";
        }
        return hash;
    }
    
    unique_ptr<Node> root;

public:
    KDTree(vector<vector<long double>>& pts, int dim) : points(pts), d(dim) {
        indices.resize(points.size());
        for (int i = 0; i < points.size(); ++i) indices[i] = i;
        root = unique_ptr<Node>(build(0, points.size() - 1, 0));
    }
    
    int findNearest(const vector<long double>& target) {
        string targetHash = hashPoint(target);
        if (memo.find(targetHash) != memo.end()) return memo[targetHash];  
        long double bestDistance = numeric_limits<long double>::max();
        int bestIndex = -1;
        nearest(root.get(), target, 0, bestDistance, bestIndex);
        memo[targetHash] = bestIndex;
        return bestIndex;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n, d;
    cin >> n >> d;
    vector<vector<long double>> points(n, vector<long double>(d));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < d; ++j)
            cin >> points[i][j];
    
    KDTree kdTree(points, d);
    
    int q;
    cin >> q;
    while (q--) {
        vector<long double> query(d);
        for (int j = 0; j < d; ++j) cin >> query[j];
        cout << kdTree.findNearest(query) + 1 << '\n';
    }
    
    return 0;
}

// Код программы можно улучшить улучшив обработку случаев, когда сравниваемые точки равны