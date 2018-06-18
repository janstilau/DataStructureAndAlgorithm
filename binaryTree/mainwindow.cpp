#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStack>
#include <QVector>
#include <QDebug>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct Level
{
    TreeNode *mNode;
    int mLevel;
    Level(TreeNode *node, int level) {this->mNode = node; this->mLevel = level;}
};

vector<Level> iterateTree(TreeNode *root) {
    vector<Level> array;
    if (!root) { return array; }
    queue<Level> stash;
    stash.push(Level(root, 1));
    while(stash.size()) {
        const Level &node = stash.front();
        stash.pop();
        array.push_back(node);
        if (node.mNode->left) {
           stash.push(Level(node.mNode->left, node.mLevel + 1));
        }
        if (node.mNode->right) {
           stash.push(Level(node.mNode->right, node.mLevel + 1));
        }
    }

    return array;
}

vector<vector<int>> levelOrder(TreeNode* root) {
    auto array = iterateTree(root);
    vector<vector<int>> result;
    vector<int> subArray;
    int currentLevel = -1;
    for (int i = 0; i < array.size(); ++i) {
        Level item = array[i];
        if (item.mLevel != currentLevel) {
            currentLevel = item.mLevel;
            if (subArray.size()) {
                result.push_back(subArray);
                subArray.clear();
            }
        }
        subArray.push_back(item.mNode->val);
    }
    if (subArray.size()) {
        result.push_back(subArray);
    }

    return result;
}

int maxDepth(TreeNode* root) {
    auto array = iterateTree(root);
    if (!array.size()) {return 0;}
    auto &level =  array[array.size() - 1];
    return level.mLevel;
}

//void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
//    vector<int> stash = nums1;
//    int i, j;
//    for (i = 0, j = 0; i < m && j < n; ++i, ++j) {

//    }
//    int index = 0;
//    while (i < m && j < n) {
//        if (nums1[i] < nums2[j]) {
//            m[index++] = nums1[i];
//            ++i;
//        } else {
//            m[index++] = nums1[j];
//            ++j;
//        }
//    }

//    while (i < m) {
//        m[index++] = nums1[i];
//        ++i;
//    }

//    while (j < n) {
//        m[index++] = nums1[j];
//        ++j;
//    }
//}
bool isBadVersion(int version){
    if (version == 1702766719) {
        return true;
    } else {
        return false;
    }
}

int firstBadVersion(int n) {
    long
    int left = 1;
    int right = n;
    int middle = (left + right) / 2;
    int times = 0;
    while (left < right) {
        middle = (left + right) / 2;
        if (isBadVersion(middle)) {
            right = middle - 1;
        } else {
            left = middle + 1;
        }
        qDebug() << middle;
//        qDebug() << times++;
    }
    int miner = middle < right? middle: right;
    int maxer = middle < right? right: middle;
    if(isBadVersion(miner)) {
        return miner;
    } else {
        return maxer;
    }
    }

bool check(vector<TreeNode *> &array) {
    if (array.size() & 0x01) {
        return false;
    }

    for (int i = 0, j = array.size() - 1; i < j; ++i, --j) {
        if ((array[i] && array[j]) && (array[i]->val == array[j]->val)) {
            continue;
        }
        if (!array[i] && !array[j]) {
            continue;
        }
        return false;
    }

    return true;
}

bool isSymmetric(TreeNode* root) {
    if (!root) { return false; }

    int nodeCount = 0;
    vector<TreeNode *> array;
    array.push_back(root);
    ++nodeCount;
    while(nodeCount) {
        if (array.size() != 1) {
            if (!check(array)) {
                return false;
            }
        }

        nodeCount = 0;
        int currentSize = array.size();
        while (array.size() != currentSize * 2) {
           array.push_back(NULL);
        }
        for (int i = currentSize - 1; i >=0; --i) {
            if (!array[i]) {
                array[2 * i + 1] = array[i];
                array[2 * i] = array[i];
                continue;
            }
            if (array[i]->right) { ++nodeCount; }
            array[2 * i + 1] = array[i]->right;
            if (array[i]->left) { ++nodeCount; }
            array[2 * i] = array[i]->left;

        }
    }

    return true;
}

