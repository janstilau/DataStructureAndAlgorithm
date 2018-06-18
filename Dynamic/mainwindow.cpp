#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stack>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>
#include <QDebug>

using namespace std;
#define MAXSIZE 99999
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        this->mTop = 0;
    }

    void push(int x) {
        if (mTop == MAXSIZE) {
            return;
        }
        mStack[mTop] = x;
        if (!mTop) {
            mMinStack[mTop] = x;
        } else {
            int currentMin = mMinStack[mTop - 1];
            mMinStack[mTop] = currentMin < x ? currentMin: x;
        }
        ++mTop;
    }

    void pop() {
        if (!mTop) { return; }
        --mTop;
    }

    int top() {
        if (!mTop) { return -1; }
        return mStack[mTop - 1];
    }

    int getMin() {
        if (!mTop) { return -1; }
        return mMinStack[mTop - 1];
    }

private:
    int mTop;
    int mStack[MAXSIZE];
    int mMinStack[MAXSIZE];
};

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

int climbStairs(int n) {
//    static std::map<int, int> stash;

//    if (stash.find(n) != stash.end()) {
//        return stash.find(n)->second;
//    }

//    if ( n == 1) {
//        return 1;
//    }
//    else if ( n == 2) {
//        return 2;
//    }

//    int result = climbStairs(n - 1) + climbStairs(n - 2);
//    stash[n] = result;
//    return result;

    int d0=0;
    int d1=1;
    for(int i=1;i<=n;++i){
        int tmp = d1;
        d1 += d0;
        d0 = tmp;
    }
    return d1;
}

int maxSubArray(vector<int>& nums) {
    int sum = 0, max = INT_MIN;
    for(int i = 0; i < nums.size(); ++i) {
        sum += nums[i];
        if (sum > max) {
            max = sum;
        }
        if (sum < 0) {
            sum = 0;
        }
    }

    return max;
}

int maxProfit(vector<int>& prices) {
    int size = prices.size();
    if (size <= 1) { return 0;}
    int maxContainer[size - 1];
    int max = 0;
    for (int i = size - 1; i >= 1; --i) {
        if (prices[i] > max) {
            max = prices[i];
        }
        maxContainer[i - 1] = max;
    }

    max = 0;
    for (int i = 0; i < size - 1; ++i) {
        int profit = maxContainer[i] - prices[i] ;
        if (profit > max) {
            max = profit;
        }
    }
    return max;
}

long rob(vector<long>& nums, long left, long right) {
    long size = right - left + 1;
    if (size <= 0) { return 0; }
    else if (size == 1) { return nums[left]; }
    else if (size == 2) {
        return std::max(nums[left], nums[left + 1]);
    }
    else if (size == 3) {
        long middle = nums[left + 1];
        long outSum = nums[left] + nums[left + 2];
        return std::max(middle, outSum);
    }

    long result = nums[left] + rob(nums, left + 2, right);
    long another = nums[left + 1] + rob(nums, left + 3, right);
    long value = std::max(result, another);

    return value;
}

int rob(vector<int>& num) {
    if (num.size() <= 1) return num.empty() ? 0 : num[0];
    vector<int> dp = {num[0], max(num[0], num[1])};
    for (int i = 2; i < num.size(); ++i) {
       dp.push_back(max(num[i] + dp[i - 2], dp[i - 1]));
    }
    return dp.back();
}

string numString(int n) {
    char buffer[10] = {0};
    sprintf(buffer, "%d", n);
    return string(buffer);
}

vector<string> fizzBuzz(int n) {
    vector<string> result;
    for (int i = 1; i <= n; ++i) {
        if (i %3 == 0) {
            if (i % 5 == 0) {
                result.push_back("FizzBuzz");
            } else {
                result.push_back("Fizz");
            }
        } else if (i % 5 == 0) {
            result.push_back("Buzz");
        } else {
            result.push_back(numString(i));
        }
    }
    return result;
}

bool isPrime(int a) {
    if(a < 2) return false;
    for(var i = 2; i<= std::sqrt(a); i++)
    {
        if(a % i == 0)return false;
    }
    return true;
}

int countPrimes(int n) {
    int count = 0;
    for (int i = 1; i < std::sqrt(n); ++i) {
        if (isPrime(i)) {
            ++count;
        }
    }
    return count;
}

void MainWindow::on_pushButton_clicked()
{
    char buffer[10] = {0};
    sprintf(buffer, "%d", 100);
    string v(buffer);
    int i;
    ++i;
}
