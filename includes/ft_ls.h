/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 03:00:05 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/09 06:09:44 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
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

typedef struct				s_info
{
	char					*name;
	unsigned char			d_type;
	unsigned int			mode;
	int						nlink;
	int						uid;
	int						gid;
	long long int			size;
	long long int			blocks;
	long int				mtime;
	long int				mtime_nsec;
	char					*pw_name;
	char					*gr_name;
}							t_info;

typedef struct				s_dirent_list
{
	t_info					*infos;
	struct s_dirent_list	*next;
}							t_dirent_list;

typedef struct				s_data
{
	int						total_blk;
	char					*path;
	char					*options_set;
	int						nb_file;
	int						max_link;
	int						max_name;
	int						max_grp;
	int						max_size;
	size_t					len_max_name;
	t_directory				*directory;
	struct s_dirent_list	*file;
}							t_data;

int							check_options(char **av, char **options_set);

void						ft_error(char *error);

t_directory					*ft_init_dir(void);
t_dirent_list				*add_list(void);
void						make_list_dirent(t_data *data, char *path);
t_data						*ft_init_data(char **av);

void						sort_lst(t_data *data);
void						sort_alpha(t_data *data, int i, int c);
void						sort_time(t_data *data, int i, int c);

void						ft_print(t_data *data);
void						l_print(t_data *data);
void						l_print_next(t_data *data, int *k);
void						print_date(t_dirent_list *file);
void						print_name(t_data *data, t_dirent_list *file);

#endif
