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
        ft_error("Yo: No such file or directory");
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
    struct passwd   *pwd;
    struct group    *grp;
    char            *foo;
    char            **timearray;
    char            *hourmin;
    hourmin = (char *)malloc(sizeof(char));

    if(lstat(str, &fileStat) < 0) 
    {
        ft_error("Yo: No such file or directory");
    }
    // if (ft_strcmp(str, "/dev") == 0)
    //     ft_printf("total 0\n");
    /*
    ** file permissions
    */
    lstat(str, &fileStat);
    if (S_ISLNK(fileStat.st_mode))
        ft_printf("l");
    else if (S_ISDIR(fileStat.st_mode) == 1)
        ft_printf("d");
    else if ((fileStat.st_mode & S_IFMT) == S_IFIFO)
        ft_printf("p");
    else if ((fileStat.st_mode & S_IFMT) == S_IFCHR)
        ft_printf("c");
    else if ((fileStat.st_mode & S_IFMT) == S_IFBLK)
        ft_printf("b");
    else if ((fileStat.st_mode & S_IFMT) == S_IFSOCK)
        ft_printf("s");
    else if ((fileStat.st_mode & S_IFMT) == S_IFREG)
        ft_printf("-");
    // ft_printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    ft_printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    ft_printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    ft_printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    ft_printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    ft_printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    ft_printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    ft_printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    ft_printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    ft_printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    ft_printf("\t");
    /*
    ** number of links
    */
    ft_printf("%5d\t",fileStat.st_nlink);      
    /*
    ** print userid. else, print numerical version
    */
    if ((pwd = getpwuid(fileStat.st_uid)) != NULL)
        ft_printf("%s\t", pwd->pw_name);
    else
        ft_printf("%d\t", fileStat.st_uid);
    /*       
    ** print %s of groupid. else, print numerical version
    */
    if ((grp = getgrgid(fileStat.st_gid)) != NULL)
        ft_printf("%s\t", grp->gr_name);
    else
        ft_printf("%d\t", fileStat.st_gid);
    /*
    ** file size / for /dev -> major/minor device numbers
    */
    if (lists->flag == 0)
        ft_printf("%5llu\t",fileStat.st_size);
    else
        ft_printf("%4ld, %4ld ", (long) major(fileStat.st_rdev), (long) minor(fileStat.st_rdev));
    /*
    ** last modification date
    ** split up ctime array into format present on ls -l (month date hour:min)
    */
    foo = ctime(&(fileStat.st_mtime));
    // printf("\nfoo: %s\n", foo[1]);
    timearray = ft_strsplit(foo, ' ');
    ft_strncpy(hourmin, timearray[3], 5);
    ft_printf("%s %2s %s\t", timearray[1], timearray[2], hourmin);
    lstat(str, &fileStat);
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
    int k = 0;
    while (timearray[k])
    {
        free(timearray[k]);
        k++;
    }
    free(timearray);
    free(hourmin);
    /*
    ** TODO: free hourmin
    ** TODO: extra attributes like @
    ** TODO: symbolic link stuff
    */
    // lstat(str, &fileStat);
    // if (S_ISLNK(fileStat.st_mode))
    //     printf("it's a link\n");


    //device type?
    // printf("device type: \t\t%d\n", fileStat.st_rdev);

    //file type
    // if (S_ISDIR(fileStat.st_mode) == 1)
    //     printf("File type: \t\tDirectory\n");
    // else if ((fileStat.st_mode & S_IFMT) == S_IFIFO)
    //     printf("File type: \t\tNamed Pipe (FIFO)\n");
    // else if ((fileStat.st_mode & S_IFMT) == S_IFCHR)
    //     printf("File type: \t\tCharacter Device\n");
    // else if ((fileStat.st_mode & S_IFMT) == S_IFBLK)
    //     printf("File type: \t\tBlock Device\n");
    // else if ((fileStat.st_mode & S_IaFMT) == S_IFSOCK)
    //     printf("File type: \t\tSocket\n");
    // else if ((fileStat.st_mode & S_IFMT) == S_IFREG)
    //     printf("File type: \t\tRegular File\n");
    // else
    //     printf("Some sort of file type error\n");

//symbolic link?
    // ft_printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");



    return (0);
}
