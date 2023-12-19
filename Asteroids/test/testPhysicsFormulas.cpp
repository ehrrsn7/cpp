/**********************************************************************
 * testPhysicsFormulas.cpp
 * orbitSimulator
 **********************************************************************/

#include "testPhysicsFormulas.hpp"

#ifdef __APPLE__
#include "physicsFormulas.hpp"  // functions to test
#include "vector.hpp"           // for Vector/children
#include "movingObject.hpp"     // for MovingObject
#include "uiInteract.hpp"       // for timestamp and seconds typedefs
#endif
#ifdef _WIN32
#include "physics-components/physicsFormulas.hpp"
#include "physics-components/vector.hpp"
#include "game-objects/moving-objects/movingObject.hpp"
#include "ui/uiInteract.hpp"
#endif

// assert helpers
double nearest(double num, int precision)
{  // rounds `num` to the nearest `precision`
   return round(num * pow(10, precision)) / pow(10, precision);
}

// test functions
void test_trigX()
{  // setup
   double magnitude = 2 * sqrt(2);
   double angleRadians = M_PI/4;
   // exercise
   auto x = trigX(magnitude, angleRadians);
   // verify
   assert(x == 2);
   assert(typeid(x) == typeid(double));
}  // breakdown

void test_trigY()
{  // setup
   double magnitude = 2 * sqrt(2);
   double angleRadians = M_PI/4;
   // exercise
   auto y = trigY(magnitude, angleRadians);
   // verify
   assert(nearest(y, 10) == 2);
   assert(typeid(y) == typeid(double));
}  // breakdown

void test_trigX_vector()
{  // setup
   Vector v;
   v.setPolar(2 * sqrt(2), M_PI/4);
   // exercise
   auto x = trigX(v);
   // verify
   assert(x == 2);
   assert(typeid(x) == typeid(double));
}  // breakdown

void test_trigY_vector()
{  // setup
   Vector v;
   v.setPolar(2 * sqrt(2), M_PI/4);
   // exercise
   auto y = trigY(v);
   // verify
   assert(nearest(y, 10) == 2);
   assert(typeid(y) == typeid(double));
}  // breakdown

void test_mag()
{  // setup
   double x = 2;
   double y = 2;
   // exercise
   auto r = mag(x, y);
   // verify
   assert(r == 2 * sqrt(2));
   assert(typeid(r) == typeid(double));
}  // breakdown

void test_mag_vector()
{  // setup
   Vector v(2, 2);
   // exercise
   auto r = mag(v);
   // verify
   assert(r == 2 * sqrt(2));
   assert(typeid(r) == typeid(double));
}  // breakdown

void test_deg()
{  // setup
   double angleRadians = 3 * M_PI/4;
   // exercise
   auto angleDegrees = deg(angleRadians);
   // verify
   assert(angleDegrees == 135);
   assert(typeid(angleDegrees) == typeid(double));
}  // breakdown

void test_rad()
{  // setup
   double angleDegrees = -270;
   // exercise
   auto angleRadians = rad(angleDegrees);
   // verify
   assert(angleRadians == -3 * M_PI/2);
   assert(typeid(angleRadians) == typeid(double));
}  // breakdown

void test_distance()
{  // setup
   Position p1(4, 5);
   Position p2(9, -5);
   // exercise
   auto d = distance(p1, p2);
   // verify
   assert(d == 5 * sqrt(5));
   assert(typeid(d) == typeid(double));
   // bonus
   auto magnitude = (p1-p2).getMagnitude();
   assert(d == magnitude);
}  // breakdown

void test_distance_objs()
{  // setup
   Interface ui;
   MovingObject obj1(ui);
   obj1.setPosition(Position(4, 5));
   MovingObject obj2(ui);
   obj2.setPosition(Position(9, -5));
   // exercise
   auto d = distance(obj1, obj2);
   // verify
   assert(d == 5 * sqrt(5));
   assert(typeid(d) == typeid(double));
}  // breakdown

void test_computeDistance()
{  // setup
   Position p1(4, 5);
   Position p2(9, -5);
   // exercise
   auto d = computeDistance(p1, p2);
   // verify
   assert(d == 5 * sqrt(5));
   assert(typeid(d) == typeid(double));
}  // breakdown
//
//void test_timeDilation()
//{  // setup
//   // exercise
//   auto dilation = timeDilation();
//   // verify
//   assert(dilation == 24);
//}  // breakdown

void test_dilateTime()
{  // setup
   auto timeDilation = 24;
   double gameTime = 5; // s
   // exercise
   auto realTime = dilateTime(gameTime);
   // verify
   assert (realTime == gameTime * timeDilation);
   assert(typeid(realTime) == typeid(double));
}  // breakdown

void test_timePerFrame()
{  // setup
   // exercise
   auto dt = 1/FPS;
   auto time = timePerFrame(dt);
   auto timeDilation = 24;
   // verify
   assert(time == timeDilation * dt);
   assert(typeid(time) == typeid(double));
}  // breakdown

void test_rotationSpeed()
{  // setup
   // exercise
   auto timeDilation = 24;
   auto dt = 1/FPS;
   auto earth_rotation_speed = earthRotationSpeed();
   // verify
   assert(earth_rotation_speed == -2 * M_PI * (timeDilation*60*dt) / SECONDS_IN_DAY);
}  // breakdown


