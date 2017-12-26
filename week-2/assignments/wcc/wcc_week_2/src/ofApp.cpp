//--------------------------------------------------------------
// @brief:  Computational rendition of "Circles in a Circle" artwork by Vassily_Kandinsky, 1923 
// Use keyboard shortcuts to show different parts of the image.
// R to show reference image
// B to show background
// C to show circles
// L to show the lines
// X to show the crossed shapes
// S to save the image
// @author: vvzen (valerio viperino)
//--------------------------------------------------------------
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cout << endl;
    cout << "***************" << endl;
    cout << "Program started" << endl;
    cout << "***************" << endl;
    cout << "Reference image loaded? " << reference_image.load("Vassily_Kandinsky_1923_-_Circles_in_a_Circle.jpg") << endl;
    cout << endl;

    // allocate memory for fbos
    reference_fbo.allocate(reference_image.getWidth(), reference_image.getHeight(), GL_RGBA);
    drawing_fbo.allocate(reference_image.getWidth(), reference_image.getHeight(), GL_RGBA, 8);
    circles_fbo.allocate(reference_image.getWidth(), reference_image.getHeight(), GL_RGBA, 8);
    xshapes_fbo.allocate(reference_image.getWidth(), reference_image.getHeight(), GL_RGBA, 8);
    bg_fbo.allocate(reference_image.getWidth(), reference_image.getHeight(), GL_RGBA, 8);

    // shortcuts
    show_background = true;
    show_reference = true;
    show_drawing = true;
    show_circles = true;
    show_xshapes = true;
}

//--------------------------------------------------------------
void ofApp::update(){

    ofEnableAntiAliasing();

    // the image reference
    ofPushStyle();
    reference_fbo.begin();
        ofClear(255, 255, 255, 0);
        //ofSetColor(255, 255, 255, 200);
        ofSetColor(255, 255, 255, 255);
        reference_image.draw(0, 0);
    reference_fbo.end();
    ofPopStyle();

    // background
    ofPushStyle();
    bg_fbo.begin();
        ofClear(0);
        ofSetColor(241, 224, 210, 220);
        //ofDrawRectangle(0, 0, bg_fbo.getWidth(), bg_fbo.getHeight());
        ofBeginShape();
            ofVertex(10, 7);
            ofVertex(657, 7);
            ofVertex(656, 669);
            ofVertex(10, 676);
        ofEndShape();
    bg_fbo.end();
    ofPopStyle();

    // crossing background shapes
    xshapes_fbo.begin();

        ofClear(255);
        ofBackground(255);

        ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
        ofPushStyle();
        ofSetPolyMode(OF_POLY_WINDING_NONZERO);
        ofSetHexColor(0x62A59A);
        ofBeginShape();
            ofVertex(129, 7);
            ofVertex(655, 646);
            ofVertex(655, 401);
            ofVertex(228, 7);
        ofEndShape();
        
        ofSetColor(208 ,168, 125, 220);
        ofBeginShape();
            ofVertex(606, 7);
            ofVertex(10, 494);
            ofVertex(10, 676);
            ofVertex(62, 676);
            ofVertex(657, 7);
        ofEndShape();
        ofPopStyle();
        ofDisableBlendMode();
    xshapes_fbo.end();

    // the lines
    ofPushStyle();
    drawing_fbo.begin();

        ofClear(0, 0);
        
        ofSetColor(0);

        // draw the main circle
        drawDonut(ofGetWidth()/2, ofGetHeight()/2 - 15, 266, 293);

        // draw the lines
        ofSetColor(0);
        ofSetLineWidth(1.9);
        ofDrawLine(460, 145, 399, 524);
        ofDrawLine(485, 134, 417, 563);
        ofDrawLine(127, 392, 521, 438);
        ofDrawLine(100, 282, 529, 401);
        ofDrawLine(179, 521, 248, 429);

        ofDrawLine(384, 513, 441, 476);
        ofDrawLine(388, 521, 447, 485);
        ofDrawLine(392, 531, 451, 494);
        
        ofDrawLine(127, 259, 100, 306);
        ofDrawLine(139, 261, 106, 302);
        
        ofDrawLine(178, 278, 165, 316);

        ofDrawLine(192, 527, 254, 436);

        ofSetLineWidth(2.1);
        ofDrawLine(125, 358, 309, 188);
        ofDrawLine(204, 138, 544, 387);
        ofDrawLine(102, 271, 531, 386);

        ofSetLineWidth(2.5);
        ofDrawLine(366, 148, 160, 420);
        ofDrawLine(339, 150, 366, 184);
        ofDrawLine(349, 139, 371, 173);

        ofDrawLine(478, 241, 505, 241);
        ofDrawLine(479, 251, 514, 251);
        // X
        ofDrawLine(167, 501, 292, 480);
        ofDrawLine(197, 471, 286, 522);

        ofDrawLine(472, 143, 408, 542);

        ofSetLineWidth(3);
        ofDrawLine(158, 175, 545, 239);
        ofDrawLine(93, 333, 552, 426);
        ofDrawLine(222, 528, 466, 117);
        ofDrawLine(132, 361, 453, 526);

        ofSetLineWidth(4);
        ofDrawLine(485, 218, 487, 477);
    
    drawing_fbo.end();
    ofPopStyle();

    // the inside circles
    circles_fbo.begin();
        
        ofClear(255);
        ofBackground(255);

        ofPushStyle();
        ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
        ofSetCircleResolution(64);

        // reds
        ofSetColor(149, 59, 78, 220);
        ofDrawCircle(153, 474, 19);
        ofSetHexColor(0x8C4322);
        drawDonut(153, 474, 19, 20);

        ofSetColor(149, 59, 78, 180);
        ofDrawCircle(260, 205, 66);
        ofSetColor(38, 23, 15, 200);
        drawDonut(260, 205, 66, 68);
        
        ofSetColor(178, 23, 37);
        ofDrawCircle(340, 233, 53);
        
        ofSetHexColor(0xC08079);
        ofDrawCircle(365, 532, 17);
        ofSetColor(0);
        drawDonut(365, 532, 17, 19);
        
        ofSetHexColor(0xCC5557);
        ofDrawCircle(244, 431, 28);
        ofSetHexColor(0x511A15);
        drawDonut(244, 431, 28, 30);
        
        ofSetHexColor(0xCC5557);
        ofDrawCircle(320, 458, 6);
        ofSetHexColor(0x00000);
        drawDonut(320, 458, 6, 7);

        ofSetHexColor(0xB85C6E);
        ofDrawCircle(513, 472, 12);
        ofSetHexColor(0x00000);
        drawDonut(513, 472, 12, 13);

        // cyan
        ofSetHexColor(0x6D9781);
        ofDrawCircle(259, 271, 37);
        
        ofSetHexColor(0x6D9781);
        ofDrawCircle(443, 310, 76);
        
        ofSetHexColor(0x6D9781);
        ofDrawCircle(190, 388, 24);
        ofSetHexColor(0x00000);
        drawDonut(190, 388, 24, 27);
        
        // yellow
        ofSetColor(236, 197, 105);
        ofDrawCircle(420, 411, 51);
        ofDrawCircle(265, 367, 76);
        ofDrawCircle(395, 484, 8);

        // dark purple
        // ofSetColor(137, 85, 99);
        ofSetColor(101, 50, 104, 220);
        ofDrawCircle(451, 187, 38);

        // greyish
        ofSetColor(60, 71, 57, 200);
        ofDrawCircle(318, 355, 92);

        // dark blue
        ofSetHexColor(0x27446C);
        ofDrawCircle(112, 382, 8);
        ofSetHexColor(0x00000);
        drawDonut(112, 382, 7, 9);

        ofSetHexColor(0x1E2223);
        ofDrawCircle(403, 218, 20);
        ofDrawCircle(452, 271, 13);
        ofDrawCircle(449, 445, 13);
        ofDrawCircle(277, 474, 4);

        ofSetColor(1, 85, 131, 220);
        ofDrawCircle(508, 318, 27);

        ofDisableBlendMode();
        
        ofPopStyle();
        
    circles_fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){

    // show different parts of the image based on keyboard shortcuts
    if (show_reference){
        reference_fbo.draw(0, 0);
    }
    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    if (show_background){
        bg_fbo.draw(0, 0);
    }
    if (show_drawing){
        drawing_fbo.draw(0, 0);
    }
    if (show_xshapes){
        xshapes_fbo.draw(0, 0);
    }
    if (show_circles){
        circles_fbo.draw(0, 0);

        // draw the center circle in add blend mode
        ofPushStyle();
        ofSetCircleResolution(40);
        ofEnableBlendMode(OF_BLENDMODE_SCREEN);
        ofSetColor(238, 59, 57, 240);
        ofDrawCircle(309, 308, 33);
        ofDisableBlendMode();
        ofSetColor(0);
        drawDonut(309, 308, 33, 37);
        ofDrawCircle(309, 308, 9);

        // draw the circles with no blending modes
        ofSetHexColor(0x681120);
        ofDrawCircle(338, 394, 9);

        ofSetHexColor(0xAF212F);
        ofDrawCircle(309, 97, 6);
        ofSetHexColor(0x00000);
        drawDonut(309, 97, 6, 8);

        ofSetColor(195, 24, 33);
        ofDrawCircle(145, 308, 15);
        ofSetColor(0);
        drawDonut(145, 308, 14, 21);
        ofPopStyle();
    }
    ofDisableBlendMode();
}

