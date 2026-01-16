# ERRORS / Todo
Ajouter tests save
fusioner test bonus et mandatory
rajouter scaling factor au resize
rajouter log transform ?
peut etre revoir rotate/translate dans mandatory et clean tt ç&
kd-tree
shift r marche plus ...
camera cassée rotation z
mesh + .obj
add syntax messages for all shapes
fractals 2D
fractals 3D bizzare avec sdf (si déplacé agit bizzarement)->désactivé resize/rotate/translate ? plus de détails ?
ajouter plus de fractals 3D ?
mode de save meilleur qualité ?
shift + r rescale la scene


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
- [x] Fractals (Mandelbulb, Julia, autre)
- [x] Ambiant Occlusion

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
- [x] Modifier FOV
- [x] Touche Reset (toute la scène et objet sélectionné)
- [x] UI (Objet sélectionné / ID camera / ID lumière / Coordonnées / commandes etc)

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
- [x] Soft Shadows
- [ ] DOF