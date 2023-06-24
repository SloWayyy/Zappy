# Zappy Server

The Zappy's server is the core of the project.

The goal of the server is to manage the game and the communication between the clients, which can be either AI players or graphical clients.

## Configuration

When launching the server, you can specify different options.

You can retrieve all of them using the following syntax:

```bash
./zappy_server -help
```

#### Table of contents

- [Connectivity](#connectivity)
- [Map size](#map-size)
- [Teams](#teams)
- [Teams capacity](#teams-capacity)
- [Frequency](#frequency)
- [Immortal mode](#immortal-mode)
- [Debug mode](#debug-mode)
- [Custom seed](#custom-seed)

### Connectivity

You can use the `-p` (`--port`) option to define a specific port for the server.

> :bulb: The default port is 4242.

> :warning: The port must be between 1 and 65535, and you may need root privileges to use a port below 1024.

### Map size

The map size can be edited using the `-x` (``--width``) and `-y` (``--height``) options.

> :bulb: The default map size is 10x10.

> :wrench: The minimum map size is **1x1**, and the maximum map size is **100x100**.

### Teams

You can define the teams that will be available in the game using the `-n` (`--names`) option.

To use it, you have to chain the names of the teams, separated by a space.

:mag: Example: `./zappy_server -n my_team my_second_team my_third_team`

> :bulb: The default teams are `Team1`, `Team2`, `Team3` and `Team4`."

> :warning: The team name `GRAPHIC` is reserved for the graphical client.

> :information_source: A total of 100 teams can be created.

### Teams capacity

You can set the maximum number of players per team using the `-c` (`--clients`) option.

> :bulb: The default number of players per team is 4.

> :rocket: The maximum number of players per team is 100, totalizing a maximum of **10,000** players.

### Frequency

You can set the frequency of the game using the `-f` (`--frequency`) option.

Please take a look at the [Server/AI Communication Protocol](./README.md) for more information about the frequency.

> :bulb: The default frequency is 100.

### Immortal mode

You can enable the immortal mode using the `--immortal` option.

In this mode, the players will consume food, which is their only way to die on **Trantor**.

### Debug mode

You can enable the debug mode using the `--debug` option.

This mode allows developers to get more information about the game.

The debug mode show the following information:

- Resources map refills
- Incantation status and verifications

### Custom seed

You can set a custom seed for the random number generator using the `--seed` option.