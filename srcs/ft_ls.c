/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 02:30:32 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/14 04:03:06 by abassibe         ###   ########.fr       */
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
	t_data	*data;
	int		i;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		ft_error("MALLOC FAILED");
	data->directory = ft_init_dir();
	data->options_set = ft_strnew(0);
	i = check_options(av, &data->options_set);
	if (!ft_strchr(data->options_set, 'R'))
	{
		data = ft_init_data(av, data, i);
		sort_lst(data);
		ft_print(data);
	}
	else
		recurs(data, av, i);
	ac = 0;
	return (0);
}
