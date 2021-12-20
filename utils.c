#include "philo.h"

int	pos_number(char *str)
{
    int	i;

    i = 0;
    while (str[i])
    {
        if (str[i] < 48 || str[i] > 57)
            return (0);
        i++;
    }
    return (1);
}

int	ft_atoi(const char *str)
{
	int		res;

	res = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res);
}