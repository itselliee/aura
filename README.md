<img src="logo.png" alt="logo" width="300"/>

## Small little OpenGL game engine

[![Human-Crafted Software](handcrafted-bronze.svg)](https://github.com/LeonardNJU/human-crafted-software)

> [!IMPORTANT]
> This software is not ready for production.

> [!IMPORTANT]
> This is a **engine** not a game **editor**, look for the official editor [here](https://github.com/itselliee/aura-editor).

This is a full new experience for me, so expect bugs, once this is properly stable on OGL, I'm moving the rendering system to Vulkan!

## Compilation

### Recommended specifications for Aura Engine

- CPU from 2010 or newer
- Atleast 6GB off RAM
- 5GB available space (preferably on a SSD)
- Linux (Ubuntu 18.04, Fedora 28 or a up-to-date rolling release distribution) or MacOS Big Sur **(Windows is not recommended)**
- GPU that supports OpenGL 4.5 (or 4.1 on MacOS)
- Patience, if you don't have a processor with 6 or more cores.

### Compilation on Arch Linux (Tested)

First, update you system with `sudo pacman -Syu` or `yay/paru`

After this is done and you have rebooted your system, run the `compile_linux.sh`
file, and it should output into "out".

### Compilation on MacOS 27 Golden Gate (Tested)

First, check if there are any updates available

Then, run `compile_osx.sh`, this should do the same as Linux,
and should output into the "out" directory.
