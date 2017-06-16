/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crea_lst_one_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 03:27:12 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/16 05:55:16 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		mode_type_file(struct stat sb)
{
	if (S_ISLNK(sb.st_mode))
		write(1, "l", 1);
	else if (S_ISREG(sb.st_mode))
		write(1, "-", 1);
	else if (S_ISDIR(sb.st_mode))
		write(1, "d", 1);
	else if (S_ISCHR(sb.st_mode))
		write(1, "c", 1);
	else if (S_ISBLK(sb.st_mode))
		write(1, "b", 1);
	else if (S_ISFIFO(sb.st_mode))
		write(1, "p", 1);
	else if (S_ISSOCK(sb.st_mode))
		write(1, "s", 1);
}

static void		mode_right_next(char c)
{
	if (c == '7')
		write(1, "rwx", 3);
	else if (c == '6')
		write(1, "rw-", 3);
	else if (c == '5')
		write(1, "r-x", 3);
	else if (c == '4')
		write(1, "r--", 3);
	else if (c == '3')
		write(1, "-wx", 3);
	else if (c == '2')
		write(1, "-w-", 3);
	else if (c == '1')
		write(1, "--x", 3);
	else
		write(1, "---", 3);
}

static void		mode_right(struct stat sb)
{
	char	*perm;
	int		i;
	int		j;

	j = 0;
	ft_sprintf(&perm, "%lo\n", (unsigned long)sb.st_mode);
	i = (int)ft_strlen(perm) - 4;
	while (j < 3)
	{
		mode_right_next(perm[i]);
		i++;
		j++;
	}
}

static void		maj_min_bloc_print(struct stat sb)
{
	if (S_ISCHR(sb.st_mode) || S_ISBLK(sb.st_mode))
	{
		ft_printf("%4d,", (MAJOR(sb.st_rdev) / 16));
		ft_printf("%4d ", MINOR(sb.st_rdev));
	}
}

void			print_one_file(struct stat sb, char *name)
{
	struct passwd	*pwuid;
	struct group	*getgrp;

	mode_type_file(sb);
	mode_right(sb);
	ft_printf(" %2u", sb.st_nlink);
	pwuid = getpwuid(sb.st_uid);
	getgrp = getgrgid(sb.st_gid);
	ft_printf(" %s ", pwuid->pw_name);
	ft_printf(" %s ", getgrp->gr_name);
	maj_min_bloc_print(sb);
	if (!S_ISCHR(sb.st_mode) || !S_ISBLK(sb.st_mode))
		ft_printf(" %lld ", sb.st_size);
	print_date_one_file(sb);
	print_name_one_file(sb, name);
}
