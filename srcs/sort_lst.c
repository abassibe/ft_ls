/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 02:50:12 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/02 06:24:29 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	sort_alpha(t_data *data, int i, int c)
{
	t_dirent_list	*addr;
	t_dirent_list	*tmp;
	struct stat		stat_tmp;

	if (!(tmp = (t_dirent_list *)malloc(sizeof(t_dirent_list))))
		ft_error("MALLOC FAILED");
	addr = data->file;
	while (i < data->nb_file)
	{
		if (c == 0)
		{
			data->file = addr;
			i++;
			c = data->nb_file - i;
		}
		if (c > 1 && (ft_strcmp(NAME, NEXT_NAME) > 0))
		{
			stat_tmp = data->file->stat;
			data->file->stat = data->file->next->stat;
			data->file->next->stat = stat_tmp;
			tmp->child = data->file->child;
			data->file->child = data->file->next->child;
			data->file->next->child = tmp->child;
		}
		else
			data->file = data->file->next;
		c--;
	}
	data->file = addr;
}

void	sort_rev(t_dirent_list *file, int i)
{
	t_dirent_list	*first;
	t_dirent_list	*rest;

	if (!file)
		return ;
	first = file;
	rest = first->next;
	if (!rest)
		return ;
	sort_rev(rest, i);
	i++;
	first->next->next = first;
	first->next = NULL;
	if (i == 1)
		file = rest;
}

t_dirent_list	*save_last_link(t_data *data, int i, int c)
{
	t_dirent_list	*addr;
	t_dirent_list	*addr2;

	addr = data->file;
	while (i < c - 1)
	{
		data->file = data->file->next;
		i++;
	}
	addr2 = data->file;
	data->file = addr;
	return (addr2);
}

void	sort_lst(t_data *data)
{
	int		i;
	int		c;
	t_dirent_list	*addr;

	i = 0;
	c = data->nb_file;
	sort_alpha(data, i, c);
	if (ft_strchr(data->options_set, 'r'))
	{
		addr = save_last_link(data, i, c);
		sort_rev(data->file, i);
		data->file = addr;
	}
	printf("%s\n", data->file->child->d_name);
	printf("%s\n", ctime(&data->file->stat.st_mtime));
	printf("%lld\n", data->file->stat.st_size);
	while (data->file)
	{
		ft_printf("%-*s", data->len_max_name + 1, data->file->child->d_name);
		data->file = data->file->next;
	}
}
