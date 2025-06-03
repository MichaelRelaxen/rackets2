# rackets2
WIP TAS tools for NPEA00386 (Ratchet & Clank 2).

# Info
## Capabilities
- Record input data.
- Play back input data.

## TODO
- Scriptable TAS inputs.
- Fix the RNG particles.
- racman (or something else) integration with setting TAS state, uploading replay file and framestepping.
- Maybe compress TAS file down to 6 bytes per frame instead of the 16 it's using right now. Would be nice.

## Building
- You need: `gcc-powerpc64-linux-gnu`, `binutils-powerpc64-linux-gnu` and `make`.
- Via wsl, to install the dependencies, run `sudo apt install -y gcc-powerpc64-linux-gnu binutils-powerpc64-linux-gnu make`.
- Then just run `make` to build.

NOTE: The Makefile is known to fail due to inconsistent line endings when your git is configured to convert line endings (Windows).

### Running on PS3
- Just load it via [racman](https://github.com/MichaelRelaxen/racman)'s patch loader.

## Credits
- [doesthisusername](https://github.com/doesthisusername) for RaC1 PS3 TAS tools, which this project is heavily based off of.
- [bordplate](https://github.com/bordplate) for helping out a lot, and creating [Helga](https://github.com/bordplate/Helga), which inspired the `cellGetPadData` hook.