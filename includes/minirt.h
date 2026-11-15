#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdbool.h>
# include <stdlib.h>

/* Minimum t accepted for a hit: avoids hitting the surface we start on */
# define EPSILON 0.0001

/* Bytes read from the .rt file at each read() call */
# define READ_SIZE 4096

/* Bits of the parser "seen" mask: A, C and L may appear only once */
# define SEEN_A 1
# define SEEN_C 2
# define SEEN_L 4

/* 3D vector: used for points, directions and RGB colors (0.0 - 1.0) */
typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

/* Ray: every point on it is origin + t * dir (dir normalized) */
typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}	t_ray;

/* Closest hit found so far: distance, point, surface normal, color */
typedef struct s_hit
{
	double	t;
	t_vec3	point;
	t_vec3	normal;
	t_vec3	color;
}	t_hit;

/* Kind of shape stored in a t_object */
typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}	t_obj_type;

/* One shape of the scene; unused fields stay 0 (e.g. dir for a sphere) */
typedef struct s_object
{
	t_obj_type		type;
	t_vec3			pos;
	t_vec3			dir;
	double			diameter;
	double			height;
	t_vec3			color;
	struct s_object	*next;
}	t_object;

/* A: ambient light, ratio in [0, 1] */
typedef struct s_ambient
{
	double	ratio;
	t_vec3	color;
}	t_ambient;

/* C: camera position, normalized view direction, horizontal FOV */
typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	dir;
	double	fov;
}	t_camera;

/* L: point light, brightness ratio in [0, 1] */
typedef struct s_light
{
	t_vec3	pos;
	double	ratio;
	t_vec3	color;
}	t_light;

/* Whole .rt file: the three unique elements plus a list of shapes */
typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_object	*objects;
}	t_scene;

/* Vector math: vec3_basic.c */
t_vec3		vec_new(double x, double y, double z);
t_vec3		vec_add(t_vec3 a, t_vec3 b);
t_vec3		vec_sub(t_vec3 a, t_vec3 b);
t_vec3		vec_scale(t_vec3 v, double s);
double		vec_dot(t_vec3 a, t_vec3 b);

/* Vector math: vec3_utils.c */
t_vec3		vec_cross(t_vec3 a, t_vec3 b);
double		vec_len(t_vec3 v);
t_vec3		vec_norm(t_vec3 v);

/* Scene helpers: scene_utils.c */
t_vec3		rgb(int r, int g, int b);
t_object	*object_new(t_obj_type type, t_vec3 pos, t_vec3 dir, t_vec3 color);
void		scene_add_object(t_scene *scene, t_object *obj);
void		scene_free(t_scene *scene);

/* Hardcoded scene of subject page 11, used to check the parser */
bool		init_test_scene(t_scene *scene);

/* Debug output of a whole scene: print_scene.c */
void		print_scene(t_scene *scene);

/* String helpers (no libft): str_utils.c, split.c */
size_t		ft_strlen(const char *s);
int			ft_strcmp(const char *a, const char *b);
bool		is_sep(char c, const char *seps);
char		**ft_split(const char *s, const char *seps);
void		free_split(char **words);

/* Numbers: ft_atof.c */
const char	*read_number(const char *s, double *out);
bool		ft_atof(const char *s, double *out);

/* Field parsers, silent (return false on bad input): parse_values.c */
bool		parse_number(const char *s, double min, double max, double *out);
bool		parse_vec3(const char *s, t_vec3 *out);
bool		parse_dir(const char *s, t_vec3 *out);
bool		parse_color(const char *s, t_vec3 *out);

/* Parser: read_file.c, parse_file.c, parse_line.c */
char		*read_file(const char *path);
bool		parse_file(const char *path, t_scene *scene);
bool		parse_line(char **words, t_scene *scene, int *seen);
bool		parse_error(const char *msg);
int			word_count(char **words);

/* One function per line type: parse_elements.c, parse_objects.c */
bool		parse_ambient(char **w, t_scene *scene);
bool		parse_camera(char **w, t_scene *scene);
bool		parse_light(char **w, t_scene *scene);
bool		parse_sphere(char **w, t_scene *scene);
bool		parse_plane(char **w, t_scene *scene);
bool		parse_cylinder(char **w, t_scene *scene);

/*
** Intersection contract, same for every shape:
** before the loop hit->t = INFINITY; a function returns true and fills
** hit only if it finds a t with EPSILON < t < hit->t (a closer hit).
*/
bool		hit_sphere(t_ray ray, t_object *obj, t_hit *hit);
bool		hit_plane(t_ray ray, t_object *obj, t_hit *hit);
bool		hit_cylinder(t_ray ray, t_object *obj, t_hit *hit);

#endif
