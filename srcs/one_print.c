/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 01:31:03 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/17 06:27:57 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	one_print(t_data *data, int i)
{
	while (i < data->nb_file)
	{
		if (((!ft_strchr(data->options_set, 'a')) &&
					(!ft_strchr(data->options_set, 'a'))) &&
				data->file->infos->name[0] == '.')
			data->nul = 0;
		else if (S_ISDIR(data->file->infos->mode))
			ft_printf("{cyan}%-s\n", data->file->infos->name);
		else if (S_ISREG(data->file->infos->mode))
			ft_printf("%-s\n", data->file->infos->name);
		else if (data->file->infos->d_type == 10)
			ft_printf("{purple}%-s\n", data->file->infos->name);
		else if (S_ISCHR(data->file->infos->mode))
			ft_printf("{yellow}%-s\n", data->file->infos->name);
		else if (S_ISBLK(data->file->infos->mode))
			ft_printf("{green}%-s\n", data->file->infos->name);
		else if (S_ISFIFO(data->file->infos->mode))
			ft_printf("{red}%-s\n", data->file->infos->name);
		else if (S_ISSOCK(data->file->infos->mode))
			ft_printf("{blue}%-s\n", data->file->infos->name);
		i++;
		data->file = data->file->next;
	}
}
