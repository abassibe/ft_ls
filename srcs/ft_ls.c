/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 02:30:32 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/02 05:14:32 by abassibe         ###   ########.fr       */
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
/*	while (data->file->next)
	{
		if (data->file->child->d_type == DT_DIR)
		{
			//TO DO LIST struct s_directory
		}
		else if (data->file->child->d_type == DT_REG)
			ft_printf("%-10s", data->file->child->d_name);
		data->file = data->file->next;
	}
*/		ft_printf("\n");
	ac = 0;
	return (0);
}
