/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:05:37 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/05/05 16:28:34 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_close_sem(t_philo *philo)
{
	sem_close(philo->data->forks_sem);
	sem_close(philo->data->print_sem);
	sem_close(philo->data->death_sem);
	sem_close(philo->data->meal_sem);
	sem_close(philo->data->eats_sem);
}

void	ft_unlink_sem(void)
{
	sem_unlink(FORKS_SEM);
	sem_unlink(PRINT_SEM);
	sem_unlink(DEATH_SEM);
	sem_unlink(MEAL_SEM);
	sem_unlink(EATS_SEM);
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
