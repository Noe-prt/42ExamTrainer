#include <unistd.h>

int *ft_rrange(int start, int end);

int main(void)
{
    int tab1_expected[] = {3, 2, 1};
    int tab2_expected[] = {2, 1, 0, -1};
    int tab3_expected[] = {0};
    int tab4_expected[] = {-3, -2, -1, 0};

    int *tab1 = ft_rrange(1, 3);
    int *tab2 = ft_rrange(-1, 2);
    int *tab3 = ft_rrange(0, 0);
    int *tab4 = ft_rrange(0, -3);

    int success = 1;

    for (int i = 0; i < 3; i++) {
        if (tab1[i] != tab1_expected[i]) success = 0;
    }
    
    for (int i = 0; i < 4; i++) {
        if (tab2[i] != tab2_expected[i]) success = 0;
    }

    if (tab3[0] != tab3_expected[0]) success = 0;

    for (int i = 0; i < 4; i++) {
        if (tab4[i] != tab4_expected[i]) success = 0;
    }

    if (success)
        write(1, "S", 1);
    else
        write(1, "F", 1);

    return 0;
}
