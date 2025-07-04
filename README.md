# Blood of Lathander BG3 arduino lights

## About this project
As well as being a programmer, I am also a cosplayer and at the time of writing I'm currently working on [Shadowheart from Baldur's Gate 3](https://bg3.wiki/wiki/File:Shadowheart_Unarmed_Model.webp). I was very fortunate to get a 3D printer as a combined birthday/Christmas present last year and have already 3D printed myself the legendary [Blood of Lathander](https://bg3.wiki/wiki/File:Blood_of_Lathander_Quest.jpg) mace as a prop to go with it. After years of threatening to make a costume that lights up, I finally decided to do it.

I've tried to make costumes light up before but found I really didn't get on with the whole electronics thing. LEDs, resistors, capacitors, all the maths, my brain just refuses. However, these days all the cool kids are doing it with Arduino and pre-wired colour changing LEDs that you can code, so it's time for me to give electronics another chance.

## The brief
- The lights should be as bright as possible. [Somewhere between a nice summer's day and the full concentrated power of the sun](https://www.youtube.com/watch?v=cA6yF9M70zM).
- Initial tests show that it's not enough to just have lights inside the main sphere - each spike needs its own individual LED. There are 13 spikes.
- There is a pummel at the other end of the weapon that would ideally have an LED inside as well.
- The power needs to last as long as possible and require minimum battery changes. Ideally no battery changes would be necessary. Once is acceptable. Twice is getting onto the edge of acceptability.
- The lights should be largely yellow with some warm white thrown in. There should be fading/pulsing/chasing effects.

I could totally ask ChatGPT to throw something together for me. However, as I cosplay competitively and have 3D printed the prop (which is less impressive than crafting it yourself), I decided I absolutely had to do the code, especially since I code for a living!


