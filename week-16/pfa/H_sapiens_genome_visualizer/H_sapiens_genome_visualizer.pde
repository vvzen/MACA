/////////////////////////////
// GENOME VISUALIZER
// liorbengai
// 2017
// DATA SOURCE:
// ftp://ftp.ncbi.nih.gov/genomes/H_sapiens/
// MORE INFO:
// https://www.ncbi.nlm.nih.gov/projects/genome/guide/human/index.shtml
/////////////////////////////

// data structures
String[] lines;
PGraphics plot;
PGraphics seq;

// counter vars
PVector plotPos;
int seqPos;
int line;
int plotCounter = 0;
int seqCounter = 0;

// scale - this controls the resolution of the final print
float unit = 1.0;

int start = 1;
int end = 19999;
String folder = "export1/";

void setup()
{
  // init sketch
  background(0);
  size( 800, 800 );
  textFont(createFont("Arial", 11));

  // get the data as an array of strings
  lines = loadStrings("hs_alt_CHM1_1.1_chr1.mfa");
  seqPos = 0;
  line = start; // skip first line

  // pgraphics for charting the sequence (color data)
  seq = createGraphics(width, 70);
  seq.beginDraw();
  seq.background(0);
  seq.strokeWeight(1);
  seq.endDraw();

  // pgraphics for plotting the sequence (color and position data)
  plotPos = new PVector(0,0);
  plot = createGraphics(width, height);
  plot.beginDraw();
  plot.background(0,0);
  plot.strokeWeight(1);
  plot.endDraw();
}

void draw() {

  // if reached max line - save and exit
  if(line > end){
    plot.save(folder+"plot"+plotCounter+"_"+int(plotPos.x)+"_"+int(plotPos.y) +".png");
    exit();
  }

  // get currnet line
  String currLine = lines[line];

  // 1.
  // plot data as sequence
  seq.beginDraw();
  for (int i = 0; i < currLine.length(); i++) {
    seq.stroke(mapColor(currLine.charAt(i)));
    seq.point(seqPos, i);
  }

  // boundary condition
  seqPos++;
  if (seqPos > width) {
    seq.save(folder+"seq"+seqCounter+"_"+line+".png");
    seq.background(0);
    seqPos = 0;
    seqCounter++;
  }
  seq.endDraw();

  // 2.
  // plot data as random walk
  plot.beginDraw();
  plot.translate(width/2, height/2);
  // add the next movement to the plot
  for (int i = 0; i < currLine.length(); i++) {
    plotPos.add(mapPos(currLine.charAt(i)));
    plot.stroke(mapColor(currLine.charAt(i)));
    plot.point(plotPos.x, plotPos.y);
  }

  // if plot goes beyond the boundary - save as image and put back in the middle
  if(abs(plotPos.x) > width/2 || abs(plotPos.y) > height/2){
    plot.save(folder+"plot"+plotCounter+"_"+int(plotPos.x)+"_"+int(plotPos.y) +".png");
    plotPos.set(0,0);
    plot.background(0,0);
    plot.point(plotPos.x, plotPos.y);
    plotCounter++;
  }
  plot.endDraw();

  // 3.
  // draw both as images on screen
  background(0);
  image(plot, 0, 0);
  image(seq, 0, height-90);

  // 4.
  // also render current line at bottom as text
  noStroke();
  fill(64);
  rect(0, height-20, width, 20);
  fill(255);
  text(line +" : "+ currLine, 10, height-6 );

  // 5.
  // move to next line for next frame
  line++;
}


// simple switch statement that maps a char to a color
color mapColor(char c) {
  color col = color(0);
  switch(c) {
  case 'n':
  case 'N':
    col = color(127);
    break;
  case 'a':
  case 'A':
    col = color(255, 0, 0);
    break;
  case 'g':
  case 'G':
    col = color(0, 255, 0);
    break;
  case 't':
  case 'T':
    col = color(0, 0, 255);
    break;
  case 'c':
  case 'C':
    col = color(255);
    break;
  }
  return col;
}

// simple switch statement that maps a char to a direction vector
PVector mapPos(char c) {
  PVector res = new PVector(0, 0);
  switch(c) {
  case 'n':
  case 'N':
    // blank - do nothing
    break;
  case 'a':
  case 'A':
    res.x += unit;
    break;
  case 'g':
  case 'G':
    res.y += unit;
    break;
  case 't':
  case 'T':
    res.x -= unit;
    break;
  case 'c':
  case 'C':
    res.y -= unit;
    break;
  }
  return res;
}
