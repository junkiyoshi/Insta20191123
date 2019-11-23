#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(1.5);

	ofNoFill();
}

//--------------------------------------------------------------
void ofApp::update() {

	this->gon = 4;
	this->gon = 8;
	for (auto i = 0; i < this->gon; i++) {

		this->gap_list.push_back(0);
	}
} 

//--------------------------------------------------------------
void ofApp::draw() {

	auto span = 144;
	auto radius = 95;
	int deg_span = 360 / 4;
	for (int x = span * 0.5; x < ofGetWidth(); x += span) {

		for (int y = span * 0.5; y < ofGetHeight(); y += span) {

			ofSeedRandom(x + ofGetWidth() * y);

			ofPushMatrix();
			ofTranslate(x, y);

			for (auto& gap : this->gap_list) { gap = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, 0.001, 0.1); }

			vector<glm::vec2> vertices;
			auto first = true;
			for (int i = 0; i < 1000; i++) {

				if (first) {

					for (auto deg = 0 + 45; deg < 360 + 45; deg += deg_span) {

						vertices.push_back(glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
					}

					ofBeginShape();
					ofVertices(vertices);
					ofEndShape(true);

					first = false;
				}
				else {

					vector<glm::vec2> tmp;
					for (auto k = 0; k < vertices.size(); k++) {

						tmp.push_back(vertices[k] + (vertices[(k + 1) % vertices.size()] - vertices[k]) * this->gap_list[k]);
					}

					for (auto k = 0; k < vertices.size(); k++) {

						ofDrawLine(vertices[k], tmp[k]);
					}

					vertices = tmp;
				}

				if (glm::distance(vertices[0], vertices[1]) < 1) {

					break;
				}
			}

			ofPopMatrix();
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}