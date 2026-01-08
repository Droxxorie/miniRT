# ERRORS

# ROADMAP
## PHASE 1 : ARCHITECTURE & PERFS
- [x] Ajouter support resolution ? R
- [x] Afficher resolution dans nom fenetre
- [x] Toggle lights & objects
- [x] Cycle cameras
- [x] Multithreading
- [x] Réactiver multi cams & lights
- [x] Modifier usage
- [x] Modifier control message
- [x] Mode sauvegarde (`--save` flag)

## PHASE 2 : PRIMITIVES
- [ ] Disque
- [ ] Triangle
- [ ] Carré/Rectangle
- [ ] Cône
- [ ] Tore (hyperboloid, paraboloid)

## PHASE 3 : OBJETS COMPOSES
- [ ] Cube & Pavé
- [ ] Pyramide base carré ou triangulaire
- [ ] BVH

## PHASE 3.5 : RAYMARCHING
- [ ] Support SDF (mdrrrr)
- [ ] Object SDF simples (Sphere, pavé, Tore)
- [ ] Fractals (Mandelbulb, Julia, autre)

## PHASE 4 : LUMIERE & MAT
- [ ] SUN (Lumière parallèle)
- [ ] Spotlight
- [ ] Texture procedurale (checkboard, rainbow, Sinus)
- [ ] UV Mapping
- [ ] Normal Map / Bump Map
- [ ] Skybox
- [ ] BRDF basique (Lambert & Phong/Blinn-Phong)
- [ ] BRDF avancé (Oren-Nayar & Cook-Torrance)
- [ ] Matériaux :
    - [ ] Choix
    - [ ] Matte/Lambert/Color
    - [ ] Transparent
    - [ ] Plastique (Blinn-Phong)
    - [ ] Miroir (refraction verre/eau/autre)
    - [ ] Texture (UV mapping)

## PHASE 5 : UX et Interactions
- [ ] Rework UX clavier/Souris
- [ ] Ajout facteur de transformation
- [ ] Modifier FOV
- [ ] Touche Reset (toute la scène et objet sélectionné)
- [ ] UI (Objet sélectionné / ID camera / ID lumière / Coordonnées / commandes etc)

## PHASE 6 : POST-PROCESS & QUALITE
- [ ] Tonemapping
- [ ] Filtres (gamma correction, Sepia, B&W)
- [ ] Sobel
- [ ] AA (via Supersampling)

## PHASE 7 : MONTE CARLO & PBR
- [ ] Matériaux PBR
- [ ] Lumière surfacique (quad)
- [ ] Matériaux Emissifs
- [ ] Path Tracing
- [ ] Soft Shadows
- [ ] DOF