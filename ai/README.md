# Zappy - AI Player

## Introduction

This part of Zappy is a functional AI player, that has its own strategy.

The aim of this part of the project is to provide a fully working player that can play the game, and do its best to win the game! :rocket:

### Table of contents

- [Launching](#launching)
- [Our strategy](#our-strategy)
    - [Prerequisites: Secure broadcasts](#prerequisites-secure-broadcasts)
    - [Define a boss!](#define-a-boss)
    - [The first levels](#the-first-levels)
    - [The food problem](#the-food-problem)
    - [To the level 8 and beyond!](#to-the-level-8-and-beyond)
    - [Attacking](#attacking)

## Launching

You can start the AI player using the following command:

```
./zappy_ai -p <port> -h <hostname> -n <name>

-p port number
-h address of the host machine
-n name of the team
```

> :bulb: The port must be the same as the one used by the server and between 1 and 65535, and you may need root privileges to use a port below 1024.

## Our strategy

Our strategy is based on different **jobs** and **roles**: each player of the team has its own role, determined by a boss.

> :bulb: Our AI player is configured to control as many players as available in the team, so that you have to launch the program only once per team.

### Prerequisites: Secure broadcasts

The broadcast channel is shared across all the players: this means any player can break our system by repeating our messages or trying to understand our processes in order to sabotage us.

To counter this phenomenon, we decided to encrypt our broadcasts, using [AES Encryption](https://pycryptodome.readthedocs.io/en/latest/src/cipher/aes.html).

> :wrench: But other players can still repeat our messages, and this could lead to several problems.

To fix this issue, we sign our messages using a **nonce**: this system ensures that the message **is only read once**, and ignores the message if it has been repeated. 

### Define a boss!

The first real step of our strategy is to define a **boss**, which will be a special AI player that will **not** level up: it's job is to manage the team, by giving to each AI a task to do.

The boss is not levelling up as an incantation lasts 300 ticks, and the boss needs to stay available to manage the players at all the time.

Once a boss has been defined, the first job of the other players is to join him, by using the `Broadcast` orientation feature, allowing them to know the direction they need to travel to get to the boss.

Once all the AI players have been centered on a single tile, the next step can start.

To allow identified communications between AI players, all players share common **UUIDs** to identify themselves.

### The first levels

The next step of the team is to level up to the level **6**, as the level 7 and 8 requires 6 players to level up.

The AI players are split between several jobs, determined by the boss based on the demand.

Those jobs are mainly:
- Find resources on the map
- Level up
- Feed the boss

> :bulb: The AI players fork to allow a sufficient number of players for the different incantations.

### The food problem

A problem that has been encountered is that there is not enough food on the map to ensure that all the players will survive, especially when players from other teams gather the food near to our boss.

To fix this issue, we created a **food farmer**:

- When an AI player spawns, it has 10 food units in its inventory.
- A player can use the instruction `Fork` to create one addtional team slot.
- One or more players will be designed to use this instruction many times, and IA spawned thanks to this process will drop their food and die.

This strategy allows us to generate hundreds of food in a matter of ticks, which definitly fixes the problem of the food in almost cases.

When AI players are waiting for other AI to perform multiplayer jobs, they can wait creating a food farmer.

> :bulb: The boss is charged to maintain everyone alive, and will order other players to take food when necessary.

### To the level 8 and beyond!

Once 4 players reached level **6**, the strategy is changing as **6** players are now required to get to the level **8**.

The strategy starts by forking at least **4** players, since 4 players need to be levelled up one level by one.

Once the necessary AI have spawned, **both** level 6 and new AIs go back to their jobs concurrently to find the resources required: when newborn players try to find linemates, the level 6 ones focus on the thystame!

:rocket: Finally, when the 4 new players reach the level 6 and everything is ready for the last levels, the players can finally execute the final incantations!

### Attacking

Our strategy does not have any attacking systems, and is focused on reaching the level 8 as fast as possible, an tries as much as possible to resist to enemy attacks.

Our strategy covers:

- Broadcast attacks in any form (replay, spam, decrypting)
- Eject attacks
- Resources theft attacks
