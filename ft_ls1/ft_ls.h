#ifndef FT_LS_H
# define FT_LS_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <time.h>
# include "libft/libft.h"
# include "libft/printf.h"

# define BUFF_SIZE 256
# define PATH_MAX 4096
# define WORD_MAX 256
# define D_NAME_MAX 32000
# define LONG_MAX 2147483647

typedef struct	s_lists
{
	char 		**timearray;
	int 		filecount;
	char		**dest;
	int 		i;
	int 		j;
	char		*temp;
	char 		*tempdest;
	int 		timeleni;
	int 		timelenj;
	int 		destleni;
	int 		destlenj;


}				t_lists;

void					init_struct(t_lists **lists);

void					list_dir(int argc, char **argv);
void					list_dira(int argc, char **argv);
int 					ls_stat(char *str);
void					list_dirr(int argc, char **argv, t_lists *lists);
void					list_dirt(int argc, char **argv, t_lists *lists);
void 					list_dirbigr(const char *dir_name);
void					list_dirl(int argc, char **argv, t_lists *lists);
char				    *extract_path(char *str);
int					    add_stat(char *str);
int 					time_stat(char *str);
void					ft_switch_time(t_lists *lists);







#endif
