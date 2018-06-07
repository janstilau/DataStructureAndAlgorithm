
//一个二维数组, 行是递增排列, 列是递增排列, 给出一个数, 判断这个数在这个二维数组里面吗.
#include <QDebug>

bool find(int *array, int rowL, int colL, int num)
{
    if (!array || rowL <= 0 || colL <= 0) {
        qDebug() << "invalid input";
        return false;
    }

    int compared;
    int row = 0;
    int col = colL - 1;
    while (row < rowL && col > 0) {
        compared = array[colL * row + col];
        if (compared == num) {
            return true;
        } else if (compared > num) {
            --col;
        } else if (compared < num) {
            ++row;
        }
    }

    return false;
}

int main()
{

}
