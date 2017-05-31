/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 03:00:05 by abassibe          #+#    #+#             */
/*   Updated: 2017/05/31 04:16:07 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS

#include <sys/types.h>
#include <dirent.h>
#include "libft.h"
#include "ft_printf.h"

# define D_DIR directory->rep
# define D_NEXT directory->next

typedef struct				s_directory
{
	DIR						*rep;
	struct directory		*next;
}							t_directory;

typedef struct				s_dirent_list
{
	struct dirent			*child;
	struct s_dirent_list	*next;
}							t_dirent_list;

typedef struct				s_data
{
	char					*options_set;
	t_directory				*directory;
	struct s_dirent_list	*file;
}							t_data;

#endif
