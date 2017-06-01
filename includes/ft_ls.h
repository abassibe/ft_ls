/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 03:00:05 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/01 05:04:39 by abassibe         ###   ########.fr       */
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
# define NAME data->file->child->d_name
# define NEXT_NAME data->file->next->child->d_name

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
	int						nb_file;
	t_directory				*directory;
	struct s_dirent_list	*file;
}							t_data;

int							check_options(char **av, char **options_set);

void						ft_error(char *error);

t_directory					*ft_init_dir(void);
t_dirent_list				*add_list(void);
void						make_list_dirent(t_data *data);
t_data						*ft_init_data(char **av);

void						sort_lst(t_data *data);

#endif
