/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:28:08 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/05/07 09:58:40 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_init(&data->mutex.print, NULL);
	pthread_mutex_init(&data->mutex.death, NULL);
	pthread_mutex_init(&data->mutex.meal, NULL);
	while (++i < data->nbr_of_philos)
		pthread_mutex_init(&data->mutex.forks[i], NULL);
}

int	init_data(char *argv[], t_data *data, int must_eats)
{

	data->nbr_of_philos = ft_atoi(argv[0]);
	data->mutex.forks = (pthread_mutex_t *)malloc(data->nbr_of_philos
			* sizeof(pthread_mutex_t));
	if (!data->mutex.forks)
		return (EXIT_FAILURE);
	data->time_to_die = ft_atoi(argv[1]);
	data->time_to_eat = ft_atoi(argv[2]);
	data->time_to_sleep = ft_atoi(argv[3]);
	data->death_happened = false;
	data->all_eats = 0;
	if (must_eats)
		data->must_eats = ft_atoi(argv[4]);
	else
		data->must_eats = -1;
	init_mutexes(data);
	return (EXIT_SUCCESS);
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
		(*philo)[i].finished = false;
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
	if (init_data(argv + 1, data, (argc == 6)) || init_philo(philo, data))
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
	if (argc == 6 && ft_atoi(argv[argc - 1]) == 0)
		return (EXIT_SUCCESS);
	if (setup_philos(&data, &philo, argc, argv) || start_simulation(philo))
	{
		cleanup(&philo);
		return (EXIT_FAILURE);
	}
	cleanup(&philo);
	return (EXIT_SUCCESS);
}
