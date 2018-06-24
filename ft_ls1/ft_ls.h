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
# include <stdbool.h>
# include <errno.h>
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
	char 		**strs;
	int 		i;
	int 		j;
	int 		k;
	char		*temp;
	char 		*tempdest;
	int 		timeleni;
	int 		timelenj;
	int 		destleni;
	int 		destlenj;
	char 		newpath[PATH_MAX];
	int 		flag;
	int 		size;
	int 		argcount;
	int 		tflag;
	int 		big_r_flag;
	int 		rflag;
	int 		lflag;
	int 		aflag;

}				t_lists;

void	arg_parsing(int argc, char **argv, t_lists *lists);
void			init_struct(t_lists **lists);
int				directory_count(DIR *dip, char *str, int flag);
void			list_dir(int argc, char **argv);
void			list_dira(int argc, char **argv, t_lists *lists);
int 			ls_stat(char *str, t_lists *lists);
void			list_dirr(int argc, char **argv, t_lists *lists);
void			list_dirt(int argc, char **argv, t_lists *lists);
void 			list_dirbigr(const char *dir_name, int flag);
void			list_dirl(int argc, char **argv, t_lists *lists);
char		    *extract_path(char *str);
int				add_stat(char *str);
int 			time_stat(char *str);
void			ft_switch_time(t_lists *lists);
void			R_first(int argc, char **argv, int flag);
void 			ls_la(int argc, char **argv, t_lists *lists);
void 			ls_lt(int argc, char **argv, t_lists *lists);
void 			ls_lta(int argc, char **argv, t_lists *lists);
void 			ls_ra(int argc, char **argv, t_lists *lists);
void 			ls_rt(int argc, char **argv, t_lists *lists);
void			lex_sort(t_lists *lists);
void 			ls_rat(int argc, char **argv, t_lists *lists);
void 			ls_lrat(int argc, char **argv, t_lists *lists);
void 			list_dirbigrt(const char *name, int flag, t_lists *lists);
void    		list_dirbigrl(const char *name, int flag, t_lists *lists);
int   			Rt_helper(const char *str, int flag, t_lists *lists);
int   			Rl_helper(const char *str, int flag, t_lists *lists);
int   			Rr_helper(const char *str, int flag, t_lists *lists);
void		    list_dirbigrr(const char *name, int flag, t_lists *lists);
int   			Rrl_helper(const char *str, int flag, t_lists *lists);
void		    list_dirbigrrl(const char *name, int flag, t_lists *lists);
void			list_dirlr(int argc, char **argv, t_lists *lists);
void			lex_sortrl(t_lists *lists);
void			list_dirta(int argc, char **argv, t_lists *lists);
void			ls_lra(int argc, char **argv, t_lists *lists);
void			rlex_sortrl(t_lists *lists);
void            ls_lrt(int argc, char **argv, t_lists *lists);
int  			rlt_helper(const char *str, int flag, t_lists *lists);
void    		rlt(const char *name, int flag, t_lists *lists);
int    			R_helper(const char *str, int flag);
int  			rbigrt_helper(const char *str, int flag, t_lists *lists);
void    		rbigrt(const char *name, int flag, t_lists *lists);
void			everything(const char *name, int flag, t_lists *lists);
int  			everything_helper(const char *str, int flag, t_lists *lists);
void			ls_stat_helper(t_lists *lists);
void 	recursive_ls_stat_helper(t_lists *lists);
void 	r_recursive_ls_stat_helper(t_lists *lists);
void    print_lists(t_lists *lists);
void    print_lists_back(t_lists *lists);
void	back_helper(t_lists *lists);
void read_helper(t_lists *lists, int flag, char *arg, DIR *dip);
void read_helper_a(t_lists *lists, int flag, char *arg, DIR *dip);
void read_helper_guts(t_lists *lists, char *arg, struct dirent *dit, char *temp, int flag);
void read_helper_guts_a(t_lists *lists, char *arg, struct dirent *dit, char *temp, int flag);
void    permissions(struct stat fileStat);
void    guidstuff(struct stat fileStat, t_lists *lists);
void    timeinfo(struct stat fileStat);
void null_check(const char *str);
void	rt_helper_helper(DIR *dip, t_lists *lists, char *arg, int flag);
void 	rl_helper_helper(DIR *dip, t_lists *lists, char *arg, int flag);
void		lt_helper(t_lists *lists, char *str);
void	lta_helper(t_lists *lists, char *str);
void	rlt_helper_helper(t_lists *lists, char *str);
void	rla_helper_helper(t_lists *lists, char *str);
void	recursive_cat(char *path, const char *name, struct dirent *entry);
void	list_dirta_helper(t_lists *lists, char *str);
void 	la_helper(char *str, t_lists *lists);
int	argc_stuff(int argc, char **argv, t_lists *lists);
void	main_two(int argc, char **argv, t_lists *lists);
void	main_three(int argc, char **argv, t_lists *lists);
void	main_four(int argc, char **argv, t_lists *lists);
void	main_five(int argc, char **argv, t_lists *lists);
void	main_six(int argc, char **argv, t_lists *lists);
void	main_seven(int argc, char **argv, t_lists *lists);
void	main_eight(int argc, char **argv, t_lists *lists);
void	main_nine(int argc, char **argv, t_lists *lists);
void	main_ten(int argc, char **argv, t_lists *lists);
void	main_eleven(int argc, char **argv, t_lists *lists);
void	main_twelve(int argc, char **argv, t_lists *lists);
void	main_thirteen(int argc, char **argv, t_lists *lists);
void	main_fourteen(int argc, char **argv, t_lists *lists);
void	main_fifteen(int argc, char **argv, t_lists *lists);







#endif
