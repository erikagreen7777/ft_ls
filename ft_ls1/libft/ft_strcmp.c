/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egreen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 06:45:10 by egreen            #+#    #+#             */
/*   Updated: 2017/10/02 10:52:25 by egreen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int		ft_strcmp(const char *s1, const char *s2)
// {
// 	size_t		i;

// 	i = 0;
// 	if (ft_strlen(s1) - ft_strlen(s2) != 0)
// 		return (ft_strlen(s1) - ft_strlen(s2));
// 	else
// 	{
// 		while ((s1[i] || s2[i]) && (s1[i] == s2[i]))
// 			i++;
// 		return (s1[i] - s2[i]);
// 	}
// }

int 	findthelength(int len1, int len2)
{
	if (len1 > len2)
		return (1);
	else if (len2 > len1)
		return (2);	
	return (0);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int len1;
	int len2;
	int longer;
	int i;
	int diff;

	diff = 9000;
	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	longer = findthelength(len1, len2);

	if (longer == 1 || longer == 0)
	{
		while (s1[i])
		{
			diff = s1[i] - s2[i];
			if (diff != 0)
				return (diff);
			i++;
		}
	}
	else if (longer == 2)
	{
		while (s2[i])
		{
			diff = s1[i] - s2[i];
			if (diff != 0)
				return (diff);
			i++;
		}
	}
	return (0);
}
