/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 02:50:12 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/01 05:32:22 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	sort_alpha(t_data *data)
{
	void		*addr;
	t_data		*tmp;
	int			i;

	if (!(tmp = (t_data *)malloc(sizeof(t_data))))
		ft_error("MALLOC FAILED");
	addr = &data->file;
	i = 0;
	while (i < data->nb_file)
	{
//		usleep(100000);
		printf("%s\n", data->file->child->d_name);
		if (ft_strcmp(NAME, NEXT_NAME) > 0)
		{
			printf("{red}test1\n");
			tmp->file = data->file->next;
			data->file->child = data->file->next->child;
			data->file->next = tmp->file;
		}
		else
		{
			printf("{green}test2\n");
			data->file = data->file->next;
		}
		if (!data->file->next)
		{
			printf("{cyan}test3\n");
			data->file = addr;
			i++;
		}
	}
}

void	sort_lst(t_data *data)
{
	sort_alpha(data);
}
