Snake Game (C++ / SFML)

A modern C++ implementation of the classic Snake game built with SFML. The game uses a real-time loop for smooth movement and input handling, and is organized using object-oriented components (e.g., Snake and Food) for maintainability.

Features
	•	Real-time keyboard controls (arrow keys / WASD depending on your build)
	•	Grid-based movement and continuous game loop
	•	Collision detection (wall + self collision)
	•	Randomized food placement and snake growth when food is consumed
	•	Clean separation of game components using headers/source organization

Tech Stack
	•	C++
	•	SFML (graphics + windowing)
	•	(Optional) Devcontainer/Docker support if you enable it in this repo

How to Run

Option A — Build locally (recommended)
	1.	Install SFML
	•	macOS (Homebrew): brew install sfml
	•	Ubuntu/Debian: sudo apt-get install libsfml-dev
	•	Windows: Download SFML and configure your compiler/linker paths
	2.	Compile (example)

	•	If you use g++ on Linux/macOS, a typical command looks like:
g++ assignment.cpp -o snake -lsfml-graphics -lsfml-window -lsfml-system

	3.	Run

	•	./snake

Note: Your compile command may vary depending on file structure and SFML installation.

Option B — Devcontainer (if included)

If this repo includes a .devcontainer/ configuration, you can open it in VS Code using “Reopen in Container” for a preconfigured environment.

Controls
	•	Move: Arrow keys (or WASD, depending on your implementation)
	•	Goal: Eat food to grow; avoid hitting walls or your own body

Project Structure
	•	assignment.cpp — main game loop + rendering + event handling
	•	snake.hpp — snake behavior and movement logic
	•	food.hpp — food spawn logic and representation

What I Learned
	•	Building interactive applications with a game loop and event-driven input
	•	Designing maintainable code using OOP and clean interfaces
	•	Debugging real-time logic (movement, collisions, edge cases)
