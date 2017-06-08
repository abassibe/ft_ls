/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_print_next.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 04:16:46 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/08 04:52:32 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_name(t_dirent_list *file)
{
	if (S_ISDIR(file->stat.st_mode))
		ft_printf(" {cyan}%-s\n", file->child->d_name);
	else if (S_ISREG(file->stat.st_mode))
		ft_printf(" %-s\n", file->child->d_name);
	else if (S_ISLNK(file->stat.st_mode))
		ft_printf(" {purple}%-s\n", file->child->d_name);
	else if (S_ISCHR(file->stat.st_mode))
		ft_printf(" {yellow}%-s\n", file->child->d_name);
	else if (S_ISBLK(file->stat.st_mode))
		ft_printf(" {green}%-s\n", file->child->d_name);
	else if (S_ISFIFO(file->stat.st_mode))
		ft_printf(" {red}%-s\n", file->child->d_name);
	else if (S_ISSOCK(file->stat.st_mode))
		ft_printf(" {blue}%-s\n", file->child->d_name);
}

void	l_print_next(t_data *data, int *k)
{
	while (data->max_link > 0)
	{
		(*k)++;
		data->max_link /= 10;
	}
	if (data->chk == 0)
		ft_printf("total %d\n", data->total_blk);
}
