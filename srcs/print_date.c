/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_date.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 02:49:48 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/16 06:08:18 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int	get_day(char *str)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (!(str[i] >= '0' && str[i] <= '9'))
		i++;
	ret = ft_atoi(&str[i]);
	return (ret);
}

static char	*get_month(char *str)
{
	int		i;
	int		j;
	char	*ret;

	ret = ft_strnew(3);
	i = 0;
	j = 0;
	while (str[i] != ' ')
		i++;
	i++;
	while (j < 3)
		ret[j++] = str[i++];
	return (ret);
}

static char	*get_hour(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	ret = ft_strnew(5);
	while (str[i] != ':')
		i++;
	i -= 2;
	while (j < 5)
		ret[j++] = str[i++];
	return (ret);
}

static int	get_year(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	i -= 6;
	return (ft_atoi(&str[i]));
}

void		print_date(t_dirent_list *file)
{
	char	*str;

	str = ctime(&file->infos->mtime);
	ft_printf("%2d ", get_day(str));
	ft_printf("%3s ", get_month(str));
	if ((time(NULL) - file->infos->mtime) < 15778800)
		ft_printf("%s", get_hour(str));
	else
		ft_printf("%d", get_year(str));
}
