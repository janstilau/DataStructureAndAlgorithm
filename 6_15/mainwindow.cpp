#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <queue>
#include <stack>

using namespace std;

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

 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

int romanToInt(string roman) {
    int result;
    for (int i = 0; i < roman.size(); ++i ) {

    }
}

bool isValid(const vector<int> &input, const vector<int> &output) {
    stack<int> imitate;
    int inputIndex = 0;
    for(int i = 0; i < (int)output.size(); ++i) {
        int num = output[i];
        if (imitate.size() && imitate.top() == num) {
            imitate.pop();
            continue;
        }
        bool found = false;
        for(; inputIndex < (int)input.size() && !found; ++inputIndex) {
            if (input[inputIndex] == num) {
                found = true;
            }
            imitate.push(input[inputIndex]);
        }
        if (found) {
            imitate.pop();
        } else {
            return false;
        }
    }

    return true;
}

struct Node
{
    Node(int num):left(NULL), right(NULL) {this->value = num;}
    int value;
    Node *left;
    Node *right;
};

vector<vector<int>> findSumPath(Node *root, int sum) {

    vector<vector<int>> result;
    vector<int> path;
    stack<Node *> stash;
    int currentSum = 0;
    stash.push(root);
    while(!stash.empty()) {
        Node *top = stash.top();
        stash.pop();
        path.push_back(top->value);
        currentSum += top->value;
        if (!top->left && !top->right) {
            if (currentSum == sum) {
                result.push_back(path);
            }
            path.pop_back();
            currentSum -= top->value;
        } else {
            if (currentSum == sum) {
                path.pop_back();
                currentSum -= top->value;
            } else {
                if (top->right) {
                    stash.push(top->right);
                }
                if (top->left) {
                    stash.push(top->left);
                }
            }
        }
    }

    return result;
}


bool isDivideByThree(int num)    {
    int n = num;
    int sum = 0;
    while (n) {
        sum += n % 10;
        n /= 10;
    }
    if (sum % 3) {
        return false;
    }else {
        return true;
    }
}

bool isPowerOfThree(int n) {
    if (n <= 2) { return false;}
    while (n) {
        if (!isDivideByThree(n)) { return false;}
        n /=  3;
        if (n == 1) { break; }
    }
    return true;
}

int hammingWeight(uint32_t n) {
    int num = 0;
    while(n) {
        if (n & 0x01){
           ++num;
        }
        n >>= 1;
    }
    return num;
}

int hammingDistance(int x, int y) {
     int value = x ^ y;
     return hammingWeight(value);
}

uint32_t reverseBits(uint32_t n) {
    uint32_t right, left;
    for (int i = 0; i < 16; ++i) {
       right = n & (1 << n);
       left = n & (1 << (31 - n));
       right <<= 31 - n;
       left >>= 31 - n;
       if (right) {
           n |= right;
       }
       else {
          n &= !(1 << 31 -n);
       }

       if (left) {
           n |= left;
       }
       else {
          n &= !(1 << 31 -n);
       }
    }
    return n;
}
bool valid(const char &left, const char &right) {
    switch (right) {
    case '}':
        return left == '{';
        break;
    case ']':
        return left == '[';
        break;
    case ')':
        return left == '(';
        break;
    default:
        break;
    }
    return false;
}

bool isValid(string s) {
    stack<char> stash;
    for (int i = 0; i < s.size(); ++i) {
       const char &letter = s[i];
       if (letter == '{' || letter == '[' || letter == '(') {
           stash.push(letter);
       } else {
           if (!stash.size()) {  return false; }
           char stashLetter = stash.top();
           stash.pop();
           if (!valid(stashLetter, letter)) { return false;}
       }
    }
    if(stash.size()) { return false; }
    return true;
}

int missingNumber(vector<int>& nums) {
    int size = nums.size();
    if (!size || size == 1) { return 0;}
    int n = 0;
    bool hasZero = false;
    for (int i = 0; i < size; ++i) {
        if (nums[i] == 0) { hasZero = true; }
        if (nums[i] > n) { n = nums[i];}
    }
    if (!hasZero) { return 0;}
    int sum = (1 + n) * n / 2;
    for (int i = 0; i < size; ++i) {
        sum -= nums[i];
    }
    return sum / 2 * -1;
}


int sum(ListNode* l1, ListNode* l2) {

    int factor = 1;
    int addend = 0;
    int sum = 0;
    while(l1 && l2) {
        int digitSum = l1->val + l2->val + addend;
        addend = digitSum >= 10? 1 : 0;
        sum += factor * (digitSum % 10);
        factor *= 10;
        l1 = l1->next;
        l2 = l2->next;
    }

    while (l1) {
        int digitSum = l1->val + addend;
        addend = digitSum >= 10? 1 : 0;
        sum += factor * (digitSum % 10);
        factor *= 10;
        l1 = l1->next;
    }

    while (l2) {
        int digitSum = l2->val + addend;
        addend = digitSum >= 10? 1 : 0;
        sum += factor * (digitSum % 10);
        factor *= 10;
        l2 = l2->next;
    }

    if (addend) { sum += factor * addend; }

    return sum;
}

ListNode *numToList(int num) {

    int digit = num % 10;
    num /= 10;
    ListNode *head = new ListNode(digit);
    ListNode *current = head;
    while (num) {
        digit = num % 10;
        num /= 10;
        ListNode *digitNode = new ListNode(digit);
        current->next = digitNode;
        current = current->next;
    }
    return head;
}

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

    int addend = 0;
    int digit = l1->val + l2->val;
    int factor = 1;
    addend = digit >= 10? 1 : 0;
    digit %= 10;

    ListNode *head = new ListNode(digit) * factor;
    ListNode *current = head;
    l1 = l1->next;
    l2 = l2->next;
    while (l1 && l2) {
        digit = l1->val + l2->val + addend;
        addend = digit >= 10? 1 : 0;
        ListNode *node = new ListNode(digit % 10) * factor;
        current->next = node;
        current = current;
    }

    ListNode *left = NULL;
    if (l1) {
        left = l1;
    } else if (l2) {
        left = l2;
    }

    while (left) {
        digit = left->val + addend;
        addend = digit >= 10? 1 : 0;
        ListNode *node = new ListNode(digit % 10) * factor;
        current->next = node;
        current = current;
    }

    if (addend) {
        current->next = new ListNode(1);
    }

    return head;
}

void MainWindow::on_pushButton_clicked()
{
    ListNode *node = new ListNode(1);
    node->next = new ListNode(9);
    node->next->next = new ListNode(9);

    ListNode *another = new ListNode(9);
//    another->next = new ListNode(6);
//    another->next->next = new ListNode(4);

    addTwoNumbers(node, another);
}






















