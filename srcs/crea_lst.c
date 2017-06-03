/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crea_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 02:45:34 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/03 05:25:08 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_directory		*ft_init_dir(void)
{
	t_directory		*directory;

	if (!(directory = (t_directory *)malloc(sizeof(t_directory))))
		ft_error("MALLOC FAILED");
	D_DIR = NULL;
	D_NEXT = NULL;
	return (directory);
}

t_dirent_list	*add_list(void)
{
	t_dirent_list	*to_add;

	if (!(to_add = (t_dirent_list *)malloc(sizeof(t_dirent_list))))
		ft_error("MALLOC FAILED");
	to_add->child = NULL;
	to_add->next = NULL;
	return (to_add);
}

void			make_list_dirent(t_data *data, char *path)
{
	t_dirent_list	*dirent_list;

	if (!(dirent_list = (t_dirent_list *)malloc(sizeof(t_dirent_list))))
		ft_error("MALLOC FAILED");
	data->file = dirent_list;
	data->nb_file = 0;
	data->len_max_name = 0;
	while ((dirent_list->child = readdir(data->directory->rep)))
	{
		if (ft_strlen(dirent_list->child->d_name) > data->len_max_name)
			data->len_max_name = ft_strlen(dirent_list->child->d_name);
		data->nb_file++;
		if ((stat(ft_strjoin(path, dirent_list->child->d_name), &dirent_list->stat)) == -1)
			ft_error("stat");
		dirent_list->next = add_list();
		dirent_list = dirent_list->next;
	}
}

t_data			*ft_init_data(char **av)
{
	t_data			*data;
	int				i;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		ft_error("MALLOC FAILED");
	data->directory = ft_init_dir();
	data->options_set = ft_strnew(0);
	i = check_options(av, &data->options_set);
	if (av[i])
	{
		if (!(data->D_DIR = opendir(av[i])))
			ft_error("OPEN DIRECTORY FAILED");
		make_list_dirent(data, ft_strjoin(av[i], "/"));
	}
	else
	{
		if (!(data->D_DIR = opendir("./")))
			ft_error("OPEN DIRECTORY FAILED");
		make_list_dirent(data, "./");
	}
	return (data);
}
