/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 23:05:36 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/21 15:10:04 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	ft_freez(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data->mutex);
	while (++i < data->nopi)
	{
		pthread_mutex_destroy(&data->forks[i]);
	}
	return ;
}

void	ft_error(void)
{
	write(2, "Error\n", 7);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_data	data;

	check_args(argc, argv);
	get_as(argc, argv, &data);
	init_data(&data);
	init_philo(&data);
	ft_usleep(200);
	ft_freez(&data);
	free(data.philos->last_eat);
	free(data.philos);
	free(data.forks);
	return (0);
}
