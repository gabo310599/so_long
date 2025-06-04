/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:28:42 by gojeda            #+#    #+#             */
/*   Updated: 2025/06/04 16:44:14 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

//str_len that doesnt count de \n
int	ft_strlen_nnl(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

//Verify if de map given is rectangle
int	map_is_rectangle(int fd)
{
	char	*str;
	int		width;
	int		curr;
	int		i;

	str = get_next_line(fd);
	if (!str)
		return (ft_printf("%s\n", EMPTY_MAP_ERROR), 0);
	width = ft_strlen_nnl(str);
	free(str);
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		curr = ft_strlen_nnl(str);
		if (curr != width)
			return (free(str), 0);
		free(str);
		i++;
	}
	return (i);
}

//Free all the memory for the map in case of error
void	free_map_error(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);	
}

//We fill the map for better handling
char	**fill_map(int fd, int rows)
{
	char	**map;
	int		cols;
	char	*line;
	int		i;

	map = (char **) malloc(sizeof(char *) * rows);
	if (!map)
		return (NULL);
	line = get_next_line(fd);
	cols = ft_strlen_nnl(line);
	i = 0;
	while (line)
	{
		map[i] = malloc(sizeof(char) * (cols + 1));
		if (!map[i])
			return (free_map_error(map), free(line), NULL);
		map[i] = fill_map_line(line);
		if (!map[i])
			return (free_map_error(map), free(line), NULL);
		i++;
		free(line);
	}
	return (map);
}

//We control if the map is valid
int	map_is_ok(char *map_route)
{
	int		fd;
	char	**map;
	int		rows;

	if (!ft_strnstr(map_route, ".ber", ft_strlen(map_route)))
		return (ft_printf("%s\n", BER_ERROR), 0);
	fd = open(map_route, O_RDONLY);
	if (fd < 0)
		return (close(fd), perror(OPEN_ERROR), 0);
	rows = map_is_rectangle(fd);
	if (!rows)
		return (close(fd), ft_printf("%s\n", NO_REC_MAP_ERROR), 0);
	close (fd);
	fd = open(map_route, O_RDONLY);
	if (fd < 0)
		return (close(fd), perror(OPEN_ERROR), 0);
	map = map_is_char(fd, rows);
	if (!map)
		return (close(fd), ft_printf("%s\n", NO_REC_MAP_ERROR), 0);
	close(fd);
	return (1);	
}
