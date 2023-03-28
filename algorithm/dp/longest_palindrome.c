/***
 * 最长回文子串
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int is_palindrome(const char *, const char *);

char *longestPalindrome(char *);

int main()
{
    char arr[] = "ibvjkmpyzsifuxcabqqpahjdeuzaybqsrsmbfplxycsafogotliyvhxjtkrbzqxlyfwujzhkdafhebvsdhkkdbhlhmaoxmbkqiwiusngkbdhlvxdyvnjrzvxmukvdfobzlmvnbnilnsyrgoygfdzjlymhprcpxsnxpcafctikxxybcusgjwmfklkffehbvlhvxfiddznwumxosomfbgxoruoqrhezgsgidgcfzbtdftjxeahriirqgxbhicoxavquhbkaomrroghdnfkknyigsluqebaqrtcwgmlnvmxoagisdmsokeznjsnwpxygjjptvyjjkbmkxvlivinmpnpxgmmorkasebngirckqcawgevljplkkgextudqaodwqmfljljhrujoerycoojwwgtklypicgkyaboqjfivbeqdlonxeidgxsyzugkntoevwfuxovazcyayvwbcqswzhytlmtmrtwpikgacnpkbwgfmpavzyjoxughwhvlsxsgttbcyrlkaarngeoaldsdtjncivhcfsaohmdhgbwkuemcembmlwbwquxfaiukoqvzmgoeppieztdacvwngbkcxknbytvztodbfnjhbtwpjlzuajnlzfmmujhcggpdcwdquutdiubgcvnxvgspmfumeqrofewynizvynavjzkbpkuxxvkjujectdyfwygnfsukvzflcuxxzvxzravzznpxttduajhbsyiywpqunnarabcroljwcbdydagachbobkcvudkoddldaucwruobfylfhyvjuynjrosxczgjwudpxaqwnboxgxybnngxxhibesiaxkicinikzzmonftqkcudlzfzutplbycejmkpxcygsafzkgudy";
    char *res = longestPalindrome(arr);
    printf("%s", res);
    return 0;
}

int is_palindrome(const char *start, const char *end)
{
    if (start == end)
        return 1;
    while (start <= end)
    {
        if (*(start) != *(end))
            return 0;
        ++start;
        --end;
    }
    return 1;
}

char *longestPalindrome(char *s)
{
    // 思路错误
    int len = strlen(s);
    if (len == 1)
        return s;
    int **dp = (int **)malloc(sizeof(int *) * len);
    int i = 0;
    int d = 0;
    int begin = 0;
    int maxLen = 1;
    for (i = 0; i < len; ++i)
    {
        dp[i] = (int *)malloc(sizeof(int) * len);
        // 1表示是回文串,0表示不是
        memset(dp[i], 0, sizeof(int) * len);
        dp[i][i] = 1;
    }

    for (d = 1; d < len; ++d)
    {
        for (i = 0; i < len - d; ++i)
        {
            int j = i + d;
            if (j >= len)
                break;
            if (s[i] != s[j])
                dp[i][j] = 0;
            else
            {
                if (j - i < 3)
                    dp[i][j] = 1;
                else
                {
                    dp[i][j] = dp[i + 1][j - 1];
                }
            }
            if (dp[i][j] == 1 && (j - i + 1) > maxLen)
            {
                begin = i;
                maxLen = j - i + 1;
            }
        }
    }
    *(s + begin + maxLen) = '\0';
    return s + begin;
}
