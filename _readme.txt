BOULDER README

DESCRIPTION:
In Boulder you controll a rolling boulder and crush obstacles.
When coming to a halt, you are able to purchase upgrades with resources
gathered from the destruction of obstacles.
When the boulder is destroyed, a new one has to be purchased, but it can
be made of a new material, changing different aspects of the boulder.

CONTROLS:
Press D to start the game (and hold it to accelerate)

When rolling:
D: Accelerate
A: Decelerate

When choosing a boulder:
Click on a boulder to purchase it

When shopping:
Click an upgrade to purchase it
D: Start new Run

HOW TO PLAY:

Stats:
Density: Influences Integrity
Brittleness: Decreases Defense value on collision
Hardness: Increases Attack value on collision
Smoothness: Increases Max Speed and acceleration, slightly decreases deceleration
Those are stored as floats, so changes might not appear to happen, but there actually is a change

Integrity: Boulder health, resets when entering the shop
Max Speed: Maximal speed of the boulder
Speed: Current speed

Materials:
There are 5 types of materials, each with its own currency dropped.
They are themed after Rock Types.

Upgrades:
Upgrades outlined with Green can be purchased by clicking on them.
They are a bit overwhelming, so here is a breakdown:

First Row:
Additive Upgrades to the primary stats (Density etc.). Increase the value by 1 flat.

Second Row:
Multiplicatice Upgrades to the primary stats. 

Third Row:
Increase the chance of Boulders of a specific type appearing in the Boulder selection.

Fourth Row:
Decrease that chance

Fifth Row:
"Meta Upgrades": Selection Level increases the possible Boulder Sizes. Difficulty increases obstacle size, resulting in more resources dropped.

Most upgrades have a cost creep. This resets when the boulder breaks, thus needing a new Boulder.

Boulder Selection:
When breaking, the Player gets a choice between 3 new boulders.

DISCLAIMER:
This is by no means a finished game.
Some ideas on what I could have done with more time:
-Better Graphics
-More Materials (not Types, just more color variation and stat distribution)
-Better Balancing

Also:
Jeremiah fittingly described tracking one issue down going down a rabbit hole.
I am aware that I could have refactored the code quite a bit, but I simply ran out of time due to health reasons.