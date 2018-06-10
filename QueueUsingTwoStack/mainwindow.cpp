#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStack>
#include <QDebug>

template <typename T> class CQueue {
public:
    void append(const T& node);
    T deleteHead();
private:
    QStack<T> mStack_1;
    QStack<T> mStack_2;
};

template<typename T> void CQueue<T>::append(const T &node) {
    mStack_1.push(node);
}

template<typename T> T CQueue<T>::deleteHead(){
    if (mStack_2.isEmpty()) {
        while (!mStack_1.isEmpty()) {
           mStack_2.push(mStack_1.pop());
        }
    }
    if (mStack_2.isEmpty()) {
        qDebug() << "error, this queue is empty";
    }
    return mStack_2.pop();
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

}
