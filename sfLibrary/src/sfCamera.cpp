#include "sfCamera.h"

void sfCamera::focalPoint()
{
	focalPointCoord.x = 0;
	focalPointCoord.y = 0;
	focalPointCoord.z = 0;
}

void sfCamera::location()
{
	cameraCoord.x = 0;
	cameraCoord.y = 0;
	// Can't use GLUT or OpenFrameworks because the GL context has
	// not been created at object contruction when run from within
	// Resolume.
	cameraCoord.z = 500; //(float)glutGet(GLUT_WINDOW_WIDTH) * 1.5;
}

void sfCamera::place()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	gluPerspective(fieldOfView, aspectRatio, zNear, zFar);
	gluPerspective(fieldOfView, (float)ofGetWidth()/ofGetHeight(), zNear, zFar);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef( 1, 1, 1 );
	gluLookAt( cameraCoord[0], cameraCoord[1], cameraCoord[2], focalPointCoord[0], focalPointCoord[1], focalPointCoord[2], upVec[0], upVec[1], upVec[2]);
}

//void sfCamera::place(){
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(fieldOfView, aspectRatio, zNear, zFar);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(focalPointCoord[0], focalPointCoord[1], focalPointCoord[2], cameraCoord[0], cameraCoord[1], cameraCoord[2], upVec[0], upVec[1], upVec[2]);
//	glScalef(1, -1, 1);
//	glTranslatef(0, -h, 0);
//}

// TODO How should I implement these? Where along the z line should this return a point?
ofxVec3f sfCamera::getViewportCenter()
{
	return ofxVec3f( _viewportCenter );
}

ofxVec3f sfCamera::getViewportSize()
{
	return ofxVec3f( _viewportSize );
}

ofxVec3f sfCamera::getViewportLowerLeft()
{
	return ofxVec3f( _viewportLowerLeft );
}

float sfCamera::getViewportLeft()
{
	ofxVec3f vVLL = getViewportLowerLeft();
	return vVLL.x;
}

float sfCamera::getViewportRight()
{
	ofxVec3f vVLL = getViewportLowerLeft();
	ofxVec3f vVS = getViewportSize();
	return vVLL.x + vVS.x;
}

float sfCamera::getViewportTop()
{
	ofxVec3f vVLL = getViewportLowerLeft();
	ofxVec3f vVS = getViewportSize();
	return vVLL.y + vVS.y;
}

float sfCamera::getViewportBottom()
{
	ofxVec3f vVLL = getViewportLowerLeft();
	return vVLL.y;
}



sfCamera::sfCamera(){
	perspective();
	focalPoint();
	location();
	up();
}

void sfCamera::focalPoint(float x, float y, float z){
	focalPointCoord.x = x;
	focalPointCoord.y = y;
	focalPointCoord.z = z;
}
void sfCamera::focalPoint(ofxVec3f _pos){
	focalPointCoord = _pos;
}
//void sfCamera::focalPoint(){
//	focalPointCoord.x = (float)w/2.0f;
//	focalPointCoord.y = (float)h/2.0f;
//	float halfFov = PI * fieldOfView / 360.0f;
//	float theTan = tanf(halfFov);
//	focalPointCoord.z = focalPointCoord.y/theTan;
//}

void sfCamera::lerpPosition(float _targetX, float _targetY, float _targetZ, float _step){
	cameraCoord.x += (_targetX - cameraCoord.x) * _step;
	cameraCoord.y += (_targetY - cameraCoord.y) * _step;
	cameraCoord.z += (_targetZ - cameraCoord.z) * _step;
}

void sfCamera::lerpPosition(ofxVec3f target, float step){
	lerpPosition(target.x, target.y, target.z, step);
}

void sfCamera::location(float x, float y, float z){
	cameraCoord.x = x;
	cameraCoord.y = y;
	cameraCoord.z = z;
}

void sfCamera::location(ofxVec3f _pos){
	cameraCoord = _pos;
}

//void sfCamera::location(){
//	cameraCoord.x = (float)w/2.0f;
//	cameraCoord.y = (float)h/2.0f;
//	cameraCoord.z = 0;
//}


void sfCamera::up(float _nx, float _ny, float _nz){
	upVec.x = _nx;
	upVec.y = _ny;
	upVec.z = _nz;
}

void sfCamera::up(ofxVec3f _up){
	upVec = _up;
}


void sfCamera::up(){
	upVec.x = 0;
	upVec.y = 1;
	upVec.z = 0;
}

void sfCamera::perspective(float _fov, float _aspect, float _zNear, float _zFar){
	fieldOfView = _fov;
	aspectRatio = _aspect;
	if(_zNear==0) _zNear = 0.01;
	zNear = _zNear;
	zFar = _zFar;
}

void sfCamera::perspective(){
	fieldOfView = 65.0f;
	// Cannot get width/height from GLUT or OpenFrameworks because
	// the GL context isn't loaded during object construction when
	// run from within Resolume.
	w = 640; //glutGet(GLUT_WINDOW_WIDTH);
	h = 480; //glutGet(GLUT_WINDOW_HEIGHT);
	aspectRatio = (float)w/(float)h;
	zNear = 1.0f;
	zFar = 10000.0f;
}


//Removes the camera, so it returns as if there was no camera
void sfCamera::remove(){
	ofSetupScreen();
}



void sfCamera::moveLocal(float _x, float _y, float _z){
	moveLocal(ofxVec3f(_x, _y, _z));
}

void sfCamera::moveLocal(ofxVec3f move){
	ofxVec3f dir =  getDir().normalized();
	focalPointCoord += dir.rescaled(move.z);
	cameraCoord += dir.rescaled(move.z);

	focalPointCoord += upVec.rescaled(move.y);
	cameraCoord += upVec.rescaled(move.y);

	focalPointCoord += dir.cross(upVec).rescaled(move.x);
	cameraCoord += dir.cross(upVec).rescaled(move.x);
}

void sfCamera::moveGlobal(float _x, float _y, float _z){
	focalPointCoord.x += _x;
	focalPointCoord.y += _y;
	focalPointCoord.z += _z;
	cameraCoord.x += _x;
	cameraCoord.y += _y;
	cameraCoord.z += _z;
}
void sfCamera::moveGlobal(ofxVec3f move){
	focalPointCoord += move;
	cameraCoord += move;
}

void sfCamera::orbitAround(ofxVec3f target, ofxVec3f axis, float angle){
	ofxVec3f vT = target;
	ofxVec3f r = cameraCoord-target;
	ofxVec3f vRotated = r.rotated(angle, axis);
	ofxVec3f vNewEye = target + vRotated;
	cameraCoord = vNewEye;
}

void sfCamera::rotate(ofxVec3f axis, float angle){
	ofxVec3f r = -cameraCoord+focalPointCoord;
	focalPointCoord = cameraCoord + r.rotated(angle, axis);
}

//
//Getters
//
ofxVec3f sfCamera::getDir(){
	return focalPointCoord-cameraCoord;
}

ofxVec3f sfCamera::getFocalPoint(){
	return focalPointCoord;
}

ofxVec3f sfCamera::getLocation(){
	return cameraCoord;
}

ofxVec3f sfCamera::getUp(){
	return upVec;
}
