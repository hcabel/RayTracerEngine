
#include "define.h"

typedef struct			s_vector2d
{
	float				x;
	float				y;
}						t_vector2d;

typedef struct			s_vector
{
	float				x;
	float				y;
	float				z;
}						t_vector;

typedef struct			s_rect
{
	int					x;
	int					y;
	int					w;
	int					h;
}						t_rect;

typedef struct			s_kernel_shape
{
	t_vector			location;
	t_vector2d			rotation;
	t_vector			scale;
	t_vector			color;
	unsigned int		sdf_index;
	int					istarget;
}						t_kernel_shape;

typedef struct			s_kernel_light
{
	t_vector			location;
	t_vector2d			rotation;
	float				intensity;
}						t_kernel_light;

typedef struct			s_kernel_scene
{
	int					shapes_num;
	int					lights_num;
	t_vector			cam_location;
	t_vector2d			cam_rotation;
	int					viewmode;
	int					img_x;
	int					img_y;
	int					img_w;
	int					img_h;
}						t_kernel_scene;

typedef struct			s_ray_hit
{
	int					hit;
	t_vector			location;
	int					hit_object_index;
	float				depth;
	unsigned int		recursion;
}						t_ray_hit;

/*
********************************************************************************
**	VECTOR UTILS
********************************************************************************
*/

