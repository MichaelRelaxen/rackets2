## rackets2
WIP TAS tools for Ratchet & Clank 2 (NPEA00386).

### Functionality
- Playback recorded inputs or scripted inputs via .rtas format.
- Record inputs to .rtas format
- Custom "RNG" + functionality for nudging RNG.
- Toggle framestepping mode and step frames.
- Ability to disable rendering and uncap the framerate.
- HUD with information useful for TASing + input display.

### Build
1. Install `binutils-powerpc64-linux-gnu` and `gcc-powerpc64-linux-gnu`.
2. Then just run `make`.

### Credits
- doesthisusername for the original TAS tools for RaC1.
- bordplate for cellGetPadData hook + help with randomness.
