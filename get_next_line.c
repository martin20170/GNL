/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphilip <mphilip@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:40:13 by mphilip           #+#    #+#             */
/*   Updated: 2023/01/06 16:40:09 by mphilip          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*null_str(int size)
{
	int		i;
	char	*result;

	i = 0;
	result = malloc(size + 1);
	if (!result)
		return (NULL);
	while (i < size + 1)
	{
		result[i] = 0;
		i++;
	}
	return (result);
}

void	ft_bzero(void *s, size_t n)
{
		char	*ptr;
		size_t	i;

	ptr = (char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;
	int		i;

	ptr = (char *)s;
	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == (char)c)
			return (&ptr[i]);
		i++;
	}
	if ((char)c == '\0')
		return (&ptr[i]);
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*dest_ptr;
	char	*src_ptr;
	size_t	i;

	dest_ptr = (char  *)dest;
	src_ptr = (char *)src;
	i = 0;
	if (dest_ptr == NULL && src_ptr == NULL)
		return (dest);
	while (i < n)
	{
		dest_ptr[i] = src_ptr[i];
		i++;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dest_ptr;
	char	*src_ptr;

	dest_ptr = (char *)dest;
	src_ptr = (char *)src;
	if (src_ptr == dest_ptr || n == 0)
		return (dest);
	if (src < dest)
	{
		while (n > 0)
		{
			dest_ptr[n - 1] = src_ptr[n - 1];
			n--;
		}
			return (dest);
	}
	else
		return (ft_memcpy(dest, src, n));
}

char	*ft_realloc_add(char *memo, char *line, int size_to_add)
{
	char	*result;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(line);
	result = null_str(len + size_to_add + 1);
	if (!result)
		return (NULL);
	while (line[i])
	{
		result[i] = line[i];
		i++;
	}
	i = 0;
	while (i < size_to_add)
	{
		result[len + i] = memo[i];
		i++;
	}
	free(line);
	return (result);
}

void	memo_clean(char *memo)
{
	char	*ptr;
	int		final_len;
	int		i;

	i = 0;
	ptr = ft_strchr(memo, '\n');
	final_len = ft_strlen(ptr) - 1;
	memo = ft_memmove(memo, ptr + 1, final_len);
	while (i < BUFFER_SIZE - final_len)
	{
		memo[final_len + i] = '\0';
		i++;
	}
}

char	*get_next_line(int fd)
{
	static char		memo[BUFFER_SIZE+1];
	char			*line;
	char			*buf;
	int				len_bef_clean;
	static size_t	bytes_count=BUFFER_SIZE;
	int secu = 0;

	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = 0;
	buf = malloc(BUFFER_SIZE+1);
	if (!buf)
		return (NULL);
	ft_bzero(buf, BUFFER_SIZE+1);
	ft_bzero(memo, BUFFER_SIZE+1);
	while (bytes_count != 0 && secu < 10)
	{
		if (memo[0] == 0)
		{
			bytes_count = read(fd, buf, BUFFER_SIZE);
			printf("%ld\n", bytes_count);
			ft_memcpy(memo, buf, bytes_count);
			printf("\n\n\nmemo : %s\n\n\n", memo);
			write(1, "\n\n1111\n\n", 8);
		}
		write(1, "\n\n2222\n\n", 8);
		if (ft_strchr(memo, '\n'))
		{
			write(1, "\n\n3333\n\n", 8);
			len_bef_clean = ft_strlen(memo);
			memo_clean(memo);
			line = ft_realloc_add(memo, line, len_bef_clean - ft_strlen(memo));
			printf("\n\n\nline : %s\n\n\n", line);
			write(1, "\n\n4444\n\n", 8);
			free(buf);
			return (line);
		}
		else
		{
			write(1, "\n\n5555\n\n", 8);
			line = ft_realloc_add(memo, line, ft_strlen(memo));
			printf("\n\n\nline : %s\n\n\n", line);
			ft_bzero(memo, BUFFER_SIZE);
			write(1, "\n\n6666\n\n", 8);
		}
		write(1, "\n\n7777\n\n", 8);
		secu++;
	}
	write(1, "\n\n8888\n\n", 8);
	free(buf);
	return (line);
}
