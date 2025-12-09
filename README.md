## 📖 About

**cub3D** is a 42 school project that recreates the world-famous Wolfenstein 3D game, the first FPS ever created. This project explores ray-casting principles to create a realistic 3D graphical representation of a maze from a first-person perspective.

### Features

#### Mandatory
- ✅ Realistic 3D maze rendering using ray-casting
- ✅ Different wall textures for each cardinal direction (North, South, East, West)
- ✅ Floor and ceiling color customization
- ✅ Smooth player movement (W, A, S, D keys)
- ✅ Rotation controls (Arrow keys)
- ✅ Map validation and error handling
- ✅ .cub file parser for scene configuration

#### Bonus
- 🎮 Mouse rotation controls
- 🖱️ Hidden cursor for immersive FPS experience
- 🎯 Wall collision detection
- ⌨️ Dual key support (WASD + Arrow keys)
- 🗺️ Minimap system

---

## 🚀 Getting Started

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/BenGallagh42/cub3D.git
   cd cub3D
   ```

2. **Compile the project**
   ```bash
   make
   ```

3. **Run the game**
   ```bash
   ./cub3D /assets/maps/valid/{choose_a_map_in_the_list}.cub
   ```

### Available Make Commands

```bash
make          # Compile the project
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Recompile the project from scratch
make norm     # Run a norminette check in the Includes/, src/ and libt/ folders
```

---

## 🎮 How to Play

### Controls

| Key | Action |
|-----|--------|
| **W** | Move forward |
| **S** | Move backward |
| **A** | Rotate left |
| **D** | Rotate right |
| **←** | Rotate left (arrow key) |
| **→** | Rotate right (arrow key) |
| **Mouse** | Look around (bonus) |
| **ESC** | Exit game |

---

## 🗺️ Map Configuration

Maps are defined in `.cub` files with the following format:

### Example Map File

```
NO ./textures/north_wall.png
SO ./textures/south_wall.png
WE ./textures/west_wall.png
EA ./textures/east_wall.png

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

### Map Elements

| Symbol | Meaning |
|--------|---------|
| `0` | Empty space (floor) |
| `1` | Wall |
| `N` | Player start position (facing North) |
| `S` | Player start position (facing South) |
| `E` | Player start position (facing East) |
| `W` | Player start position (facing West) |
| ` ` | Void (outside map) |

### Configuration Parameters

| Parameter | Description | Format |
|-----------|-------------|--------|
| `NO` | North wall texture | `NO ./path/to/texture.png` |
| `SO` | South wall texture | `SO ./path/to/texture.png` |
| `WE` | West wall texture | `WE ./path/to/texture.png` |
| `EA` | East wall texture | `EA ./path/to/texture.png` |
| `F` | Floor color | `F R,G,B` (0-255) |
| `C` | Ceiling color | `C R,G,B` (0-255) |

### Map Rules

- ✅ Map must be surrounded by walls (`1`)
- ✅ Exactly one player start position required (`N`, `S`, `E`, or `W`)
- ✅ Map must be last element in `.cub` file
- ✅ All textures must be valid `.png` or `.xpm` files
- ✅ RGB values must be in range 0-255

---

## 📁 Project Structure

```
cub3D/
│
├── inc/
│   └── cub3d.h                 # Main header file with structures and prototypes
│
├── src/
│   ├── main.c                  # Entry point and initialization
│   │
│   ├── utils/
│   │   ├── error.c             # Error handling and cleanup
│   │   └── free.c              # Memory management utilities
│   │
│   ├── parser/
│   │   ├── parser.c            # Main parsing logic
│   │   ├── parser_utils.c      # Parsing helper functions
│   │   ├── parse_textures.c    # Texture path parsing
│   │   ├── parse_colors.c      # Floor/ceiling color parsing
│   │   ├── parse_map.c         # Map grid parsing
│   │   ├── parse_map_utils.c   # Map validation helpers
│   │   └── validate_map.c      # Map validation and flood fill
│   │
│   ├── render/
│   │   ├── init_mlx.c          # MLX initialization
│   │   ├── init_player.c       # Player setup
│   │   ├── load_textures.c     # Texture loading
│   │   ├── loop.c              # Main game loop
│   │   ├── draw.c              # Drawing functions
│   │   ├── raycaster.c         # Ray-casting algorithm
│   │   └── raycaster2.c        # Ray-casting calculations
│   │
│   └── hooks/
│       ├── key_hook.c          # Keyboard input handling
│       ├── movement.c          # Player movement
│       └── rotate.c            # Player rotation (keyboard + mouse)
│
├── libft/                      # Custom C library
│   ├── src/
│   ├── inc/
│   └── Makefile
│
├── MLX42/                      # Graphics library
│   ├── include/
│   ├── src/
│   └── Makefile
│
├── assets/
│   ├── maps/
│   │   ├── valid/              # Valid map files
│   │   └── invalid/            # Invalid map files for testing
│   │
│   └── textures/               # Wall texture files
│
├── Makefile                    # Build configuration
└── README.md                   # This file
```

---

## 🛠️ Technical Details

### Ray-Casting Algorithm

The project uses the **DDA (Digital Differential Analysis)** algorithm to cast rays and detect wall intersections:

1. **Ray Direction Calculation**: For each vertical screen stripe, calculate the ray direction based on player position and camera plane
2. **DDA Algorithm**: Step through the map grid until hitting a wall
3. **Wall Distance**: Calculate perpendicular distance to avoid fish-eye effect
4. **Wall Height**: Compute wall slice height based on distance
5. **Texture Mapping**: Sample the appropriate texture based on wall orientation and hit position

### Performance Optimizations

- Efficient pixel-by-pixel rendering using MLX42
- Optimized DDA algorithm for fast wall detection
- Pre-calculated trigonometric values for rotation
- Direct memory buffer manipulation for drawing

---

### Error Handling
The program validates:
- ✅ File extension (`.cub`)
- ✅ File readability
- ✅ Texture file existence and format
- ✅ Color values (0-255)
- ✅ Map structure (walls, player position)
- ✅ Map closure (flood fill algorithm)
