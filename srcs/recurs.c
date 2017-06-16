/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 02:48:45 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/16 06:32:29 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_recurs	*crea_lst_rec(void)
{
	t_recurs	*lst;

	if (!(lst = malloc(sizeof(t_recurs))))
		ft_error("Malloc");
	lst->next = NULL;
	lst->dir = NULL;
	lst->rep = NULL;
	lst->path = NULL;
	return (lst);
}

void		search_next(t_data *data, t_recurs *lst)
{
	char	**str;

	str = malloc(sizeof(char **) * 1);
	str[0] = ft_strjoin(lst->path, "/");
	str[0] = ft_strjoin(str[0], lst->dir->d_name);
	lst->next = crea_lst_rec();
	ft_printf("\n%s:\n", str[0]);
	if (!(lst->next->rep = opendir(str[0])))
		ft_printf("ls: %s: Permission denied\n", lst->dir->d_name);
	else
	{
		ft_init_data(str, data, 0);
		sort_lst(data);
		ft_print(data);
		search_directory(data, str, lst->next, 0);
	}
}

void		search_directory(t_data *data, char **av, t_recurs *lst, int i)
{
	if (av[i])
		lst->path = ft_strdup(av[i]);
	else
		lst->path = ft_strdup(".");
	while ((lst->dir = readdir(lst->rep)))
	{
		if (lst->dir->d_name[0] == '.' && !ft_strchr(data->options_set, 'a'))
			i = 0;
		else if (lst->dir->d_type == 4 && !(ft_strequ(lst->dir->d_name, "."))
				&& !(ft_strequ(lst->dir->d_name, "..")))
			search_next(data, lst);
	}
	closedir(lst->rep);
}

void		recurs_next(t_data *data, t_recurs *lst, char **av, int i)
{
	struct stat		sb;

	if (stat("./", &sb) == -1)
		ft_error("stat");
	if (!S_ISDIR(sb.st_mode))
	{
		ft_init_data(av, data, i);
		exit(0);
	}
	if (!(lst->rep = opendir("./")))
		ft_error("OPEN DIRECTORY FAILED");
	ft_init_data(av, data, i);
	sort_lst(data);
	ft_print(data);
	search_directory(data, av, lst, i);
}

void		recurs(t_data *data, char **av, int i)
{
	struct stat		sb;
	t_recurs		*lst;

	lst = crea_lst_rec();
	if (av[i])
	{
		if (stat(av[i], &sb) == -1)
			ft_error("stat");
		if (!S_ISDIR(sb.st_mode))
		{
			ft_printf("%s\n", av[i]);
			exit(0);
		}
		if (!(lst->rep = opendir(av[i])))
			ft_error("OPEN DIRECTORY FAILED");
		ft_init_data(av, data, i);
		sort_lst(data);
		ft_print(data);
		search_directory(data, av, lst, i);
	}
	else
		recurs_next(data, lst, av, i);
}
