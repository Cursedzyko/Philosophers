/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 23:05:36 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/16 00:23:51 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    t_data data;

    check_args(argc, argv);
    get_as(argc, argv, &data);
    printf("%d %d %d %d %d\n", data.nopi, data.t_die, data.t_eat, data.t_sleep, data.nfe);
}

void    ft_error(void)
{
    write(2, "Error\n", 7);
    exit(EXIT_FAILURE);
}

void    check_args(int argc, char **argv)
{
    int i;

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

void    get_as(int ac, char **av, t_data *data)
{
    data->nopi = ft_atoi(av[1]);
    data->t_die = ft_atoi(av[2]);
    data->t_eat = ft_atoi(av[3]);
    data->t_sleep = ft_atoi(av[4]);
    if (ac - 1 == 5)
        data->nfe = ft_atoi(av[5]);
    else
        data->nfe = -1;
    // if (data->t_die < 60 || data->t_eat < 60 || \
    // data->t_sleep < 60 || data->nopi > 200)
    //     ft_error();
    return ;
}