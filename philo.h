/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:56:44 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/15 23:37:31 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
    int nopi;
    int t_die;
    int t_eat;
    int t_sleep;
    int nfe;
    
}t_data;

int	ft_atoi(const char *str);
void    ft_error(void);
void    check_args(int argc, char **argv);
void    get_as(int ac, char **av, t_data *data);

#endif