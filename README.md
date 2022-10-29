# Lego-Sequencer
Lego-Sequencer project

# Disclaimer
This project is heavily inspired from  the Monster Lab by SAMTOMINDUSTRYS, see https://github.com/SAMTOMINDUSTRYS/monsterlab . Especially the phenotype table for the sequenced monster was is here in good use.

# Requirements
To build the sequencer, a few items need to be available, respective need to be available:

1. Arduino Uno R3 (https://docs.arduino.cc/hardware/uno-rev3)
2. A stepping motor plus controller
3. An RGB sensor (e.g. Adafruit TCS34725)
4. 2x2 Lego bricks in four colours (preferrably red, green, blue and yellow)
5. Something to build the sequencer, I used also Lego for that, but wood, acryl, etc should do as well
6. Installed craiyon API (https://github.com/FireHead90544/craiyon.py)
7. Installed Arduino IDE (https://www.arduino.cc/en/software)
8. Install R and RStudio and all required libraries (if you do not have them, install them as you reveive the error messages ;) )

Instead of using an Arduino and stepping motor, I used in this project actually an Elegoo starter kit that contains a compatible microcontroller, stepper and stepper controller. You can find it here https://www.elegoo.com/products/elegoo-uno-most-complete-starter-kit

# Setup

## Building the sequencer and wiring it

On the project page you can find a detailed series of pictures, how the Lego sequencer was build and wired:

http://danielfischer.name/life/tech-projects/lego-sequencer/

## Setting up the Arduino

Figure out on which COM-port your microcontroller / arduino works, load the ino-file to it and you are good.

Of course, here you would need to adjust some of the parameters, as they are tailored to the model that I used and my RGB sensor. So, what you would need to do is to find out, how far the sledge needs to be pulled in, what is the sise of the bricks you use, how many genes you inlcude into your model and then how far it needs to move out again.

Further, I think the colour readings might be different for you, so the colour determination might need also some adjustments. But anyway, I think with that respect the code is rather self-explanatory. In case you run into troubles, please reach out e.g. by opening an issue here.

This process might be some back anf forth process but eventually you will get there.

## Preparing the python API
Make sure you have Python installed (e.g. by running `python` and then install the Craiyon API. To test it, you could run the python script alone

```
 python generateImages.py "A Happy four-legged Grass Monster with Four red eyes, Patches , Shell and horns"
```

If that works, you can go on.

## Setting up the R-script
Then, open the R-script `monsterSequencer.Rmd`. First, you want to see if all required libraries are available on your system - if not, it would be good to install them.

Otherwise, all should be good and you can render the document "knit it". Once you click knit, the sequencer should start, send the readings to the R software, R sends it to the python API and generates then the report in pdf format.

# Questions?
In case you have troubles setting up the sequencer, please contact me here via the issues.

# Re-use
Of course you can use all of the available stuff here for your own projects (as this one here is also already a reuse and extension of the original project Monster-Lab). In case you got inspired by this, it would be nice to drop a line and tell your story also to the inventor Sam, e.g. reach out via Twitter @samstudio8 and @monsterdnalab. For reaching out on twitter to me, my user is also there @fischuu .
