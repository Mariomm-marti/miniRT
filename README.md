# miniRT
This project introduces the following topics:
- Intermediate raytracing protocol implementation (visibility part)
- Image saving in a non-compressed format (BMP)
- Deep error management
- Basic raytracing protocol implementation (shading part, by using Lambert law and other light properties)

## Before explaining how the project works, how to compile and run it
### On MacOS outside the 42 Network
You will have to make some changes to make sure MiniLibX can be properly used.
The way I recommend installing it is by compiling MiniLibX from sources (which can be found on intra project page, or by using this instance [minilibx](https://github.com/ttshivhula/minilibx)) 
and copying `mlx.h` into `/usr/local/include/mlx.h` and `libmlx.a` to `/usr/local/lib/libmlx.a`

Then proceed the same way as if you were on a 42 iMac

### On 42 Network campus iMacs
To make it work on 42 iMacs, you need to clone somewhere (to make it easier, under `srcs/` is a good option) both [libft](https://github.com/Mariomm-marti/libft) and [get_next_line](https://github.com/Mariomm-marti/get_next_line) as they are required dependencies.

The following step is to compile it, you can do it with a simple `make`, or if you cloned the dependencies somewhere that is not under `srcs`, using `make MINIRT_LIBFT=../relative/path/to/libft MINIRT_GNL=/absolute/paths/work/too` will do the job.

An output file called `miniRT` will be produced (otherwise message me, `mmartin-` on Slack).

### How to run miniRT
Program usage is `./miniRT <rt_file> [--save]`. If `--save` is not specified,
a window will open with the rendered content of the file. If `--save` is specified,
a `screenshot.bmp` image will be generated.

The structure of a `.rt` file is as follow:
| Parameter                     | Arguments                                                                                              | Usage example                       |
|-------------------------------|--------------------------------------------------------------------------------------------------------|-------------------------------------|
| R<resolution parameter>       | X[width of window] Y[height of window]                                                                 | R 1920 1080                         |
| A<ambient lighting parameter> | R[ratio of ambient light] C[color of ambient light]                                                    | A 0.01 127,255,0                    |
| c<camera or viewpoint>        | O[x,y,z coordinates] D[x,y,z normalized direction] F[field of view]                                    | C 0,0,-40 0,0,1 80                  |
| l<point of light>             | O[x,y,z coordinates] R[ratio of light] C[color of light]                                               | l 0,100,0 1.0 255,0,0               |
| sp<sphere>                    | O[x,y,z coordinates] D[diameter of sphere] C[color of sphere]                                          | sp 0,40,0 19 255,255,255            |
| pl<infinite plane>            | O[x,y,z coordinates] D[x,y,z normalized direction] C[color of plane]                                   | pl 0,15,0 0,1,0 255,0,0             |
| sq<square>                    | O[x,y,z coordinates] D[x,y,z normalized direction] C[color of square]                                  | sq 0,0,0 0,0,1 255,0,255            |
| cy<cylinder>                  | O[x,y,z coordinates] D[x,y,z normalized direction] D[diameter of cyl] H[height of cyl] C[color of cyl] | cy 0,0,0 0,1,1 8 30 255,0,0         |
| tr<triangle>                  | A[x,y,z vertex 1] B[x,y,z vertex 2] C[x,y,z vertex3] C[color of triangle]                              | tr 0,20,10 15,-4,-10 12,0,0 255,0,0 |

## How the project work
First of all, I had to learn maths from scratch. At the start of the project I didn't know nor understand any of linear algebra or trigonometry.
For this matter, I used 3blue1brown Linear Algebra resources.

Talking about resources, the list for everything I've used to learn about this topic (and even rasterization and similar topics):
- [Essence of linear algebra, by 3blue1brown](https://www.youtube.com/playlist?list=PLZHQObOWTQDPD3MizzM2xVFitgF8hE_ab)
- [Geometry, by Scratchapixel](https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/geometry)
- [Fast, Minimum Storage Ray/Triangle Intersection, by Tomas Möller and Ben Trumbore 1997](http://www.graphics.cornell.edu/pubs/1997/MT97.pdf)
- [Geometric equation for sphere and plane, By Scratchapixel](https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes)
- [Ray-cylinder intersection, by Denis Zorin 1999](https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes)

The project consists of four parts:
- Argument validation and file reading and validation
- Visibility part by ray-geometry intersection
- Shading part, using Lambert law and intersection between objects
- Saving image to BMP or displaying it to window

## Score
This project took me too long because of the mathematic base I had to adquire. It will be greatly improved over time, but as I cannot submit it 
again it will remain with 100/100 (with bonus it would be 100/115).

![Visual proof of success](https://i.imgur.com/cShTiUa.png)
