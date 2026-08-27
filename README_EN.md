# Zelda64Recomp Simplified Chinese Enhanced Edition

[简体中文](README.md)

This is a Simplified Chinese enhanced edition based on [Zelda64Recomp v1.2.2](https://github.com/Zelda64Recomp/Zelda64Recomp/tree/v1.2.2). It provides a Chinese launcher, a Chinese in-game interface, and several additional features.

This project is not an official Zelda64Recomp release. Copyright for the original project belongs to its original authors and contributors.

## Features

- Simplified Chinese launcher and in-game settings interface
- Chinese fonts and localized UI resources
- Separate first-person and third-person X/Y mouse sensitivity
- Mouse button bindings
- Runtime 1x, 2x, and 4x game-speed switching
- Return to the launcher main screen from the game with a safe application restart
- Prebuilt Windows release package

Chinese text, textures, and other game mods are not included in this repository. ROMs, save data, and other original game assets are also not included.

## Download and Run

Download the latest Windows package from the [Releases](../../releases) page, extract it, and run:

```text
Zelda64Recomp月陨启动器.exe
```

You must provide your own legally obtained NTSC-U version of the *The Legend of Zelda: Majora's Mask* N64 ROM. The ROM is not provided by this project and is not distributed with the release package.

The release package is located at:

```text
release/Zelda64Recompiled-v1.2.2-CN/
```

## Build from Source

### Clone the Repository

This project uses Git submodules:

```powershell
git clone --recurse-submodules <your-repository-url>
cd Z64RE_CN_Launcher
```

If the repository was already cloned without submodules:

```powershell
git submodule update --init --recursive
```

### Build Requirements

Windows builds require:

- Visual Studio 2022
- Desktop development with C++
- C++ Clang Compiler for Windows
- C++ CMake tools for Windows
- `make`

See [BUILDING.md](BUILDING.md) for the complete upstream build requirements and ROM preparation steps.

Building requires a decompressed ROM to generate the source files. The program should still be run with a standard `.z64` ROM. ROMs and generated `RecompiledFuncs/` and `RecompiledPatches/` files must not be committed to the repository.

## Upstream

- Upstream project: [Zelda64Recomp](https://github.com/Zelda64Recomp/Zelda64Recomp)
- Upstream version: `v1.2.2`
- Upstream commit: `54950a10408599d1d63802ee21cc2c4b05bfd378`
- Rendering engine: [RT64](https://github.com/rt64/rt64)

This project retains the upstream license and copyright notices. Upstream changes may be merged as needed.

## License and Third-Party Assets

The upstream source and the source modified by this project are licensed under the [GNU GPLv3](COPYING). When distributing modified source or binaries, provide the corresponding source and retain the license, copyright notices, and modification notices.

Third-party assets are covered by their respective licenses. Refer to the license files included in their directories. For example:

- `assets/promptfont/LICENSE.txt`: SIL Open Font License 1.1
- Dependencies under `lib/`: see the license files provided by each dependency

Before publishing, confirm that every added or replaced font under `assets/` permits redistribution, and include the relevant license or copyright notice.

## Releases

Before publishing a new Windows release, run:

```powershell
./scripts/verify-release.ps1
```

After verification succeeds, compress the package under `release/` and upload it to a GitHub Release. Do not upload ROMs, save data, mod packages, or other original game assets to the repository or its Releases.

## Thanks

Thanks to the authors and contributors of Zelda64Recomp, N64: Recompiled, RT64, RmlUi, FreeType, lunasvg, Gamepad Motion Helpers, and the other dependency projects.
