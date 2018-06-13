#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStack>
#include <QVector>
#include <QDebug>

struct Node
{
    int data;
    Node *left;
    Node *right;
};

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
void iterateLRM(Node *root) {
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
}

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
    Node* root = createTree(0, preOrder.length() - 1, 0, inOrder.length() - 1);
//    recurseMLR(root);
//    qDebug() << "";
//    recurseLMR(root);
//    qDebug() << "";
//    recurseLRM(root);
    iterateMLR(root);
    qDebug() << "";
    iterateLMR(root);
    qDebug() << "";
    iterateLRM(root);
}
