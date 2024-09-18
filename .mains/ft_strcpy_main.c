#include <unistd.h>

char* ft_strcpy(char *dest, char *src);

int	main(void)
{
	int	i;

	i = 0;
	char	dest[15];
	char	src[] = "Hello";

	ft_strcpy(dest, src);
	while (src[i])
	{
		if (dest[i] != src[i])
		{
			write(1, "F", 1);
			return (0);
		}
		i++;
	}
	write(1, "S", 1);
	return (0);
}
