# Navier-Stokes
A numeric solver for Navier-Stokes equations

## Usage

### Dependencies
* SFML

### Compilation
Run `make` in the root directory.

### Running
Run `./main.out` in the root directory. The program supports the following command line arguments:
* `-energy` - shows the total energy of the system at each time step
* `-time <time>` - sets simulation time to `<time>` seconds
* `-velocities` - render velocity field together with smoke
* `-render` - renders the system to a video file in the `render` directory
