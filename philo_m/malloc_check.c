/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyunusov <zyunusov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 23:30:08 by zyunusov          #+#    #+#             */
/*   Updated: 2022/11/22 23:30:18 by zyunusov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	ft_malloc(void **ptr, size_t n)
{
	*ptr = malloc(n);
	if (*ptr)
		return (TRUE);
	return (FALSE);
}
