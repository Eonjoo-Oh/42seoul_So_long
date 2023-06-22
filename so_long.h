/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoh <eoh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:57:50 by eoh               #+#    #+#             */
/*   Updated: 2023/06/23 03:16:53 by eoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG
#define SO_LONG

# include "mlx/opengl/mlx.h"
# include "ft_printf/ft_printf.h"
# include "gnl/get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

#define COLLECTOR 0
#define EXIT 1
#define PLAYERS 2

typedef struct s_map{
	char	**form;
	void	*mlx_ptr;
	void	*win_ptr;
	char	*path;
	int		element[3];
	int		l;
	int		w;
	int		fd;
	int		p_pos[2];//현재 p_pos
	int		c_pos[2];//현재 p_pos
	int		e_pos[2];
	int		cur_p_i;//keyhook렌더링에서 쓰임
	int		cur_p_j;//keyhook렌더링
	int		move;
	int		collected;
}	t_map;

typedef	struct s_visited{
	int	i;
	int	j;
	struct s_visited *next;
}	t_visited;

typedef struct s_bfs {
	int	i;
	int	j;
	int	visited;
}	t_bfs;

typedef struct s_queue {
	int				front;
	int				rear;
	int				col;
	int				exit;
	struct s_bfs	*bfs;
}	t_queue;

typedef struct s_img {
	void	*player;
	void	*map;
	void	*wall;
	void	*collector;
	void	*exit;
	int		size;
} t_img;

typedef struct s_all {
	t_map *map_all;
	t_img *img_all;
} t_all;
/*
typedef struct s_position
{
	int x;
	int y;
	int use;
} t_position;
t_position* arr = (t_position*)malloc(sizeof(t_position) * size);
arr[0].x = 10;
arr[0].y = 5;
arr[0].use = TRUE;
arr[1].x = 20;

구조체의 배열 array of struct

while(arr[i].use != FALSE)
{

}
*/

//map
t_map	*map_main(void *mlx_ptr, char *argv);
t_map *init_map(void *m_ptr, char *argv);
char	**read_map(t_map *map);
void	free_map(t_map *map, char **map_form);

//map_utils
void	check_map_name(char *name);
void	get_map_length(char *name, t_map *map);
int		get_map_width(char *str);
void	get_map_length(char *name, t_map *map);
//int		delete_n(char **res, t_map *map);

//map_validate
void	map_validate_main(t_map *map);
void	check_element(t_map *map);
void	check_element_num(t_map *map);
void	check_wall(t_map *map);
void	get_position(t_map *map);

//bfs
int		bfs_main(t_map *map);
t_queue	*init_queue (t_map *map);
void	enqueue_unvisited(t_queue *queue, t_map *map);
int		check_visited(t_queue *queue, int x, int y);

//queue
void	enqueue(t_queue *queue, t_map *map, int i, int j);
void	dequeue(t_queue *queue);
int	queue_full(t_queue *queue, t_map *map);
int	queue_empty(t_queue *queue);

//utils
int	rev_strncmp(char *s1, char *s2, int n);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	error_msg(char *message);
void	perror_msg(void);

//render img
t_img	*render_img_main(void *mlx, t_map *map);
void	render_img(void *mlx, void *win, t_img *img, t_map *map);
t_img	*init_img(void *mlx);

//key hook
int	check_keycode(int keycode, t_all *all);
int key_esc(int keycode, t_all *all);
int	key_w(int keycode, t_all *all);
int	key_s(int keycode, t_all *all);
int	key_d(int keycode, t_all *all);
int	key_a(int keycode, t_all *all);

//key hook utils
void	key_find_player(t_map *map);
int	get_collector_num(t_map *map);
int	key_check_movable(t_map *map, int keycode);

#endif