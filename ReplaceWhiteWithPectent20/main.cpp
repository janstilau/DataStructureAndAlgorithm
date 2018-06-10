
// 把一个字符串的空格替换成为%20. 保证字符串有足够的剩余空间.
#include <QDebug>
void replace(char *text, int length) {
    if (!text || length <= 0) { return; }
    int replacedLength = 0;
    for (int i = 0; i < length; i++) {
        if (text[i] == ' ') {
            replacedLength += 3;
        } else {
            ++replacedLength;
        }
    }

    text[replacedLength + 1] = '\0';

    int j = replacedLength - 1;
    for (int i = length - 1; i > 0; --i) {
        if (text[i] == ' ') {
            text[j--] = '0';
            text[j--] = '2';
            text[j--] = '/';
        } else {
            text[j--] = text[i];
        }
    }
}

int main()
{   const int length = 1000000000;
    char text[length] = "hell owrld hehehe ";
    replace(text, strlen(text));
}
