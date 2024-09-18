#include <unistd.h>

int	ft_strlen(char *str);

int	main(void)
{
	char *str = "Salut mec";
	if (ft_strlen(str) != 9)
	{
		write(1, "F", 1);
		return (0);
	}
	write(1, "S", 1);
	return (0);
}
