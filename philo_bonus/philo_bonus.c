/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reda <reda@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:59:42 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/05/09 18:39:39 by reda             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_semaphores(t_data *data)
{
	int	philo_nbr;

	philo_nbr = data->nbr_of_philos;
	data->sem.forks_sem = sem_open(FORKS_SEM, O_CREAT, 0644, philo_nbr);
	data->sem.print_sem = sem_open(PRINT_SEM, O_CREAT, 0644, 1);
	data->sem.death_sem = sem_open(DEATH_SEM, O_CREAT, 0644, 1);
	data->sem.meal_sem = sem_open(MEAL_SEM, O_CREAT, 0644, 1);
	data->sem.eats_sem = sem_open(EATS_SEM, O_CREAT, 0644, 0);
	if (data->sem.forks_sem == SEM_FAILED || data->sem.print_sem == SEM_FAILED
		|| data->sem.death_sem == SEM_FAILED || data->sem.meal_sem == SEM_FAILED
		|| data->sem.eats_sem == SEM_FAILED)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_data(char *argv[], t_data *data, int must_eats)
{
	data->nbr_of_philos = ft_atoi(argv[0]);
	data->time_to_die = ft_atoi(argv[1]);
	data->time_to_eat = ft_atoi(argv[2]);
	data->time_to_sleep = ft_atoi(argv[3]);
	data->death_happened = false;
	data->pids = (pid_t *)malloc(sizeof(pid_t) * data->nbr_of_philos);
	if (!data->pids)
		return (EXIT_FAILURE);
	ft_unlink_sem();
	if (init_semaphores(data))
		return (EXIT_FAILURE);
	if (must_eats)
		data->must_eats = ft_atoi(argv[4]);
	else
		data->must_eats = -1;
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
