#ifndef	MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
#include <stdint.h>
# include <math.h>
// # include "src/libmlx/mlx.h"
// # include "src/libmlx/mlx_int.h"

# define ARGS_NUM	"[!!] Incorrect number of args!\n"

# define FILE_OPN	"[!!] Could not open file!\n"

# define FCNT_SPLT					"[!!] Could not split file content\n"
# define LCNT_SPLT					"[!!] Could not split line content\n"
# define CLR_SPLT					"[!!] Could not split colors\n"
# define CRD_SPLT					"[!!] Could not split coordinates\n"
# define VEC_SPLT					"[!!] Could not split vector\n"

# define INVL_MAP					"[!!] Invalid Map!\n"
# define INVL_ID					"[!!] Invalid Identifier\n"

# define INVL_AMBIENT_RATIO			"[!!] Invalid Ambient Ratio\n"
# define INVL_AMBIENT_COLORS		"[!!] Invalid Ambient Color\n"
# define INVL_AMBIENT_INFO			"[!!] Extra Ambient Info\n"

# define INVL_CAMERA_COORDINATES	"[!!] Invalid Camera Coordinates\n"
# define INVL_CAMERA_VECTOR			"[!!] Invalid Camera Vector\n"
# define INVL_CAMERA_FOV			"[!!] Invalid Camera FOV\n"
# define INVL_CAMERA_INFO			"[!!] Extra Camera Info\n"

# define INVL_LIGHT_COORDINATES		"[!!] Invalid Light Coordinates\n"
# define INVL_LIGHT_RATIO			"[!!] Invalid Light Ratio\n"
# define INVL_LIGHT_INFO			"[!!] Extra Light Info\n"

# define INVL_SPHERE_COORDINATES	"[!!] Invalid Sphere Coordinates\n"
# define INVL_SPHERE_COLOR			"[!!] Invalid Sphere Color\n"
# define INVL_SPHERE_DIAMETER		"[!!] Invalid Sphere Diameter\n"
# define INVL_SPHERE_INFO			"[!!] Extra Sphere Info\n"

# define INVL_PLANE_COORDINATES		"[!!] Invalid Plan Coordinates\n"
# define INVL_PLANE_VECTOR			"[!!] Invalid Plane Vector\n"
# define INVL_PLANE_COLOR		  	"[!!] Invalid Plane Color\n"
# define INVL_PLANE_INFO			"[!!] Extra Plane Info\n"

# define INVL_CYLINDER_COORDINATES	"[!!] Invalid Cylinder Coordinates\n"
# define INVL_CYLINDER_VECTOR		"[!!] Invalid Cylinder Vector\n"
# define INVL_CYLINDER_DIAMETER		"[!!] Invalid Cylinder Diameter\n"
# define INVL_CYLINDER_HEIGHT		"[!!] Invalid Plane Height\n"
# define INVL_CYLINDER_COLOR		"[!!] Invalid Cylinder Color\n"
# define INVL_CYLINDER_INFO			"[!!] Extra Cylinder Info\n"

# define MLX_INIT					"[!!] Could not init mlx session!\n"
# define WIN_INIT					"[!!] Could not create mlx window!\n"
# define IMG_INIT					"[!!] Could not create mlx image!\n"
# define IMG_ADDR					"[!!] Could not retrieve image address!\n"

# define DBLCAPID	"[ii] Elements which are defined by a capital letter can only be declared once in the scene.\n"

# define WIDTH	200
# define HEIGHT	200

typedef enum e_return
{
	R_SUCCESS,
	R_FAILURE,
	R_MALLOC,
	R_INVALID,
	R_FILEDESC,
	R_FCNTSPLT,
	R_LIBMLX,
	R_DBLCAPID
}	t_return;

typedef enum e_id
{
	ID_AMBIENT,
	ID_CAMERA,
	ID_LIGHT,
	ID_SPHERE,
	ID_PLANE,
	ID_CYLINDER,
	ID_INVALID
}	t_id;

typedef struct s_ambient
{
	bool			is_set;
	double			ratio;
	int32_t			color[3];
}	t_ambient;

typedef struct s_camera
{
	bool			is_set;
	double			pos[3];
	double			vector[3];
	int32_t			fov;
}	t_camera;

typedef struct s_light
{
	bool			is_set;
	double			pos[3];
	double			ratio;
}	t_light;

typedef struct s_sphere
{
	double			pos[3];
	double			diameter;
	int32_t			color[3];
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_plane
{
	double			pos[3];
	double			vector[3];
	int32_t			color[3];
	struct s_plane	*next;
}	t_plane;

typedef struct s_cylinder
{
	double				pos[3];
	double				vector[3];
	double				diameter;
	double				height;
	int32_t				color[3];
	struct s_cylinder	*next;
}	t_cylinder;

typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;

	int32_t			bpx;
	int32_t			sl;
	int32_t			e;

	char			*img_addr;
}	t_mlx;

typedef struct s_minirt
{
	t_ambient		ambient;
	t_camera		camera;
	t_light			light;
	uint32_t		n_sphere;
	t_sphere		*sphere;
	uint32_t		n_plane;
	t_plane			*plane;
	uint32_t		n_cylinder;
	t_cylinder		*cylinder;

	t_mlx			mlx;
}	t_minirt;


/* tools */
// stools
uint64_t	mrt_strlcpy(char *dst, const char *src, uint64_t dstsize);
int32_t		mrt_strncmp(const char *s1, const char *s2, size_t n);
int32_t		mrt_strcmp(const char *s1, const char *s2);
bool		mrt_strchr(const char *s, int c);
uint32_t	mrt_strlen(const char *s);
char		*mrt_strdup(const char *s);

bool		mrt_setdouble(char *str, double *nb);
bool		mrt_setuint32(char *str, uint32_t *value, int32_t max);
bool		mrt_setcolor(char *str, uint32_t *color[]);
bool		mrt_setcords(char *str, double *cords[]);
bool		mrt_setvector(char *str, double *vector[]);

char		**mrt_split(char const *s, char c);

void		mrt_error(const char *error_msg);
bool		mrt_isspace(int c);

// ftools;
# define	FREAD_SIZE 1024

char		*mrt_readfile(char *filename);

// memtools
void		*mrt_calloc(size_t count, size_t size);
void		mrt_memset(void *p, int c, uint32_t size);
void		mrt_free(void **p);
void		mrt_free_arr(char **arr);
void		mrt_free_all(t_minirt *mrt);

// links
t_sphere	*add_sphere(t_minirt *mrt);
t_plane		*add_plane(t_minirt *mrt);
t_cylinder	*add_cylinder(t_minirt *mrt);

t_return	mrt_init(t_minirt *mrt);
t_return	mrt_initmlx(t_mlx *mlx);
void		mrt_freemlx(t_mlx mlx);

/* parser */
t_return	mrt_parser(const char *filename, t_minirt *mrt);

t_return	mrt_extract(t_minirt *mrt, char *line);

/* viewer */
t_return	mrt_viewer(t_minirt *mrt);

int			mrt_trace(t_minirt *mrt, int h, int w);

#endif