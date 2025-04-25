/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:03:21 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/04/25 21:29:18 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long get_time()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	
}

void	think(t_philo *philo)
{
	printf("timestamp_in_ms X is thinking\n");
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		// think();
		// pick_up_forks();
		// eat();
		// put_down_forks();
		// sleep_philo();
	}
	return (NULL);
}

int	start_simulation(t_philo **philo)
{
	pthread_t	*thread;
	int			philos_nbr;
	int			i;

	philos_nbr = (*philo)->data->nbr_of_philos;
	thread = (pthread_t *) malloc(sizeof(pthread_t) * philos_nbr);
	if (!thread)
		return (EXIT_FAILURE);
	i = 0;
	while (i < philos_nbr)
	{
		if (pthread_create(&thread[i], NULL, routine, philo) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
//	5				200			200			200
/*
	◦timestamp_in_ms X has taken a fork
	◦timestamp_in_ms X is eating
	◦timestamp_in_ms X is sleeping
	◦timestamp_in_ms X is thinking
	◦timestamp_in_ms X died
*/