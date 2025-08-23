/**
 * By: Frank Vanris
 * Date: 8/7/2025
 * Desc: Creating a Compass class for the GadgetBuddy, a new screen state for project direction.
 */

 #include "Compass.h"
 #include "data&states/PinDeclarationsConstants.h"

 const char* COMPASS_ERROR_MSG = "Compass Error!";

 Compass::Compass() : 
    mHasError(false),
    mX(0), mY(0), mZ(0), mHeading(0) 
 {
    strcpy(mDirection, "N");
 }
 

 void Compass::setup() {
     mCompass.init();
     mCompass.setMagneticDeclination(15, 1);    
     mHasError = false;
 }

 void Compass::loop() {
     updateReadings();
 }


 void Compass::updateReadings() {
    // Read compass data
    mCompass.read();

    // Get raw values
    mX = mCompass.getX();
    mY = mCompass.getY();
    mZ = mCompass.getZ();
    byte azimuth = mCompass.getAzimuth();
    mHeading = static_cast<int>(azimuth);

    // Validate readings
    if (!validateReadings()) {
        mHasError = true;
        return;
    }

    // use library's getDirection method like in my test
    char dirArray[3];
    mCompass.getDirection(dirArray, azimuth);
    mDirection[0] = dirArray[0];
    mDirection[1] = dirArray[1];
    mDirection[2] = dirArray[2];
    mDirection[3] = '\0';

    mHasError = false;
 }

 bool Compass::validateReadings() {
    // Check for sensor connection issues
    if(mX == 0 && mY == 0 && mZ == 0) {
        return false;
    }

    // Check for reasonable heading values
    if(mHeading < 0 || mHeading > 360) {
        return false;
    }

    return true;
 }

 // CompassInterface implementations
 int Compass::getHeading() const {
    return mHasError ? 0 : mHeading;
 }

 const char* Compass::getDirection() const {
    return mHasError ? "ERR" : mDirection;
 }

 int Compass::getX() const {
    return mHasError ? 0 : mX;
 }

 int Compass::getY() const {
    return mHasError ? 0 : mY;
 }

 int Compass::getZ() const {
    return mHasError ? 0 : mZ;
 }

 const char* Compass::getErrorMessage() {
     return mHasError ? COMPASS_ERROR_MSG : nullptr;
 }
 