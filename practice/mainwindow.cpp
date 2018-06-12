#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <math.h>
#include <string>

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

int reverse(int x) {
    int sign = x < 0? -1: 1;
    x = abs(x);
    int stash[20];
    int capacity = 0;
    while(x) {
        stash[capacity++] = x % 10;
        x /= 10;
    }

    int reversed = 0;
    int i = 0;
    int maxInt = pow(2, 31) - 1;
    while(capacity) {
        if ((maxInt - stash[i]) / 10 < reversed) {
            return 0;
        }
        reversed *= 10;
        if (maxInt - stash[i] < reversed) {
            return 0;
        }
        reversed += stash[i++];
        --capacity;
    }

    return reversed * sign;
}

int letterIndex(char letter) {
    if ('a' <= letter && letter <= 'z') {
        return letter - 'a';
    } else if ('A' <= letter && letter <= 'Z') {
        return letter - 'A' + 26;
    } else {
        return -1;
    }

}

int firstUniqChar(string s) {
    int num[52] = {0};
    for(int i = 0; i < s.size(); ++i) {
        int index = letterIndex(s.at(i));
        if (index != -1) { num[index] ++; }
    }
    for (int i = 0; i < s.size(); ++i) {
        int index = letterIndex(s.at(i));
        if (num[index] == 1) { return i; }
    }

    return -1;
}


string countAndSay(int n) {
    if (n <= 0) {
        return "error input";
    }
    if (n == 1) {
        return "1";
    }

    string degreaded = countAndSay(n - 1);
    string result = "";
    for(int i = 0; i < (int)degreaded.size(); ) {
        char letter = degreaded.at(i);
        int num = 0;
        while (i < degreaded.size() && letter == degreaded[i]) {
           ++num;
           ++i;
        }
        string numStr = "";
        while(num) {
            numStr.push_back(num % 10 + '0');
            num /= 10;
        }
        for (int i = numStr.size() - 1; i >= 0; --i) {
            result.push_back(numStr.at(i));
        }
        result.push_back(letter);
    }
    int i = 0;
    i = 1;
    return result;
}

bool isAnagram(string s, string t) {

    int sArray[26] = {0};
    int tArray[26] = {0};

    for (int i = 0; i < s.size(); ++i) {
        sArray[s.at(i) - 'a']++;
    }
    for (int i = 0; i < t.size(); ++i) {
        tArray[t.at(i) - 'a']++;
    }

    for (int i = 0; i < 26; ++i) {
        if (sArray[i] != tArray[i]) {
            return false;
        }
    }

    return true;
}

bool isPalindrome(string s) {
    int length = 0 ;
    char container[s.size()];
    for (int i = 0; i < s.size(); ++i) {
        char letter = s.at(i);
        if ('a' <= letter && letter <= 'z') {
            letter = letter + 'a' - 'A';
        }
        if (('a' <= letter && letter <= 'z') || ('0' <= letter && letter <= '9')) {
            container[length++] = s[i];
        }
    }

    for (int i = 0, j = length - 1; i < j; ++i, --j) {
        if (container[i] != container[j]) { return false;}
    }

    return true;
}

int strStr(string haystack, string needle) {
    if (!needle.size()) { return 0; }
    for (int i = 0; i < haystack.size(); ++i) {
        int stackIndex = i;
        int j;
        for (j = 0; j < needle.size() && stackIndex < haystack.size(); ++j, ++stackIndex) {
            if (haystack.at(stackIndex) != needle.at(j)) {
                break;
            }
        }
        if (j == needle.size()) { return i; }
    }

    return -1;
}

string longestCommonPrefix(vector<string>& strs) {
    if (!strs.size()) { return ""; }
    string text = strs.at(0);
    string result = "";
    string temp = "";
    for(int i = 1; i <= text.size(); ++i) {
        temp = text.substr(0, i);
        bool allIn = true;
        for (int j = 1; j < strs.size(); ++j) {
            if (strs.at(j).find(temp) != 0) {
                allIn = false;
                break;
            }
        }
        if (allIn) {
            result = temp;
        }
    }
    return result;
}

void MainWindow::on_pushButton_clicked()
{

}






















