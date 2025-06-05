# rackets2
WIP TAS tools for NPEA00386 (Ratchet & Clank 2).

## Building
- You need: `gcc-powerpc64-linux-gnu`, `binutils-powerpc64-linux-gnu` and `make`.
- Via wsl, to install the dependencies, run `sudo apt install -y gcc-powerpc64-linux-gnu binutils-powerpc64-linux-gnu make`.
- Then just run `make` to build.

### Running on PS3
- Just load it via [racman](https://github.com/MichaelRelaxen/racman)'s patch loader.

## Credits
- [doesthisusername](https://github.com/doesthisusername)
- [bordplate](https://github.com/bordplate) for helping out a lot, and creating [Helga](https://github.com/bordplate/Helga), which inspired the `cellGetPadData` hook.