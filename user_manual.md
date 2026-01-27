# miniRT - User Manual

miniRT is a raytracing project developed at 42.
It starts as a classic Whitted-style raytracer (Mandatory) and evolves into a full Physically Based Rendering (PBR) Path Tracer with global illumination (Bonus).

---

## **MANDATORY (Standard Raytracer)**

This section describes the usage of the basic version of the engine.

### **1. Usage**
```./miniRT <scene.rt>```

### 2. Basic Controls
|Key / Action|Description              |
|------------|-------------------------|
-ESC         |Exit the program cleanly.|
|Red Cross   |Close the window.        |

### **3. Scene Format**
The scene file defines basic geometric objects and lighting.

**Unique Entities**
|ID|Parameters       |Description                                         |
|--|-----------------|----------------------------------------------------|
|A |"ratio r,g,b"    |Ambient Light. Intensity [0.0-1.0] and color.       |
|C |pos dir fov      |"Camera. Position, Orientation vector, FOV [0-180]."|
|L |"pos ratio r,g,b"|"Point Light. Position, Brightness ratio, Color."   |

**Objects**
|ID|Parameters                         |Description|
|--|-----------------------------------|-----------|
|sp|"center diameter r,g,b"            |Sphere.    |
|pl|"point normal r,g,b"               |Plane.     |
|cy|"center axis diameter height r,g,b"|Cylinder.  |

## **BONUS (Path Tracer & PBR)**

The bonus version features a robust Path Tracing engine with Next Event Estimation (NEE), PBR materials (Cook-Torrance), fractals, and real-time editing.

### **1. Usage & Arguments**
```./miniRT_bonus <scene.rt> [FLAGS]```

**Flags:**
* ```--save``` : Renders the scene off-screen and saves it to the output/ folder.

* ```--save <filename.bmp>``` : Saves with a specific filename.

* ```--debug <MODE>``` : Launches in specific debug visualization mode.

### **2. Controls & Real-time Editing**

The engine allows real-time navigation and object manipulation.

**General**

* ```ESC``` : Exit program.
* ```ENTER``` : Save screenshot (saved to output/YYYYMMDD_HHMMSS.bmp).
* ```H``` : Print help/controls to the terminal.
* ```I``` : Print info about the selected object/light to the terminal.
* ```R``` : Reset current selection.
* ```SHIFT + R``` : Reset the entire scene (Camera & Objects).

**Render Modes (Num 1-8)**

|Key|Mode   |Description                       |
|---|-------|----------------------------------|
|1  |SHADE  |Final PBR Render (Path Tracing).  |
|2  |NORMAL |Visualize Surface Normals.        |
|3  |AO     |Ambient Occlusion visualization.  |
|4  |DEPTH  |Z-Depth buffer visualization.     |
|5  |SHADOWS|Shadow mask visualization.        |
|6  |LIGHTS |Direct light contribution only.   |
|7  |UV     |Texture coordinates visualization.|
|8  |CHECKER|UV mapping calibration pattern.   |

**Selection & Editing**

* ```Left Click``` : Select object or light under the cursor.
* ```TAB``` : Switch between TRANSLATE and ROTATE modes.
* ```SPACE``` : Cycle selection (Next Object / Next Light).
* ```C / L``` : Explicitly switch control to Camera (C) or Light (L).
* ```T``` : Toggle Visibility (for Objects) or Active State (for Lights).

**Movement (Camera or Selection)**

|Key  |Action                           |
|-----|---------------------------------|
|W / S|Move Forward / Backward (Z-axis).|
|A / D|Move Left / Right (X-axis).      |
|Q / E|Move Up / Down (Y-axis).         |

**Resizing (Selected Object)**
* ```Scroll``` : Resize Height / Main Radius.
* ```SHIFT + Scroll``` : Resize Width / Secondary Radius.
* ```CTRL + Scroll``` : Resize Depth.
* ```ALT + Scroll``` : Resize specific axis (depending on object).

### **3. ```.rt``` Scene Format (Advanced)**

The bonus parser supports global configuration, advanced lights, and complex primitives.

**Global Configuration**

* ```R <width> <height>``` : Window resolution.
* ```SAMPLES <count>``` : Samples per pixel (Enable Pathtracing / Pathracing Quality).
* ```mtllib <file.mtl>``` : Link an external material library.

**Advanced Lights**

* **SUN** : ```SUN <dir> <brightness> <color>``` (Directional Light).
* **SPOT** : ```SPOT <pos> <dir> <cutoff> <brightness> <color>``` (Cone Light).
* **QUAD** : ```QUAD <pos> <dir> <width> <height> <brightness> <color>``` (Area Light).

**Environment**

* **SB** : ```SB <texture.xpm>``` (Skybox texture). If missing, uses procedural sky.

**Extended Primitives**

All objects accept ```-usemtl <MaterialName>``` at the end of the line.
* **con** (Cone): ```con <pos> <axis> <radius> <height> <color>```.
* **rec** (Rectangle): ```rec <center> <normal> <width> <height> <color>```.
* **dis** (Disk): ```dis <center> <normal> <radius> <color>```.
* **tri** (Triangle): ```tri <p1> <p2> <p3> <color>```.
* **tor** (Torus): ```tor <center> <axis> <major_r> <minor_r> <color>```.
* **box** (Box): ```box <center> <axis> <width> <height> <depth> <color>```.

Fractals (SDF Rendering)
* **menger_sponge** : ```menger_sponge <pos> <normal> <size> <scale> <color>```.
* **mandelbulb** : ```mandelbulb <pos> <normal> <size> <power> <color>```.
* **mandelbox** : ```mandelbox <pos> <normal> <size> <slice> <inner_r> <fold> <outer_r> <color>```.
* **julia_set** : ```julia_set <pos> <normal> <size> <quat_xyzw> <cut> <trap> <preset> <color>```.

### **4. ```.mtl``` Material Format (PBR)**
Define complex materials in a separate file.

**Structure**

```
newmtl <MaterialName>
illum <mode>
Kd <r> <g> <b>
...
```

**Parameters**
* **Illumination Models (```illum```) :**
  * ```0``` : Emissive (Light source).
  * ```1``` : Lambert (Matte).
  * ```2``` : Phong.
  * ```3``` : Metal (Conductive).
  * ```4``` : Dielectric (Glass, Water).
  * ```5``` : Oren-Nayar (Realistic rough surface).
  * ```6``` : Cook-Torrance (Full PBR).
* **Properties :**
  * ```Kd``` : Diffuse Color (Albedo).
  * ```Ks``` : Specular Color (or F0 for metals).
  * ```Ke``` : Emissive Color (Light intensity).
  * ```Ns``` : Shininess (Converted to Roughness internally).
  * ```Ni``` : Index of Refraction (IOR).
  * ```Tr``` : Transparency (0=Opaque, 1=Transparent).
  * ```Pm``` : Metallic (0=Plastic, 1=Metal).
  * ```Tf``` : Absorbance (Transmission color).
* **Texture Maps :**
  * ```map_Kd``` : Albedo Map.
  * ```map_Bump``` / ```Bump``` : Normal Map.
  * ```map_Ns``` : Roughness Map.
  * ```map_Pr``` : Metallic Map.
  * ```map_Ke``` : Emission Map.
  * ```map_Ks``` : Specular Map.
* **Procedural :**
  * ```pattern <type>``` : ```checker```, ```rainbow```, ```wave```, ```perlin```, ```marble```.
  * ```uv_scale <value>``` : Scaling factor for UVs.