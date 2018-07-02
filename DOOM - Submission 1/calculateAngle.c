float calculateAngle(float vec1[3], float vec2[3]) {
    float product = mathVecInner(vec1, vec2, 3);
    float mag1 = mathVecMagnitude(vec1, 3);
    float mag2 = mathVecMagnitude(vec2, 3);
    float result = acosf(product/(mag1*mag2));
    //DEBUG(("Angle between these two vectors in radians is %f", result));
    return result;
}
