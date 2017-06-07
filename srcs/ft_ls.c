/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 02:30:32 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/07 03:03:56 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			ft_error(char *error)
{
	perror(error);
	exit(0);
}

int				main(int ac, char **av)
{
	t_data			*data;

	data = ft_init_data(av);
	sort_lst(data);
	ft_print(data);
	ac = 0;
	return (0);
}
