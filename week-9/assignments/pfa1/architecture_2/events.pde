////////////////////////////
////////  EVENTS  //////////
////////////////////////////
void keyPressed(){
    if (key == 'a'){
        drawAxis = !drawAxis;
    }
    if (key == 'g'){
        drawGrid = !drawGrid;
    }
    if (key == 'd'){
        debug = !debug;
    }
    if (key == 's'){
        saveFrame("architectural_2_####.png");
    }
    println(mouseX);
    println(mouseY);
}