/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:59:42 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/05/01 13:21:57 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_shared_data(char *argv[], t_data *data, int must_eats)
{
	int	i;

	i = -1;
	data->nbr_of_philos = ft_atoi(argv[0]);
	data->time_to_die = ft_atoi(argv[1]);
	data->time_to_eat = ft_atoi(argv[2]);
	data->time_to_sleep = ft_atoi(argv[3]);
	data->death_happened = false;
	data->all_eats = 0;
	data->forks_sem = sem_open(FORKS_SEM, O_CREAT, 0644, data->nbr_of_philos);
	data->print_sem = sem_open(PRINT_SEM, O_CREAT, 0644, 1);
	data->death_sem = sem_open(DEATH_SEM, O_CREAT, 0644, 1);
	data->meal_sem = sem_open(MEAL_SEM, O_CREAT, 0644, 1);
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
		(*philo)[i].finished = false;
		(*philo)[i].last_meal_time = 0;
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
