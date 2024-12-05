
#include "minitalk.h"

static void	parse_sign(const char **nptr, int *neg)
{
	while (**nptr == ' ' || **nptr == '\t' || **nptr == '\n' || **nptr == '\r'
		|| **nptr == '\v' || **nptr == '\f')
	{
		(*nptr)++;
	}
	if (**nptr == '-' || **nptr == '+')
	{
		if (**nptr == '-')
			*neg = -1;
		(*nptr)++;
	}
}

int	ft_atoi(const char *nptr)
{
	long long	num;
	int			neg;

	num = 0;
	neg = 1;
	parse_sign(&nptr, &neg);
	while (*nptr >= '0' && *nptr <= '9')
	{
		if ((num > (LONG_MAX - (*nptr - '0')) / 10))
		{
			if (neg == 1)
				return ((int)LONG_MAX);
			return ((int)LONG_MIN);
		}
		num = num * 10 + (*nptr - '0');
		nptr++;
	}
	return (num * neg);
}

