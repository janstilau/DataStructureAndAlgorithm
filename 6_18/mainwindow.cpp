#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <QDebug>
#include <iostream>

using namespace std;

struct TreeNode {
 int val;
 TreeNode *left;
 TreeNode *right;
 TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct TreeLinkNode {
  TreeLinkNode *left;
  TreeLinkNode *right;
  TreeLinkNode *next;
};

vector<int> topKFrequent(vector<int>& nums, int k) {
    map<int, int> times;
    vector<int> result;
    for(int i = 0; i < nums.size(); ++i) {
        times[nums[i]]++;
    }

    auto it = times.begin();
    vector<int> keys;
    while (it != times.end()) {
        keys.push_back(it->first);
        ++it;
    }

    sort(keys.begin(), keys.end(), [&times](int x, int y) {
        return times[x] > times[y];
    } );

    for (int i = 0; i < k; ++i) {
        result.push_back(keys[i]);
    }

    return result;
}

int numIslands(vector<vector<char>>& grid) {

    int m = grid.size();
    if (!m) { return 0; }
    int n = grid[0].size();
    if (!n) { return 0; }

    vector<vector<int>> islandRegions;
    vector<vector<bool>> visited(m, vector<bool>(n, false));

    int left, right, top, bottom, x, y;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!visited[i][j] && grid[i][j] == '1') {
                queue<int> stash;
                vector<int> region;
                stash.push(i * n + j);
                while (!stash.empty()) {
                    int position = stash.front();
                    stash.pop();
                    x = position % n;
                    y = position / n;
                    if (visited[y][x]) {continue; }
                    visited[y][x] = true;
                    region.push_back(position);
                    top = position / n - 1;
                    bottom = position / n + 1;
                    left = position % n - 1;
                    right = position % n + 1;
                    if (left > 0 && (grid[y][left] == '1')) {
                        stash.push(y * n + left);
                    }
                    if (bottom < m && (grid[bottom][x] == '1')) {
                        stash.push(bottom * n + x);
                    }
                    if (right < n  && (grid[y][right] == '1')) {
                        stash.push(y * n + right);
                    }
                    if (top > 0 && (grid[top][x] == '1')) {
                        stash.push(top * n + x);
                    }
                }
                if (!region.empty()) { islandRegions.push_back(region);}
            }
        }
    }

    return islandRegions.size();
}

