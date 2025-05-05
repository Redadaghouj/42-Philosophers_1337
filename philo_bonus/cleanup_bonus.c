/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:05:37 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/05/05 21:56:08 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_close_sem(t_philo *philo)
{
	t_sem	sem;

	sem = philo->data->sem;
	sem_close(sem.forks_sem);
	sem_close(sem.print_sem);
	sem_close(sem.death_sem);
	sem_close(sem.meal_sem);
	sem_close(sem.eats_sem);
}

void	ft_unlink_sem(void)
{
	sem_unlink(FORKS_SEM);
	sem_unlink(PRINT_SEM);
	sem_unlink(DEATH_SEM);
	sem_unlink(MEAL_SEM);
	sem_unlink(EATS_SEM);
}

void	post_eats_sem(t_philo *philo)
{
	int	i;

	i = -1;
	if (philo->data->must_eats != -1)
	{
		while (++i < philo->data->nbr_of_philos)
			sem_post(philo->data->sem.eats_sem);
	}
}

void	cleanup(t_philo **philo)
{
	if (*philo)
	{
		ft_close_sem(*philo);
		if ((*philo)->data->pids)
		{
			free((*philo)->data->pids);
			(*philo)->data->pids = NULL;
		}
		ft_unlink_sem();
		free(*philo);
		*philo = NULL;
	}
}
