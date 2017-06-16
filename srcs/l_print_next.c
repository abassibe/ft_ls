/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_print_next.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 04:16:46 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/16 06:18:38 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	display_size(t_data *data, t_dirent_list *file)
{
	int		i;
	int		j;

	i = 0;
	j = data->max_size;
	if (S_ISCHR(file->infos->mode) || S_ISBLK(file->infos->mode))
		return ;
	while (j > 0)
	{
		j /= 10;
		i++;
	}
	ft_printf("%*lld ", i + 1, file->infos->size);
}

void	print_name_one_file(struct stat sb, char *name)
{
	char	*buf;

	buf = ft_strnew(50);
	if (S_ISDIR(sb.st_mode))
		ft_printf(" {cyan}%s\n", name);
	else if (S_ISREG(sb.st_mode))
		ft_printf(" %s\n", name);
	else if (S_ISLNK(sb.st_mode))
	{
		ft_printf(" {purple}%s", name);
		readlink(ft_strjoin("./", name), buf, 50);
		ft_printf(" -> %s\n", buf);
	}
	else if (S_ISCHR(sb.st_mode))
		ft_printf(" {yellow}%s\n", name);
	else if (S_ISBLK(sb.st_mode))
		ft_printf(" {green}%s\n", name);
	else if (S_ISFIFO(sb.st_mode))
		ft_printf(" {red}%s\n", name);
	else if (S_ISSOCK(sb.st_mode))
		ft_printf(" {blue}%-s\n", name);
}

void	print_name(t_data *data, t_dirent_list *file)
{
	char	*buf;

	buf = ft_strnew(50);
	if (S_ISDIR(file->infos->mode))
		ft_printf(" {cyan}%-s\n", file->infos->name);
	else if (S_ISREG(file->infos->mode))
		ft_printf(" %-s\n", file->infos->name);
	else if (file->infos->d_type == 10)
	{
		ft_printf(" {purple}%-s", file->infos->name);
		readlink(ft_strjoin(data->path, data->file->infos->name), buf, 50);
		ft_printf(" -> %s\n", buf);
	}
	else if (S_ISCHR(file->infos->mode))
		ft_printf(" {yellow}%-s\n", file->infos->name);
	else if (S_ISBLK(file->infos->mode))
		ft_printf(" {green}%-s\n", file->infos->name);
	else if (S_ISFIFO(file->infos->mode))
		ft_printf(" {red}%-s\n", file->infos->name);
	else if (S_ISSOCK(file->infos->mode))
		ft_printf(" {blue}%-s\n", file->infos->name);
}

void	l_print_next(t_data *data, int *k)
{
	while (data->max_link > 0)
	{
		(*k)++;
		data->max_link /= 10;
	}
	ft_printf("total %d\n", data->total_blk);
}