t_vector	vector_add(t_vector a, t_vector b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

t_vector	vector_subtract(t_vector a, t_vector b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return (a);
}

t_vector	vector_mult(t_vector v, float mult)
{
	v.x *= mult;
	v.y *= mult;
	v.z *= mult;
	return (v);
}

t_vector	new_vector(float x, float y, float z)
{
	t_vector	newvector;

	newvector.x = x;
	newvector.y = y;
	newvector.z = z;
	return (newvector);
}

float		vector_length(t_vector a)
{
	return (sqrt((float)(a.x * a.x + a.y * a.y + a.z * a.z)));
}

t_vector	vector_normalize(t_vector a)
{
	float	length;

	length = vector_length(a);
	a.x = a.x / length;
	a.y = a.y / length;
	a.z = a.z / length;
	return (a);
}

t_vector	vector_crossproduct(t_vector a,
								t_vector b)
{
	t_vector	r;

	r.x = (a.y - b.z) * (a.z - b.y);
	r.y = (a.z - b.x) * (a.x - b.z);
	r.z = (a.x - b.y) * (a.y - b.x);
	return (r);
}

float		vector_dot(	t_vector a,
						t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}


/*
********************************************************************************
**	SDF FUNCTION
********************************************************************************
*/

float	sdf_cube(	t_vector p,
					t_vector obj_scale)
{
	t_vector	q;
	t_vector	y;
	float		diff;

	q.x = fabs(p.x) - obj_scale.x;
	q.y = fabs(p.y) - obj_scale.y;
	q.z = fabs(p.z) - obj_scale.z;
	y.x = (fmax((double)q.x, 0));
	y.y = (fmax((double)q.y, 0.0));
	y.z = (fmax((double)q.z, 0.0));
	diff = fmin(fmax((double)q.x, fmax((double)q.y, (double)q.z)), 0.0);
	return (vector_length(y) + diff);
}

float	sdf_plane(	t_vector p,
					t_vector obj_scale)
{
	t_vector	q;
	t_vector	y;
	float		diff;

	q.x = fabs(p.x) - obj_scale.x;
	q.y = fabs(p.y) - 0.0005;
	q.z = fabs(p.z) - obj_scale.z;
	y.x = (fmax((double)q.x, 0.0));
	y.y = (fmax((double)q.y, 0.0));
	y.z = (fmax((double)q.z, 0.0));
	diff = fmin(fmax((double)q.x, fmax((double)q.y, (double)q.z)), 0.0);
	return (vector_length(y) + diff);
}

float	sdf_cylinder(	t_vector p,
						t_vector obj_scale)
{
	float	a;
	float	b;
	float	c;
	float	d;

	a = sqrt(p.x * p.x + p.z * p.z) - obj_scale.x;
	b = fabs(p.y) - obj_scale.y;
	c = fmax((double)a, 0.0);
	d = fmax((double)b, 0.0);
	return (fmin(fmax((double)a, (double)b), 0.0) + sqrt(c * c + d * d));
}

float	sdf_sphere(	t_vector p,
					t_vector obj_scale)
{
	return(vector_length(p) - obj_scale.x);
}

float	sdf_cone(	t_vector p,
					t_vector obj_scale)
{
	t_vector	q;
	t_vector	a;
	t_vector	b;
	float		d;
	float		s;

	q.x = obj_scale.x * obj_scale.x / obj_scale.x;
	q.y = obj_scale.x * -obj_scale.x / obj_scale.z;
	q.z = 0;
	p.x = sqrt(p.x * p.x + p.z * p.z);
	p.y = p.y;
	p.z = 0;
	a.x = p.x - q.x * fmax((double)1, fmax((double)0, vector_dot(p, q)
		/ (double)vector_dot(q, q)));
	a.y = p.y - q.y * fmin((double)1, fmax((double)0, vector_dot(p, q)
		/ (double)vector_dot(q, q)));
	a.z = 0;
	b.x = p.x - q.x * fmin((double)1, fmax((double)0, p.x / (double)q.x));
	b.y = p.y - q.y * fmin((double)1, fmax((double)0, p.x / (double)q.x));
	b.z = 0;
	s = (q.y < 0 ? -1.0 : 1.0);
	d = fmin(vector_dot(b, b), vector_dot(a, a));
	s = fmax(s * (p.x * q.y - p.y * q.x), s * (p.y - q.y));
	return (sqrt(d) * (s < 0 ? -1.0 : 1.0));
}

/*
********************************************************************************
**	TRACE RAY
********************************************************************************
*/

float	dispatch_sdf(	t_vector p,
						t_vector obj_scale,
						int sdf_index)
{
	if (sdf_index == 1)
		return (sdf_cone(p, obj_scale));
	if (sdf_index == 2)
		return (sdf_cube(p, obj_scale));
	if (sdf_index == 3)
		return (sdf_cylinder(p, obj_scale));
	if (sdf_index == 4)
		return (sdf_plane(p, obj_scale));
	return (sdf_sphere(p, obj_scale));
}

float	get_nearest_surface_distance(	__constant t_kernel_shape *shapes,
										int shapesnum,
										t_vector p,
										int *hit_object_index)
{
	float		distance;
	float		tmp;
	int			i;
	t_vector	obj_loc;
	t_vector	obj_scale;

	i = 0;
	while (i < shapesnum && (distance > 0 || i == 0))
	{
		obj_loc.x = p.x - shapes[i].location.x;
		obj_loc.y = p.y - shapes[i].location.y;
		obj_loc.z = p.z - shapes[i].location.z;
		obj_scale.x = shapes[i].scale.x;
		obj_scale.y = shapes[i].scale.y;
		obj_scale.z = shapes[i].scale.z;
		tmp = dispatch_sdf(obj_loc, obj_scale, shapes[i].sdf_index);
		if (i == 0 || distance > tmp)
		{
			*hit_object_index = i;
			distance = tmp;
		}
		i++;
	}
	return (distance);
}

t_ray_hit		trace_ray(	__constant t_kernel_shape *shapes,
							int shapesnum,
							t_vector dir,
							t_vector start_location)
{
	t_ray_hit	result;
	t_vector	p;
	float		nearest_surface;

	result.recursion = 0;
	result.depth = 0;
	while (result.recursion < 100 && result.depth < 200)
	{
		p = vector_add(start_location, vector_mult(dir, result.depth));
		nearest_surface = get_nearest_surface_distance(shapes, shapesnum, p, &result.hit_object_index);
		if (nearest_surface <= 0.0005)
		{
			result.hit = 1;
			result.location = p;
			return (result);
		}
		result.depth += nearest_surface;
		result.recursion++;
	}
	result.hit = (result.depth < 200 ? 1 : 0);
	result.location = p;
	return (result);
}

/*
********************************************************************************
**	NORMAL MAP
********************************************************************************
*/

t_vector	normal_map_to_rgb(t_vector normal)
{
	normal.x = (normal.x + 1) * 127.5;
	normal.y = (normal.y + 1) * 127.5;
	normal.z = (normal.z + 1) * 127.5;
	return (normal);
}

float	normal_get_nearest_surface_distance(__constant t_kernel_shape *shapes,
											int shapesnum,
											t_vector p)
{
	float		distance;
	float		tmp;
	int			i;
	t_vector	obj_loc;
	t_vector	obj_scale;

	i = 0;
	distance = 0;
	while (i < shapesnum && (distance > 0 || i == 0))
	{
		obj_loc.x = p.x - shapes[i].location.x;
		obj_loc.y = p.y - shapes[i].location.y;
		obj_loc.z = p.z - shapes[i].location.z;
		obj_scale.x = shapes[i].scale.x;
		obj_scale.y = shapes[i].scale.y;
		obj_scale.z = shapes[i].scale.z;
		tmp = dispatch_sdf(obj_loc, obj_scale, shapes[i].sdf_index);
		if (i == 0 || distance > tmp)
			distance = tmp;
		i++;
	}
	return (distance);
}

t_vector	get_normal_map(	__constant t_kernel_shape *shapes,
							int shapes_num,
							t_vector p)
{
	float		tab[4];
	t_vector	normal;
	t_vector2d	eps;

	eps.x = 1.0 * 0.5773 * 0.0005;
	eps.y = -1.0 * 0.5773 * 0.0005;
	tab[0] = normal_get_nearest_surface_distance(shapes, shapes_num, vector_add(p, new_vector(eps.x, eps.y, eps.y)));
	tab[1] = normal_get_nearest_surface_distance(shapes, shapes_num, vector_add(p, new_vector(eps.y, eps.y, eps.x)));
	tab[2] = normal_get_nearest_surface_distance(shapes, shapes_num, vector_add(p, new_vector(eps.y, eps.x, eps.y)));
	tab[3] = normal_get_nearest_surface_distance(shapes, shapes_num, vector_add(p, new_vector(eps.x, eps.x, eps.x)));
	normal.x =	eps.x * tab[0] +
				eps.y * tab[1] +
				eps.y * tab[2] +
				eps.x * tab[3];
	normal.y =	eps.y * tab[0] +
				eps.y * tab[1] +
				eps.x * tab[2] +
				eps.x * tab[3];
	normal.z =	eps.y * tab[0] +
				eps.x * tab[1] +
				eps.y * tab[2] +
				eps.x * tab[3];
	return (vector_normalize(normal));
}

/*
********************************************************************************
**	RAY DIRECTION
********************************************************************************
*/

float	deg2rad(float degrees)
{
	return (degrees * M_PI / 180);
}

t_vector		get_ray_dir(t_vector2d coordinates,
							t_rect area,
							t_vector2d rot)
{
	t_vector	dir;
	t_vector2d	pixel;
	float		scale;
	float		ratio;

	ratio = area.w / (float)area.h;
	scale = tan(deg2rad(45));
	pixel.x = (2 * ((coordinates.x + 0.5) / area.w) - 1) * scale * ratio;
	pixel.y = (1 - 2 * ((coordinates.y + 0.5) / area.h)) * scale;

	dir = new_vector(pixel.x, pixel.y, 1);
	return (vector_normalize(dir));
}

/*
********************************************************************************
**	MAIN
********************************************************************************
*/

int			check_for_hidden_obj(	__constant t_kernel_light *lights,
									int	amount,
									t_vector dir,
									t_vector cam_location,
									float prec)
{
	t_vector		tmp;
	unsigned int	i;

	i = 0;
	while (i < amount)
	{
		tmp = vector_normalize(vector_subtract(lights[i].location, cam_location));
		if (tmp.x + prec >= dir.x && tmp.x - prec <= dir.x
			&& tmp.y + prec >= dir.y && tmp.y - prec <= dir.y
			&& tmp.z + prec >= dir.z && tmp.z - prec <= dir.z)
			return (1);
		i++;
	}
	return (0);
}

#define FOG_START 0.5

int				is_one_ray_viewmode(int vm)
{
	if (vm == UNLIT_VIEWMODE || vm == NORMAL_VIEWMODE | vm == ITERATION_VIEWMODE
		|| vm == DISTANCE_FOG_VIEWMODE)
		return (GOOD);
	return (FAILED);
}

unsigned int	get_color_from_one_ray_viewmode(__constant t_kernel_shape *shapes,
												unsigned int shapes_num,
												t_ray_hit *ray,
												int viewmode)
{
	t_vector		color;
	unsigned int	tmp;

	if (!ray->hit && viewmode != ITERATION_VIEWMODE)
		return (viewmode == DISTANCE_FOG_VIEWMODE ? 0x0 : DISTANCE_FOG_COLOR);
	if (viewmode == DISTANCE_FOG_VIEWMODE)
	{
		tmp = (fabs(fmax(ray->depth / VIEW_DISTANCE, (float)FOG_START)
			- 1) * (1 / fmax((float)0.0001, (float)(1 - FOG_START)))) * 255;
		color.x = tmp;
		color.y = tmp;
		color.z = tmp;
	}
	else if (viewmode == UNLIT_VIEWMODE)
	{
		color.x = (shapes[ray->hit_object_index].color.x);
		color.y = (shapes[ray->hit_object_index].color.y);
		color.z = (shapes[ray->hit_object_index].color.z);
	}
	else if (viewmode == NORMAL_VIEWMODE)
		color = normal_map_to_rgb(get_normal_map(shapes, shapes_num, ray->location));
	else if (viewmode == ITERATION_VIEWMODE)
	{
		color.x = ray->recursion / (float)RAY_LOOP * (float)255;
		color.y = ray->recursion / (float)RAY_LOOP * (float)255;
		color.z = ray->recursion / (float)RAY_LOOP * (float)255;
	}
	else
		return (0xFF0000FF);
	return (((int)color.x << 24) + ((int)color.y << 16)
		+ ((int)color.z << 8) + 0xFF);
}

#define KS 1.0
#define KD 0.7
#define KA 0.2

static float	phong_lighting(	const t_kernel_scene *scene,
								__constant t_kernel_shape *shapes,
								__constant t_kernel_light *lights,
								t_vector oldir,
								t_ray_hit *ray,
								int index)
{
	t_vector	N;
	t_vector	L;
	t_vector	R;
	float		dotLN;
	float		dotRV;
	float		intensity;

	N = get_normal_map(shapes, scene->shapes_num, ray->location);
	L = vector_subtract(lights[index].location, ray->location);

	if (vector_length(L) >= 100)
		return (0);
	intensity = fabs((vector_length(L) - 100) / (float)100);

	L = vector_normalize(L);

	L = vector_mult(L, -1);
	R.x = L.x - 2 * vector_dot(L, N) * N.x;
	R.y = L.y - 2 * vector_dot(L, N) * N.y;
	R.z = L.z - 2 * vector_dot(L, N) * N.z;
	L = vector_mult(L, -1);

	dotLN = vector_dot(L, N);
	dotRV = vector_dot(R, vector_mult(oldir, -1));
	if (dotLN < 0)
		return (0);
	if (dotRV < 0)
		return (intensity * (KD * dotLN));
	return (intensity * (KD * dotLN + KS * pow(dotRV, 250)));
}

unsigned int	raymarching_light_steps(const t_kernel_scene *scene,
								__constant t_kernel_shape *shapes,
								__constant t_kernel_light *lights,
								t_vector oldir,
								t_ray_hit *ray)
{
	t_vector	color;
	float		intensity;

	intensity = 0.1;
	for (int i = 0; i < scene->lights_num; i++)
		intensity += fmax((float)0, phong_lighting(scene, shapes, lights, oldir, ray, i));
	intensity = fmin((float)1, intensity);
	intensity *= fabs(fmax(ray->depth / (float)VIEW_DISTANCE, (float)FOG_START)
		- 1) * (1 / fmax((float)0.0001, (float)(1 - FOG_START)));

	if (scene->viewmode == DIRECT_ILLUMINATION_VIEWMODE)
		return (((int)(intensity * 255) << 24) + ((int)(intensity * 255) << 16)
			+ (int)(intensity * 0xFF00) + 0xFF);

	color.x = shapes[ray->hit_object_index].color.x * intensity;
	color.y = shapes[ray->hit_object_index].color.y * intensity;
	color.z = shapes[ray->hit_object_index].color.z * intensity;
	return (((int)color.x << 24) + ((int)color.y << 16)
		+ ((int)color.z << 8) + 0xFF);
}

__kernel void	gpu_raymarching(__global int *pxl_color,
								__constant t_kernel_shape *shapes,
								__constant t_kernel_light *lights,
								const t_kernel_scene scene)
{
	t_ray_hit	ray;
	int			pxl_index;
	double		depth;
	t_vector2d	coordinates;
	t_vector	dir;
	t_rect		img;
	t_vector	start_location;

	img.x = scene.img_x;
	img.y = scene.img_y;
	img.w = scene.img_w;
	img.h = scene.img_h;

	pxl_index = get_global_id(0);
	coordinates.x = pxl_index % scene.img_w;
	coordinates.y = pxl_index / scene.img_w;

	dir = get_ray_dir(coordinates, img, scene.cam_rotation);
	if (scene.viewmode != GAME_VIEWMODE && scene.viewmode != ITERATION_VIEWMODE
		&& check_for_hidden_obj(lights, scene.lights_num, dir, scene.cam_location, .025))
	{
		pxl_color[pxl_index] = 0xFF0000FF;
		return ;
	}
	ray = trace_ray(shapes, scene.shapes_num, dir, scene.cam_location);
	ray.depth = fmin((float)VIEW_DISTANCE, fmax((float)0.0, ray.depth));

	if (is_one_ray_viewmode(scene.viewmode) == GOOD)
	{
		pxl_color[pxl_index] = get_color_from_one_ray_viewmode(shapes, scene.shapes_num, &ray, scene.viewmode);
		return ;
	}
	if (!ray.hit)
	{
		pxl_color[pxl_index] = DISTANCE_FOG_COLOR;
		return ;
	}
	pxl_color[pxl_index] = raymarching_light_steps(&scene, shapes, lights, dir, &ray);
}
