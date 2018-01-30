#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(125);
	video.setDeviceID(0);
    video.setDesiredFrameRate(60);
    video.initGrabber(640, 480);
    debug = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    particleSys.applyForce(ofVec2f(0,-0.1));
    particleSys.update();
    
	video.update();		//Decode the new frame if needed
	//Do computing only if the new frame was obtained
	if ( video.isFrameNew() ) {
		//Store the previous frame, if it exists till now
		if ( grayImage.bAllocated ) {
			grayImagePrev = grayImage;
		}

		//Getting a new frame
		image.setFromPixels( video.getPixelsRef() );
		image.mirror(false, true);
		grayImage = image; //Convert to grayscale image

		//Do processing if grayImagePrev is inited
		if ( grayImagePrev.bAllocated ) {
			//Get absolute difference
			diff.absDiff( grayImage, grayImagePrev );

			//We want to amplify the difference to obtain
			//better visibility of motion
			//We do it by multiplication. But to do it, we
			//need to convert diff to float image first
			diffFloat = diff;	//Convert to float image
			diffFloat *= 5.0;	//Amplify the pixel values (original = 5.0)

			//Update the accumulation buffer
			if ( !bufferFloat.bAllocated ) {
				//If the buffer is not initialized, then
				//just set it equal to diffFloat
				bufferFloat = diffFloat;
			}
			else {
				//Slow damping the buffer to zero
				bufferFloat *= 0.65; //original = 0.85
				//Add current difference image to the buffer

				bufferFloat += diffFloat;
				bufferFloat.erode(); //helps get rid of noise (remove if not needed)
			}
		}
	}
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground( 255, 255, 255 );	//Set the background color

	//Draw only if diffFloat image is ready.
	//It happens when the second frame from the video is obtained
	if ( diffFloat.bAllocated ) {
		//Get image dimensions
		int w = grayImage.width;
		int h = grayImage.height;

        //Set color for images drawing
        ofSetColor( 255, 255, 255 );

        //Draw images grayImage,  diffFloat, bufferFloat
        if (debug)
        {
            grayImage.draw( 0, 0, w/2, h/2 );
            diffFloat.draw( w/2, 0, w/2, h/2 );
            bufferFloat.draw( 0, h/2, w/2, h/2 );
        }
        else image.draw( 0, 0, ofGetWidth(), ofGetHeight() );

        //Draw the image motion areas
        if (debug)
        {
            //Shift and scale the coordinate system
            ofPushMatrix();
            ofTranslate( w/2, h/2);
            ofScale( 0.5, 0.5 );
            //Draw bounding rectangle
            ofSetColor(0, 0, 0);
            ofNoFill();
        }

        //Get bufferFloat pixels
        float *pixels = bufferFloat.getPixelsAsFloats();

        //Scan all pixels
        for (int y=0; y<h; y+=1)
        {
            for (int x=0; x<w; x+=1)
            {
                //Get the pixel value
                float value = pixels[ x + w * y ];
                //If value exceed threshold, then draw pixel
                if ( value >= 0.9 ) {                           //original was 0.9
                    if (debug) {ofRect( x, y, 1, 1 );}
                    else if (ofRandom(1)<0.003){ particleSys.addParticle(x, y); }
                    
                   //EDIT HERE: this is where you'll be activating
                   //the grid locations or generating particles
                   //the debug mode draws small black points in the bottom right square
                }
            }
        }
	}
    
    particleSys.draw();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    debug = !debug;
}
