/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:30:28 by mnajem            #+#    #+#             */
/*   Updated: 2025/10/03 18:47:58 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	srclen;

	i = 0;
	srclen = ft_strlen(src);
	if (size == 0)
		return (srclen);
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}

char	*ft_strdup(char *s)
{
	size_t	i;
	char	*dub;

	i = 0;
	i = ft_strlen(s);
	dub = malloc(i + 1);
	if (!dub)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dub[i] = s[i];
		i++;
	}
	dub[i] = '\0';
	return (dub);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	slen;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	slen = ft_strlen(s + start);
	if (len > slen)
		len = slen;
	sub = malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	sub[len] = '\0';
	return (sub);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	l1;
	size_t	l2;
	char	*ns;
	size_t	i;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	i = 0;
	ns = (char *)malloc(l1 + l2 + 1);
	if (!ns)
		return (NULL);
	while (i < l1)
	{
		ns[i] = s1[i];
		i++;
	}
	while (i < l1 + l2)
	{
		ns[i] = s2[i - l1];
		i++;
	}
	ns[i] = '\0';
	free(s1);
	return (ns);
}
