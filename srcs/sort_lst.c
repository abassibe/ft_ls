/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 02:50:12 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/14 02:20:07 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	sort_rev(t_dirent_list **file)
{
	t_dirent_list	*first;
	t_dirent_list	*rest;

	if (!*file)
		return ;
	first = *file;
	rest = first->next;
	if (!rest)
		return ;
	sort_rev(&rest);
	first->next->next = first;
	first->next = NULL;
	*file = rest;
}

void	sort_lst(t_data *data)
{
	int		i;
	int		c;

	i = 0;
	c = data->nb_file;
	sort_alpha(data, i, c);
	if (ft_strchr(data->options_set, 't'))
		sort_time(data, i, c);
	if (ft_strchr(data->options_set, 'r'))
		sort_rev(&data->file);
}
