#include "../ft_ls.h"
		
static void get_lengths(t_lists *lists)
{
	/*
	** get strlen of st_mtime items
	*/
	lists->timeleni = ft_strlen(lists->timearray[lists->i]);
	lists->timelenj = ft_strlen(lists->timearray[lists->j]);
	/*
	** get strlen of corresponding folder names
	*/
	lists->destleni = ft_strlen(lists->dest[lists->i]);
	lists->destlenj = ft_strlen(lists->dest[lists->j]);
	/*
	** allocate space for the temps for the swap
	*/
	// lists->temp = (char *)malloc(lists->timeleni + 1);
	// lists->tempdest = (char *)malloc(lists->destleni + 1);
}

static void	switch_helper(t_lists *lists)
{
	get_lengths(lists);
	lists->temp = ft_strdup(lists->timearray[lists->i]);
	lists->tempdest = ft_strdup(lists->dest[lists->i]);
	ft_bzero(lists->timearray[lists->i], lists->timeleni);
	ft_bzero(lists->dest[lists->i], lists->destleni);
	lists->timearray[lists->i] = ft_strdup(lists->timearray[lists->j]);
	lists->dest[lists->i] = ft_strdup(lists->dest[lists->j]);
	ft_bzero(lists->timearray[lists->j], lists->timelenj);
	ft_bzero(lists->dest[lists->j], lists->destlenj);
	lists->timearray[lists->j] = ft_strdup(lists->temp);
	lists->dest[lists->j] = ft_strdup(lists->tempdest);
	free(lists->temp);
	free(lists->tempdest);
}

// static void switch_equal_helper(t_lists *lists)
// {
// 	/*
// 	** if the time stamp is the same
// 	*/
// 	if (ft_strcmp(lists->dest[lists->i], lists->dest[lists->j]) > 0) /* add a flag here for ls -r stuff? */
// 	{
// 		get_lengths(lists);
// 		lists->temp = ft_strdup(lists->timearray[lists->i]);
// 		lists->tempdest = ft_strdup(lists->dest[lists->i]);
// 		ft_bzero(lists->timearray[lists->i], lists->timeleni);
// 		ft_bzero(lists->dest[lists->i], lists->destleni);
// 		lists->timearray[lists->i] = ft_strdup(lists->timearray[lists->j]);
// 		lists->dest[lists->i] = ft_strdup(lists->dest[lists->j]);
// 		ft_bzero(lists->timearray[lists->j], lists->timelenj);
// 		ft_bzero(lists->dest[lists->j], lists->destlenj);
// 		lists->timearray[lists->j] = ft_strdup(lists->temp);
// 		lists->dest[lists->j] = ft_strdup(lists->tempdest);
// 		free(lists->temp);
// 		free(lists->tempdest);
// 	}
// }
void	ft_switch_time(t_lists *lists)
{
	lists->i = -1;
	while (++lists->i < lists->filecount)
	{
		lists->j = lists->i + 1;
		while (lists->j < lists->filecount)
		{
			/*
			** find the oldest time
			*/
			if (ft_atoi(lists->timearray[lists->i]) < ft_atoi(lists->timearray[lists->j]))
			{
				switch_helper(lists);
			}
			else if (ft_atoi(lists->timearray[lists->i]) == ft_atoi(lists->timearray[lists->j]))
			{
				if (ft_strcmp(lists->dest[lists->i], lists->dest[lists->j]) > 0)
					switch_helper(lists);
			}
			lists->j++;
		}
	}
}
