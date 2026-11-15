<div align="center">

<a href="https://42.fr/"><img src="https://raw.githubusercontent.com/doooriian/42-Badges/main/badges/cub3dm.png" width="125" alt="Cub3d 42 project badge" /></a>

# Cub3d

**3D raycasting engine · Linux**

<img src="https://img.shields.io/badge/42%20School-Project-7C3AED?style=flat-square" alt="42 School project" />

</div>

---

## 🔎 Overview

**Cub3d** is a group of two project at 42 School that implements a basic 3D game engine using raycasting, inspired by classic games like *Wolfenstein 3D*.  
This project tests your skills in graphics programming, coordinate transformations, texture mapping, user input, and scene rendering under constraints.  

The goal is to create a navigable 3D environment using raycasting, wall textures, and floor/ceiling colors while handling player movement and collisions.

---

## ✨ Key Features

- **Raycasting Engine**  
  Casts rays to determine wall slices and distances, drawing a 3D perspective from a 2D map layout.

- **Map Parsing**  
  Reads `.cub` map files, validates map layouts (walls closed, valid characters), and extracts textures/colors.

- **Texture Mapping**  
  Applies wall textures, floor and ceiling colors, correct orientation and scaling.

- **Player Movement & Look**  
  Handles keyboard inputs (forward, backward, left, right, rotate) smoothly while checking collisions.

- **Bonus Features**  
  Additional doors, mouse controls and a minimap are implemented in the bonus sources.
  
---

## 🛠️ Technologies Used

- **[C](https://devdocs.io/c/)** — Core programming language  
- **[MLX (MiniLibX)](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html)** — Graphics and window handling  
- **[Makefile](https://www.gnu.org/software/make/manual/make.html)** — Build system  
- **Mathematics & Linear Algebra** — For raycasting calculations, vector operations

---

## 🚀 How to Build and Run

**Platform:** Linux with X11 and the Linux MiniLibX. This project is not configured to run natively on macOS.

Clone and compile:

```bash
git clone git@github.com:doooriian/Cub3d.git
cd Cub3d
make
```

Run the program with a map file:

```bash
./cub3D maps/official.cub
```

Controls during gameplay:
- Move: **W**, **A**, **S**, **D**  
- Rotate / Turn: **Left / Right arrows OR pressing left mouse click and dragging**  
- Exit: **ESC**

To clean and rebuild:

```bash
make clean
make fclean
make re
```

---

## 🧪 Testing

Tested with:
- Multiple `.cub` map files (simple and complex)  
- Edge cases on map boundaries and invalid inputs  
- Texture alignment and scaling  
- Collision detection with walls  
- Performance consistency (frame rendering, no flickering)


---

## 📚 Resources

- **[Raycasting Theory & Tutorials](https://lodev.org/cgtutor/raycasting.html)**  
- **[MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html)**  
- **[Wolfenstein 3D Engine Explanation](https://permadi.com/1996/05/ray-casting-tutorial/)**  

---

## 📬 Contact

Feel free to reach out or contribute to this project on [GitHub](https://github.com/doooriian)!
