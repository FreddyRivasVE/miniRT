/*
bool	mrt_hit_plane(t_ray ray, t_plane plane, float *t_hit)
{
	float	denom;
	float	t;
	t_vec4	to_plane;

	denom = vec4_dot(plane.normal, ray.direction);
	if (fabs(denom) < 1e-6) // casi 0, el rayo es paralelo
		return (false);
	to_plane = plane.point - ray.origin;
	t = vec4_dot(to_plane, plane.normal) / denom;
	if (t < 0)
		return (false); // intersección detrás del origen
	*t_hit = t;
	return (true);
}

 * Calcula si un rayo intersecta una esfera en el espacio 3D.
 *
 * Esta función resuelve la ecuación cuadrática que surge al sustituir
 * la ecuación del rayo en la ecuación implícita de una esfera:
 *
 *    |P(t) - C|^2 = r^2   donde P(t) = O + tD
 *
 * P(t): punto del rayo en función de t
 * C: centro de la esfera
 * r: radio de la esfera
 * O: origen del rayo
 * D: dirección del rayo
 *
 * Se obtiene una ecuación de segundo grado en t:
 *    at^2 + bt + c = 0
 * y se calcula su discriminante para saber si hay intersección.
 *
 * Si hay colisión, se guarda en *t_hit el valor más cercano de t > 0
 * (es decir, la distancia desde el origen del rayo al punto de impacto)
 * y se retorna true.
 * 
 * @param ray     El rayo con origen y dirección
 * @param sphere  La esfera con centro y radio
 * @param t_hit   Puntero donde se guarda la distancia al punto de colisión
 * @return        true si hay intersección visible, false si no
 

bool	mrt_hit_sphere(t_ray ray, t_sphere sphere, float *t_hit)
{
	t_vec4	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	oc = ray.origin - sphere.center;
	a = vec4_dot(ray.direction, ray.direction);
	b = 2.0f * vec4_dot(oc, ray.direction);
	c = vec4_dot(oc, oc) - (sphere.radius * sphere.radius);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	*t_hit = (-b - sqrtf(discriminant)) / (2.0f * a);
	return (*t_hit > 0);
}
 
t_ray	mrt_create_ray(t_vec4 origin, t_vec4 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_ray	mrt_generate_camera_ray(t_camera_view camera, float pixel_x, float pixel_y, t_window window)
{
	float	normalized_x;
	float	normalized_y;
	t_vec4	image_point;
	t_vec4	ray_dir;

	normalized_x = pixel_x / (window.width - 1);
	normalized_y = pixel_y / (window.height - 1);
	image_point = camera.bottom_left_corner +\
			(normalized_x * camera.horizontal)\
			 + (normalized_y * camera.vertical);
	ray_dir = image_point - camera.origin;
	return (mrt_create_ray(camera.origin, ray_dir));
}


 * Calcula el color que debe tener un rayo lanzado desde la cámara en la escena.
 * 
 * Esta función determina si el rayo intersecta con una esfera fija en el espacio.
 * Si hay intersección, calcula la iluminación en el punto de impacto
 * usando un modelo simple con luz puntual que considera luz difusa y especular.
 * Si no hay intersección, retorna un color de fondo degradado (skybox simple).
 * 
 * @param ray El rayo con origen y dirección desde la cámara.
 * @param elements Puntero a elementos de la escena (no usado en esta versión).
 * @return t_vec4 Color RGBA resultante para el rayo.
 * 
 * Proceso:
 * 1. Define una esfera con centro en (0,0,-5) y radio 1.
 * 2. Verifica si el rayo intersecta la esfera con mrt_hit_sphere().
 * 3. Si hay impacto:
 *    - Calcula el punto de impacto y el vector normal en ese punto.
 *    - Define una luz puntual con componentes difusa y especular.
 *    - Calcula la intensidad de la luz difusa basada en el ángulo entre normal y dirección de luz.
 *    - Calcula la intensidad especular basada en el ángulo entre la dirección de vista y el vector reflejado.
 *    - Suma el color base de la esfera con las componentes difusa y especular.
 * 4. Si no hay impacto:
 *    - Calcula un color de fondo degradado entre blanco y azul en función de la dirección del rayo.
 

t_vec4 mrt_ray_color(t_ray ray, t_data *elements)
{
	float			t_sphere_hit;
	float			t_plane_hit;
	bool			hit_sphere = mrt_hit_sphere(ray, sphere, &t_sphere_hit);
	bool			hit_plane = mrt_hit_plane(ray, plane, &t_plane_hit);

	elements = NULL;
	if (hit_sphere && (!hit_plane || t_sphere_hit < t_plane_hit))
	{
		t_vec4 point = ray.origin + vec4_scale(ray.direction, t_sphere_hit);
		t_vec4 normal = vec4_normalize(point - sphere.center);
		t_vec4 light_dir = vec4_normalize(light.position - point);
		float diff_intensity = fmax(0.0f, vec4_dot(normal, light_dir)) * light.diff_power;
		t_vec4 diff = vec4_scale(light.diff_color, diff_intensity);
		t_vec4 view_dir = vec4_normalize(ray.origin - point);
		t_vec4 reflect_dir = vec4_reflect(vec4_scale(light_dir, -1.0f), normal);
		float shininess = 32.0f;
		float spec_intensity = powf(fmax(0.0f, vec4_dot(view_dir, reflect_dir)), shininess) * light.spec_power;
		t_vec4 spec = vec4_scale(light.spec_color, spec_intensity);
		t_vec4 base_color = (t_vec4){0.8f, 0.6f, 0.0f, 0.0f}; // color de la esfera
		return (vec4_add(base_color, vec4_add(diff, spec)));
	}
	else if (hit_plane)
	{
		t_vec4 point = ray.origin + vec4_scale(ray.direction, t_plane_hit);
		t_vec4 normal = vec4_normalize(plane.normal);
		t_vec4 light_dir = vec4_normalize(light.position - point);
		float diff_intensity = fmax(0.0f, vec4_dot(normal, light_dir)) * light.diff_power;
		t_vec4 diff = vec4_scale(light.diff_color, diff_intensity);
		t_vec4 base_color = (t_vec4){0.2f, 0.5f, 0.2f, 0.0f}; // color del plano
		return (vec4_add(base_color, diff)); // sin especular por ahora
	}
	t_vec4 black = (t_vec4){0.0f, 0.0f, 0.0f, 0.0f};
	return (black);
}


 * Limita un valor flotante dentro de un rango dado.
 *
 * Si el valor `x` es menor que `min`, devuelve `min`.
 * Si el valor `x` es mayor que `max`, devuelve `max`.
 * Si `x` está dentro del rango `[min, max]`, lo devuelve sin cambios.
 *
 * Es útil para asegurar que un valor permanezca dentro de un intervalo
 * válido, por ejemplo, para colores en el rango [0.0, 1.0].
 *
 * @param x   Valor a limitar
 * @param min Límite inferior
 * @param max Límite superior
 * @return    Valor clamped entre min y max
 

float	mrt_clamp_float(float x, float min, float max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

void	mrt_put_color(t_vec4 color, int x, int y, t_window window)
{
	int			index;
	uint8_t		*pixels;

	index = (y * window.width + x) * 4;
	pixels = window.image->pixels;
	pixels[index] = (uint8_t)(255.99 * mrt_clamp_float(color[0], 0, 0.999));
	pixels[index + 1] = (uint8_t)(255.99 * mrt_clamp_float(color[1], 0, 0.999));
	pixels[index + 2] = (uint8_t)(255.99 * mrt_clamp_float(color[2], 0, 0.999));
	pixels[index + 3] = 255;
}
*/

