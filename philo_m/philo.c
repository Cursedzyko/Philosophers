/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 23:50:13 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/23 14:06:18 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Function to create strcut for philo mutexs for write data and print*/
t_bool	ft_philo_init(t_cfg *cfg, int ac, char **av)
{
	cfg->tid = NULL;
	cfg->philo = NULL;
	cfg->fork = NULL;
	cfg->time = NULL;
	if (!ft_philo_parse(cfg, ac, av))
		return (FALSE);
	if (!(!pthread_mutex_init(&cfg->mutex, NULL) && \
		!pthread_mutex_init(&cfg->print, NULL) && \
		ft_malloc((void **)&cfg->tid, sizeof(pthread_t) * cfg->n) && \
		ft_malloc((void **)&cfg->philo, sizeof(t_philo) * cfg->n) && \
		ft_malloc((void **)&cfg->fork, sizeof(pthread_mutex_t) * cfg->n) && \
		ft_malloc((void **)&cfg->time, sizeof(pthread_mutex_t) * cfg->n)))
		return (FALSE);
	cfg->curr_eat = 0;
	if (!ft_philo_threads(cfg))
		return (FALSE);
	return (TRUE);
}

void	ft_philo_destroy(t_cfg *cfg)
{
	free(cfg->tid);
	free(cfg->philo);
	free(cfg->fork);
	free(cfg->time);
}

static t_bool	ft_philo_check_dead(t_philo *philo, t_cfg *cfg)
{
	t_bool	ret;

	ret = FALSE;
	pthread_mutex_lock(&cfg->time[philo->id]);
	if (ft_routine_check_time(philo->t_last, cfg->t_die))
	{
		pthread_mutex_lock(&cfg->print);
		printf("%ld %d died\n", ft_gettime() - cfg->t_start, philo->id + 1);
		ft_routine_end(cfg);
		pthread_mutex_unlock(&cfg->print);
		ret = TRUE;
	}
	pthread_mutex_unlock(&cfg->time[philo->id]);
	return (ret);
}

static t_bool	ft_philo_check_full(t_cfg *cfg)
{
	t_bool	ret;

	ret = FALSE;
	pthread_mutex_lock(&cfg->mutex);
	if (cfg->curr_eat == cfg->n)
	{
		pthread_mutex_lock(&cfg->print);
		ft_routine_end(cfg);
		pthread_mutex_unlock(&cfg->print);
		ret = TRUE;
	}
	pthread_mutex_unlock(&cfg->mutex);
	return (ret);
}

void	ft_philo(int ac, char **av)
{
	t_cfg	cfg;
	int		i;
	t_bool	sim;

	if (!ft_philo_init(&cfg, ac, av))
		return (ft_philo_destroy(&cfg));
	sim = TRUE;
	while (sim)
	{
		i = 0;
		if (ft_philo_check_full(&cfg))
			break ;
		while (i < cfg.n && sim)
			sim = !ft_philo_check_dead(&cfg.philo[i++], &cfg);
	}
	i = 0;
	while (i < cfg.n)
		pthread_join(cfg.tid[i++], NULL);
	ft_philo_destroy(&cfg);
}
