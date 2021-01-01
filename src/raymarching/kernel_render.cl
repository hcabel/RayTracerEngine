
typedef struct __attribute__ ((packed))	s_vector2d
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

typedef struct			s_kernel_scene
{
	int					shapes_num;
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

t_vector	vector_crossproduct(t_vector a, t_vector b)
{
	t_vector	r;

	r.x = (a.y - b.z) * (a.z - b.y);
	r.y = (a.z - b.x) * (a.x - b.z);
	r.z = (a.x - b.y) * (a.y - b.x);
	return (r);
}

float		vector_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}


/*
********************************************************************************
**	SDF FUNCTION
********************************************************************************
*/

float	sdf_cube(t_vector p, t_vector obj_scale)
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

float	sdf_plane(t_vector p, t_vector obj_scale)
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

float	sdf_cylinder(t_vector p, t_vector obj_scale)
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

float	sdf_sphere(t_vector p, t_vector obj_scale)
{
	return(vector_length(p) - obj_scale.x);
}

float	sdf_cone(t_vector p, t_vector obj_scale)
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

float	dispatch_sdf(t_vector p, t_vector obj_scale, int sdf_index)
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

float	get_nearest_surface_distance(__constant t_kernel_shape *shapes,
			int shapesnum, t_vector p, int *hit_object_index)
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

t_ray_hit		trace_ray(__constant t_kernel_shape *shapes, int shapesnum,
					t_vector dir, t_vector start_location)
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
	result.hit = 0;
	result.location = p;
	return (result);
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

t_vector		get_ray_dir(t_vector2d coordinates, t_rect area, t_vector2d rot)
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

unsigned int	set_pixel_color_value(__constant t_kernel_shape *shapes,
					t_ray_hit *ray, int viewmode)
{
	t_vector		color;
	float			intensity;

	color.x = 0;
	color.y = 0;
	color.z = 0;
	if (ray->hit == 1 && shapes[ray->hit_object_index].istarget == 1)
		return (0xff5733ff);
	else if (viewmode == 1 && ray->hit == 1)
	{
		color.x = (shapes[ray->hit_object_index].color.x);
		color.y = (shapes[ray->hit_object_index].color.y);
		color.z = (shapes[ray->hit_object_index].color.z);
	/*else if (viewmode == 2 && ray->hit == 1)
		color = normal_map_to_rgb(get_normal_map(ray->location, scene,
			ray->hit_object));*/
	}
	else if (viewmode == 3)
	{
		color.x = ray->recursion / (float)100 * (float)255;
		color.y = ray->recursion / (float)100 * (float)255;
		color.z = ray->recursion / (float)100 * (float)255;
	}
	else if (ray->hit == 1)
	{
		/*intensity = get_light_intensity(scene, ray->location,
			ray->hit_object, olddir, scene->lights, 2);
		intensity = intensity / 1.2 + 0.1;
		intensity *= fabs(fmax(ray->distance / VIEW_DISTANCE, 0.5)
			- 1) * (1 / (1 - 0.5));*/
		intensity = 1;
		if (viewmode == 4)
		{
			color.x = intensity * 255;
			color.y = intensity * 255;
			color.z = intensity * 255;
		}
		else
		{
			color.x = (shapes[ray->hit_object_index].color.x * intensity);
			color.y = (shapes[ray->hit_object_index].color.y * intensity);
			color.z = (shapes[ray->hit_object_index].color.z * intensity);
		}
	}
	return (((int)color.x << 24) + ((int)color.y << 16)
		+ ((int)color.z << 8) + 0xFF);
}

__kernel void	gpu_raymarching(__global int *pxl_color,
								__constant t_kernel_shape *shapes,
								const t_kernel_scene scene)
{
	t_ray_hit	ray;
	int			pxl_index;
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
	ray = trace_ray(shapes, scene.shapes_num, dir, scene.cam_location);

	pxl_color[pxl_index] = set_pixel_color_value(shapes, &ray, scene.viewmode);
}
