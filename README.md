# SlimeMold
This project visualizes a simulation of the formation of <a href=https://en.wikipedia.org/wiki/Slime_mold>Slime mold</a> networks. Slime molds are eukaryotic single-celled organisms that are fungus-like protists. They are known to form large, complex transport networks and this simulation seeks to examine how they form over time through a variety of parameters.

![Screenshot_20230207_034919](https://user-images.githubusercontent.com/29548845/217387841-fba00aec-c04d-4688-84af-2f8f9e72d794.png)

## Usage
The simulation can be found <a href=https://github.com/AstrosBoy15/SlimeMold/releases/tag/Release>here</a>. The project can be run via the SlimeMold.exe file. Within the simulation, using the space bar will toggle between pausing and unpausing the simulation. There are a variety of parameters that can be changed in the GUI panel including the speed at which slime particles move, how quickly their trails decay and diffuse, and how far and where the particles can sense the trail left behind by other cells.

![Screenshot_20230207_035004](https://user-images.githubusercontent.com/29548845/217387846-8704acab-3cdc-4014-aec5-d4014b57fe49.png)

## Project Details
This project was done in February of 2022. It uses C++ with OpenGL for rendering the simulation to the screen. Compute shaders are used to calculate how each particle should behave at each time step, and for simulating the diffusion and decay of the trails. A fragment shader is then used to render this output. <a href=https://github.com/ocornut/imgui>Dear ImGUI</a> was used to display the GUI options. This project was inspired by a video done by <a href=https://www.youtube.com/@SebastianLague>Sebastian Lague</a> and can be found <a href=https://youtu.be/X-iSQQgOd1A>here</a>. The paper, <a href=https://uwe-repository.worktribe.com/preview/980585/artl.2010.16.2.pdf>Characteristics of Pattern Formation and Evolution in Approximations of Physarum Transport Networks</a> by Jeff Jones and a <a href=https://cargocollective.com/sagejenson/physarum>write-up</a> on the simulation by Sage Jenson, were used in the implementation of the simulation.

![Screenshot_20230207_035208](https://user-images.githubusercontent.com/29548845/217387848-7f358814-369a-4bf4-81d1-5a270f15ff6f.png)

## Future Work
One potential feature that could be added to this simulation is the presence of multiple slime species. These species could each have unique interactions with one another such as competition of collaboration. Each species could be representing using a different color channel in the diffusion map, allowing for up to four species being simulated. Another important feature to be added is the ability to allow the user to define starting patterns for the slime mold particles to use. With this, presets coul dbe added that are based on experimental data to show the comparison between the simulation and real examples.
