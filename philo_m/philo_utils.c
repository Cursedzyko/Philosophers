/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 23:49:38 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/22 23:49:41 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	ft_philo_parse(t_cfg *cfg, int ac, char **av)
{
	cfg->n = ft_atoi(av[0]);
	cfg->t_die = ft_atoi(av[1]);
	cfg->t_eat = ft_atoi(av[2]);
	cfg->t_sleep = ft_atoi(av[3]);
	cfg->n_eat = -1;
	if (ac == 5)
		cfg->n_eat = ft_atoi(av[4]);
	if (cfg->n <= 0 || cfg->t_die <= 0 || \
		cfg->t_eat <= 0 || cfg->t_sleep <= 0 || \
		(cfg->n_eat <= 0 && ac == 5))
		return (FALSE);
	return (TRUE);
}

void	ft_philo_threads_join(t_cfg *cfg)
{
	int	i;

	i = 0;
	while (i < cfg->n)
	{
		if (!cfg->philo[i].pthread_error)
			pthread_join(cfg->tid[i], NULL);
		++i;
	}
}

static t_bool	ft_philo_mutex(t_cfg *cfg)
{
	int	i;

	i = 0;
	while (i < cfg->n)
	{
		if (pthread_mutex_init(&cfg->fork[i], NULL) || \
			pthread_mutex_init(&cfg->time[i], NULL) || \
			pthread_mutex_init(&cfg->philo[i].mutex, NULL))
			return (FALSE);
		cfg->philo[i].t_last = cfg->t_start;
		cfg->philo[i].id = i;
		cfg->philo[i].sim = TRUE;
		cfg->philo[i].pthread_error = TRUE;
		++i;
	}
	return (TRUE);
}

t_bool	ft_philo_threads(t_cfg *cfg)
{
	int	i;

	cfg->t_start = ft_gettime();
	if (!ft_philo_mutex(cfg))
		return (FALSE);
	i = 0;
	while (i < cfg->n)
	{
		cfg->philo[i].pthread_error = \
		pthread_create(&cfg->tid[i], NULL, &ft_routine, cfg);
		if (cfg->philo[i].pthread_error)
		{
			ft_routine_end(cfg);
			ft_philo_threads_join(cfg);
			return (FALSE);
		}
		++i;
	}
	return (TRUE);
}
