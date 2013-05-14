Planetary Triumph
=================

A console based game reminiscent of Galactic Conquest.

![screenshot](images/screenshot1.png)

Building
========

The project can be build using SCons by running the 'scons' command from the root of the project. This will create a Debug folder which contains the binary. The project must be built with C++11 support and depends on ncurses/pdcurses for output.


Controls
========

Valid command syntax is of the form:

{source planet(s) | "all"} {destination planet} [amount of population to move | percent of population to move]

For example, the command "a b 10" will move 10 population from planet 'A' to planet 'b'. Multiple planets can be selected as sources by typing their names in sequence. So the command "abm c .20" will move 20% of the population from planets A, B and M to planet c. Selecting "all" as a source will move population from all owned planets.

If nothing is supplied for the third argument, DEFAULT_MOVE_PERCENT percentage of the population will be moved. The current move percentage can be seen in the upper right-hand corner of the screen. This value may be adjusted using the up and down arrows.

The human player's planets are represented with the color green in terminals which support color, and are capitalized for terminals which do not. The players ships are represented by a green '*', while enemy ships are shown as a '.' of the AI's color.

Configuration
=============

The game will attempt to open the "config.ini" file to read in configuration options. If it is unable to find this file, it will create one with the default options.

