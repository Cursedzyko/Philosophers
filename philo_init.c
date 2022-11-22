/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 13:47:13 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/22 13:43:57 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_philo *philo)
{
	printstatus(philo, "is sleeping", 1);
	ft_usleep(philo->data->t_sleep);
}

void	ft_thinking(t_philo *philo)
{
	printstatus(philo, "is thinking", 1);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->num - 1]);
	printstatus(philo, "has taken a fork", 1);
	pthread_mutex_lock(&philo->data->forks[philo->num % philo->data->nopi]);
	printstatus(philo, "has taken a fork", 1);
	printstatus(philo, "is eating", 1);
	ft_usleep(philo->data->t_eat);
	pthread_mutex_lock(&philo->data->ful);
	philo->last_eat[philo->num - 1] = get_time();
	pthread_mutex_unlock(&philo->data->ful);
	pthread_mutex_unlock(&philo->data->forks[philo->num - 1]);
	pthread_mutex_unlock(&philo->data->forks[philo->num % philo->data->nopi]);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		is_eat;

	is_eat = 0;
	philo = (t_philo *)arg;
	if (philo->num % 2)
		usleep(100);
	while (1)
	{
		ft_eat(philo);
		is_eat += 1;
		if (philo->data->nfe != -1)
		{
			if (is_eat >= philo->data->nfe)
			{
				pthread_mutex_lock(&philo->data->mu);
				philo->data->die = 2;
				pthread_mutex_unlock(&philo->data->mu);
				break ;
			}
		}
		ft_sleep(philo);
		ft_thinking(philo);
	}
	return (NULL);
}

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->current = get_time();
	pthread_mutex_init(&data->mutex, NULL);
	while (i < data->nopi)
	{
		pthread_mutex_lock(&data->ful);
		data->philos[i].last_eat[data->philos->num - 1] = get_time();
		pthread_mutex_unlock(&data->ful);
		pthread_create(&data->philos[i].ph, NULL, &routine, &data->philos[i]);
		i++;
	}
	check_death(data->philos);
	i = 0;
	while (i < data->nopi && (!data->die || data->nfe != -1))
	{
		pthread_join(data->philos[i].ph, NULL);
		i++;
	}
	return ;
}
