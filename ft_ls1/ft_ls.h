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
# define WORD_MAX 1000

void					list_dir(int argc, char **argv);
void					list_dira(int argc, char **argv);
int 					ls_stat(char **argv);

#endif
