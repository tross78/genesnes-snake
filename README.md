A cross-platform implementation of the classic game Snake for the Sega Megadrive/Genesis and the Nintendo SNES.

##Getting Started
To build the game, you'll need the following dependencies:

- pvsneslib Docker image built from custom Docker file under https://github.com/tross78/megadrive-snes/docker-pvsneslib
- SGDK Docker image https://registry.gitlab.com/doragasu/docker-sgdk:v1.80

The build system is currently very hacky and the process for building the game for each platform is different. 
The snes and genesis folders contain code specific to each platform, while the common code is copied to them.
