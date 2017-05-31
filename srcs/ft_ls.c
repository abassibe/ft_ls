/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 02:30:32 by abassibe          #+#    #+#             */
/*   Updated: 2017/05/31 06:08:00 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			ft_error(char *error)
{
	ft_printf("%s\n", error);
	exit(0);
}

t_directory		*ft_init_dir(void)
{
	t_directory		*directory;

	if (!(directory = ft_memalloc(sizeof(t_directory))))
		ft_error("MALLOC FAILED");
	directory->rep = NULL;
	directory->next = NULL;
	return (directory);
}

int				check_options(char **av, char **options_set)
{
	int				i;
	char			*options;

	i = 0;
	options = ft_strdup("-l-R-a-r-t");
	while (av[++i])
	{
		if (!(ft_strstr(options, av[i])))
			return (i);
		*options_set = ft_strjoin(*options_set, av[i]);
	}
	return (i);
}

t_dirent_list	*add_list(void)
{
	t_dirent_list	*to_add;

	if (!(to_add = ft_memalloc(sizeof(t_dirent_list))))
		ft_error("MALLOC FAILED");
	to_add->child = NULL;
	to_add->next = NULL;
	return (to_add);
}

void			make_list_dirent(t_data *data)
{
	t_dirent_list	*dirent_list;

	if (!(dirent_list = ft_memalloc(sizeof(t_dirent_list))))
		ft_error("MALLOC FAILED");
	data->file = dirent_list;
	while ((dirent_list->child = readdir(data->directory->rep)))
	{
		dirent_list->next = add_list();
		dirent_list = dirent_list->next;
	}
}

t_data			*ft_init_data(char **av)
{
	t_data			*data;
	int				i;

	if (!(data = ft_memalloc(sizeof(data))))
		ft_error("MALLOC FAILED");
	data->directory = ft_init_dir();
	data->options_set = ft_strnew(0);;
	i = check_options(av, &data->options_set);
	if (av[i])
	{
		if (!(data->D_DIR = opendir(av[i])))
			ft_error("OPEN DIRECTORY FAILED");
	}
	else
		if (!(data->D_DIR = opendir("./")))
			ft_error("OPEN DIRECTORY FAILED");
	make_list_dirent(data);
	return (data);
}

int				main(int ac, char **av)
{
	t_data			*data;

	data = ft_init_data(av);
	while (data->file->next)
	{
		if (data->file->child->d_type == DT_DIR)
		{
			//TO DO LIST struct s_directory
		}
		else if (data->file->child->d_type == DT_REG)
			ft_printf("%-10s", data->file->child->d_name);
		data->file = data->file->next;
	}
		ft_printf("\n");
	ac = 0;
	return (0);
}
