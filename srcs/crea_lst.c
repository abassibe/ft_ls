/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crea_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 02:45:34 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/21 01:48:12 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	fill_infos(t_data *data, t_dirent_list *dirent_list)
{
	if (dirent_list->infos->nlink > data->max_link)
		data->max_link = dirent_list->infos->nlink;
	if (data->max_size < dirent_list->infos->size)
		data->max_size = dirent_list->infos->size;
	if (data->max_name < (int)ft_strlen(dirent_list->infos->pw_name))
		data->max_name = (int)ft_strlen(dirent_list->infos->pw_name);
	if (data->max_grp < (int)ft_strlen(dirent_list->infos->gr_name))
		data->max_grp = (int)ft_strlen(dirent_list->infos->gr_name);
	data->total_blk += dirent_list->infos->blocks;
	if (dirent_list->infos->name[0] == '.' &&
			!ft_strchr(data->options_set, 'a'))
		data->total_blk -= dirent_list->infos->blocks;
}

void	get_stat(t_dirent_list *dirent_list, struct stat getstat)
{
	dirent_list->infos->mode = getstat.st_mode;
	dirent_list->infos->nlink = getstat.st_nlink;
	dirent_list->infos->uid = getstat.st_uid;
	dirent_list->infos->gid = getstat.st_gid;
	dirent_list->infos->size = getstat.st_size;
	dirent_list->infos->blocks = getstat.st_blocks;
	dirent_list->infos->mtime = getstat.st_mtime;
	dirent_list->infos->mtime_nsec = getstat.st_mtimespec.tv_nsec;
	dirent_list->infos->rdev = getstat.st_rdev;
	dirent_list->infos->atime = getstat.st_atime;
}

void	get_data(t_data *data, t_dirent_list *dirent_list, char *path)
{
	struct stat		getstat;
	struct passwd	*pwuid;
	struct group	*getgrp;

	if (ft_strlen(dirent_list->infos->name) > data->len_max_name)
		data->len_max_name = ft_strlen(dirent_list->infos->name);
	data->nb_file++;
	if ((lstat(ft_strjoin(path, dirent_list->infos->name), &getstat)) == -1)
		get_stat_rst(dirent_list);
	else
		get_stat(dirent_list, getstat);
	if (!(pwuid = getpwuid(dirent_list->infos->uid)))
	{
		dirent_list->infos->pw_name = ft_strnew(0);
		return ;
	}
	if (!(getgrp = getgrgid(dirent_list->infos->gid)))
	{
		dirent_list->infos->gr_name = ft_strnew(0);
		return ;
	}
	dirent_list->infos->pw_name = ft_strdup(pwuid->pw_name);
	dirent_list->infos->gr_name = ft_strdup(getgrp->gr_name);
	fill_infos(data, dirent_list);
}

void	make_list_dirent(t_data *data, char *path)
{
	t_dirent_list	*dirent_list;
	struct dirent	*child;

	dirent_list = add_list();
	data->file = dirent_list;
	data->nb_file = 0;
	data->max_link = 0;
	data->len_max_name = 0;
	data->max_size = 0;
	data->total_blk = 0;
	data->max_name = 0;
	data->max_grp = 0;
	data->path = ft_strdup(path);
	while ((child = readdir(data->directory->rep)))
	{
		dirent_list->infos->d_type = child->d_type;
		dirent_list->infos->name = ft_strdup(child->d_name);
		get_data(data, dirent_list, path);
		if (S_ISCHR(dirent_list->infos->mode) ||
				S_ISBLK(dirent_list->infos->mode))
			data->chk = 1;
		dirent_list->next = add_list();
		dirent_list = dirent_list->next;
	}
	dirent_list = NULL;
}

t_data	*ft_init_data(char **av, t_data *data, int i)
{
	struct stat		sb;

	if (av[i])
	{
		if (stat(av[i], &sb) == -1)
			ft_error("stat4");
		if (!S_ISDIR(sb.st_mode))
		{
			print_one_file(sb, av[i]);
			exit(0);
		}
		if (!(data->directory->rep = opendir(av[i])))
			ft_error("OPEN DIRECTORY FAILED");
		if (av[i][0] == '/' && av[i][1] == 0)
			make_list_dirent(data, av[i]);
		else
			make_list_dirent(data, ft_strjoin(av[i], "/"));
	}
	else
	{
		if (!(data->directory->rep = opendir("./")))
			ft_error("OPEN DIRECTORY FAILED");
		make_list_dirent(data, "./");
	}
	return (data);
}
