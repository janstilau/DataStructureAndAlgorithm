#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <queue>
#include <stack>
#include <vector>
#include <map>

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

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

int findKthLargest(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    int value;
    for (int i  = nums.size() - 1; k != 0; --k, --i) {
        value = nums[i];
    }
    return value;
}

int findPeakElement(vector<int>& nums) {
    int size = nums.size();
    if(size == 1) {
        return 0;
    } else if(size == 2) {
        return nums[0] > nums[1]? 0: 1;
    }

    if (nums[0] > nums[1]) { return 0;}
    if (nums[size - 1] > nums[size - 2]) { return size - 1;}
    for (int i = 1; i < size - 1; ++i ) {
        if(nums[i - 1] < nums[i] && nums[i] > nums[i + 1]) {
            return i;
        }
    }
    return -1;
}

vector<int> searchRange(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    vector<int> result;

    int middle;
    while(left <= right) {
        middle = (left + right) / 2;
        if (nums[middle] == target) {
            break;
        } else if (nums[middle] > target) {
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }

    if (left < right) {

        int i = middle;
        int j = middle;

        while(i > 0 && nums[i] == target) {
            --i;
        }
        ++i;
        while(j < nums.size() - 1 && nums[j] == target) {
            ++j;
        }
        --j;
        result.push_back(i);
        result.push_back(j);

    } else {
        result.push_back(-1);
        result.push_back(-1);
    }

    return result;
}


bool insertsct(const Interval& former, const Interval& hinder){
    if (former.start <= hinder.start) {
        return former.end >= hinder.start;
    } else {
        return hinder.end >= former.start;
    }
}

vector<Interval> merge(vector<Interval>& intervals) {
    vector<Interval> copy = intervals;
    int size = copy.size();
    for (int i = 0; i < size; ++i) {
        Interval &item = copy[i];
        for (int j = i + 1; j < size; ++j) {
            Interval &hinder = copy[j];
            if (insertsct(item, hinder)) {
                item.start = min(item.start, hinder.start);
                item.end = max(item.end, hinder.end);
                copy.erase(copy.begin() + j);
                j = i ;
                --size;
            }
        }
    }

    return copy;
}

int search(vector<int>& nums, int target) {

    if (!nums.size()) {return -1;}
    int left = 0;
    int right = nums.size();
    int middle;
    while (left <= right) {
        middle = (left + right) / 2;
        if (nums[middle] >= nums[0]) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    int largetIndex = middle;
    if (nums[middle - 1] > nums[middle]) {
        largetIndex = middle - 1;
    }
    if(target >= nums[0]) {
        left = 0;
        right = largetIndex;
    } else {
        left = largetIndex +1;
        right = nums.size() - 1;
    }

    while (left <= right) {
        middle = (left + right) / 2;
        if (nums[middle] == target) {
            return middle;
        } else if(nums[middle] > target) {
            right = middle - 1;
        } else {
            left = middle + 1 ;
        }
    }

    return -1;
}

void MainWindow::on_pushButton_clicked()
{
    vector<int> nums = {2,3,4,5,1};
    int value = search(nums, 1);
}
