/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:42:01 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/04/28 20:59:37 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	int		res;
	int		prev_res;	

	res = 0;
	i = 0;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		prev_res = res;
		res = res * 10 + (nptr[i] - '0');
		if (prev_res > res)
			return (-1);
		i++;
	}
	return (res);
}
