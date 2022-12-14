/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 23:49:53 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/23 14:35:38 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	ft_routine_take_fork(t_philo *philo, t_cfg *cfg)
{
	if (philo->f1 == philo->f2)
		return (FALSE);
	pthread_mutex_lock(&cfg->fork[philo->f1]);
	ft_routine_status(cfg, philo);
	pthread_mutex_lock(&cfg->fork[philo->f2]);
	ft_routine_status(cfg, philo);
	philo->state = PH_EATING;
	return (TRUE);
}

void	ft_routine_eating(t_philo *philo, t_cfg *cfg)
{
	pthread_mutex_lock(&cfg->time[philo->id]);
	philo->t_last = ft_routine_status(cfg, philo);
	pthread_mutex_unlock(&cfg->time[philo->id]);
	ft_routine_wait(philo, philo->t_last, cfg->t_eat);
	philo->state = PH_SLEEPING;
	pthread_mutex_unlock(&cfg->fork[philo->f2]);
	pthread_mutex_unlock(&cfg->fork[philo->f1]);
	if (++philo->n_eat == cfg->n_eat)
	{
		pthread_mutex_lock(&cfg->mutex);
		++cfg->curr_eat;
		pthread_mutex_unlock(&cfg->mutex);
	}
}

void	ft_routine_sleeping(t_philo *philo, t_cfg *cfg)
{
	long	t_sleep_start;

	t_sleep_start = ft_routine_status(cfg, philo);
	ft_routine_wait(philo, t_sleep_start, cfg->t_sleep);
	philo->state = PH_THINKING;
}

void	ft_routine_thinking(t_philo *philo, t_cfg *cfg)
{
	ft_routine_status(cfg, philo);
	philo->state = PH_TAKES_FORK;
	usleep(1);
}

void	*ft_routine(void *data)
{
	t_cfg	*cfg;
	t_philo	*philo;
	t_bool	sim;

	cfg = (t_cfg *)data;
	philo = ft_routine_init(cfg);
	if (philo->id % 2 == 1)
		ft_routine_wait(philo, philo->t_last, cfg->t_sleep);
	sim = TRUE;
	while (sim)
	{
		pthread_mutex_lock(&philo->mutex);
		sim = philo->sim;
		pthread_mutex_unlock(&philo->mutex);
		if (!ft_routine_take_fork(philo, cfg))
			continue ;
		ft_routine_eating(philo, cfg);
		ft_routine_sleeping(philo, cfg);
		ft_routine_thinking(philo, cfg);
	}
	return (NULL);
}
