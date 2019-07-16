/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:12:37 by igarbuz           #+#    #+#             */
/*   Updated: 2019/06/27 14:04:03 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H

# define LEMIN_H

# include <stdio.h>
# include <limits.h>
# include "libft.h"
# include "ft_printf.h"

# include <SDL.h>

# define START "##start"
# define END "##end"

/*
** STACK_SIZE TO BE MAXIMAZED FOR 100 000 : 400 KB
** STACK   : 0x80000, 0x40000, 0x20000, 0x10000, 0x8000, 0x4000, 0x2000, 0x1000
** STACK_M : 0x7ffff, 0x3ffff, 0x1ffff, 0x0ffff, 0x7fff, 0x3fff, 0x1fff, 0x0fff;
*/

# define NODES 0x10000
# define NODES_M 0xffff

# define EDGES_M 1 * NODES_M
# define EDGES 1 * NODES
# define EDGES_N 256
# define EDGES_N_M 255

# define PATH 0x1000

# define OUT 10000
# define TOFREE 512
# define NAME 512

# define WIDTH 1200
# define HEIGHT 800
# define NB_FRAME 64

# define BUFF_SIZE_LEMIN 0x80000
# define BUFF_SIZE_LEMIN_M 0x7fffff
# define IN_BUF 0x10000
# define IN_BUF_M 0xffff

# define MAX_BACK 10
# define MAX_ITER 15

typedef struct			s_input {
	char				*buf[IN_BUF];
	int					last;
}						t_input;

/*
** s_node: x, y and name correspond to coordinates of a node and its name;
** Used exclusively for the visualisation;
** c - capacity; By default is 1;
** *in represents an adresse of input node;
** *out represents an addresse of output node;
** hd = head or last element of the list;
*/
typedef struct			s_node {
	char				*name;
	int					x;
	int					y;
	char				c;
	char				visited;
	int					hd;
	struct s_edge		*edges[EDGES_N];
}						t_node;

/*
** s_edge: structure holding two pointers to adjusent edges;
** ignore = 0 by default;
** c1_2 and c1_2 = 1 by default;
** if edge has noly one connection, it must be *a1;
*/
typedef struct			s_edge {
	t_node				*a1;
	t_node				*a2;
	char				ignore;
	char				c1_2;
	char				c2_1;
}						t_edge;

/*
** t_path is a chained list of pointers to edges
*/
typedef struct			s_path {
	t_node				*node;
	t_edge				*edge;
	int					ant;
	struct s_path		*next;
	struct s_path		*prev;
}						t_path;

/*
** t_solution is a chained list of pointers to pathes
** t_solution->ln is a length of current path; All paths
** are ordered in increasing order;
*/
typedef struct			s_solution {
	t_path				*path;
	t_path				*last_step;
	t_node				*last_node;
	t_edge				*last_edge;
	char				is_valid;
	int					ln;
	int					steps;
	int					ants;
	int					moving;
	char				rotated;
	int					backward;
	struct s_solution	*next;
	struct s_solution	*prev;
}						t_solution;

/*
** t_bfs is a chained list of different bfs solutions;
** only one solutions is passed to t_graph as final;
*/
typedef struct			s_bfs {
	t_solution			*solution;
	t_solution			*sol_sort;
	t_solution			*last_sol_sort;
	char				there_is_path;
	int					steps;
	int					opt_paths;
	int					paths;
	struct s_bfs		*next;
}						t_bfs;

/*
** t_graph structure containt graph data: nodes, edges;
** len - number of nodes in the graph;
** hd - head is a pointer to the last node in the graph;
** *start is a pointer to the SOURCE;
** *end is a pointer to the SINK;
** ants - number of ants;
*/
typedef struct			s_graph {
	t_node				nodes[NODES];
	t_edge				edges[EDGES];
	int					hd_n;
	int					hd_e;
	t_node				*start;
	t_node				*end;
	int					ants;
	int					sent;
	t_bfs				*bfs;
	t_bfs				*curr_bfs;
	t_bfs				*shortest;
	t_input				*input;
	char				vis;
	int					iters;
}						t_graph;

/*
** t_out saves output string
*/
typedef struct			s_out {
	char				*out[OUT];
	char				*hd;
}						t_out;

/*
** s_free structure contains all pointers to all datatypes to be freed
*/
typedef struct			s_free {
	t_graph				**graph;
}						t_free;

typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Renderer		*rend;
	SDL_Surface			*surface;
	SDL_Texture			*texture;
	int					state;
	int					delay;
}						t_sdl;

typedef struct			s_point {
	int					x;
	int					y;
}						t_point;

