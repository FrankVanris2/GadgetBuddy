/**
 * @file Compass.cpp
 * @author Frank Vanris
 * @date 8/7/2025
 * @brief Implementation of the Compass class for GadgetBuddy, providing directional readings and error handling.
 *
 * This file contains the logic for interfacing with the QMC5883L compass sensor,
 * including sensor initialization, periodic sampling, error validation, and conversion
 * of raw readings to heading and cardinal direction for display.
 */

 #include "Compass.h"

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
 }

 void Compass::loop() {
     updateReadings();
 }

 void Compass::updateReadings() {
    mCompass.read();

    mX = mCompass.getX();
    mY = mCompass.getY();
    mZ = mCompass.getZ();
    byte azimuth = mCompass.getAzimuth();
    mHeading = static_cast<int>(azimuth);

    if (!validateReadings()) {
        mHasError = true;
        return;
    }

    char dirArray[3];
    mCompass.getDirection(dirArray, azimuth);
    mDirection[0] = dirArray[0];
    mDirection[1] = dirArray[1];
    mDirection[2] = dirArray[2];
    mDirection[3] = '\0';

    mHasError = false;
 }

 bool Compass::validateReadings() {
    if(mX == 0 && mY == 0 && mZ == 0) {
        return false;
    }

    if(mHeading < 0 || mHeading > 360) {
        return false;
    }

    return true;
 }

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
 