#include <unistd.h>
#include <string.h>

int ft_strcmp(char *s1, char *s2);

int strcmp_tester(char *s1, char *s2)
{
    if (ft_strcmp(s1, s2) == strcmp(s1, s2))
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
    char s1[] = "Test1";
	char s2[] = "OK";
	char s3[] = "Same";
	char s4[] = "Size";
	char s5[] = "Shorter";
	char s6[] = "ThanMyself";
    if (strcmp_tester(s1, s2) && strcmp_tester(s3, s4) && strcmp_tester(s5, s6))
    {
        write(1, "S", 1);
        return (0);
    }
    write(1, "F", 1);
    return (0);
}