/*
** global veriable g_tofree of type s_free points to s_free structure that must
** be accessible from everywhere to free allocated memory in case of
** non-expected exit;
*/
extern struct s_free	g_tofree;

/*
** check_input.c
*/
char					get_type(char *line, char ***tbl);
void					ft_freetbl(char **tbl);

/*
** append_graph.c
*/
void					append_graph(t_graph *graph, char *line, int *tag);

/*
** append_graph_lib.c
*/
void					append_node(char **tbl, t_graph *graph, int tag);
void					check_append_edge(char **tbl, t_graph *graph);
void					check_node_uniq(char **tbl, t_graph *graph);

/*
** append_graph_lib_checks.c
*/
t_node					*check_node_exist(char *name, t_graph *graph);
char					check_edge_exist(t_node *node_1, t_node *node_2,
						t_graph *graph);
void					check_node_uniq(char **tbl, t_graph *graph);
void					append_edge(t_node *node_1, t_node *node_2,
						t_graph *graph);
void					check_append_edge(char **tbl, t_graph *graph);

/*
** find_max_flow.c
*/

/*
** initialize.c
** init_node and init_edge make static at release;
*/
void					init_graph(t_graph **graph);
void					init_node(t_node *node);
void					init_edge(t_edge *edge);

/*
** error_handler.c
*/
void					error(int code);
void					ft_free(void);
void					add_tofree(void *memalc);

/*
** find_paths.c
*/
void					find_paths(t_graph *graph);

/*
** find_shortest.c
*/
void					find_shortest(t_graph *graph);
void					find_opt_solution(t_bfs *bfs);

/*
** init_for_paths.c
*/
t_path					*init_path(t_node *first);
t_solution				*init_solution(t_node *first);
t_bfs					*init_bfs(t_node *first);
t_bfs					*push_new_bfs(t_graph *graph);
t_solution				*copy_solution(t_solution *sol,
						t_solution *copy, char x);

/*
** move_remove_for_paths.c
*/
void					free_solution(t_solution *sol);
void					unchain_solution(t_solution *sol, t_bfs *curr_bfs);
void					remove_solution(t_bfs *curr_bfs, t_solution *new_sol);
void					move_to_sorted(t_solution *new_sol, t_bfs *curr_bfs);
void					path_is_found(t_solution *new_sol, t_bfs *curr_bfs,
						t_graph *graph);

/*
** set_reset_for_paths.c
*/
void					reset_edge_capacities(t_graph *graph);
void					reset_node_capacities(t_graph *graph);
void					capacity_to_zero(t_path *path);
void					check_colisions_and_reset(t_graph *graph);
void					clone_solution_field(t_solution *sol, t_solution *copy,
						char x);

/*
** check_count_for_paths.c
*/
char					check_colisions(t_path *new_path, t_graph *graph);
int						forbidden_from_here(t_node *node, t_solution *solution);
t_node					*can_we_go(t_node *node, t_edge *edge, t_path *path);
char					is_skip(int branches, t_solution *curr_sol,
						t_graph *graph);

/*
** check_count_for_paths.c
*/
void					retain_input(t_graph *graph, char *str);
void					init_input(t_graph *graph);

/*
** check_for_check_input.c
*/
int						check_number(char *str);
void					check_node(char **tbl);
void					check_edge(char **tbl);

/*
** calc_steps.c
*/
void					calc_paths_bfs(t_bfs *bfs);
void					calc_steps_bfs(t_bfs *bfs, int ants);

/*
** move_ants.c
*/
void					send_ants(t_graph *graph);
void					send_ants_view(t_graph *graph);

/*
** print_ants.c
*/
int						print_path_ants(char *str, t_path *path);
void					write_input(t_graph *graph);
int						write_result(char *str, t_graph *graph);

/*
** viewer.c
*/
void					viewer(t_graph *graph, t_sdl *sdl);
int						sdl_init(t_graph *graph, t_sdl *sdl);
void					sdl_exit(t_sdl *sdl);

/*
** draw_ants.c
*/
int						draw_ants(t_graph *graph, t_sdl *sdl, int k, int i);

/*
** draw_control.c
*/
int						draw_control(t_graph *graph, t_sdl *sdl);
int						viewer_control(t_sdl *sdl);

/*
** draw_map.c
*/
int						setup_map(t_graph *graph);
int						draw_map(t_graph *graph, t_sdl *sdl);

/*
** add_to_previous.c
*/
void					check_add_to_previous(t_solution *new_sol,
						t_graph *graph, t_bfs *bfs);

/*
** copy_before_or_after.c
*/
void					copy_before(t_solution *copy, t_solution *sol_to_paste,
						t_bfs *bfs);
void					copy_after(t_solution *copy, t_solution *sol_to_paste,
						t_bfs *bfs);

#endif
