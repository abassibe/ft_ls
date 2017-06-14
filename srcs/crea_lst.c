/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crea_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 02:45:34 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/14 04:49:52 by abassibe         ###   ########.fr       */
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

void			fill_infos(t_data *data, t_dirent_list *dirent_list)
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
}

void			get_data(t_data *data, t_dirent_list *dirent_list, char *path)
{
	struct stat		getstat;
	struct passwd	*pwuid;
	struct group	*getgrp;

	if (ft_strlen(dirent_list->infos->name) > data->len_max_name)
		data->len_max_name = ft_strlen(dirent_list->infos->name);
	data->nb_file++;
	if ((lstat(ft_strjoin(path, dirent_list->infos->name), &getstat)) == -1)
		ft_error("stat");
	dirent_list->infos->mode = getstat.st_mode;
	dirent_list->infos->nlink = getstat.st_nlink;
	dirent_list->infos->uid = getstat.st_uid;
	dirent_list->infos->gid = getstat.st_gid;
	dirent_list->infos->size = getstat.st_size;
	dirent_list->infos->blocks = getstat.st_blocks;
	dirent_list->infos->mtime = getstat.st_mtime;
	dirent_list->infos->mtime_nsec = getstat.st_mtimespec.tv_nsec;
	dirent_list->infos->rdev = getstat.st_rdev;
	if (!(pwuid = getpwuid(dirent_list->infos->uid)))
		ft_error("getpwuid");
	if (!(getgrp = getgrgid(dirent_list->infos->gid)))
		ft_error("getgrgid");
	dirent_list->infos->pw_name = ft_strdup(pwuid->pw_name);
	dirent_list->infos->gr_name = ft_strdup(getgrp->gr_name);
	fill_infos(data, dirent_list);
}

void			make_list_dirent(t_data *data, char *path)
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

t_data			*ft_init_data(char **av, t_data *data, int i)
{
	struct stat		sb;

	if (av[i])
	{
		if (stat(av[i], &sb) == -1)
			ft_error("stat");
		if (!S_ISDIR(sb.st_mode))
		{
			ft_printf("%s\n", av[i]);
			exit (0);
		}
		if (!(data->directory->rep = opendir(av[i])))
			ft_error("OPEN DIRECTORY FAILED");
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
