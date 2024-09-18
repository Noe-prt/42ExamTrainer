#include <unistd.h>
#include <string.h>

char *ft_strdup(char *src);

int strdup_tester(char *str)
{
    strcmp(strdup(str), ft_strdup(str)) == 0 ? 1 : 0;
}

int	main(void)
{
    char *str1 = "Test";
    char *str2 = "484df41hdy1h111fs1fsd15sf15sdf115d15fdgs15gfd4sg1615df156g1515g4erg4561esg156gr15156g15eg15eg15e51e51g1515ge156e156eg156e15156ge516e1551eg51eg15g1551eg15e516eg15e15eg1515e55eg51e15e51g5151eg15eg1515egr515151erg51er51e51e551ee5eg51egr51er51er5er5eg51e5r1e51rg5egr5eg51erg5e1r51e6rg51egr516ee5g15e1g5e1g5e1g51ger51egr51erg55reg5er55er55";
    if (strdup_tester(str1) && strdup_tester(str2))
    {
        write(1, "S", 1);
        return (0);
    }
    write(1, "F", 1);
    return (0);
}