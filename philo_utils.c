/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 23:12:19 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/21 14:22:43 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printstatus(t_philo *philo, char *s, int d)
{
	pthread_mutex_lock(&philo->data->mutex);
	printf("%lld %d %s\n", get_time() - philo->data->current, philo->num, s);
	if (d)
		pthread_mutex_unlock(&philo->data->mutex);
}

void	ft_usleep(int time)
{
	long long	t;

	t = get_time();
	while (get_time() - t < time)
		usleep(100);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_atoi(const char *str)
{
	long int	num;
	long int	old_num;
	int			sign;

	num = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		old_num = num;
		num = (num * 10) + (*str - '0');
		if ((old_num < 0 && num > 0) || (old_num > 0 && num < 0))
			return ((sign == 1) * -1);
		str++;
	}
	return (num * sign);
}
