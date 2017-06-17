/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 02:50:12 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/17 05:00:23 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			sort_rev(t_dirent_list **file, int i, t_data *data)
{
	t_dirent_list	*current;
	t_dirent_list	*tmp1;
	t_dirent_list	*tmp2;

	current = *file;
	tmp1 = NULL;
	tmp2 = NULL;
	while (i < data->nb_file)
	{
		tmp1 = current;
		current = current->next;
		tmp1->next = tmp2;
		tmp2 = tmp1;
		i++;
	}
	*file = tmp1;
}

void			sort_lst(t_data *data)
{
	int		i;
	int		c;

	i = 0;
	c = data->nb_file;
	if (!ft_strchr(data->options_set, 'f'))
		sort_alpha(data, i, c);
	if (ft_strchr(data->options_set, 't') && !ft_strchr(data->options_set, 'f'))
		sort_time(data, i, c);
	if (ft_strchr(data->options_set, 'r') && !ft_strchr(data->options_set, 'f'))
		sort_rev(&data->file, i, data);
}
