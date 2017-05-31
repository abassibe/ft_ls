/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 03:00:05 by abassibe          #+#    #+#             */
/*   Updated: 2017/05/31 03:02:04 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS

#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include "libft.h"

# define D_DIRd irectory->rep
# define D_NEXT directory->next

typedef struct			s_directory
{
	DIR					*rep;
	struct directory	*next;
}						t_directory;

typedef struct			s_data
{
	char				*options_set;
	t_directory*		directory;
	struct dirent		*file;
}						t_data;

#endif
