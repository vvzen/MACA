# README

This folder contains all of the necessary code for the **Programming for Artists 1** term 1 submission.

An online version of this repository is available on [github](https://github.com/VVZen/MACA/tree/master/end-1-term-projects/pfa1/idea-1).

1. The **text-analysis-python** directory contains the python script used to generate a list of the most recurring words used by generative artists to describe their artworks/bio.
The script loads up all the .txt files contained inside the *text-analysis-python/text-sources* directory, filters from stopwords (prepositions, conjuctions, etc..) and then saves all of the words to a sorted json array of hash tables called *words_frequency_score.json* located inside *../generative_bot_stx_pfa1/bin/data/*.
The array is sorted by word appereances in the texts (ie: **art** is the first word and appears 315 times.)
To run the script, simply type:
    ```cd text-analysis-python```
    ```python analyse_texts.py``` 

2. The **generative_bot_stx_pfa1** is the actual openframeworks project used to generate the final image.
Why openframeworks? Because it gives us much more control. 
The app loads up the **words_frequency_score.json** file and feeds the contained words into a boids simulation. 
Basically it just creates a B/W image (fbo) made of all the words (in white) against a (black) bg, then creates another fbo where the boids simulation happens. The boids will have **"fear"** of the white pixels in the B/W fbo, and this will lead to the boids bouncing inside the letters and then finally exiting from them. 
In order to run the project on your machine, you must do the openframeworks magic.. 
    1. create a new project using the of project generator
    ![generate_project](generate_project.png)
    2. add *ofxGUI*, *ofxJSON*, *ofxXMLSettings* as addons
    3. in the src folder of your generated project, add all the source files contained in the src folder of this repository.
    4. add all the files from the *bin/data* folder into your new project *bin/data* folder.
    5. compile!
To build the project using the **make** system, just go into the folder of your new project and type:
    ```make && make RunRelease```

## Other infos
Right now the of app is set so that it will run for a random amount of time and then before exiting it will create a large 6000x3375 tif image in the *output* folder. The required time is from 15 to 20 minutes (smaller images will take less time).
In order to change the resolution, edit the **globals.cpp** file.
![globals.cpp](globals.png).
Please note that the resolution of the generated file is independent of the current size of the ofApp window, since the boids run in a separate fbo. If you don't have a 6k monitor, well, you'll only see a portion of the final image.
To create a screenshot of the image while the app is still running, press 'w'. 
