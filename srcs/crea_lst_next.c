/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crea_lst_next.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 06:05:47 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/16 06:06:24 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_directory		*ft_init_dir(void)
{
	t_directory		*directory;

	if (!(directory = (t_directory *)malloc(sizeof(t_directory))))
		ft_error("MALLOC FAILED");
	if (!(directory->rep = (DIR *)malloc(sizeof(DIR))))
		ft_error("MALLOC FAILED");
	directory->rep = NULL;
	directory->next = NULL;
	return (directory);
}

t_dirent_list	*add_list(void)
{
	t_dirent_list	*to_add;

	if (!(to_add = (t_dirent_list *)malloc(sizeof(t_dirent_list))))
		ft_error("MALLOC FAILED");
	if (!(to_add->infos = (t_info *)malloc(sizeof(t_info))))
		ft_error("MALLOC FAILED");
	to_add->next = NULL;
	return (to_add);
}
