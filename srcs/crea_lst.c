/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crea_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 02:45:34 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/08 06:06:37 by abassibe         ###   ########.fr       */
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
	to_add->pwuid = NULL;
	to_add->getgrp = NULL;
	return (to_add);
}

void			get_data(t_data *data, t_dirent_list *dirent_list, char *path)
{
	if (ft_strlen(dirent_list->child->d_name) > data->len_max_name)
		data->len_max_name = ft_strlen(dirent_list->child->d_name);
	data->nb_file++;
	if ((stat(ft_strjoin(path, dirent_list->child->d_name), &dirent_list->stat)) == -1)
		ft_error("stat");
	if (dirent_list->stat.st_nlink > data->max_link)
		data->max_link = dirent_list->stat.st_nlink;
	if (!(dirent_list->pwuid = getpwuid(dirent_list->stat.st_uid)))
		ft_error("getpwuid");
	if (!(dirent_list->getgrp = getgrgid(dirent_list->stat.st_gid)))
		ft_error("getgrgid");
	if (data->max_size < dirent_list->stat.st_size)
		data->max_size = dirent_list->stat.st_size;
	if (data->max_name < (int)ft_strlen(dirent_list->pwuid->pw_name))
		data->max_name = (int)ft_strlen(dirent_list->pwuid->pw_name);
	if (data->max_grp < (int)ft_strlen(dirent_list->getgrp->gr_name))
		data->max_grp = (int)ft_strlen(dirent_list->getgrp->gr_name);
	data->total_blk += dirent_list->stat.st_blocks;
//	printf("%s\n", dirent_list->child->d_name);
}

void			make_list_dirent(t_data *data, char *path)
{
	t_dirent_list	*dirent_list;
//	int		i = 0;

	dirent_list = add_list();
	data->file = dirent_list;
	data->nb_file = 0;
	data->max_link = 0;
	data->len_max_name = 0;
	data->max_size = 0;
	data->total_blk = 0;
	data->max_name = 0;
	data->max_grp = 0;
	while ((dirent_list->child = readdir(data->directory->rep)))
	{
		get_data(data, dirent_list, path);
		dirent_list->next = add_list();
		dirent_list = dirent_list->next;
	}
/*	while (i < data->nb_file)
	{
		printf("%s\n", data->file->child->d_name);
		data->file = data->file->next;
		i++;
	}*/
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
		data->chk = 1;
	}
	else
	{
		if (!(data->D_DIR = opendir("./")))
			ft_error("OPEN DIRECTORY FAILED");
		make_list_dirent(data, "./");
		data->chk = 0;
	}
	return (data);
}
