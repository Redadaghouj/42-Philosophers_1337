/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:28:08 by reda              #+#    #+#             */
/*   Updated: 2025/04/28 18:04:06 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_philo **philo)
{
	int	i;

	i = 0;
	if (*philo)
	{
		while (i < (*philo)->data->nbr_of_philos)
		{
			pthread_mutex_destroy(&(*philo)->data->forks[i]);
			i++;
		}
		pthread_mutex_destroy(&(*philo)->data->print);
		pthread_mutex_destroy(&(*philo)->data->death);
		pthread_mutex_destroy(&(*philo)->data->layer);
		free((*philo)->data->forks);
		free(*philo);
		philo = NULL;
	}
}

void	init_shared_data(char *argv[], t_data *data, int must_eats)
{
	int	i;

	i = 0;
	data->nbr_of_philos = ft_atoi(argv[0]);
	data->forks = (pthread_mutex_t *)malloc(data->nbr_of_philos
			* sizeof(pthread_mutex_t));
	data->time_to_die = ft_atoi(argv[1]);
	data->time_to_eat = ft_atoi(argv[2]) * MS_TO_US;
	data->time_to_sleep = ft_atoi(argv[3]) * MS_TO_US;
	data->death_happened = false;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->layer, NULL);
	while (i < data->nbr_of_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	if (must_eats)
		data->must_eats = ft_atoi(argv[4]);
	else
		data->must_eats = -1;
}

int	init_philo(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	*philo = (t_philo *) malloc(sizeof(t_philo) * data->nbr_of_philos);
	if (!(*philo))
		return (EXIT_FAILURE);
	while (i < data->nbr_of_philos)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].data = data;
		(*philo)[i].meals_count = 0;
		(*philo)[i].last_meal_time = 0;
		(*philo)[i].left_fork = i;
		(*philo)[i].right_fork = (i + 1) % data->nbr_of_philos;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	setup_philos(t_data *data, t_philo **philo, int argc, char *argv[])
{
	if (parse_and_validate_args(argc - 1, argv + 1))
	{
		print_error("Error: At least one argument is not valid.\n");
		return (EXIT_FAILURE);
	}
	init_shared_data(argv + 1, data, (argc == 6));
	if (init_philo(philo, data))
	{
		print_error("Error: Malloc failed.\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philo;

	if (argc != 5 && argc != 6)
	{
		print_error("Error: Invalid number of arguments, Expected 5 or 6.\n");
		return (EXIT_FAILURE);
	}
	if (setup_philos(&data, &philo, argc, argv) || start_simulation(philo))
	{
		cleanup(&philo);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