//void test_calcHeight()
//{  // setup
//   double x = 10000000;
//   double y = 10000000;
//   Position p(x, y);
//   // exercise
//   auto height = calcHeight(p);
//   // verify
//   assert(height == mag(x, y) - EARTH_RADIUS);
//   assert(typeid(height) == typeid(double));
//}  // breakdown

//void test_calcHeight_earth()
//{  // setup
//   double x = 10000000;
//   double y = 10000000;
//   Position p(x, y);
//   Earth e;
//   e.setPosition(Position(400, 500));
//   // exercise
//   auto height = calcHeight(p, e);
//   // verify
//   assert(height == distance(p, e.getPosition()) - EARTH_RADIUS);
//   assert(typeid(height) == typeid(double));
//}  // breakdown

void test_directionOfGravity()
{  // setup
   Position p1;
   p1.setPolar(4000000, M_PI/6);
   Position p2(0,0);
   // exercise
   auto direction = directionOfGravity(p1, p2);
   // verify
   assert(direction == M_PI/6);
   assert(typeid(direction) == typeid(double));
}  // breakdown

void test_directionOfGravity_objs()
{  // setup
   Interface ui;
   Position p;
   p.setPolar(4000000, M_PI/6);
   MovingObject obj1(ui);
   obj1.setPosition(p);
   MovingObject obj2(ui);
   // exercise
   auto direction = directionOfGravity(obj1, obj2);
   // verify
   assert(direction == M_PI/6);
   assert(typeid(direction) == typeid(double));
}  // breakdown

//void test_forceDueToGravity()
//{  // setup
//   Earth e;
//   Sputnik s;
//   Position p;
//   double magnitude = 4000000;
//   double angleRadians = M_PI/6;
//   p.setPolar(magnitude, angleRadians);
//   s.setPosition(p);
//   // exercise
//   auto fg = forceDueToGravity(s, e); // sputnik <- fg <- earth
//   // verify
//   assert(fg.getAngleRadians() == angleRadians);
//   assert(fg.getMagnitude() == G * s.getMass() * e.getMass() / pow(distance(s, e), 2));
//   assert(typeid(fg) == typeid(Gravity));
//}  // breakdown

//void test_calcGravity()
//{  // setup
//   double height = 400000000;
//   // exercise
//   auto agMag = calcGravity(height);
//   // verify
//   assert(agMag == ACCEL_DUE_TO_GRAVITY_EARTH * (pow((EARTH_RADIUS / (EARTH_RADIUS + height)), 2)));
//   assert(typeid(agMag) == typeid(double));
//}  // breakdown

//void test_calcGravityVector()
//{  // setup
//   Position p;
//   double magnitude = 4000000;
//   double angleRadians = M_PI/6;
//   p.setPolar(magnitude, angleRadians);
//   // exercise
//   auto ag = calcGravityVector(p);
//   // verify
//   assert(ag.getMagnitude() == calcGravity(calcHeight(p)));
//   assert(ag.getAngleRadians() == angleRadians);
//   assert(typeid(ag) == typeid(Acceleration));
//}  // breakdown

void test_aToD()
{  // setup
   double angle = M_PI/4;
   double dt = 1; // s
   Acceleration a;
   a.setPolar(1, angle); // m/s/s
   Velocity v0;
   v0.setPolar(2, angle); // m/s
   Position p0;
   p0.setPolar(3, angle); // m
   // exercise
   auto d = aToD(a, v0, dt, p0.getMagnitude());;
   // verify
   assert(d == 5.5); // m
   assert(typeid(d) == typeid(double));
}  // breakdown

void test_aToX()
{  // setup
   double dt = 1; // s
   Acceleration a(1, 0);
   Velocity v0(2, 0);
   Position p0(3, 0);
   // exercise
   auto d = aToX(a, v0, dt, p0.getMagnitude());
   // verify
   assert(d == 5.5); // m
   assert(typeid(d) == typeid(double));
}  // breakdown

void test_aToY()
{  // setup
   double dt = 1; // s
   Acceleration a(0, 1);
   Velocity v0(0, 2);
   Position p0(0, 3);
   // exercise
   auto d = aToY(a, v0, dt, p0.getMagnitude());
   // verify
   assert(d == 5.5); // m
   assert(typeid(d) == typeid(double));
}  // breakdown

void test_aToDx()
{  // setup
   double dt = 1; // s
   Acceleration a(0, 1); // 1 m/s/s up
   Velocity v0(0, 2); // 2 m/s up
   auto test = 0.0;
   // exercise
   auto d = aToDx(a, v0, dt);
   // verify
   assert(d == test); // m
   assert(typeid(d) == typeid(double));
}  // breakdown

void test_aToDy()
{  // setup
   // exercise
   // verify
}  // breakdown

void test_aToV()
{  // setup
   // exercise
   // verify
}  // breakdown

void testPhysicsFormulas()
{  test_trigX();
   test_trigY();
   test_trigX_vector();
   test_trigY_vector();
   test_mag();
   test_mag_vector();
   test_deg();
   test_rad();
   test_distance();
   test_distance_objs();
   test_computeDistance();
//   test_timeDilation();
   test_dilateTime();
   test_timePerFrame();
   test_rotationSpeed();
//   test_calcHeight();
//   test_calcHeight_earth();
   test_directionOfGravity();
   test_directionOfGravity_objs();
//   test_forceDueToGravity();
//   test_calcGravity();
//   test_calcGravityVector();
   test_aToD();
   test_aToX();
   test_aToY();
   test_aToDx();
   test_aToDy();
   test_aToV();
}
