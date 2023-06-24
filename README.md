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

> :warning: The following dependencies are required for each part of the project:

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
  <p>If you're using the <strong>Fedora</strong> Linux distribution, you can <code>make install</code> for an automatic installation of the Raylib.</p> 
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

## Usage

Now that the project is installed, let's create a new iteration of Trantor!

To do so, you must start the server, using the following command:

```bash
./zappy_server
```

> :wrench: The server is highly **configurable**. Please refer to the [Server documentation](./server/README.md) for more information. 

The server is now connected to the Internet and can be accessed using the port *4242* by default, or any port you want using the *-p* parameter.

The graphical client can be launched alongside the server, using the following command:

```bash
./zappy_gui -h <hostname> -p <port>
```

Hostname is the IP address of the server, and port is the port used by the server.

> :bulb: If you're running the server and the client on the same computer, you can use the **127.0.0.1** address.

Finally, you can run one or more AI players.

To use the provided AI player, you can run the following command:

```bash
./zappy_ai -h <hostname> -p <port> -n <team_name>
```

The hostname and port are similar to the graphical client, and the team name is the name of the team you want to join.

> :bulb: The provided AI program is configured to connect enough AI players to fill the specified team so that you only have to run the program once per team.

:rocket: You can run any program that follows the [Server/AI Communication Protocol](./server/README.md).

## External documentations

Each part of the project has its own documentation:

- [Server documentation](./server/README.md)
- [Graphical client documentation](./gui/README.md)
- [AI player documentation](./ai/README.md)

:mag: If you are looking for a specific information about one of the parts, please refer to the corresponding documentation.

## Troubleshooting

If you encounter any problem during the installation or the usage of the project, you can create an [issue](https://github.com/EdenComp/Zappy/issues/) explaning your problem.

We will try to help you as soon as possible.

## Contributing

You're invited to contribute to the project!

You have an idea to improve the project? You found a bug? Feel free to create an [issue](https://github.com/EdenComp/Zappy/issues/) to share your idea with us!

You can also **fork** the repository and submit a [pull request](https://github.com/EdenComp/Zappy/pulls/) to propose your changes.

## Our Trantor Survivors (a.k.a. developers)

| [<img src="https://github.com/EdenComp.png?size=85" width=85><br><sub>Florian Lauch</sub>](https://github.com/EdenComp) | [<img src="https://github.com/SloWayyy.png?size=85" width=85><br><sub>Mehdi Djendar</sub>](https://github.com/SloWayyy) | [<img src="https://github.com/Sloyi.png?size=85" width=85><br><sub>Rayan Es-Seffar</sub>](https://github.com/Sloyi) | [<img src="https://github.com/JonathanYakan.png?size=85" width=85><br><sub>Jonathan Yakan</sub>](https://github.com/JonathanYakan) | [<img src="https://github.com/Tahalani.png?size=85" width=85><br><sub>Taha ALANI</sub>](https://github.com/Tahalani) | [<img src="https://github.com/kvn703.png?size=85" width=85><br><sub>Kevin NADARAJAH</sub>](https://github.com/kvn703) |
|:-----------------------------------------------------------------------------------------------------------------------:|:-----------------------------------------------------------------------------------------------------------------------:|:-------------------------------------------------------------------------------------------------------------------:|:----------------------------------------------------------------------------------------------------------------------------------:|:--------------------------------------------------------------------------------------------------------------:|:--------------------------------------------------------------------------------------------------------------------------:|
