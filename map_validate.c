/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoh <eoh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 00:15:49 by eoh               #+#    #+#             */
/*   Updated: 2023/06/24 10:38:04 by eoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_position(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->l)
	{
		j = 0;
		while (j < map->w)
		{
			if (map->form[i][j] == 'P')
			{
				map->p_pos[0] = i;
				map->p_pos[1] = j;
			}
			j++;
		}
		i++;
	}
}

void	check_wall(t_map *map)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (i < map->l)
	{
		line = map->form[i];
		if (i == 0 || i == map->l - 1)
		{
			j = 0;
			while (j < map->w)
			{
				if (line[j] != '1')
					error_msg("invalid map");
				j++;
			}
		}
		else
		{
			if (line[0] != '1' || line[map->w - 1] != '1')
				error_msg("invalid map");
		}
		i++;
	}
}

void	check_element(t_map *map)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (i < map->l)
	{
		line = map->form[i];
		j = 0;
		while (j < map->w)
		{
			if (line[j] != '0' && line[j] != '1' && line[j] != 'C' \
			&& line[j] != 'E' && line[j] != 'P')
				free_check_element(map, "element error");
			if (line[j] == 'C')
				map->element[COLLECTOR]++;
			else if (line[j] == 'E')
				map->element[EXIT]++;
			else if (line[j] == 'P')
				map->element[PLAYERS]++;
			j++;
		}
		i++;
	}
}

void	check_element_num(t_map *map)
{
	if (map->element[COLLECTOR] == 0)
		error_msg("element error");
	if (map->element[EXIT] != 1 || map->element[PLAYERS] != 1)
		error_msg("element error");
}

void	map_validate_main(t_map *map, t_all *all)
{
	check_element(map);
	check_element_num(map);
	check_wall(map);
	if (bfs_main(map, all) == -1)
		error_msg("invalid map");
}
