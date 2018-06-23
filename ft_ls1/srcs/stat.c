#include "../ft_ls.h"


char    *extract_path(char *str)
{
    int             len;
    char            *newstr;

    newstr = (char *)malloc(sizeof(char));
    len = ft_strlen(str) - ft_strlen(ft_strstr(str, "/"));
    ft_strncpy(newstr, str, len);
    printf("newstr: %s\n", newstr);
    return (newstr);
}

int    add_stat(char *str)
{
    struct stat     fileStat;
    if(lstat(str, &fileStat) < 0) 
    {
        ft_error("add_stat(): No such file or directory");
    }
    return (fileStat.st_blocks);

}


int time_stat(char *str)
{
    struct stat     fileStat;
    if(lstat(str, &fileStat) < 0) 
    {
        ft_error("time_stat: No such file or directory");
    }
    return (fileStat.st_mtime);
}

char *readlink_malloc (const char *filename)
{
  int size = 32767;
  char *buffer = NULL;
  int i;
  i = 0;

  while (1)
    {
      buffer = (char *)malloc(sizeof(char) * size);
      int nchars = readlink(filename, buffer, size);
      if (nchars < 0)
        {
          free (buffer);
          return NULL;
        }
      if (nchars < size)
      {
        buffer[nchars] = '\0';
        return (buffer);
      }
      size *= 2;
      i++;
    }
}

int ls_stat(char *str,  t_lists *lists)
{
    struct stat     fileStat;
    // struct passwd   *pwd;
    // struct group    *grp;
    // char            *foo;
    // char            **timearray;
    // char            *hourmin;
    // time_t          current;

    if(lstat(str, &fileStat) < 0) 
        ft_error("ls_stat: No such file or directory");
    /*
    ** file permissions    -------------------------------------------------------> function start here
    */
    permissions(fileStat);
    // if (S_ISLNK(fileStat.st_mode))
    //     ft_printf("l");
    // else if (S_ISDIR(fileStat.st_mode) == 1)
    //     ft_printf("d");
    // else if ((fileStat.st_mode & S_IFMT) == S_IFIFO)
    //     ft_printf("p");
    // else if ((fileStat.st_mode & S_IFMT) == S_IFCHR)
    //     ft_printf("c");
    // else if ((fileStat.st_mode & S_IFMT) == S_IFBLK)
    //     ft_printf("b");
    // else if ((fileStat.st_mode & S_IFMT) == S_IFSOCK)
    //     ft_printf("s");
    // else if ((fileStat.st_mode & S_IFMT) == S_IFREG)
    //     ft_printf("-");
    // ft_printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    // ft_printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    // ft_printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    // ft_printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    // ft_printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    // ft_printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    // ft_printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    // ft_printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    // ft_printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    // ft_printf("\t");
    /*
    ** number of links  ---------------------------------------------------------------> function end here
    */
    guidstuff(fileStat, lists);
    // ft_printf("%5d\t",fileStat.st_nlink);      
    // /*
    // ** print userid. else, print numerical version
    // */
    // if ((pwd = getpwuid(fileStat.st_uid)) != NULL)
    //     ft_printf("%s\t", pwd->pw_name);
    // else
    //     ft_printf("%d\t", fileStat.st_uid);
    // /*       
    // ** print %s of groupid. else, print numerical version
    // */
    // if ((grp = getgrgid(fileStat.st_gid)) != NULL)
    //     ft_printf("%s\t", grp->gr_name);
    // else
    //     ft_printf("%d\t", fileStat.st_gid);
    // /*
    // ** file size / for /dev -> major/minor device numbers
    // */
    // if (lists->flag == 0)
    //     ft_printf("%5llu\t",fileStat.st_size);
    // else
    //     ft_printf("%4ld, %4ld ", (long) major(fileStat.st_rdev), (long) minor(fileStat.st_rdev));
    /*
    ** last modification date
    ** split up ctime array into format present on ls -l (month date hour:min)
    **  
    **
    **
    **     -----------------------------------------------------------------------------> function start here
    */
    timeinfo(fileStat);
    // hourmin = (char *)malloc(sizeof(char));
    // foo = ctime(&(fileStat.st_mtime));
    // /*
    // ** if (foo > ctime - 6 months) || (foo < ctime + 6 months)
    // */
    // timearray = ft_strsplit(foo, ' ');
    // if (fileStat.st_mtime > time(&current) + 15780000 || fileStat.st_mtime < time(&current) - 15780000)
    // {
    //     char year[5];
    //     ft_strncpy(year, timearray[4], 4);
    //     ft_printf("%s  ", year);
    // }
    // else
    // {
    //     ft_strncpy(hourmin, timearray[3], 5);
    //     ft_printf("%s %2s %s  ", timearray[1], timearray[2], hourmin);
    // }
    // int k = 0;
    // while (timearray[k])
    // {
    //     free(timearray[k]);
    //     k++;
    // }
    // free(timearray);
    // free(hourmin);
    /*
    **        --------------------------------------------------------------------------------> function end here
    */
    if (S_ISLNK(fileStat.st_mode))
    {
        char *buf = readlink_malloc(str);
        printf("%s -> %s\n", str, buf);
    }
    else
        ft_printf("%s\n", str);
    /*
    ** TODO: free timearray
    */
    return (0);
}
