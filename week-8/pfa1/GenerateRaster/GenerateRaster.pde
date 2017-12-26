////////////////////////////////
//  WEEK 8 LIVE SESSION      //
//  GenerateRaster.pde      //
// liorbengai              //
// November 28 2017       //
///////////////////////////

// an array to hold our generated data
int [][] imgData;
int sz  = 256; // width and height of the 2D array

void setup(){
  size(256,256);
  frameRate(60);
  imgData = new int[sz][sz]; // instantiate the 2D array
  populateImg(0); // make all values in it be zero
}

void draw(){

  randomizeImg(); // use random() to generate patterns
  //noisifyImg(); // use noise() to generate patterns
  //sinifyImg(); // use sin() to generate patterns

  // drawtoRects(); // draw the data as rectangles (SLOW)
  drawToPixels(); // draw the data as pixels (FAST)

  // display the actual frameRate
  fill(255,0,0);
  text(frameRate, 10, 20);
}

// draw the data DIRECTLY to the pixels array (relatively fast)
void drawToPixels(){
  loadPixels();
  for(int i =  0; i < height ; i++){
    for(int j =  0; j < width ; j++){
      pixels[ j * width + i  ] = color(imgData[i][j]);
    }
  }
  updatePixels();
}

// draw the array as a grid of rectangles (much slower)
void drawtoRects(){
  float rectSz = width/ sz;
  noStroke();
  for(int i =  0; i < sz ; i++){
    for(int j =  0; j < sz ; j++){
      fill(imgData[i][j]);
      rect( i * rectSz , j * rectSz, rectSz, rectSz   );
    }
  }
}

// use sin() to draw a pattern
void sinifyImg(){
  for(int i =  0; i < sz ; i++){
    for(int j =  0; j < sz ; j++){
      // use mouse to scale the sampling
      float valA = sin(i * mouseX * 0.001);
      float valB = sin(j * mouseY * 0.001);
      imgData[i][j] = floor( abs( valA  * valB  * 256) );
    }
  }
}

// use noise to draw a pattern
void noisifyImg(){
  // use mouse to scale the sampling
  float sclX = (mouseX*1.0/ width) * 0.1;
  float sclY = (mouseY*1.0/ height) * 0.1;

  for(int i =  0; i < sz ; i++){
    for(int j =  0; j < sz ; j++){
      imgData[i][j] = floor(   noise( i * sclX , j * sclY ) * 256  );
    }
  }
}

// get a random value for each pixel
void randomizeImg(){
  for(int i =  0; i < sz ; i++){
    for(int j =  0; j < sz ; j++){
      imgData[i][j] = floor(random(256));
    }
  }
}

// set the entire dataset as a uniform value
void populateImg(int n){
  for(int i =  0; i < sz ; i++){
    for(int j =  0; j < sz ; j++){
      imgData[i][j] = n;
    }
  }
}







// Enjoy!
