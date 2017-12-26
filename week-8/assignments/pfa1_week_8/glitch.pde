/* 
    Here go all the functions and variables related to glitching.
    Glitch code taken from:

    ASDF Pixel Sort
    Kim Asendorf | 2010 | kimasendorf.com
 
    sorting modes
 
    0 = black
    1 = brightness
    2 = white
 
 */


int glitch_mode = glitchMode;

// image path is relative to sketch directory
// PImage glitchedImage;
// String glitchedImageFileName = "moonwalk";
// String fileType = "jpg";

// int loops = 1;

// threshold values to determine sorting start and end pixels
int blackValue;
int brightnessValue;
int whiteValue;

int row;
int column;

// set the current initial state of the vars required by the glitch
void initValues(){

    glitch_mode = glitchMode;

    // threshold values to determine sorting start and end pixels
    blackValue = -16000000;
    brightnessValue = brightnessThreshold;
    whiteValue = -13000000;

    row = 0;
    column = 0;
}

void sortRow() {
  // current row
  int y = row;
  
  // where to start sorting
  int x = 0;
  
  // where to stop sorting
  int xend = 0;
  
  while(xend < glitchedImage.width-1) {
    switch(glitch_mode) {
        case 0:
            x = getFirstNotBlackX(x, y);
            xend = getNextBlackX(x, y);
            break;
        case 1:
            x = getFirstBrightX(x, y);
            xend = getNextDarkX(x, y);
            break;
        case 2:
            x = getFirstNotWhiteX(x, y);
            xend = getNextWhiteX(x, y);
            break;
        default:
            break;
    }
    
    if(x < 0) break;
    
    int sortLength = xend-x;
    
    color[] unsorted = new color[sortLength];
    color[] sorted = new color[sortLength];
    
    for(int i=0; i<sortLength; i++) {
        unsorted[i] = glitchedImage.pixels[x + i + y * glitchedImage.width];
    }
    
    sorted = sort(unsorted);
    
    for(int i=0; i<sortLength; i++) {
        glitchedImage.pixels[x + i + y * glitchedImage.width] = sorted[i];      
    }
    
    x = xend+1;
  }
}


void sortColumn() {
    // current column
    int x = column;
  
    // where to start sorting
    int y = 0;
  
    // where to stop sorting
    int yend = 0;
  
    while(yend < glitchedImage.height-1) {
    
        switch(glitch_mode) {
            case 0:
                y = getFirstNotBlackY(x, y);
                yend = getNextBlackY(x, y);
                break;
            case 1:
                y = getFirstBrightY(x, y);
                yend = getNextDarkY(x, y);
                break;
            case 2:
                y = getFirstNotWhiteY(x, y);
                yend = getNextWhiteY(x, y);
                break;
            default:
                break;
        }
        
        if(y < 0) break;
        
        int sortLength = yend-y;
        
        color[] unsorted = new color[sortLength];
        color[] sorted = new color[sortLength];
        
        for(int i=0; i<sortLength; i++) {
            unsorted[i] = glitchedImage.pixels[x + (y+i) * glitchedImage.width];
        }
        
        sorted = sort(unsorted);
        
        for(int i=0; i<sortLength; i++) {
            glitchedImage.pixels[x + (y+i) * glitchedImage.width] = sorted[i];
        }
        
        y = yend+1;
    }
}


// black x
int getFirstNotBlackX(int x, int y) {
  
    while(glitchedImage.pixels[x + y * glitchedImage.width] < blackValue) {
        x++;
        if(x >= glitchedImage.width) 
            return -1;
    }
    
    return x;
}

int getNextBlackX(int x, int y) {
    x++;
    
    while(glitchedImage.pixels[x + y * glitchedImage.width] > blackValue) {
        x++;
        if(x >= glitchedImage.width) 
            return glitchedImage.width-1;
    }
    
    return x-1;
}

// brightness x
int getFirstBrightX(int x, int y) {
  
    while(brightness(glitchedImage.pixels[x + y * glitchedImage.width]) < brightnessValue) {
        x++;
        if(x >= glitchedImage.width){
            return -1;
        }
    }
  
    return x;
}

int getNextDarkX(int _x, int _y) {
    int x = _x+1;
    int y = _y;
    
    while(brightness(glitchedImage.pixels[x + y * glitchedImage.width]) > brightnessValue) {
        x++;
        if(x >= glitchedImage.width)
            return glitchedImage.width-1;
    }
    return x-1;
}

// white x
int getFirstNotWhiteX(int x, int y) {

    while(glitchedImage.pixels[x + y * glitchedImage.width] > whiteValue) {
        x++;
        if(x >= glitchedImage.width) 
            return -1;
    }
    return x;
}

int getNextWhiteX(int x, int y) {
    x++;

    while(glitchedImage.pixels[x + y * glitchedImage.width] < whiteValue) {
        x++;
        if(x >= glitchedImage.width) 
            return glitchedImage.width-1;
    }
    return x-1;
}


// black y
int getFirstNotBlackY(int x, int y) {

    if(y < glitchedImage.height) {
        while(glitchedImage.pixels[x + y * glitchedImage.width] < blackValue) {
            y++;
            if(y >= glitchedImage.height)
                return -1;
        }
    }
  
    return y;
}

int getNextBlackY(int x, int y) {
  y++;

    if(y < glitchedImage.height) {
        while(glitchedImage.pixels[x + y * glitchedImage.width] > blackValue) {
            y++;
            if(y >= glitchedImage.height)
                return glitchedImage.height-1;
        }
    }
  
    return y-1;
}

// brightness y
int getFirstBrightY(int x, int y) {

    if(y < glitchedImage.height) {
        while(brightness(glitchedImage.pixels[x + y * glitchedImage.width]) < brightnessValue) {
            y++;
            if(y >= glitchedImage.height)
                return -1;
        }
    }
  
    return y;
}

int getNextDarkY(int x, int y) {
  y++;

    if(y < glitchedImage.height) {
        while(brightness(glitchedImage.pixels[x + y * glitchedImage.width]) > brightnessValue) {
            y++;
            if(y >= glitchedImage.height)
                return glitchedImage.height-1;
        }
    }

    return y-1;
}

// white y
int getFirstNotWhiteY(int x, int y) {

    if(y < glitchedImage.height) {
        while(glitchedImage.pixels[x + y * glitchedImage.width] > whiteValue) {
            y++;
            if(y >= glitchedImage.height)
                return -1;
        }
    }
  
    return y;
}

int getNextWhiteY(int x, int y) {
  y++;
  
    if(y < glitchedImage.height) {
        while(glitchedImage.pixels[x + y * glitchedImage.width] < whiteValue) {
            y++;
            if(y >= glitchedImage.height) 
                return glitchedImage.height-1;
        }
    }
  
    return y-1;
}