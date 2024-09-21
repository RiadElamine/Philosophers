/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:50:55 by relamine          #+#    #+#             */
/*   Updated: 2024/09/04 12:42:27 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

static int	parse_sign_and_whitespace(char **str)
{
	while ((**str >= 9 && **str <= 13) || **str == 32)
		(*str)++;
	if (**str == '\0')
		return (-1);
	if (**str == '-')
		return (-1);
	if (**str == '+')
	{
		(*str)++;
		if (**str == '+' || **str == '-')
			return (-1);
		if (**str == '\0')
			return (-1);
	}
	return (0);
}

static int	ft_atoi_checker(char *str)
{
	int	res;

	res = 0;
	if (parse_sign_and_whitespace(&str) == -1)
		return (-1);
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		if (res > MAXINT || (res == MAXINT && *str > '7'))
			return (-1);
		res = res * 10 + (*(str++) - '0');
		while ((*str >= 9 && *str <= 13) || *str == 32)
		{
			str++;
			if (*str != '\0' && !((*str >= 9 && *str <= 13) || *str == 32))
				return (-1);
		}
	}
	return (res);
}

int	*ft_parser(int ac, char **av)
{
	int	i;
	int	*args;

	i = 0;
	if (ac < 5 || ac > 6)
		return (printf("Error: Wrong number of arguments\n"), NULL);
	args = malloc(sizeof(int) * (ac - 1));
	if (!args)
	{
		printf("Error: Malloc failed\n");
		return (NULL);
	}
	while (i < (ac - 1))
	{
		args[i] = ft_atoi_checker(av[i + 1]);
		if (args[i] == -1 || args[i] == 0)
		{
			free(args);
			printf("Error: Argument %d\n", i + 1);
			return (NULL);
		}
		i++;
	}
	return (args);
}
