# miniRT - User Manual

This document provides complete instructions on how to use the **miniRT** engine, including controls, command-line arguments, and the syntax for scene (`.rt`) and material (`.mtl`) files.

---

## 1. Usage & Command-Line Arguments

The project provides two executables: `miniRT` (Mandatory, basic Whitted-style raytracer) and `miniRT_bonus` (Advanced Path Tracer with SDFs, PBR, and OBJ support).

| Mode | Command | Description |
|---|---|---|
| **Mandatory** | `./miniRT <scene.rt>` | Runs the standard raytracer. |
| **Bonus** | `./miniRT_bonus <scene_bonus.rt> [OPTIONS]` | Runs the advanced path tracer. |

### Bonus Options
| Flag | Example | Description |
|---|---|---|
| `--save` | `--save` or `--save custom.bmp` | Renders the scene completely off-screen and saves it to a `.bmp` file (default: `output/output.bmp`). |
| `--debug` | `--debug NORMAL` | Launches the engine with a specific debug visualization mode active. |

---

## 2. Controls (Bonus Mode)

The bonus engine allows for real-time navigation and object manipulation.

### Keyboard Controls
| Key | Action |
|---|---|
| **W / S** (or **Z / S**) | Move Camera/Object Forward / Backward (Z-axis) |
| **A / D** (or **Q / D**) | Move Camera/Object Left / Right (X-axis) |
| **Q / E** (or **A / E**) | Move Camera/Object Up / Down (Y-axis) |
| **Arrow Keys** | Look around (Camera) / Rotate Object |
| **TAB** | Switch between **TRANSLATE** and **ROTATE** manipulation modes |
| **SPACE** | Cycle selection to the next object or light |
| **C** | Explicitly select the active Camera |
| **L** | Explicitly select the first Light |
| **I** | Print info about the currently selected object/camera/light in the terminal |
| **T** | Toggle visibility of the selected object / active state of the light |
| **R** | Reset transformations of the currently selected element |
| **SHIFT + R** | Reset the entire scene (Camera and all objects) |
| **ENTER** | Save a screenshot of the current render to `output/YYYYMMDD_HHMMSS.bmp` |
| **H** | Print this help/controls menu to the terminal |
| **ESC** | Exit the program cleanly |

### Mouse Controls
| Action | Context | Effect |
|---|---|---|
| **Left Click** | Global | Select the object or light under the cursor (Raycasting) |
| **Scroll Wheel** | Camera | Adjust the **FOV** (Field of View) |
| **Scroll Wheel** | Object | Resize uniformly (Scale / Main Radius / Height) |
| **SHIFT + Scroll** | Object | Resize Width / Secondary Radius |
| **CTRL + Scroll** | Object | Resize Depth |
| **ALT + Scroll** | Object | Resize a specific secondary axis depending on the object type |

### Debug & Render Modes (Keys 1-8)
You can instantly switch the rendering pipeline to inspect the scene data.

| Key | Mode | Description |
|---|---|---|
| **1** | `SHADE` | Final PBR Render (Path Tracing / Default). |
| **2** | `NORMAL` | Visualize Surface Normals (XYZ mapped to RGB). |
| **3** | `AO` | Ambient Occlusion visualization. |
| **4** | `DEPTH` | Z-Depth buffer visualization. |
| **5** | `SHADOWS` | Shadow mask visualization. |
| **6** | `LIGHTS` | Direct light contribution only (no textures). |
| **7** | `UV` | Texture coordinates visualization (u, v). |
| **8** | `CHECKER` | Applies a UV mapping calibration pattern to all objects. |

---

## 3. Scene Format (`.rt`)

The scene file defines the environment, cameras, lights, and objects. Each element is defined on a single line starting with a specific identifier.

### Global Settings & Environment
| ID | Syntax | Description |
|---|---|---|
| **R** | `R <width> <height>` | Window resolution (Bonus only). |
| **A** | `A <ratio> <r,g,b>` | Ambient lighting intensity [0.0-1.0] and color. |
| **C** | `C <x,y,z> <dx,dy,dz> <fov>` | Camera position, orientation vector, and FOV [0-180]. |
| **SAMPLES** | `SAMPLES <count>` | Rays per pixel for Path Tracing quality (Bonus). |
| **AA** | `AA <count>` | Anti-Aliasing level for standard raytracing. |
| **SB** | `SB <texture.xpm>` | Skybox texture (uses procedural sky if omitted). |
| **mtllib** | `mtllib <file.mtl>` | Link an external Material Library for PBR. |
| **FILTER** | `FILTER <TYPE> [args]` | Post-process filters: `SOBEL`, `BNW`, `SEPIA`, `GAUSSIAN <radius>`, `SHARPEN <strength>`, `CONTRAST <factor>`, `SATURATION <factor>`. |

### Lights
| ID | Syntax | Description |
|---|---|---|
| **L** | `L <x,y,z> <ratio> <r,g,b>` | Standard Point Light. |
| **SUN** | `SUN <dx,dy,dz> <ratio> <r,g,b>` | Directional Light (infinite distance). |
| **SPOT** | `SPOT <x,y,z> <dx,dy,dz> <angle> <ratio> <r,g,b>` | Spotlight with a cutoff angle. |
| **QUAD** | `QUAD <x,y,z> <dx,dy,dz> <width> <height> <ratio> <r,g,b>` | Area Light (emits soft shadows in path tracing). |

