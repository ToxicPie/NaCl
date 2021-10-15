struct car_p {
  double x, y, z;
};
struct sph_p {
  double r, theta, phi;
};

sph_p conv(car_p p) {
  double r = sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
  double theta = asin(p.y / r);
  double phi = atan2(p.y, p.x);
  return {r, theta, phi};
}
car_p conv(sph_p p) {
  double x = p.r * cos(p.theta) * sin(p.phi);
  double y = p.r * cos(p.theta) * cos(p.phi);
  double z = p.r * sin(p.theta);
  return {x, y, z};
}
