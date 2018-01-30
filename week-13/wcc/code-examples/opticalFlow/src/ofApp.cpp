#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	video.setDeviceID(0);
    video.setDesiredFrameRate(60);
    video.initGrabber(640, 480);
    calculatedFlow = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	video.update();		//Decode the new frame if needed

	if ( video.isFrameNew() )
    {
		if ( gray1.bAllocated ) {
			gray2 = gray1;
			calculatedFlow = true;
		}

        //Convert to ofxCv images
        ofPixels & pixels = video.getPixels();
        currentColor.setFromPixels( pixels );

        float decimate = 0.25;              //Decimate images to 25% (makes calculations faster + works like a blurr too)
        ofxCvColorImage imageDecimated1;
        imageDecimated1.allocate( currentColor.width * decimate, currentColor.height * decimate );
        imageDecimated1.scaleIntoMe( currentColor, CV_INTER_AREA );             //High-quality resize
        gray1 = imageDecimated1;

		if ( gray2.bAllocated ) {
            Mat img1( gray1.getCvImage() );  //Create OpenCV images
            Mat img2( gray2.getCvImage() );
            Mat flow;                        //Image for flow
            //Computing optical flow (visit https://goo.gl/jm1Vfr for explanation of parameters)
            calcOpticalFlowFarneback( img1, img2, flow, 0.7, 3, 11, 5, 5, 1.1, 0 );
            //Split flow into separate images
            vector<Mat> flowPlanes;
            split( flow, flowPlanes );
            //Copy float planes to ofxCv images flowX and flowY
            //we call this to convert back from native openCV to ofxOpenCV data types
            IplImage iplX( flowPlanes[0] );
            flowX = &iplX;
            IplImage iplY( flowPlanes[1] );
            flowY = &iplY;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground( 255, 255, 255);	//Set the background color

    if (calculatedFlow)
    {
        ofSetColor( 255, 255, 255 );
        video.draw( 0, 0);

        int w = gray1.width;
        int h = gray1.height;

        //1. Input images + optical flow
        ofPushMatrix();
        ofScale( 4, 4 );

        //Optical flow
        float *flowXPixels = flowX.getPixelsAsFloats();
        float *flowYPixels = flowY.getPixelsAsFloats();
        ofSetColor( 0, 0, 255 );
        for (int y=0; y<h; y+=5) {
            for (int x=0; x<w; x+=5) {
                float fx = flowXPixels[ x + w * y ];
                float fy = flowYPixels[ x + w * y ];
                //Draw only long vectors
                if ( fabs( fx ) + fabs( fy ) > 1 ) {
                    ofDrawRectangle( x-0.5, y-0.5, 1, 1 );
                    ofDrawLine( x, y, x + fx, y + fy );
                }
            }
        }
        ofPopMatrix();
    }
}
