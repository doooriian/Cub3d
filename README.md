<br />
<p align="center">
  <a href="https://42.fr/">
    <img src="https://github.com/doooriian/42-Badges/blob/main/42_Logo.png" alt="42 Logo" width="250" height="250">
  </a>

  <h1 align="center">Cub3d</h1>

  <p align="center">
    A 3D raycasting game project from 42 School
    <br /><br />
    <img src="https://github.com/doooriian/42-Badges/blob/main/badges/cub3dm.png" alt="Cub3d Badge" width="150">
  </p>
</p>

<p align="center">
  <img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/doooriian/Cub3d?color=1A237E" />
  <img alt="Code language count" src="https://img.shields.io/github/languages/count/doooriian/Cub3d?color=00BCD4" />
  <img alt="GitHub top language" src="https://img.shields.io/github/languages/top/doooriian/Cub3d?color=7B1FA2" />
  <img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/doooriian/Cub3d?color=D32F2F" />
</p>

---

## ✨ Overview

**Cub3d** is a group of two project at 42 School that implements a basic 3D game engine using raycasting, inspired by classic games like *Wolfenstein 3D*.  
This project tests your skills in graphics programming, coordinate transformations, texture mapping, user input, and scene rendering under constraints.  

The goal is to render a navigable 3D environment from a 2D map, with wall textures, floor and ceiling colors, and reliable player movement.

---

## 📑 Key Features

- **Raycasting Engine**  
  Casts rays to determine wall slices and distances, drawing a 3D perspective from a 2D map layout.

- **Map Parsing**  
  Reads `.cub` map files, validates map layouts (walls closed, valid characters), and extracts textures/colors.

- **Texture Mapping**  
  Applies wall textures, floor and ceiling colors, correct orientation and scaling.

- **Player Movement & Look**  
  Handles keyboard inputs (forward, backward, left, right, rotate) smoothly while checking collisions.

- **Additional rendering features**  
  The bonus build includes extra gameplay and rendering components, including doors and a minimap.
  
---

## 🛠️ Technologies Used

- **[C](https://devdocs.io/c/)** — Core programming language  
- **[MLX (MiniLibX)](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html)** — Graphics and window handling  
- **[Makefile](https://www.gnu.org/software/make/manual/make.html)** — Build system  
- **Mathematics & Linear Algebra** — For raycasting calculations, vector operations

---

## 🚀 How to Build and Run

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

## 📸 Visual Example

A screenshot or short gameplay GIF can be added here to demonstrate the rendering engine. The previous media link was removed because the referenced GIF is not present in the linked repository.

---

## 📚 Resources

- **[Raycasting Theory & Tutorials](https://lodev.org/cgtutor/raycasting.html)**  
- **[MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html)**  
- **[Wolfenstein 3D Engine Explanation](https://permadi.com/1996/05/ray-casting-tutorial/)**  

---

## 📬 Contact

Feel free to reach out or contribute to this project on [GitHub](https://github.com/doooriian)!
