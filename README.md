# snake_game
Version 0.0.1 - non working playground
TODO:
1. Rethink Chain struct and internals for Snake - we don't need to know coordinates, texture only!
2. Important task - we need to keep smooth turning, taking into consideration diameter of bodyChains!
	- One straightforward solution is to include queue into Chain struct, to track all turns and turn coordinates for each chain element.
3. Animate snake head (static and moving)
4. Add .gitignore	


It would be fun to make head growing and splitting at some moment into chains. So, different fruits would generate different grow speed. Also, different fruits would generate different body chain colors, colorkeying 
and alpha-blending. And each snake would become different rainbow being. 

As long-term enhancement it would be interesting to generate splitted tail for some specific fruits.

