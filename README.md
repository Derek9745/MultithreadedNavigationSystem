This is a multithreaded pathfinding navigation system, designed to optimize real time pathfinding systems for a large-scale number of navigation agents in the Unity Game Engine, using graph based-algorithms (A*) and parallelization for optimal performance. 

<img width="840" height="717" alt="image" src="https://github.com/user-attachments/assets/4e62b6d5-9a4c-4c93-91bb-b3dd9d44018c" />

1.This project required multiple components for the full implementation to work correctly. First there is a Unity program written in C#, named Model that controls interfacing with the Unity Game Engine for implementing the navigation agents into a Unity Scene. The Unity Game Engine handles agent visualization and movement within a 3d grid-based coordinate system, and performance monitoring with the Unity Profiler.

2.In C++, an implementation of A* search algorithm was implemented. Initially this was Dijkstra’s algorithm, but the realization of needing a real grid-based representation for pathfinding lead to it being modified to A*. It uses a heuristic approach for pathfinding.

3.This was then turned into a DLL (Dynamic Link Library) for interfacing with Unity, as Unity requires C#, so a C style API was created in a header file called PathfindingAPI.h and exposed with simple data types (int, float, void) for the DLL.

4.The Model script and calls the DLL API sending a batch request of pathfinding jobs to run, and creates a data structure called a blocking collection, which holds individual NavAgent game objects that will be instantiated into a Unity scene. Batch size is dependent on the number of agents, with various thresholds. Batching was used instead of sending each job individually to reduce computationally expensive overhead of going from C# to C++.

In the multithreaded implementation, OpenMP distributes pathfinding agent creation and computational tasks across multiple CPU threads, allowing different agents to compute paths concurrently.

Run Requirements<br>
Unity Editor: 2022.3 LTS or newer<br>
Operating System: Windows 10/11 (64-bit)<br>
Architecture: x86_64<br>
Native C++ DLL:<br>
Must be located in:<br>
Assets/Plugins/x86_64/<br>
Must be compiled for x64<br>

Build Requirements<br>
Unity (C#)<br>
Unity Hub + Unity Editor (2022.3 LTS or newer)<br>

C++ DLL (Pathfinding)<br>
IDE/Compiler: Visual Studio 2019 or newer<br>
C++ Standard: C++17 or newer<br>
Platform: x64<br>
Configuration: Release (recommended)<br>
Compiler Flags:<br>
OpenMP enabled (/openmp)<br>
Dependencies:<br>
OpenMP (included with MSVC)<br>
