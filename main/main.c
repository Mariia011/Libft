#include "/Users/marikhac/Desktop/libft/libft.h"

/*char foo(unsigned int i, char c)
{
	return (c + i);
}*/

int main()
{
	//int n = 2;
	//int fd = 21;
	///ft_putnbr_fd(n, fd);
	char *str = "Hello dh jdjd I love Bananas";
	char *set = "d";
	char *new = ft_strtrim(str, set);
	printf("The initial line is: %s\n Trimmed is: %s\n", str, new);
    return 0;
}
