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

void pushStackLMR(Node *node, QStack<Node *> &stack) {
    if (!node) { return; }
    pushStackLMR(node->left, stack);
    stack.push_back(node);
    pushStackLMR(node->right, stack);
}

void iterateLMR(Node *root) {
    QStack<Node *> stack;
    pushStackLMR(root, stack);
    while(!stack.isEmpty()) {
        handleNode(stack.pop());
    }
}

void iterateLRM(Node *root) {
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
    recurseMLR(root);
    qDebug() << "";
    recurseLMR(root);
    qDebug() << "";
    recurseLRM(root);


}
