<div align="center">

<a href="https://42.fr/"><img src="https://raw.githubusercontent.com/doooriian/42-Badges/main/badges/cub3dm.png" alt="Cub3d 42 badge" width="125" /></a>

# Cub3d

**42 School · 🎮 Software engineering project**

<img src="https://img.shields.io/badge/42_Project-C%20%7C%20Raycasting-7C3AED?style=flat-square" alt="Cub3d technology" />
<img src="https://img.shields.io/badge/Documentation-Project_Overview-334155?style=flat-square" alt="Project documentation" />

</div>

---

A 3D rendering engine built in C as a two-person project, using raycasting to display a navigable scene from a 2D map.


---

## 🔎 Overview

Cub3d explores the foundations of real-time 3D rendering: projecting walls from a 2D layout, loading textures, and handling player movement and collisions.


---

## ✨ Features

- Raycasting-based wall rendering and perspective
- Parsing and validation of `.cub` maps
- Wall textures, floor and ceiling colors
- Player movement, rotation and collision handling
- Bonus implementation with doors, mouse interaction and minimap


---

## 🧩 Technical approach

The code separates map/configuration parsing, raycasting, wall rendering, input management and game state. The bonus code lives in `srcs_bonus/`.

> **Tech stack** · C · MiniLibX (Linux) · X11 · Make · Geometry.


---

## 🚀 Build and usage

**Platform:** Linux with X11. This repository uses the Linux MiniLibX and is **not configured to build or run natively on macOS**.

Prerequisites include a C compiler, Make, X11 development libraries and the dependencies needed by MiniLibX.

```bash
git clone https://github.com/doooriian/Cub3d.git
cd Cub3d
make
./cub3D maps/official.cub
```

To build the bonus version:

```bash
make bonus
./cub3D_bonus maps/official.cub
```

Use `W`, `A`, `S`, `D` for movement, arrow keys to rotate and `Esc` to exit. The bonus includes additional mouse input.


---

## 🧪 Verification

The repository contains multiple `.cub` maps suitable for checking different scene layouts and input validation. No automated CI test suite is included; run the binary in a compatible Linux graphical session.


---

## ⚠️ Notes and limitations

- Linux/X11 only in its current configuration; native macOS support is not included
- The rendering relies on raycasting rather than a general-purpose polygonal 3D engine
- Created collaboratively by two 42 students

---

<div align="center">

<sub>Part of the <a href="https://42.fr/">42 curriculum</a> · <a href="https://github.com/doooriian">Back to my GitHub profile</a></sub>

</div>
