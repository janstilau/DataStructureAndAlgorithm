#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <QDebug>

QVector<int> array = {0, 123, 123, 32, 90, 998, -123, 1233, 687, 489};

void bubbleSort(QVector<int> &array) {
    // 注意排序的次数是 length - 1次
    int temp;
    for (int i = 0; i < array.length() - 1; ++i) {
        for (int j = 0; j < array.length() - 1 - i; ++j) {
            if (array[j] < array[j + 1]) {
                temp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = temp;
            }
        }
    }
}

void selectSort(QVector<int> &array) {
    int temp;
    for (int i = 0; i < array.length(); ++i) {
        int num = array[i];
        int index = -1;
        for (int j = i + 1; j < array.length(); ++j) {
            if (array[j] > num) {
                index = j;
                num = array[j];
            }
        }
        if (index != -1) {
            temp = array[i];
            array[i] = array[index];
            array[index] = temp;
        }
    }
}

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void quickSort(QVector<int> &array, int left, int right) {
    if (!array.size()) { return; }
    if (right <= left) { return; }

    int i = left + 1;
    int j = right;
    int compared = array[left];
    while (i < j) {
        while(array[j] > compared && i < j) {
            --j;
        }
        while(array[i] < compared && i < j) {
            ++i;
        }
        if (i != j) {
            swap(array[i], array[j]);
        }
    }

    if (i == j) {
        swap(array[i], array[left]);
    }
    quickSort(array, left, i - 1);
    quickSort(array, i + 1, right);

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
    quickSort(array, 0, array.size() - 1);
    qDebug() << "end";
}
