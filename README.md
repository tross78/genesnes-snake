## GeneSnes-Snake

A cross-platform implementation of the classic game Snake for the Sega Megadrive/Genesis and the Nintendo SNES.

# Getting Started
To build the game, you'll need the following dependencies:

- pvsneslib Docker image built from custom Docker file under [/docker-pvsneslib/Dockerfile](/docker-pvsneslib/Dockerfile)
- SGDK Docker image https://registry.gitlab.com/doragasu/docker-sgdk:v1.80

The build system is currently very hacky and the process for building the game for each platform is different. 
The snes and genesis folders contain code specific to each platform, while the common code is copied to them.

The scripts are currently hardcoded to run the roms with BSNES and DGEN emulators.
