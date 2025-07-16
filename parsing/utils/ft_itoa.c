#include <minishell.h>

static char	*ft_char(char *s, unsigned int number, long int len)
{
	while (number > 0)
	{
		s[len--] = '0' + (number % 10);
		number = number / 10;
	}
	return (s);
}

static long int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n, garbage **garb)
{
	char				*s;
	long int			len;
	unsigned int		number;
	int					sign;

	if (n == 0)
		return (ft_strdup_gc("0", garb));
	sign = 1;
	len = ft_len(n);
	// Allocation avec garbage collector
	s = (char *)ft_malloc(sizeof(char) * (len + 1), garb);
	if (!s)
		return (NULL);
	s[len--] = '\0';
	if (n < 0)
	{
		sign = -1;
		number = (unsigned int)(-n);
		s[0] = '-';
	}
	else
		number = (unsigned int)n;
	s = ft_char(s, number, len);
	return (s);
}