bool compare(TreeNode *left, TreeNode *right) {
    if (!left && !right) { return true; }
    if (left || right) { return false; }
    return (left->val == right->val) && (compare(left->left, right->right)) && (compare(left->right, right->left));
}

bool isSymmetric_(TreeNode* root) {
    if(!root) {
        return true;
    }

    return compare(root->left, root->right);
}

void handleNode(Node *node) {
    qDebug() << node->data;
}

void recurseMLR(Node *root) {
    if (!root) { return; }
    handleNode(root);
    recurseMLR(root->left);
    recurseMLR(root->right);
}

void recurseLMR(Node *root) {
     if (!root) { return; }
    recurseLMR(root->left);
    handleNode(root);
    recurseLMR(root->right);
}

void recurseLRM(Node *root) {
     if (!root) { return; }
    recurseLRM(root->left);
    recurseLRM(root->right);
    handleNode(root);
}

// 访问节点, 就是出栈的时候
// 访问一个节点之后, 先入栈 right, 然后入栈 left
// 访问下一个节点, 就是出栈 top 的过程, 所以先处理 right, 在处理完 right 只有, 就是处理 right 为根节点的树.
// left 节点只有在 right 树处理完之后才会处理.
void iterateMLR(Node *root) {
    QStack<Node *> stack;
    stack.push(root);
    while(!stack.isEmpty()) {
        Node *current = stack.pop();
        handleNode(current);
        if (current->right) {
            stack.push_back(current->right);
        }
        if (current->left) {
            stack.push_back(current->left);
        }
    }
}

// 一个节点, 如果有 left 那么 left 就要一直入栈,
// 当一个节点没有 left 的时候, 就该访问这个节点, 然后入栈这个节点的 right
// right 节点入栈之后, 也是一直入栈 left, 直到没有 left 才会访问这个节点, 也就是说, 先入栈, 然后在没有 left 的时候出栈并且操作.
void iterateLMR(Node *root) {
    QStack<Node *> stack;
    Node *current = root;
    while (current || !stack.isEmpty()) {
        if (current) {
            stack.push_back(current);
            current = current->left;
            continue;
        }
        current = stack.pop();
        handleNode(current);
        current = current->right;
    }

}

// 可以这样理解, 这是一个埋点的过程, 最后会处理的埋到 stackResult 的最后面
// 首先是 root 节点, root 节点最后会被处理, 所以弹出后埋到了 stackResult 的最后面
// 然后 root 节点的两个子节点, right 会被后处理, 所以先被埋到 stackResult 里面
// 然后是埋整个 right 子树的过程, 当 right 子树都被埋进 result 之后, 才处理 left 子树
// stackStash 的逻辑其实是和 MLR 是相同的, 只不过这个处理是埋点.
QStack<Node *> iterateLRM(Node *root) {
    QStack<Node *> stackStash;
    QStack<Node *> stackResult;

    stackStash.push_back(root);
    while (!stackStash.isEmpty()) {
        Node *current = stackStash.pop();
        if (current->left) {
            stackStash.push_back(current->left);
        }
        if (current->right) {
            stackStash.push_back(current->right);
        }
        stackResult.push_back(current);
    }

    while (!stackResult.isEmpty()) {
        Node *current = stackResult.pop();
        handleNode(current);
    }
    return stackResult;
}

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

// in place
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (!l1) { return l2; }
    if (!l2) { return l1; }
    ListNode *current = NULL;
    ListNode *another = NULL;
    ListNode *mergeHead = NULL;

    if (l1->val < l2->val) {
        mergeHead = l1;
        current = l1;
        another = l2;
    } else {
        mergeHead = l2;
        current = l2;
        another = l1;
    }

    while(another && current) {
        ListNode *next = current->next;
        if (!next) {
            current->next = another;
            break;
        }
        if (next->val < another->val) {
            current = current->next;
        } else {
            ListNode *anotherNext = another->next;
            another->next = current->next;
            current->next = another;
            another = anotherNext;
        }
    }

    return mergeHead;
}

