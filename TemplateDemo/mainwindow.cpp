#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <math.h>
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

bool isPalindrome(string s) {

//    if (!s.size()) { return true; }
//    char container[s.size()];
//    int size = s.size();
//    int length = 0;
//    for (int i = 0; i < s.size(); ++i) {
//        char letter = s.at(i);
//        if ('A' <= letter && letter <= 'Z') {
//            letter += 'a' - 'A' ;
//        }
//        if (('a' <= letter && letter <= 'z') || ('0' <= letter && letter <= '9') ) {
//            container[length] = letter;
//            ++length;
//        }
//    }

//    if (!length) { return false; }
//    for(int i = 0, j = length - 1; i < j; ++i, --j) {
//        if (container[i] != container[j]) {
//            return false;
//        }
//    }

//    return true;
}

int myAtoi(string str) {

    int maxInt = pow(2, 31) - 1;
    int minInt = pow(2, 31);
    int maxIntDevideTen = maxInt / 10;
    int minIntDevideTen = minInt / 10;

    int result = 0;
    int symbol = 1;
    bool symbolSetted = false;
    int item;
    for(int i = 0; i < str.size(); ++i) {
        char letter = str.at(i);
        if (letter == ' ') { continue; }
        if (letter == '+' || letter == '-') {
            if (symbolSetted) { break; }
            symbol = letter == '+' ? 1: -1;
            symbolSetted = true;
            continue;
        }
        if (letter < '0' || letter > '9') {
            break;
        }

        if (symbol == 1) {
            if (maxIntDevideTen < result) {
                result = maxInt;
                break;
            }

            result *= 10;
            item = letter - '0';
            if (maxInt - result < item) {
                result = maxInt;
                break;
            }
            result += item;
        } else {
            if (minIntDevideTen > result) {
                result = minInt;
                break;
            }

            result *= 10;
            item = letter - '0';
            if (minInt - result > item) {
                result = minInt;
                break;
            }
            result -= item;
        }
    }

    return result;
}
bool isBadVersion(long version) {

    if (1150769282 <= version) {
        return true;
    }
    return false;
}

int firstBadVersion(int n) {
    long left = 1;
    long right = n;
    long middle;
    while(right - left > 3) {
        middle = (right + left) / 2;
        if (isBadVersion(middle)) {
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }

    right = right == n? n: right + 1;
    for (long i = left; i <= right; ++i) {
        if (isBadVersion(i)) {
            return i;
        }
    }
    return 0;
}

void MainWindow::on_pushButton_clicked()
{
    firstBadVersion(1420736637);
}
