/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:21:27 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/22 13:39:26 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->ful);
		if (get_time() - philo->last_eat[philo->num - 1] \
		>= philo->data->t_die)
		{
			pthread_mutex_unlock(&philo->data->ful);
			pthread_mutex_lock(&philo->data->mu);
			if (philo->data->die != 2)
				printstatus(philo, "died", 0);
			philo->data->die = 1;
			pthread_mutex_unlock(&philo->data->mu);
			break ;
		}
		pthread_mutex_unlock(&philo->data->ful);
	}
	return (NULL);
}
