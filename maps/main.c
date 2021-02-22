#include <stdio.h>
#include "../libft/libft.h"

int check_name(char *s)
{
	int size;
	char *check;

	size = ft_strlen(s);
	check = ft_strnstr((s + size - 4), ".cub", size);

	return (check == NULL ? 0 : 1);
}



int main (int argc, char *argv[])
{
	if (argc == 2)
	{
		printf("Ok\n");
		printf("%s, %zu\n", argv[1], ft_strlen(argv[1]));
		printf("tem .cub? %d", check_name(argv[1]));
	}
	else
	{
		printf("Error");
		return (1);
	}
	return (0);
}