### Analytic Objects
*Bonus: Append `-usemtl <MaterialName>` at the end of any object line to apply a material from the `.mtl` file.*

| ID | Syntax | Description |
|---|---|---|
| **sp** | `sp <x,y,z> <diameter> <r,g,b>` | Sphere. |
| **pl** | `pl <x,y,z> <nx,ny,nz> <r,g,b>` | Infinite Plane. |
| **cy** | `cy <x,y,z> <dx,dy,dz> <diameter> <height> <r,g,b>` | Cylinder. |
| **con** | `con <x,y,z> <dx,dy,dz> <diameter> <height> <r,g,b>` | Cone. |
| **box** | `box <x,y,z> <dx,dy,dz> <width> <height> <depth> <r,g,b>` | 3D Box. |
| **rec** | `rec <x,y,z> <nx,ny,nz> <width> <height> <r,g,b>` | 2D Rectangle. |
| **dis** | `dis <x,y,z> <nx,ny,nz> <diameter> <r,g,b>` | 2D Disk. |
| **tri** | `tri <p1_x,y,z> <p2_x,y,z> <p3_x,y,z> <r,g,b>` | Triangle. |
| **tor** | `tor <x,y,z> <nx,ny,nz> <major_r> <minor_r> <r,g,b>` | Torus. |

### Meshes & Fractals (Bonus)
| ID | Syntax | Description |
|---|---|---|
| **obj** | `obj <file.obj> <x,y,z> <dx,dy,dz> <scale> <r,g,b> [-usemtl <Mat>]` | Load a 3D Mesh. The `.obj` file is resolved relative to the `.rt` file's directory. |
| **mandelbulb** | `mandelbulb <x,y,z> <nx,ny,nz> <size> <power> <r,g,b>` | 3D Mandelbulb Fractal. |
| **mandelbox** | `mandelbox <x,y,z> <nx,ny,nz> <size> <slice> <in_r> <fold> <out_r> <r,g,b>` | 3D Mandelbox Fractal. |
| **menger_sponge**| `menger_sponge <x,y,z> <nx,ny,nz> <size> <scale> <r,g,b>` | Menger Sponge Fractal. |
| **julia_set** | `julia_set <x,y,z> <nx,ny,nz> <size> <qx,qy,qz,qw> <cut> <trap> <preset> <r,g,b>`| 4D Julia Set slice. |

---

## 4. Material Format (`.mtl`)

Linked via the `mtllib` directive, this file defines reusable PBR materials.

### Basic Structure
```text
newmtl <MaterialName>
illum <mode>
Kd <r> <g> <b>
...
```

### Parameters
| Parameter | Values / Syntax | Description |
|---|---|---|
| **illum** | `0` to `6` | Illumination model (see below). |
| **Kd** | `R G B` [0.0 - 1.0] | Diffuse Color / Albedo. |
| **Ks** | `R G B` [0.0 - 1.0] | Specular Color (or F0 reflectance for metals). |
| **Ke** | `R G B` [0.0 - infinity] | Emissive Color (Light intensity). |
| **Ns** | Float | Shininess (Automatically converted to Roughness internally). |
| **Ni** | Float | Index of Refraction (IOR) for dielectrics (e.g., Glass = 1.5). |
| **Tr** | `0.0` to `1.0` | Transparency (`0` = Opaque, `1` = Transparent). |
| **Pm** | `0.0` or `1.0` | Metallic factor (`0` = Plastic/Dielectric, `1` = Metal). |
| **Tf** | `R G B` [0.0 - 1.0] | Absorbance / Transmission color for Beer-Lambert volumetric absorption. |

### Illumination Models (`illum`)
| ID | Model | Best For |
|---|---|---|
| `0` | **Emissive** | Light sources, glowing objects (Neon, LEDs). |
| `1` | **Lambert** | Perfect matte, perfectly diffuse surfaces. |
| `2` | **Phong** | Basic glossy surfaces (legacy CGI look). |
| `3` | **Metal** | Conductive materials (Gold, Silver, Copper). |
| `4` | **Dielectric** | Refractive materials (Glass, Water, Diamond). |
| `5` | **Oren-Nayar** | Realistic rough diffuse surfaces (Clay, Sand, Moon surface). |
| `6` | **Cook-Torrance** | Full PBR microfacet model (Realistic plastics, rough metals). |

### Textures & Procedurals
| Directive | Syntax | Description |
|---|---|---|
| **map_Kd** | `map_Kd <file.xpm>` | Albedo/Color Map. |
| **Bump** | `Bump <file.xpm>` | Normal Map (also accepts `map_Bump`). |
| **map_Ns** | `map_Ns <file.xpm>` | Roughness Map. |
| **map_Pr** | `map_Pr <file.xpm>` | Metallic Map. |
| **map_Ke** | `map_Ke <file.xpm>` | Emission Map. |
| **map_Ks** | `map_Ks <file.xpm>` | Specular Map. |
| **pattern** | `pattern <type>` | Procedural texture: `checker`, `rainbow`, `wave`, `perlin`, `marble`. |
| **uv_scale** | `uv_scale <float>` | Scaling multiplier for UV coordinates. |