bool isPalindrome(ListNode* head) {
    if(!head) { return false;}
    int length = 0;
    for(ListNode *iter = head; iter; iter = iter->next) {
        ++length;
    }
    int step = length/2;
    bool isOdd = length & 0x01;
    ListNode *advanceNode = head;
    stack<int> stack;
    while (step--) {
       stack.push(advanceNode->val);
       advanceNode = advanceNode->next;
    }
    if(isOdd) {
        advanceNode = advanceNode->next;
    }


    for (; advanceNode; advanceNode = advanceNode->next) {
        int value = stack.top();
        stack.pop();
        if (value != advanceNode->val) {
            return false;
        }
    }

    return true;
}

bool hasCycle(ListNode *head) {
    if (!head) { return false;}
    ListNode *stash = head;
    head = head->next;
    while (head) {
        if (head == stash) { return true;}
    }
    return false;
}

//bool equal(Node *node, Node *another) {
//    boolean flag=false;
//    ListNode *fast=head;
//    ListNode *slow=head;
//    while(true){
//        if(fast==null||fast->next==null)
//            return false;
//        slow=slow->next;
//        fast=fast->next->next;
//        if(fast==slow){
//            flag=true;
//            break;
//        }
//    }
//    return flag;
//}

//bool fildSubTree(Node *root, Node *subRoot) {
//    if (!root || !subRoot) { return false; }

//    bool result = true;
//    QStack<Node *> stack = iterateLRM(root);
//    while (!stack.isEmpty()) {
//        Node *node = stack.pop();
//        if (node->data != subRoot->data) { continue; }
//        if (equal(node, subRoot)) {
//            return true;
//        }
//    }

//    return false;
//}

QVector<int> preOrder = {1, 2, 4, 7, 3, 5, 6, 8};
QVector<int> inOrder= {4, 7, 2, 1, 5, 3, 8, 6};

Node *createTree(int preStart, int preEnd, int inStart, int inEnd) {
    if ((preEnd - preStart) != (inEnd - inStart)) {
        return nullptr;
    }
    if (preEnd < preStart || inEnd < inStart) {
        return nullptr;
    }

    int middle= preOrder[preStart];
    int middleIndex;
    for(middleIndex = inStart; middleIndex <= inEnd; ++middleIndex) {
        if (inOrder[middleIndex] == middle) {
            break;
        }
    }

    if (middleIndex > inEnd) { return nullptr;}

    int lLength = middleIndex - inStart;

    int leftPS = preStart + 1;
    int leftPE = preStart + lLength;
    int leftIS = inStart;
    int leftIE = inStart + lLength - 1;

    int rightPS = preStart + 1 + lLength;
    int rightPE = preEnd;
    int rightIS = inStart + lLength + 1;
    int rightIE = inEnd;

    Node *middleNode = new Node();
    middleNode->data = middle;
    middleNode->left = createTree(leftPS, leftPE, leftIS, leftIE);
    middleNode->right = createTree(rightPS, rightPE, rightIS, rightIE);
    return middleNode;
}

// 向一颗二叉搜索树, 插入一个新的结点
Node *insertSearchNode(int data, Node* rootNode) {

    if (!rootNode) {
        rootNode = new Node();
        rootNode->data = data;
    } else {
        if (data < rootNode->data) {
            rootNode->left = insertSearchNode(data, rootNode->left);
        } else {
            rootNode->right = insertSearchNode(data, rootNode->right)
        }

    }
    return rootNode;
}

Node *findSearchNodeRecurisely(int data, Node* rootNode) {

    if (data == rootNode->data) {
        return rootNode;
    } else if (data > rootNode->data) {
        return findSearchNode(data, rootNode->right);
    } else {
        return findSearchNode(data, rootNode->left);
    }
}

Node *findSearchNodeIteratively(int data, Node *rootNode) {
    if (!rootNode) { return NULL;}
    while (rootNode) {
        if (rootNode->data == data) {
            return rootNode;
        } else if (rootNode->data > data) {
            rootNode = rootNode->right;
        } else {
            rootNode = rootNode->left;
        }
    }
    return NULL;
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

void MainWindow::on_pushButton_clicked()
{
    firstBadVersion(2126753390);
}
