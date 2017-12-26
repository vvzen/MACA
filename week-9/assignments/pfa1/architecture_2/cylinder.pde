/*-------------------------------------------------
@brief:   Draws a cylinder
@args:    
@details: taken from http://vormplus.be/blog/article/drawing-a-cylinder-with-processing
@author:  Jan Vantomme
@return:  
-------------------------------------------------*/
void cylinder(float r, float h, int sides){

    float angle = 360 / sides;
    float halfHeight = h / 2;

    // draw top shape
    beginShape();
    for (int i = 0; i < sides; i++) {
        float x = cos( radians( i * angle ) ) * r;
        float y = sin( radians( i * angle ) ) * r;
        vertex( x, y, -halfHeight );    
    }
    endShape(CLOSE);

    // draw bottom shape
    beginShape();
    for (int i = 0; i < sides; i++) {
        float x = cos( radians( i * angle ) ) * r;
        float y = sin( radians( i * angle ) ) * r;
        vertex( x, y, halfHeight );    
    }
    endShape(CLOSE);

    // draw body
    beginShape(TRIANGLE_STRIP);
    for (int i = 0; i <= sides + 1; i++) {
        float x = cos( radians( i * angle ) ) * r;
        float y = sin( radians( i * angle ) ) * r;
        vertex( x, y, halfHeight);
        vertex( x, y, -halfHeight);    
    }
    endShape(CLOSE);
}

void drawCircle(float r, float h, int sides){

    float angle = 360 / sides;
    float halfHeight = h / 2;

    beginShape();
    for (int i = 0; i < sides; i++) {
        float x = cos( radians( i * angle ) ) * r;
        float y = sin( radians( i * angle ) ) * r;
        vertex( x, y, -halfHeight );    
    }
    endShape(CLOSE);
}