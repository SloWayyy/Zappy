# Zappy Server

The Zappy's server is the core of the project.

The goal of the server is to manage the game and the communication between the clients, which can be either AI players or graphical clients.

## Configuration

When launching the server, you can specify different options.

You can retrieve all of them using the following syntax:

```bash
./zappy_server -help
```

### Connectivity

You can use the `-p` (`--port`) option to define a specific port for the server.

> :bulb: The default port is 4242.

> :warning: The port must be between 1 and 65535, and you may need root privileges to use a port below 1024.

### Map size

The map size can be edited using the `-x` (``--width``) and `-y` (``--height``) options.

> :bulb: The default map size is 10x10.

> :wrench: The minimum map size is **1x1**, and the maximum map size is **100x100**.
