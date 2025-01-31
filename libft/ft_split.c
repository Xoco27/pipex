/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:00:28 by cfleuret          #+#    #+#             */
/*   Updated: 2024/10/31 11:18:54 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_count(const char *s, char c)
{
	int	i;
	int	n;
	int	word;

	i = 0;
	n = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] != c && word == 0)
		{
			word = 1;
			n++;
		}
		else if (s[i] == c)
			word = 0;
		i++;
	}
	return (n);
}

static char	**ft_separate(const char *s, char c, char **tab, int n)
{
	int	i;
	int	start;
	int	l;
	int	j;
	int	k;

	i = 0;
	j = -1;
	while (j++ < n - 1)
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		l = i - start;
		tab[j] = (char *)malloc((l + 1) * sizeof(char));
		if (tab[j] == NULL)
			return (NULL);
		k = -1;
		while (k++ < l)
			tab[j][k] = s[start + k];
		tab[j][l] = '\0';
	}
	return (tab);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	int		n;

	if (!s)
		return (NULL);
	n = ft_count(s, c);
	tab = (char **)malloc((n + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	if (n == 0)
	{
		tab[0] = NULL;
		return (tab);
	}
	tab = ft_separate(s, c, tab, n);
	if (tab == NULL)
		return (NULL);
	tab[n] = NULL;
	return (tab);
}

/*int    main(void)
{
    char    **tab;
    int        i;

    tab = ft_split("hello!", ' ');
    if (tab == NULL)
    {
        printf(NULL);
        return (1);
    }
    i = 0;
    while (tab[i])
    {
        printf("%s\n", tab[i]);
        i++;
    }
    return (0);
}*/
