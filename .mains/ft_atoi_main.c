#include <unistd.h>
#include <stdlib.h>

int ft_atoi(const char *str);

int atoi_tester(char *str)
{
    int atoi_false = ft_atoi(str);
    int atoi_true = atoi(str);
    if (atoi_false == atoi_true)
    {
        return (1);
    }
    else
    {
        return (0);
    }
}

int main(void)
{
    char *str1 = "#";
    int test1 = atoi_tester(str1);
    char *str2 = "-1231";
    int test2 = atoi_tester(str2);
    char *str3 = "+465737858abvc35456";
    int test3 = atoi_tester(str3);
    char *str4 = "abcbdh++++465737858abvc35456";
    int test4 = atoi_tester(str4);
    char *str5 = "-+-465848abc74";
    int test5 = atoi_tester(str5);
    char *str6 = "           +465848abc74";
    int test6 = atoi_tester(str6);
    if (test1 && test2 && test3 && test4 && test5 && test6)
    {
        write(1, "S", 1);
        return (0);
    }
    write(1, "F", 1);
    return (0);
}

