int [][] imgData;

int size = 64;

float zStep = 0.0;

void setup(){
  size(64, 64);
  
  imgData = new int[size][size];
  println("width  : " + width);
  println("height : " + height);
  
}

void draw(){
  
  float rectSize = width / size;
  noStroke();
  
  //randomizeImage();
  //noisifyImage();
  //sinefyImage();
  drawImage(rectSize);
  noLoop();
  
}

void randomizeImage(){
  
  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
        //imgData[i][j] = floor(random(256));
        imgData[i][j] = floor(random(256));
    }
  }
}

void populateImage(int n){
  
  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
        imgData[i][j] = n;
    }
  }
}

void noisifyImage(){
  
  //float stepX = (mouseX * 1.0 / width);
  //float stepY = (mouseY * 1.0 / height);
  
  println(zStep);
  
  if (mouseY > height / 2){
    zStep += 0.01;
  }
  else if (mouseY <= height / 2){
    zStep -= 0.01;
  }
  
  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
        //imgData[i][j] = floor(random(256));
        //imgData[i][j] = floor(noise(zStep, j * 0.015, 0.1) * 256);
        imgData[i][j] = floor(noise(i * 0.1, j * 0.1, frameCount*0.015) * 256);
    }
  }
}

void sinefyImage(){
  
  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
      
        int a = floor(map(sin(i*0.05), -1, 1, 0, 256));
        int c = floor(map((cos(i*0.1)), -1, 1, 0, 256));
        
        int b = floor(map(noise(i * 0.1, j * 0.1), -1, 1, 0, 256));
        
        //println("a: " + a);
        
        imgData[i][j] = a;
        //imgData[i][j] = floor(1.0 / (map(noise(i * 0.01, j * 0.01), -1, 1, 0, 1)));
    }
  }
}


void drawImage(float rectSize){
  
  loadPixels();
  
  for (int i = 0; i < height; i++){
    //int c = 0;
    for (int j = 0; j < width; j++){
        //fill(imgData[i][j]);
        //rect(i*rectSize, j*rectSize, rectSize, rectSize);
        int position = j * width + i;
        pixels[position] = color(0,0,255);
        //c++;
        
    }
    //println("c: " + c);
  }
  
  updatePixels();
  
}