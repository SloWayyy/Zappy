# Zappy

A multiplayer game composed of a server, a graphical client and AI players

## Introduction

Zappy is a multiplayer game where the goal for a player is to collect resources to evolve and win the game.

The game is played on a server where AI players and graphical clients can connect.
The server is composed of a map, which is a grid of squares.

> :rocket: The user is not directly playing: programs do so!

Each player starts at level *1* and belongs to a _team_. Its goal is to survive on the world of **Trantor** by collecting resources on the map.
There is two kinds of resources: **food**, which is consumed by the player to survive, and **stones**, which are used to evolve.
The process of elevation, also known as **incantation**, requires a certain amount of stones and players on the same position to be performed.

> :star: The winning team is the first with **6 players** at level **8**.

## Installation

To install the game, you need to clone the repository and run the `make` command at the root of the repository.

```bash
git clone git@github.com:EdenComp/Zappy.git Zappy
cd Zappy
make
```

> :warn: The following dependencies are required for each part of the project:

<details>
  <summary>Server</summary>
  <p>The only dependencies required for the server are the standard lib C and a C compiler, which are mostly already installed on your computer.</p>
  <p>Here are some resources that could help you in case of troubleshoots:</p>
  <ul>
    <li><a href="https://www.gnu.org/software/libc/manual/html_node/Installation.html">Standard Library C installation</a></li>
    <li><a href="https://gcc.gnu.org/install/">GNU C Compiler (gcc) installation</a></li>
  </ul>
</details>

<details>
  <summary>Graphical client</summary>
  <p>The graphical client is using <a href="">Raylib</a> for rendering purposes, coupled to the C++ language, which is most of the times already available on your computer.</p>
  <p>If you're using the <strong>Fedora</strong> Linux distribution, you can run the script located in <code>install/raylib_install.sh</code> for an automatic installation of the Raylib.</p> 
  <p>If you're using <strong>Arch Linux</strong>, Raylib can be installed using <strong>pacman</strong> with the following command: <code>sudo pacman -Sy raylib</code></p>
  <p>If you're using none of them, you can check the <a href="https://github.com/raysan5/raylib/wiki">Raylib Wiki</a> which contains installation steps for several configurations.</p>
</details>

<details>
  <summary>AI Players</summary>
  <p>The AI player we used is developed in Python, using the <code>pycryptodome</code> package.</p>
  <ul>
    <li><a href="https://docs.python.org/3/using/unix.html">Python installation</a></li>
    <li>The required package can be installed using <code>pip install pycryptodome</code></li>
  </ul>
</details>
