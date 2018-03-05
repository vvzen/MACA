#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(40, 100, 40);
	// open an outgoing connection to HOST:PORT
	sender.setup(HOST, PORT);
	
	receiver.setup(RECEIVE_PORT);
}

//--------------------------------------------------------------
void ofApp::update(){

	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(m);

		// check for mouse moved message
		if(m.getAddress() == "/coords/"){
			// both the arguments are ints
			float x = m.getArgAsFloat(0);
			float y = m.getArgAsFloat(1);
			received_points.push_back(ofPoint(x, y));
		}
		else if (m.getAddress() == "/clear/"){
			received_points.clear();
		}
		else if (m.getAddress() == "/newline/"){
			ofPolyline line;
			cout << "received new line" << endl;
			for (int i = 0; i < received_points.size(); i++){
				line.addVertex(received_points.at(i).x, received_points.at(i).y);
			}
			received_lines.push_back(line);
			received_points.clear();
		}
		/* // check for mouse button message
		else if(m.getAddress() == "/mouse/button"){
			// the single argument is a string
			mouseButtonState = m.getArgAsString(1);
		}
		else if (m.getAddress() == "/test") {
			string msg_string;
            myNum = m.getArgAsInt(0);
            myNum2 = m.getArgAsFloat(1);
            myString = m.getArgAsString(2);
            myTime = m.getArgAsFloat(3);
            msg_string = m.getAddress() + " " + ofToString(myNum) + " " + ofToString(myNum2) + " " + myString + " " + ofToString(myTime);// + " " + msg_string;
            messageBuffer.push_front(msg_string);
		}
        else {
            // unrecognized message: display on the bottom of the screen
            messageBuffer.push_front(m.getAddress() + ": UNRECOGNIZED MESSAGE");
        } */
	}

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackground(0);

	// display instructions
	string buf;
	buf = "sending osc messages to" + string(HOST) + ofToString(PORT);
	ofDrawBitmapString(buf, 10, 20);
	ofDrawBitmapString("move the mouse to send osc message [/mouse/position <x> <y>]", 10, 50);
	ofDrawBitmapString("click to send osc message [/mouse/button <button> <\"up\"|\"down\">]", 10, 65);
	ofDrawBitmapString("press A to send osc message [/test 1 3.5 hello <time>]", 10, 80);

	// ofPolyline my_line;
	
	// my points
	// for (int i = 0; i < positions.size(); i++){
	// 	my_line.addVertex(positions.at(i));
	// }
	// ofPolyline his_line;

	/* // the points I received
	for (int i = 0; i < received_points.size(); i++){
		his_line.addVertex(received_points.at(i));
	} */


	for (int p = 0; p < received_lines.size(); p++){
		ofPolyline line = received_lines.at(p);
		line.draw();
		// for (int i = 0; i < line.size(); i++){
		// 	line.addVertex(line.)
		// }
	}

	// my_line.draw();
	// his_line.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	// if(key == 'a' || key == 'A'){
	// 	ofxOscMessage m;
	// 	m.setAddress("/test");
	// 	m.addIntArg(1);
	// 	m.addFloatArg(3.5f);
	// 	m.addStringArg("hello");
	// 	m.addFloatArg(ofGetElapsedTimef());
	// 	sender.sendMessage(m, false);
	// }

	switch (key){
		case 's':{
			ofxOscMessage m;
			m.setAddress("/coords/");

			cout << "here!" << endl;
			
			// for (int i = 0; i < positions.size(); i++){
			//	m.addFloatArg(positions.at(i).x);
			//	m.addFloatArg(positions.at(i).y);
			// }
			
			sender.sendMessage(m, false);
			break;
		}
		case 'c' : {
			ofxOscMessage m;
			m.setAddress("/clear/");

			cout << "clear!" << endl;

			positions.clear();

			// for (int i = 0; i < positions.size(); i++){
			//	m.addFloatArg(positions.at(i).x);
			//	m.addFloatArg(positions.at(i).y);
			// }
			
			sender.sendMessage(m, false);
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
	
	// ofxOscMessage m;
	
	// m.setAddress("/mouse/position");
	// m.addIntArg(x);
	// m.addIntArg(y);

	// sender.sendMessage(m, false);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	// ofxOscMessage m;
	// m.setAddress("/mouse/button");
	// m.addIntArg(button);
	// m.addStringArg("down");
	// sender.sendMessage(m, false);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	// ofxOscMessage m;
	// m.setAddress("/mouse/button");
	// m.addIntArg(button);
	// m.addStringArg("up");
	// sender.sendMessage(m, false);

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

	positions.push_back(ofPoint(x, y));

	ofxOscMessage m;
	m.setAddress("/coords/");

	cout << "here!" << endl;
	
	m.addFloatArg(x);
	m.addFloatArg(y);

	sender.sendMessage(m, false);

	// ofxOscMessage m;
	// m.setAddress("/mouse/dragged");
	// m.addIntArg(button);
	// m.addStringArg("up");
	// sender.sendMessage(m, false);

}

