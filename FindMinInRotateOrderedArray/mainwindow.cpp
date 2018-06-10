#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

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

int findMinIterately(const vector<int> &array) {
    int n = array.size();
    if (!n) { return -1; }

    for (int i = 1; i < n; ++i){
        if (array[i] < array[i - 1]) {
            return array[i];
        }
    }

    return array[0];
}

int findMinInRoated(const vector<int> &array) {
    int n = array.size();
    if (!n) { return -1; }
    if (array[0] < array[n - 1]) { return array[0]; }

    int left = 0;
    int right = array.size() - 1;
    int mid;
    while (true) {
        if (left == right - 1) {
            break;
        }

        mid = (left + right) / 2;
        int midValue = array[mid];
        if (midValue == array[left] && midValue == array[right]) { return findMinIterately(array); } // 如果左右中都相等, 无法判断中是左边的还是右边的.
        if (midValue >= array[left]) {
            left = mid;
        } else if (midValue < array[right]) {
            right = mid;
        }
    }
    return array[right];
}

void MainWindow::on_pushButton_clicked()
{
    vector<int> array = {1, 2, 3, 4, 5, 6, 123, 123, 322, 443, 5435, 6546, 7457, 8576};
    vector<int> rotated = {322, 443, 5435, 6546, 7457, 8576, 1, 2, 3, 4, 5, 6, 123, 123};
    int value = findMinInRoated(rotated);
    qDebug() << value;
}
