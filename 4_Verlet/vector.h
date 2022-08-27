//A C++ fast and lightweight 3D vector library.
//Optimized to be as fast as possible maintaining great usability.
/* 
 * This file is part of the Vector3D distribution (https://github.com/cdelv/Vector3D).
 * Copyright (c) 2022 Carlos Andres del Valle.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, 3 version.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include <iostream>
#include <cmath>

class vector3D{
 private:
  double X, Y, Z;

 public:
  //Initialize the vector
  void load(double x0, double y0, double z0);
  //Get the components
  double x(void){return X;};
  double y(void){return Y;};
  double z(void){return Z;};
  //Show the vector
  void show(void);
  //-------------------------
  //Vectorial operators
  //-------------------------
  //Equal
  void operator= (vector3D v2);
  //Sum
  vector3D operator+ (vector3D v2);
  void operator+=(vector3D v2);
  //Substraction
  vector3D operator- (vector3D v2);
  void operator-=(vector3D v2);
  //Scalar multiplication
  vector3D operator* (double a);
  void operator*=(double a);
  friend vector3D operator* (double a,vector3D v1);	
  //Scalar division
  vector3D operator/ (double a);
  void operator/=(double a);
  //Dot product
  double operator* (vector3D v2);
  //Cross product
  vector3D operator^ (vector3D v2);
  //Norm operations
  double norm2(void);    
  double norm(void);
  //Angle between two vectors
  friend double angle(vector3D v1, vector3D v2);
};