void connect(TreeLinkNode *root) {
    if (root->left && root->right) {
        root->left->next = root->right;
        if (root->left->right) {
            root->left->right->next = root->right->left ? root->right->left: NULL;
        }
    }
    if (root->left) {
        connect(root->left);
    }
    if (root->right) {
        connect(root->right);
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

TreeNode *buildTree(const vector<int>& preorder, int preLeft, int preRight, vector<int>& inorder, int inLeft, int inRight) {
    int size = preRight - preLeft + 1;
    int inSize = inRight - inLeft + 1;
    if (size != inSize) { return NULL;}
    if (size <= 0) { return NULL;}

    int middleValue = preorder[preLeft];
    qDebug() << "middleValue" << middleValue << "preLeft" << preLeft << "preRight" << preRight << "inleft" << inLeft << "inright" <<inRight;
    TreeNode *middleNode = new TreeNode(middleValue);
    int inMiddlePosition = -1;
    for (int i = inLeft; i <= inRight; ++i) {
        if (inorder[i] == middleValue) {
            inMiddlePosition = i;
            break;
        }
    }
    if (inMiddlePosition == -1) {
        return middleNode;
    }
    int leftSize = inMiddlePosition - inLeft;
    int rightSize = inRight - inMiddlePosition;

    middleNode->left = buildTree(preorder, preLeft + 1, preLeft + 1 + leftSize - 1 , inorder, inLeft, inMiddlePosition - 1);
    middleNode->right = buildTree(preorder, preLeft + 1 + leftSize, preLeft + 1 + leftSize + rightSize - 1, inorder, inMiddlePosition + 1, inMiddlePosition + 1 + rightSize - 1);
    return middleNode;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    if (preorder.size() != inorder.size()) { return NULL; }
    set<int> preSet;
    set<int> inSet;
    for (int i = 0; i < preorder.size(); ++i) {
        if (preSet.find(preorder[i]) != preSet.end()) {
            return NULL;
        }
        preSet.insert(preorder[i]);
    }
    for (int i = 0; i < inorder.size(); ++i) {
        if (inSet.find(inorder[i]) != inSet.end()) {
            return NULL;
        }
        inSet.insert(inorder[i]);
    }
    if (preSet != inSet) {
        return NULL;
    }

    return buildTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
}

void inorderRecurively(TreeNode *root, vector<int> &result) {
    if (!root) {
        return;
    }

    inorderRecurively(root->left, result);
    result.push_back(root->val);
    inorderRecurively(root->right, result);
}

vector<int> inorderIteratively(TreeNode *root) {

    stack<TreeNode *> stack;

    vector<int> result;
    TreeNode *current = root;

    while(current || !stack.empty()) {
        if (current) {
            stack.push(current);
            current = current->left;
            continue;
        }

        current = stack.top();
        stack.pop();
        result.push_back(current->val);
        current = current->right;
    }

    return result;

}

vector<int> inorderTraversal(TreeNode* root) {

    return inorderIteratively(root);
}

int kthSmallest(TreeNode* root, int k) {
    stack<TreeNode *> stash;
    TreeNode *current = root;
    TreeNode *temp;

    int i = 0;
    while(current || !stash.empty()) {
        if (current) {
            stash.push(current);
            current = current->left;
            continue;
        }

        temp = stash.top();
        stash.pop();
        ++i;
        if (i == k) {
            return temp->val;
        }
        current = temp->right;
    }

    return -1;
}

struct NodeLevel
{
    NodeLevel(TreeNode* root, int level) {this->node = root; this->level = level; }
    TreeNode *node;
    int level;
};

vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) { return result; }

    vector<NodeLevel> recorder;
    queue<NodeLevel> stash;
    stash.push(NodeLevel(root, 1));
    while(!stash.empty()) {
        const NodeLevel &node = stash.front();
        recorder.push_back(node);
        stash.pop();
        if (node.node->left) {
            stash.push(NodeLevel(node.node->left, node.level + 1));
        }
        if (node.node->right) {
            stash.push(NodeLevel(node.node->right, node.level + 1));
        }
    }

    bool reverse = false;
    for(int i= 0; i < recorder.size(); ++i) {
        int currentLevel = recorder[i].level;
        int j = i;
        while(recorder[j].level == currentLevel && j < recorder.size()) {
            ++j;
        }
        --j;
        vector<int> levelSequence;
        if (reverse) {
            for (int start = j; start >= i; --start) {
                levelSequence.push_back(recorder[start].node->val);
            }
        } else {
            for (int start = i; start <= j; ++start) {
                levelSequence.push_back(recorder[start].node->val);
            }
        }
        result.push_back(levelSequence);
        reverse = !reverse;
        i = j;
    }

    return result;
}

void sortColors(vector<int>& nums) {
    int counts[3] = {0};
    for (int i = 0; i < nums.size(); ++i) {
        counts[nums[i]]++;
    }

    int begin = 0;
    for(int i = 0; i < 3; i++) {
        int count = counts[i];
        int flag = begin;
        for (; begin < flag + count; ++begin) {
            nums[begin] = i;
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
//    vector<int> nums = {1,1,1,2, 2,2 , 2,2,3, 3, 3,3,3,3};
//    topKFrequent(nums, 2);

    vector<int> data{ 3,1,2,7,5 };
    //构造堆，最大堆
    make_heap(data.begin(), data.end(), less<int>());
    //pop堆顶元素，最大的元素
    pop_heap(data.begin(), data.end(), less<int>());
    cout << data.back() << endl;//输出7
    data.pop_back();
    //往堆中添加元素
    data.push_back(4);
    push_heap(data.begin(), data.end(), less<int>());//调整堆
    //排序
    sort_heap(data.begin(), data.end(), less<int>());
    for (int x : data)
        cout << x << " ";
    cout << endl;//输出 1，2，3，4，5

}
