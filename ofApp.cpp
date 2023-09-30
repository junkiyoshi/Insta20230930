#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetCircleResolution(36);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	for (int i = this->location_list.size() - 1; i >= 0; i--) {

		this->radius_list[i] += this->speed_list[i];

		if (this->radius_list[i] > this->max_radius_list[i]) {

			this->location_list.erase(this->location_list.begin() + i);
			this->radius_list.erase(this->radius_list.begin() + i);
			this->speed_list.erase(this->speed_list.begin() + i);
			this->max_radius_list.erase(this->max_radius_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
		}
	}

	ofColor color;
	for (int i = 0; i < 100; i++) {

		int y = (int)(ofGetFrameNum() * 5 + (i % 2) * 360) % 720 - 360;
		int x = ofRandom(-300, 300);
		color.setHsb(ofMap((int)(x  + 300 + ofRandom(100)) % 300, 0, 300, 0, 255), 180, 255);

		auto location = glm::vec2(x, y);
		this->location_list.push_back(location);
		this->radius_list.push_back(1);
		this->speed_list.push_back(ofRandom(0.5, 2.5));
		this->max_radius_list.push_back(ofRandom(5, ofRandom(10, 30)));
		this->color_list.push_back(color);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int i = 0; i < this->location_list.size(); i++) {

		ofNoFill();
		ofSetColor(this->color_list[i], this->radius_list[i] < this->max_radius_list[i] * 0.5 ? 255 : ofMap(this->radius_list[i], this->max_radius_list[i] * 0.5, this->max_radius_list[i], 255, 30));
		ofDrawCircle(this->location_list[i], this->radius_list[i]);

		ofFill();
		ofSetColor(this->color_list[i], ofMap(this->radius_list[i], 1, this->max_radius_list[i], 255, 30));
		ofDrawCircle(this->location_list[i], this->radius_list[i]);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}