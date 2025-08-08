
//#include <stdio.h>

//int	chck_nb(char *str)
//{
//	int	i;

//	i = 0;
//	while (str && (str[i] == ' ' || str[i] == '\t'))
//		i++;
//	if (str && (str[i] == '-' || str[i] == '+'))
//	{
//		i++;
//		while (str[i] != '\0')
//		{
//			if (!(str[i] >= '0' && str[i] <= '9'))
//				return (-1);
//			i++;
//		}
//		return (0);
//	}
//	else
//	{
//		while (str && str[i] != '\0')
//		{
//			if (!(str[i] >= '0' && str[i] <= '9'))
//				return (-1);
//			i++;
//		}
//		return (0);
//	}
//}


//int main(int argc, char **argv)
//{
//	printf("%d\n\n", chck_nb(argv[1]));
//}