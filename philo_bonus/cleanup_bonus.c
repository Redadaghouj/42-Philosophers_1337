/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:05:37 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/05/02 12:29:43 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_close_sem(t_philo *philo)
{
	sem_close(philo->data->forks_sem);
	sem_close(philo->data->print_sem);
	sem_close(philo->data->death_sem);
	sem_close(philo->data->meal_sem);
}

void	ft_unlink_sem(void)
{
	sem_unlink(FORKS_SEM);
	sem_unlink(PRINT_SEM);
	sem_unlink(DEATH_SEM);
	sem_unlink(MEAL_SEM);
}

// void	cleanup(t_philo **philo)
// {
// 	int	i;

// 	i = 0;
// 	if (*philo)
// 	{
// 		ft_close_sem(*philo);
// 		ft_unlink_sem();
// 		free((*philo)->data->pids);
// 		(*philo)->data->pids = NULL;
// 		free(*philo);
// 		*philo = NULL;
// 	}
// }

void cleanup(t_philo **philo)
{
    if (*philo)
    {
        if ((*philo)->data)
        {
            ft_close_sem(*philo);
            ft_unlink_sem();
            if ((*philo)->data->pids)
                free((*philo)->data->pids);
            free((*philo)->data);
        }
        free(*philo);
        *philo = NULL;
    }
}
