float distanceTo(float place[3], float dest[3]){
  float vecBetween[3];
  float distance;
  mathVecSubtract(vecBetween, dest, place, 3);
  distance = mathVecMagnitude(vecBetween, 3);
  return distance;
}
