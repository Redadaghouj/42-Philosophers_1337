/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opener.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:28:08 by reda              #+#    #+#             */
/*   Updated: 2025/04/21 22:59:51 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo/philo.h"

int	main(void)
{
	sem_t	*sema;
	int		sem_val;

	sema = sem_open("/my_sem", 0);
	sleep(7);
	if (sema == SEM_FAILED)
	{
		if (errno == ENOENT)
			printf("Error: file does not exist\n");
		else
			perror("Error");
		exit(EXIT_FAILURE);
	}
	printf("Semaphore opened successfully (still exists).\n");
	sem_close(sema);
	sem_unlink("/my_sem");
	return (EXIT_SUCCESS);
}
