/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:26:34 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/04/25 18:27:40 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*free_buffer(char **buffer)
{
	int	i;

	i = 0;
	while (buffer[i] != NULL)
	{
		free(buffer[i]);
		i++;
	}
	free(buffer);
	return (NULL);
}
