#include "/Users/marikhac/Desktop/libft/libft.h"

char foo(unsigned int i, char c)
{
	return (c + i);
}

int main()
{
	char *str = ft_strmapi("1234", foo);
	printf("%s\n", str);
	free(str);
	return 0;
}