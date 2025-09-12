# Blood of Lathander BG3 arduino lights

[See it in action on Youtube](https://www.youtube.com/shorts/zHxYY-EACBM)

[<img src="https://imgur.com/61Io7Xb.jpg" width=500/>](https://imgur.com/a/tQtlB1w)

[<img src="https://imgur.com/SnlP3ev.jpg" width=500/>](https://imgur.com/SnlP3ev)

## About this project

As well as being a programmer, I am also a cosplayer and at the time of writing I'm currently working on [Shadowheart from Baldur's Gate 3](https://bg3.wiki/wiki/File:Shadowheart_Unarmed_Model.webp). I was very fortunate to get a 3D printer as a combined birthday/Christmas present last year and have already 3D printed myself the legendary [Blood of Lathander](https://bg3.wiki/wiki/File:Blood_of_Lathander_Quest.jpg) mace as a prop to go with it. After years of threatening to make a costume that lights up, I finally decided to do it.

I've tried to make costumes light up before but found I really didn't get on with the whole electronics thing. LEDs, resistors, capacitors, all the maths, my brain just refuses. However, these days all the cool kids are doing it with Arduino and pre-wired colour changing LEDs that you can code, so it's time for me to give electronics another chance.

## The brief

- The lights should be as bright as possible. [Somewhere between a nice summer's day and the full concentrated power of the sun](https://www.youtube.com/watch?v=cA6yF9M70zM).
- Initial tests show that it's not enough to just have lights inside the main sphere - each spike needs its own individual LED. There are 13 spikes.
- There is a pummel at the other end of the weapon that would ideally have an LED inside as well.
- The power needs to last as long as possible and require minimum battery changes. Ideally no battery changes would be necessary for a full convention day in the region of 8 hours. Once is acceptable. Twice is getting onto the edge of acceptability.
- The lights should be largely yellow with some warm white thrown in. There should be fading/pulsing/chasing effects.

I could totally ask ChatGPT to throw something together for me. However, as I cosplay competitively and have 3D printed the prop (which is less impressive than crafting it yourself), I decided I absolutely had to do the code, especially since I code for a living!

## The end result

Ultimately I was reasonably happy with how this all turned out. I found it quite challenging writing this code due to the strictly synchronous nature of the language behind it - if you tell an LED to be X colour for Y seconds, you cannot make other LEDs do other things in the meantime, which led to some interesting problem solving.

To be honest I had a bit of a nightmare getting this whole thing to work. I managed to short out one of my chips, my soldering fell apart and had to be redone, the flimsy wires on my battery came out, nightmare. I HIGHLY recommend going to the official Adafruit forums if you need help as it is full of wonderful, helpful people. ChatGPT did help along the way but did lead me down some bad paths that ended up costing me money that I didn't need to spend.

I entered the cosplay contest at the first convention I wore this costume to and I won! I had so many lovely comments about my costume and the weapon.

### Battery life

As described in the brief above, battery life was important. ChatGPT told me my LEDs should be able to run just fine for 8.5-9 hours based on the code and battery capacity I'd given it. Not one to take ChatGPT at its word, I charged my battery overnight and set the thing going one morning to see what would happen. After 12 hours the LEDs were still going strong and I abandoned the test, satisfied.

### Number of LEDs

Following the battery test, I determined that I had battery capacity to spare so I put more LEDs inside, so I had 2 inside the main ball part and not attached to any particular spike, as well as making them be white a higher percentage of the time (which is brighter but consumes more battery). It still easily lasts a whole convention day. I originally briefed myself that I needed 13 LEDs, but ended up with 16 which is great. I could probably get away with even more if I wanted.

## Want to make your own?

I love to hear it! I've written some advice below.

### Taking this to a convention

Please do be aware that different conventions have different rules about what "weapons" they will allow inside. Always make sure to check and even if you're allowed to take it in, be respectful and don't go swinging this around. Don't be the reason your convention stops allowing props like this inside.

### Supplies needed

- 3D print files. There are a lot of people online selling 3D print files for very reasonable prices. I bought mine from [SilverPanther3D on Etsy](https://www.etsy.com/uk/listing/1891570389/fantasy-blood-of-lathander-mace-baldurs).
- 3D print filament - I lean towards Creality HyperPLA as I have a Creality printer and get good results with it. This is what I used for the main body of the weapon. I used Sunlu transparent PLA for the yellow and red parts. In honesty I think the yellow PLA on my end result is a bit too yellow - I'd be interested in hearing what you go for if you make this.
- An arduino chip capable of outputting 5V (important to note as most of them do 3.7V as standard) and taking a LiPo battery. I have an Adafruit RP2040 which may have been overkill for the purpose.
- Individually addressable LEDs. The official term is "neopixels"
- A high-ish capacity LiPo battery. You are unlikely to be able to find a USB power bank small enough to fit inside the weapon. I used a 3500mAh battery.
- Soldering supplies, including wires (I started with 30AWG wire, which is discrete but a pain to work with. Some parts of my project use 22AWG which is a bit chunkier but sturdier and easier to work with).
- Various paints and primers to colour it all with.
- I highly recommend including a switch in your circuit between your Arduino device and the LEDs so you can easily turn it off if the situation calls. Do be aware that your Arduino will draw a small amount of power from the battery even if the LEDs are off, so your battery will eventually be drained if you leave it plugged in. Fine on the day, but don't expect to come back to your prop a week later and find it still has power if you didn't disconnect the battery.

### Connecting your Adafruit device

- Positive (ideally red) wire should connect from 5V port on your device to the "in" connector on the first of your LEDs.
- Negative (ideally black) wire should connect from the GND port on your device to the GND connector on the first of your LEDs.
- Data (usually either green or white) wire should connect to the Din (data in) connector on your first LED. It can connect to any of the data pins on your device as long as you tell the code which pin you're using. This code uses pin 9.

ChatGPT told me I should ideally have a 1000uF capacitor between the positive and negative lines and a 330Ω resistor on the data line to prevent any unlikely power surges. I originally tried this but it gave me so much grief I gave up on that idea. If you're making this however, it may be well-advised to pursue this.