//--------------------------------------------------------------
// openframeworks has no nice built-in method to draw a circle
// with a bigger stroke width, hence I created a "donut" method
//--------------------------------------------------------------
void ofApp::drawDonut(float x, float y, float innerRadius, float outerRadius){

    ofMesh donut_mesh;
    donut_mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

    float shift = 0.2;

    // draw the triangle strip around a center point using polar coords
    for (float angle = 0; angle < 2 * PI; angle+=0.1){
        
        ofVec3f v_inner(innerRadius * cos(angle), innerRadius * sin(angle), 0.0);
        ofVec3f v_outer(outerRadius * cos(angle + shift), outerRadius * sin(angle + shift), 0.0);

        donut_mesh.addVertex(v_inner);
        donut_mesh.addVertex(v_outer);
    }
    // close the strip
    ofVec3f v_inner(innerRadius * cos(0), innerRadius * sin(0), 0.0);
    ofVec3f v_outer(outerRadius * cos(0 + shift), outerRadius * sin(0 + shift), 0.0);

    donut_mesh.addVertex(v_inner);
    donut_mesh.addVertex(v_outer);

    // offset
    ofPushMatrix();
        ofTranslate(x, y, 0);
        donut_mesh.draw();
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key){
        case 'r':
            show_reference = !show_reference;
            break;
        case 'l':
            show_drawing = !show_drawing;
            break;
        case 'c':
            show_circles = !show_circles;
            break;
        case 'x':
            show_xshapes = !show_xshapes;
            break;
        case 'b':
            show_background = !show_background;
            break;
        case 's':
            grab.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
            grab.save("screenshot.png");
            break;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    // print to stdout current position of mouse
    cout << "current mouse position: " << x << ", " << y << endl;
}
