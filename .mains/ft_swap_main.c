#include <unistd.h>

void    ft_swap(int *a, int *b);

int main(void)
{
    int a = 5;
    int b = 10;
    ft_swap(&a, &b);
    if (a == 10 && b == 5)
    {
        write(1, "S", 1);
        return (0);
    }
    write(1, "F", 1);
    return (0);
}