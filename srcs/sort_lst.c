/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 02:50:12 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/16 05:38:54 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_dirent_list	*creat_elem(void)
{
	t_dirent_list	*new;

	if (!(new = malloc(sizeof(t_dirent_list))))
		ft_error("Malloc");
	return (new);
}

t_dirent_list	*sort_rev(t_dirent_list *file, int i, t_data *data)
{
	t_dirent_list	*new;
	t_dirent_list	*suivant;

	while (i < data->nb_file)
	{
		suivant = creat_elem();
		suivant = file->next;
		file->next = new;
		new = file;
		file = suivant;
		i++;
	}
	return (new);
}

void			sort_lst(t_data *data)
{
	int		i;
	int		c;

	i = 0;
	c = data->nb_file;
	sort_alpha(data, i, c);
	if (ft_strchr(data->options_set, 't'))
		sort_time(data, i, c);
	if (ft_strchr(data->options_set, 'r'))
		data->file = sort_rev(data->file, i, data);
}
