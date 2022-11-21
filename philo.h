/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:56:44 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/21 13:54:35 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct philo
{
	struct s_data	*data;
	int				is_eat;
	int				is_die;
	int				num;
	int				fork;
	long long		*last_eat;
	int				numb;
	pthread_t		ph;
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	ful;
	pthread_mutex_t	mutex;
	pthread_mutex_t	mu;
	int				nopi;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nfe;
	long long		*last_eat;
	long long		current;
	int				die;
}	t_data;

int			ft_atoi(const char *str);
void		ft_error(void);
void		check_args(int argc, char **argv);
void		get_as(int ac, char **av, t_data *data);
void		init_data(t_data *data);
void		*check_death(t_philo *philo);
void		printstatus(t_philo *philo, char *s, int d);
long long	get_time(void);
void		ft_usleep(int time);
void		init_philo(t_data *data);
void		*routine(void *arg);
void		ft_freez(t_data *data);
#endif