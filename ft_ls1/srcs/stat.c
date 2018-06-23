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
    char            *buf; 

    if(lstat(str, &fileStat) < 0) 
        ft_error("ls_stat: No such file or directory");
    permissions(fileStat);
    guidstuff(fileStat, lists);
    timeinfo(fileStat);
    if (S_ISLNK(fileStat.st_mode))
    {
        buf = readlink_malloc(str);
        printf("%s -> %s\n", str, buf);
    }
    else
        ft_printf("%s\n", str);
    return (0);
}
