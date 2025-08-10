
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

int count_singl_qoute(char *str)
{
	int i;
	i = 0;
	
	while (str[i] != '\0' && str[i] == '\'')
	{
		i++;
	}
	if (i > 0)
		i--;
	return i;
}

int count_double_qoute(char *str)
{
	int i;
	i = 0;
	
	while (str[i] != '\0' && str[i] == '"')
	{
		i++;
	}
	if (i > 0)
		i--;
	return i;
}

int is_double_qout(char *str)
{
	int i;
	i = 0;
	while (str[i] != '\0' && (str[i] == '"' || str[i] == '\''))
	{
		if (str[i] != '"')
			return (1);
		i++;
	}
	return 0;
}

int is_single_qout(char *str)
{
	int i;
	i = 0;
	while (str[i] != '\0' && (str[i] == '"' || str[i] == '\''))
	{
		if (str[i] != '\'')
			return (1);
		i++;
	}
	return 0;
}

int expand_or_no(char *str)
{
	if (is_single_qout(str) == 0)
	{
		if ((count_singl_qoute(str) % 2) == 1)
			return (0);
		else 
			return (1);
	}
	else if (is_double_qout(str) == 0)
		return 0;
	else if (str[0] == '"')
	{
		return (count_double_qoute(str) % 2);
	}
	else
	{
		if ((count_singl_qoute(str) % 2) == 1)
			return (0);
		else 
			return (1);
	}
}

int main(int argc, char **argv)
{
	char *line;

	while(1)
	{
		line = readline("minishell$ ");
		printf("%d\n\n", expand_or_no(line));
	}
	
}