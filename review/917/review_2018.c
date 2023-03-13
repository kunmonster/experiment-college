#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort_str(char **, int);
void upper_input_intoFile();

int main(int argc, char **argv)
{
    // sort_str(argv, argc);
    // for (int i = 0; i < argc; i++)
    // {
    //     printf("%s\n", argv[i]);
    // }
    upper_input_intoFile();
    return 0;
}

// 冒泡
void sort_str(char **str, int c)
{
    int flag = 0;

    for (int i = 0; i < c; i++)
    {
        for (int j = 0; j < c - i - 1; ++j)
        {
            // 前面的更大,不需要再去挨个比较,strcmp可以直接帮助我们完成这项工作
            if (strcmp(str[j], str[j + 1]) > 0)
            {
                // 这里不能直接交换,长度不知道,可能发生问题,但是我们可以直接换指针的指向就行

                char *temp = str[j];
                str[j] = str[j + 1];
                str[j + 1] = temp;
                temp = NULL;
                flag = 1;
            }
        }
        if (flag)
            break;
    }
}

void upper_input_intoFile()
{
    char s[101];
    // 这个函数把换行留在输入里,最后一个会变成\n
    fgets(s, 100, stdin);
    // 处理
    int size = strlen(s);
    for (int i = 0; i < size; i++)
    {
        if (s[i] == '\n')
        {
            s[i] = '\0';
            break;
        }
        // 转成大写

        if ('a' <= s[i] && s[i] <= 'z')
            s[i] -= 32;
    }

    printf("输入的字符串为:%s\n", s);

    // 不能使用相对路径,因为fopen底层要打开文件,必须提供目录信息
    const char *filename = "D:\\vscode\\c++Gitrepo\\review\\917/text.txt";
    FILE *out;

    out = fopen(filename, "w");

    if (out == NULL)
    {
        printf("文件打开失败!");
        exit(-1);
    }
    for (int i = 0; i < strlen(s); i++)
    {
        putc(s[i], out);
    }

    if (fclose(out) != 0)
    {
        fprintf(stderr, "文件关闭失败");
        return;
    }

    FILE *in = fopen(filename, "r");
    char ch;
    while ((ch = fgetc(in)) != EOF)
        printf("%c", ch);
    fclose(in);
}