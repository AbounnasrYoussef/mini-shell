
#include "../minishell.h"


int	ft_isalnum(int c)
{
	unsigned char	s;

	s = (unsigned char)c;
	if ((s >= '0' && s <= '9') || (s >= 'a' && s <= 'z')
		|| (s >= 'A' && s <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}