// 一个数组, 有一个元素是独有一份的, 其他的都是双份的, 找出这个元素. 空间复杂O(1), 时间复杂度 O(N)

#include <QDebug>
#include <set>

using namespace std;

int findAlone(std::vector<int> nums, int length) {
// O(n2)
//    int i = 0;
//    int j = 0;
//    bool found = false;
//    for (; i < length; ++i) {
//        found = false;
//        for (j = 0; j < length; ++j) {
//            if (i != j) {
//                if (array[i] == array[j]) { found = true; }
//            }
//        }
//        if (!found) { return i;}
//    }
//    i = -1;
//    return i;

// method 2
//    std::set<int> container;
//    for (int i = 0; i < nums.size(); ++i) {
//        std::set<int>::iterator it = container.find(nums[i]);
//        if (it != container.end()) {
//            container.erase(it);
//        } else {
//            container.insert(nums[i]);
//        }
//    }

//   std::set<int>::iterator it = container.begin();
//   int value = *it;
//   return value;

// or
    int value = 0;
    for (auto num: nums) {
        value ^= num;
    }

// 对于抑或操作, 和0抑或, 保留原值, 和1抑或, 翻转自己.所以自己和自己抑或, 得到0.
// 为什么抑或操作和顺序无关, 就是因为和0抑或保存原值, 所以无论多少个0, 都和原值一样, 只看1的操作.

    return value;

}

int main()
{
    int array[] = {1, 1, 2, 2, 3, 4, 5,6,7, 4, 5, 6, 7};
    int index = findAlone(array, 13);
    qDebug() << index;

    return 0;
}
