import processing.serial.*;

Serial port;
PImage logo;
int bg_color = 0;
String received_data = null;

int new_line_char_ascii = 10;

void setup(){
  colorMode(HSB, 255);
   
  size(10, 10);
  
  println("Available serial ports: ");
  for (int i = 0; i < Serial.list().length; i++){
    println("\t" + Serial.list()[i]); 
  }
  
  logo = loadImage("http://arduino.cc/logo.png");
  surface.setResizable(true);
  surface.setSize(logo.width, logo.height);
  
  port = new Serial(this, Serial.list()[1], 9600);
  port.clear();
}

void draw(){
  
  while (port.available() > 0){
    received_data = port.readStringUntil(new_line_char_ascii);
    if (received_data != null && "".equals(received_data.trim()) == false){
      print("received_data: ");
      print(received_data.trim());
      
      bg_color = Integer.parseInt(received_data.trim());
      print(", bg color: ");
      println(bg_color);
     
    }
    else {
      bg_color = 0;
    }
    //println(port.read());
  }
  
  background(bg_color);
  image(logo, 0, 0);
  
  port.clear();
}