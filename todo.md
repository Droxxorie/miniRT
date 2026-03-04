# ERRORS / Todo
mesh + .obj
no shadow disk ?
revoir parsing .mtl
modifier readme 42 + git ou fusion des deux
revoir user_manual et potentielement netoyer readme
faire scenes et screen de fractals et autre pour readme

# ROADMAP
## PHASE 1 : ARCHITECTURE & PERFS
- [x] Ajouter support resolution ? R
- [x] Afficher resolution dans nom fenetre
- [x] Toggle lights & objects
- [x] Cycle cameras
- [x] Multithreading
- [x] Rendu par tuiles
- [x] Parcours spiral des tuiles
- [x] Affichage progressif (polling main thread 100ms)
- [x] Surface cache (prepare_surface, albedo/roughness/metallic/f0)
- [x] Optimisation layout structs (padding mémoire)
- [x] Réactiver multi cams & lights
- [x] Modifier usage
- [x] Modifier control message
- [x] Mode sauvegarde (`--save` flag)

## PHASE 2 : PRIMITIVES
- [x] Disque
- [x] Triangle
- [x] Carré/Rectangle
- [x] Tore (hyperboloid, paraboloid)

## PHASE 3 : OBJETS COMPOSES
- [x] Cube & Pavé
- [ ] Pyramide base carré ou triangulaire
- [x] Cône
- [x] BVH
- [x] Occlusion culling
- [x] Back-Face-Culling

## PHASE 3.5 : RAYMARCHING
- [x] Support SDF (mdrrrr)
- [x] Object SDF simples (Sphere, pavé, Tore)
- [x] Fractals :
    - [x] MandelBulb
    - [x] MandelBox
    - [x] Julia (TA MERE)
    - [x] Menger Sponge
- [x] Ambiant Occlusion

## PHASE 4 : LUMIERE & MAT
- [x] SUN (Lumière parallèle)
- [x] Spotlight
- [x] Quad Light
- [x] Texture procedurale (checkboard, rainbow, Sinus, Perlin)
- [x] Normal Map / Bump Map
- [x] Skybox
- [x] BRDF basique :
    - [x] Lambert
    - [x] Phong/Blinn-Phong
- [x] BRDF avancé :
    - [x] Oren-Nayar
    - [x] Cook-Torrance
- [x] Matériaux :
    - [x] Choix
    - [x] Matte/Lambert/Color
    - [x] Transparent + Beer Lambert + mat
    - [x] Plastique (Blinn-Phong)
    - [x] Miroir (refraction verre/eau/autre)
    - [x] Texture (UV mapping)

## PHASE 5 : UX et Interactions
- [ ] Rework UX clavier/Souris
- [x] Ajout facteur de transformation
- [x] Modifier FOV
- [x] Touche Reset (toute la scène et objet sélectionné)
- [x] UI (Objet sélectionné / ID camera / ID lumière / Coordonnées / commandes etc)

## PHASE 6 : POST-PROCESS & QUALITE
- [x] Tonemapping & HDR
- [ ] Filtres (gamma correction, Sepia, B&W)
- [ ] Sobel
- [x] AA (via Supersampling)
- [x] Nearest Neighbor

## PHASE 7 : MONTE CARLO & PBR
- [x] Matériaux PBR
- [x] Lumière surfacique (quad)
- [x] Matériaux Emissifs
- [x] Path Tracing
- [x] Multi importance sampling
- [x] Soft Shadows
- [x] Transmittance shadow rays (verre transparent)
- [ ] DOF