t_camera_view	setup_camera_view(t_camera *cam)
{
	t_camera_view	view;
	t_vec4			up;
	t_vec4			w;
	t_vec4			u;
	t_vec4			v;
	t_vec4			half_horiz;
	t_vec4			half_vert;
	double			theta;
	double			half_height;
	double			half_width;

	view.origin = cam->origin;
	theta = cam->fov * (PI / 180.0);
	half_height = tan(theta / 2.0);
	half_width = ASPECT_RATIO * half_height;
	up = vec4_create(0, 1, 0, 0);
	w = vec4_normalize(vec4_scale(cam->direction, -1));
	u = vec4_normalize(vec4_cross(up, w));
	v = vec4_cross(w, u);
	view.horizontal = vec4_scale(u, 2.0 * half_width);
	view.vertical = vec4_scale(v, 2.0 * half_height);
	half_horiz = vec4_scale(view.horizontal, 0.5);
	half_vert = vec4_scale(view.vertical, 0.5);
	view.bottom_left_corner = vec4_sub(
			vec4_sub(
				vec4_sub(view.origin, half_horiz),
				half_vert),
			w);
	return (view);
}


void	mrt_draw_to_window(t_window window, t_data *elements)
{
	int				j;
	int				i;
//	t_vec4			color;
//	t_ray			ray;

	j = 0;
	(void)elements; // Evita warning de variable no usada
	while (j < window.height)
	{
		i = 0;
		while (i < window.width)
		{
			//ray = mrt_generate_camera_ray(camera, i, j, window);
			//color = mrt_ray_color(ray, NULL);
			//mrt_put_color(color, i, j, window);
			i++;
		}
		j++;
	}
}