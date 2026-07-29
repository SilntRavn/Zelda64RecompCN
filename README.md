# Zelda64Recomp Simplified Chinese Launcher

Chinese launcher source and Windows distribution for Zelda64Recomp 1.2.2.

Upstream source base: `Zelda64Recomp/Zelda64Recomp` commit
`54950a10408599d1d63802ee21cc2c4b05bfd378`.

This repository is kept separate from the Chinese text/texture Mod repository. It contains the
launcher UI localization, Chinese UI fonts and the accepted Windows executable package, but no
ROM, save data, MM Reloaded pack, NRM, or RTZ files.

## Repository layout

- `assets/`: authoritative launcher UI assets. These match the accepted deployed build.
- `src/`, `include/`, `lib/`, etc.: Zelda64Recomp 1.2.2 source tree.
- `docs/UPSTREAM_README.md`: upstream project README.
- `release/Zelda64Recompiled-v1.2.2-CN/`: clean Windows distribution without Mods.
- `scripts/verify-release.ps1`: validates the accepted EXE and runtime DLL hashes.

## Current executable

- File: `Zelda64Recomp月陨启动器.exe`
- SHA-256: `5881B23739E41C9352000DC0D543173CA1F9BDFB11D537A7E3BC511761C629D3`

The accepted deployed `assets/recomp.rcss` has SHA-256
`65315B959BB4B3DC1BE5FF240F07AA98D9852A11929A7372628888138B906690`.
It intentionally preserves the user-approved visual overrides from the installed launcher.

## Build and publishing

See `BUILDING.md` for upstream build prerequisites. ROM data and generated recompilation output
are not part of this repository.

After cloning, initialize the pinned upstream dependencies with:

```powershell
git submodule update --init --recursive
```

For GitHub, commit the source tree and publish the contents of `release/` as a GitHub Release.
Run `scripts/verify-release.ps1` before uploading. Review font redistribution permissions before
making the repository public.
