/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:28:08 by reda              #+#    #+#             */
/*   Updated: 2025/04/23 20:08:57 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
	{
		print_error("Error: Invalid number of arguments, Expected 4 or 5.\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// eating, sleeping, thinking
// nbr_of_philos time_to_die time_to_eat time_to_sleep [nbr_of_times_each_philo_must_eat]
//	5				200			200			200
//	10000					10100-10300	10300-10500
//	10500			10700

/*
	◦timestamp_in_ms X has taken a fork
	◦timestamp_in_ms X is eating
	◦timestamp_in_ms X is sleeping
	◦timestamp_in_ms X is thinking
	◦timestamp_in_ms X died
*/