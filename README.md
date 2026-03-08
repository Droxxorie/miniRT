*This project has been created as part of the 42 curriculum by eraad, jehubert.*

![Banner](output/green_glass.bmp)

# miniRT - Raytracing Engine

## Description
**miniRT** is a hybrid rendering engine developed in C using the **MinilibX**. Designed as a comprehensive introduction to computer-generated imagery, this project goes far beyond standard requirements. The engine seamlessly combines **Analytic Raytracing** (Whitted-style), **Path Tracing** (Monte Carlo integration for global illumination), and **Raymarching** (Signed Distance Functions) to render highly realistic 3D scenes with Physically Based Rendering (PBR) materials.

## Key Features & Technologies

### Architecture & Performance
* **Multi-threading**: Optimized tile-based rendering with a spiral path algorithm, utilizing all available CPU cores.
* **Acceleration Structures**: Bounding Volume Hierarchy (BVH) for fast ray-object intersections.
* **Culling**: Implements Back-Face Culling and Occlusion Culling.
* **Progressive Rendering**: Real-time tile visualization with intermediate updates.

### Lighting & Physically Based Rendering (PBR)
* **BRDF Models**: Supports Lambert (diffuse), Oren-Nayar (rough surfaces), Cook-Torrance (microfacet metallic/plastic), and Dielectric (refraction, glass, water).
* **Global Illumination**: Fully implemented Path Tracing with Color Bleeding.
* **Advanced Light Sampling**: Next Event Estimation (NEE) and Multiple Importance Sampling (MIS) using the power heuristic to combine light and BSDF sampling efficiently.
* **Volumetrics**: Volumetric absorption for transparent materials using the Beer-Lambert law.
* **Light Types**: Point lights, Sun (directional), Spotlights, Quad (area) lights, and Emissive materials.
* **Shadows & AO**: Physically accurate soft shadows and Ambient Occlusion.

### Geometry & SDF Raymarching
* **Analytic Primitives**: Spheres, planes, cylinders, cones, boxes, rectangles, disks, triangles, and toruses.
* **Mesh Loading**: Full support for `.obj` files with automatic triangulation and BVH integration.
* **3D Fractals**: Signed Distance Functions (SDF) implementation rendering complex mathematical structures: Mandelbulb, Mandelbox, 4D Julia Set, and Menger Sponge.

### Textures & Post-Processing
* **Material Mapping**: Full `.mtl` support with diffuse, normal (bump), roughness, metallic, emission, and specular maps (via `.xpm` textures).
* **Procedural Textures**: Checkerboard, Perlin noise, sine waves, and rainbow patterns.
* **Post-Process Filters**: Anti-Aliasing (SSAA), ACES Tone Mapping, Gaussian Blur, Sobel (edge detection), Sepia, Black & White, Sharpen, Contrast, and Saturation adjustments.

## Instructions

### Compilation
The graphics engine relies on MinilibX, which is automatically compiled.
```bash
# Standard Raytracer (Mandatory part)
make

# Advanced Path Tracer with PBR, OBJ, and SDFs (Bonus part)
make bonus
```

### Execution
```bash
./miniRT scene.rt
./miniRT_bonus scene_bonus.rt
```

**For comprehensive details on how to use the engine, keyboard/mouse controls, and how to write `.rt` and `.mtl` files, please consult the [User Manual](user_manual.md).**

## Gallery

### PBR & Materials
![Cornell Box PBR](output/cornell_mirrors_2K.bmp)
*Physically Based Rendering in a Cornell Box.*

![Glass Refraction](output/green_glass.bmp)
*Dielectric materials with Beer-Lambert absorption.*

![Earth](output/20260128_182557.bmp)
*Textured sphere with normal, emission, and roughness maps.*

### Fractals & Raymarching
![Mandelbulb](output/fractals/20260114_184545.bmp)
*SDF Raymarching: Zoom on Mandelbulb.*

![Mandelbox](output/fractals/20260114_222948.bmp)
*SDF Raymarching: Mandelbox.*

![Julia 4D](output/fractals/20260118_131248.bmp)
*SDF Raymarching: Exploration of the 4D Julia Set.*

### Path Tracing
![Cornell Mirrors](output/pathtrace_cornell_box_mirrors.bmp)
*Path Tracing with mirrors.*

![Classic Path Tracing](output/Cornell_box_5000.bmp)
*5000 samples Path Tracing.*

### Bloopers & Fails
*Building a rendering engine is a journey filled with artistic bugs!*

![Broken Normals](output/broken.bmp)
*The Broken Normals.*

![AABB Issue](output/aabb_issue.bmp)
*Entering the Matrix (AABB issues).*

![Black Hole](output/black_hole.bmp)
*The Black Hole incident.*

![SDF Broken](output/borken_sdf.bmp)
*Broken SDF computations.*

## Resources & AI Usage

### Resources
* **Peter Shirley** - *Ray Tracing in One Weekend* book series.
* **Inigo Quilez** - Articles and mathematical foundations for Signed Distance Functions (SDF) and fractals.
* **Scratchapixel** - Theoretical and mathematical foundations for computer graphics and raytracing.
* **My brother** - Incredible source of inspiration since 1999 (Reference: *ISIR Project*).

### AI Usage
During the development of this project, Artificial Intelligence tools were utilized as assistants for several specific tasks:
* **Refactoring**: Assisting with refactoring complex functions to adhere strictly to the 42 Norm (max 25 lines, max 5 variables, explicit naming conventions).
* **Research**: Quickly finding exact mathematical formulas and best practices for specific graphic algorithms (e.g., BRDF models, MIS weights).
* **Testing**: Generating complex, edge-case `.rt` scenes to deeply test the engine's limits and robustness.
* **Documentation**: Structuring and formatting this README and the detailed User Manual.
* **Problem Solving**: Identifying the origins of unexpected rendering artifacts, eliminating flawed implementation ideas, and debugging logic errors during the Path Tracing implementation.
