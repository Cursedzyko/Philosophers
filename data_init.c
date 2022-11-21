/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 13:50:00 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/21 13:54:56 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_args(int argc, char **argv)
{
	int	i;

	if (argc - 1 == 5 || argc - 1 == 4)
	{
		i = 1;
		while (argv[i] != NULL)
		{
			if (ft_atoi(argv[i]) <= 0)
				ft_error();
			i++;
		}
	}
	else
		ft_error();
}

void	get_as(int ac, char **av, t_data *data)
{
	data->nopi = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (ac - 1 == 5)
		data->nfe = ft_atoi(av[5]);
	else
		data->nfe = -1;
	if (data->t_die < 60 || data->t_eat < 60 || \
	data->t_sleep < 60 || data->nopi > 200)
		ft_error();
	return ;
}

void	init_data(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->nopi);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nopi);
	data->last_eat = malloc(sizeof(long long) * data->nopi);
	if (!data->philos || !data->forks)
		ft_error();
	while (i < data->nopi)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			ft_error();
		data->philos[i].num = i + 1;
		data->philos[i].data = data;
		data->die = 0;
		data->philos[i].last_eat = data->last_eat;
		i++;
	}
	if (pthread_mutex_init(&data->ful, NULL))
		ft_error();
	if (pthread_mutex_init(&data->mu, NULL))
		ft_error();
}
