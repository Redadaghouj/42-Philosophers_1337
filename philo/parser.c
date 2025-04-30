/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:04:45 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/04/25 12:53:37 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	parse_and_validate_args(int argc, char *argv[])
{
	int	i;
	int	num_philos;

	num_philos = ft_atoi(argv[0]);
	if (num_philos < MIN_PHILOS || num_philos > MAX_PHILOS)
		return (EXIT_FAILURE);
	i = 1;
	while (i < argc)
	{
		if (is_digit(argv[i]) || ft_atoi(argv[i]) == -1)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
