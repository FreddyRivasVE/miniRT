# miniRT

Un **ray tracer minimalista** en C basado en el modelo de iluminación de **Phong**. Proyecto de la escuela 42 que tiene como objetivo introducir los conceptos de gráficos 3D y geometría computacional.

![Ejemplo de render](https://github.com/FreddyRivasVE/miniRT/blob/main/codigo/scenes/render_ejemplo.png)

## 🎯 Objetivos

* Implementar un motor de ray tracing básico en C.
* Comprender los fundamentos de las intersecciones entre rayos y objetos geométricos.
* Aplicar el modelo de iluminación de Phong para obtener un render realista.
* Practicar el parsing de archivos de configuración (`.rt`).
* Trabajar con estructuras de datos y matemáticas aplicadas a gráficos 3D.


## ✨ Características principales

### Mandatory
* Soporte para **objetos básicos**: esfera, plano, cilindro.
* **Cámara** configurable desde archivo `.rt`.
* **Luz** única con color y componente ambiente.
* Iluminación con modelo **Phong** (ambiente + difusa + especular).
* **Sombras** básicas.
* **Antialiasing** MSAA 4x para suavizado de bordes.
* **Materiales diferenciados** con niveles de brillo configurable.
* Manejo de **errores** en parsing.
* Renderizado en ventana usando [MLX42](https://github.com/codam-coding-college/MLX42).

### Bonus
* **Múltiples luces** de colores independientes (vs una sola luz).
* Objeto **cono semi-infinito** con vértice puntiagudo y base circular.
* **Patrón checkerboard** (tablero de ajedrez) en planos con toggle interactivo.

## 📂 Estructura del proyecto

```
miniRT/
├── include/                # Archivos de cabecera (.h) del mandatory.
|   ├── minirt.h       
|   ├── mrt_struct.h
|
├── include_bonus/          # Archivos de cabecera (.h) del bonus.
|   ├── minirt_bonus.h       
|   ├── mrt_struct_bonus.h  
|
├── src/                    # Código fuente principal (parser, render, objetos, operaciones con vectores, etc.)
├── src_bonus/              # Bonus (múltiples luces, cono, checkerboard pattern)
├── scenes/                 # Escenas de ejemplo en formato .rt
├── libs/                   # Librerías (libft, MLX42)
├── Makefile                # Script de compilación
└── README.md
```

## 📋 Reglas del Makefile

El `Makefile` incluye reglas adicionales para habilitar ciertas características:

* **Compilación estándar**

  ```bash
  make
  ```
  Genera el ejecutable `miniRT` con funcionalidad básica.

* **Compilación bonus**

  ```bash
  make bonus
  ```
  Genera el ejecutable `miniRT_bonus` con todas las características avanzadas.

* **Compilación con antialiasing**
  Activa MSAA 4x para suavizado de bordes

  ```bash
  make anti       
  ```

* **Compilación con materiales**
  Permite activar diferentes tipos de materiales con niveles de reflexión específicos.
  Disponible tanto para mandatory como bonus. Cada regla aplica un `flag` distinto al compilador que modifica los valores de `SHININESS_ACTIVE` y `REFLECTION_INTENSITY`:

  ✨ **Mate** - Superficie opaca, sin brillo (`SHININESS=5.0f, REFLECTION=0.1f`)
  ```bash
  make matte
  ```
  
  ✨ **Plástico** - Brillo moderado (`SHININESS=32.0f, REFLECTION=0.8f`)
  ```bash
  make plastic
  ```
  
  ✨ **Madera** - Brillo natural sutil (`SHININESS=8.0f, REFLECTION=0.3f`)
  ```bash
  make wood
  ```
  
  ✨ **Brillante** - Superficie muy reflectante (`SHININESS=256.0f, REFLECTION=1.5f`)
  ```bash
  make shiny
  ```

## ▶️ Ejecución

* **Mandatory**

  ```bash
  ./miniRT scenes/example.rt
  ```

* **Bonus**

  ```bash
  ./miniRT_bonus scenes/example.rt
  ```


* El programa recibe como argumento un archivo `.rt` que describe la escena.
* Si el archivo no es válido o contiene errores de formato, se muestra un mensaje de error.

### 🎮 Controles

* **ESC**: Cerrar la aplicación (mandatory y bonus)
* **P**: Alternar patrón checkerboard en planos (solo bonus)

### 📄 Formato de archivos .rt

**Objetos soportados:**
* `A` - **Luz ambiente**: `A [ratio] [R,G,B]`
  - `A 0.2 255,255,255` → ratio: 0.2, color: blanco
* `C` - **Cámara**: `C [x,y,z] [nx,ny,nz] [FOV]`
  - `C -50,0,20 0,0,1 70` → posición: (-50,0,20), dirección: (0,0,1), FOV: 70°
* `L` - **Luz puntual**: `L [x,y,z] [brillo] [R,G,B]`
  - `L -40,0,30 0.7 255,255,255` → posición: (-40,0,30), brillo: 0.7, color: blanco
* `sp` - **Esfera**: `sp [x,y,z] [diámetro] [R,G,B]`
  - `sp 0,0,20 20 255,0,0` → centro: (0,0,20), diámetro: 20, color: rojo
* `pl` - **Plano**: `pl [x,y,z] [nx,ny,nz] [R,G,B]`
  - `pl 0,0,0 0,1.0,0 255,0,225` → punto: (0,0,0), normal: (0,1,0), color: magenta
* `cy` - **Cilindro**: `cy [x,y,z] [nx,ny,nz] [diámetro] [altura] [R,G,B]`
  - `cy 50,0,20.6 0,0,1.0 14.2 21.42 10,0,255` → centro: (50,0,20.6), eje: (0,0,1), ⌀: 14.2, h: 21.42, color: azul
* `cn` - **Cono (bonus)**: `cn [x,y,z] [nx,ny,nz] [diámetro] [altura] [R,G,B]`
  - `cn 0,0,20.6 0,0,1.0 14.2 21.42 255,255,0` → vértice: (0,0,20.6), eje: (0,0,1), ⌀base: 14.2, h: 21.42, color: amarillo

**Ejemplo de escena bonus con múltiples luces:**
```
A 0.2 255,255,255
C -50,0,20 0,0,1 70
L -40,0,30 0.7 255,255,255
L 40,0,30 0.5 255,100,100
sp 0,0,20 20 255,0,0
pl 0,-10,0 0,1,0 100,100,100
cn 30,0,20 0,0,1 10 15 255,255,0
```


## 🤓 Técnica de Ray Tracing

En **MiniRT**, el ray tracing es la técnica que permite generar la imagen 3D a partir de los objetos y las luces de la escena. Este proceso se realiza en los siguientes pasos:

1. **Construcción del rayo**
   Para cada píxel en la pantalla, se construye un rayo que “viaja” desde la cámara hacia la escena. La dirección de este rayo se calcula a partir de la posición de la cámara, la dirección en la que mira y la posición del píxel en la pantalla.

2. **Pruebas de intersección**
   Cada rayo se verifica para ver si choca con algún objeto de la escena. Se usan funciones específicas según el tipo de objeto: `hit_sphere` para esferas, `hit_plane` para planos, `hit_cone` para conos y `hit_cylinder` para cilindros. Si el rayo no intersecta ningún objeto, el píxel recibe el color del fondo.

3. **Cálculo del color**
   Cuando un rayo intersecta un objeto, se calcula el color del punto de intersección considerando:

   * El material del objeto (color base, reflexión, etc.)
   * Las fuentes de luz de la escena
   * Las sombras, verificando si otros objetos bloquean la luz que llega al punto.
     Esto permite que la imagen final tenga iluminación y profundidad realista.

4. **Renderizado de la imagen**
   El color calculado para cada píxel se utiliza para construir la imagen final en 2D que vemos en pantalla. Repetir este proceso para todos los píxeles genera la escena completa renderizada.

### 🔍 Antialiasing (MSAA 4x)

Técnica que elimina el efecto "dientes de sierra" en los bordes, creando transiciones suaves.

**Problema:** Los píxeles son cuadrados discretos, pero los objetos tienen formas continuas → bordes "pixelados"

**Solución MSAA:**
1. **4 rayos por píxel** en lugar de 1
2. **Sub-píxel sampling** en posiciones específicas:
   ```
   +-------+-------+
   | 0.25  | 0.75  |  ← Offsets dentro del píxel
   | 0.25  | 0.25  |  
   +-------+-------+
   | 0.25  | 0.75  |
   | 0.75  | 0.75  |
   +-------+-------+
   ```
3. **Promedio final:** `color = (c1 + c2 + c3 + c4) / 4`

**Beneficio:** Bordes suaves especialmente en objetos curvos, con costo 4x en rendimiento

### 📐 Intersecciones Ray-Objeto

El corazón del ray tracing: encontrar dónde el rayo toca cada objeto.

**Rayo:** `P(t) = O + t*D` (origen + distancia×dirección)

**Proceso:**
1. Ecuación geométrica del objeto
2. Sustituir rayo en ecuación  
3. Resolver para encontrar `t`
4. Validar `t > 0` (delante de cámara)

#### **Esfera** 
`(P - Centro)² = radio²` → Ecuación cuadrática: `at² + bt + c = 0`
```
a = |D|²
b = 2*D·(O-Centro)  
c = |O-Centro|² - radio²
```

#### **Plano**
`Normal·P + distancia = 0` → Ecuación lineal: `t = -(N·O + d) / (N·D)`

#### **Cilindro con Tapas**
Distancia perpendicular al eje = radio → Proyección 2D + ecuación cuadrática + intersección con tapas circulares

#### **Cono Semi-Infinito con Base (Bonus)**
Ecuación cónica + restricciones de altura + intersección con base circular

#### **Optimizaciones Implementadas**
* **Precision epsilons:** Diferentes valores según contexto
  - `E_NORMAL = 1e-4f` para intersecciones y normales
  - `E_LIGHT = 1e-3f` para sombras (evita self-shadowing)
* **Early exit:** Si discriminante < 0, salir inmediatamente  
* **t_closest tracking:** Solo procesar intersección más cercana
* **Hit context structure:** Optimiza paso de parámetros entre funciones

### 💡 Modelo de Iluminación Phong

El color final se calcula sumando tres componentes de luz:

**Fórmula:** `Color_Final = (Ambiente + Difusa + Especular) × Color_Material`

#### **Implementación Principal:**
```c
  t_vec4	mrt_light_color(t_data *elements, t_hit *hit, t_ray *ray)
  {
    t_vec4		sum;
    t_vec4		contrib;
    t_light		*node;
    t_light		*light;

    sum = (t_vec4){0, 0, 0, 0};
    mrt_set_ambient(elements, hit, &sum);
    node = elements->light;
    while (node)
    {
      light = (t_light *)node;
      contrib = mrt_one_light_color(elements, hit, ray, light);
      sum = vec4_add(sum, contrib);
      node = node->next;
    }
    return (vec4_mul(sum, hit->material->base_color));
  }
```

#### **Componentes:**
1. **Ambiente**: Iluminación base uniforme (`I_a = ambient × ratio`)
2. **Difusa**: Superficie mate según ángulo (`I_d = max(0, N·L) × brightness`)  
3. **Especular**: Reflexión brillante (`I_s = max(0, R·V)^shininess × brightness`)
4. **Sombras**: Test con `shadow_ray` hacia cada luz

**Resultado visual:**
- Ambiente: Color constante en zonas sin luz directa
- Difusa: Graduación suave según orientación 
- Especular: Highlights que siguen el movimiento de cámara
- Sombras: Oclusión realista entre objetos


## 🌟 Renderizado Principal: [mrt_render.c](https://github.com/FreddyRivasVE/miniRT/blob/main/codigo/src/mrt_render.c)

**Función corazón:** `mrt_draw_to_window` - recorre cada píxel y calcula su color

```c
void	mrt_draw_to_window(t_window window, t_data *elements)
{
	t_camera_view	camera;
	t_ray			ray;
	t_vec4			color;
	int				coords[2];

	coords[1] = 0;
	camera = mrt_compute_camera_view(elements->camera, window);
	while (coords[1] < window.height)
	{
		coords[0] = 0;
		while (coords[0] < window.width)
		{
			if (ANTIALIASING == 1)
				color = mrt_render_with_msaa(camera, coords, window, elements);
			else
			{
				ray = mrt_generate_ray(camera, (float)coords[0],
						(float)coords[1], window);
				color = mrt_ray_color(&ray, elements);
			}
			mrt_put_color(color, coords[0], coords[1], window);
			coords[0]++;
		}
		coords[1]++;
	}
}
```

**Flujo:** Cámara → Rayo por píxel → Intersección → Iluminación → Pantalla

## Autores

- [Freddy Rivas](https://github.com/FreddyRivasVE)
- [Brenda Rivera](https://github.com/briveraarg)

## Licencia

Este proyecto es parte del plan de estudios de 42 y no está licenciado para distribución comercial. Uso educativo solamente.

## Recursos

- [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
- [Iluminación y Render](https://www.google.es/books/edition/Iluminaci%C3%B3n_y_Render_Edici%C3%B3n_2007/NpDEPQAACAAJ?hl=es&kptab=overview)
- [Blinn–Phong reflection model](https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model)
- [Using Vector Instructions through Built-in Functions](https://gcc.gnu.org/onlinedocs/gcc/Vector-Extensions.html)