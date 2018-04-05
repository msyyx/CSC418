/***********************************************************
	
	Starter code for Assignment 3
	
	Implements scene_object.h

***********************************************************/

#include <cmath>
#include "scene_object.h"

bool UnitSquare::intersect(Ray3D& ray, const Matrix4x4& worldToModel,
		const Matrix4x4& modelToWorld) {
	// TODO: implement intersection code for UnitSquare, which is
	// defined on the xy-plane, with vertices (0.5, 0.5, 0), 
	// (-0.5, 0.5, 0), (-0.5, -0.5, 0), (0.5, -0.5, 0), and normal
	// (0, 0, 1).
	//
	// Your goal here is to fill ray.intersection with correct values
	// should an intersection occur.  This includes intersection.point, 
	// intersection.normal, intersection.none, intersection.t_value.   
	//
	// HINT: Remember to first transform the ray into object space  
	// to simplify the intersection test.

	Vector3D dir = worldToModel * ray.dir;
	Point3D origin = worldToModel * ray.origin;

	float t = -(origin[2]/dir[2]);;

	if (t <= 0) {
		return false;
	} 

	float x = origin[0] + t * dir[0];
	float y = origin[1] + t * dir[1];

	if (!(x>=-0.5 && x<=0.5 && y>=-0.5 && y<=0.5)) {
		if (ray.intersection.none || t_val < ray.intersection.t_value) {
			ray.intersection.point = modelToWorld * Point3D(x, y, 0.0);
			ray.intersection.normal = wordToModel.transpose() * Point3D(0.0, 0.0, 1.0);;
			ray.intersection.normal.normalize();
			ray.intersection.none = false;
			ray.intersection.t_value = t;
			return true;
		}
	}
	return false;
}

bool UnitSphere::intersect(Ray3D& ray, const Matrix4x4& worldToModel,
		const Matrix4x4& modelToWorld) {
	// TODO: implement intersection code for UnitSphere, which is centred 
	// on the origin.  
	//
	// Your goal here is to fill ray.intersection with correct values
	// should an intersection occur.  This includes intersection.point, 
	// intersection.normal, intersection.none, intersection.t_value.   
	//
	// HINT: Remember to first transform the ray into object space  
	// to simplify the intersection test.

	Vector3D dir = worldToModel * ray.dir;
	Point3D origin = worldToModel * ray.origin;
	
	float t;
	float A = dir.dot(dir);
	float B = 2.0 * dir.dor(origin - Point3D(0.0, 0.0, 0.0));
	float C = (origin - Point3D(0.0, 0.0, 0.0)).dot(origin - Point3D(0.0, 0.0, 0.0)) - 1;

	float D = B * B - 4 * A * C;

	if (D < 0.0){
		return false;
	}

	else {
		t = fmin(-B + sqrt(discr))/(2.0 * A), (-B - sqrt(discr))/(2.0 * A);
		if (t <= 0){
			return false;
		}
	}

	if (!ray.intersection.none && ray.intersection.t_value < t){
		return false;
	}

	Point3D intersect(origin[0] + t * dir[0], origin[1] + t * dir[1], origin[2] + t * dir[2]);
	Vector3D normal(origin[0] + t * dir[0], origin[1] + t * dir[1], origin[2] + t * dir[2]);
	normal.normalize();

	ray.intersection.point = modelToWorld * point;
	ray.intersection.normal = transNorm(worldToModel, normal);
	ray.intersection.normal.normalize();
	ray.intersection.none = false;
	ray.intersection.t_value = t;
	return true;
}

void SceneNode::rotate(char axis, double angle) {
	Matrix4x4 rotation;
	double toRadian = 2*M_PI/360.0;
	int i;
	
	for (i = 0; i < 2; i++) {
		switch(axis) {
			case 'x':
				rotation[0][0] = 1;
				rotation[1][1] = cos(angle*toRadian);
				rotation[1][2] = -sin(angle*toRadian);
				rotation[2][1] = sin(angle*toRadian);
				rotation[2][2] = cos(angle*toRadian);
				rotation[3][3] = 1;
			break;
			case 'y':
				rotation[0][0] = cos(angle*toRadian);
				rotation[0][2] = sin(angle*toRadian);
				rotation[1][1] = 1;
				rotation[2][0] = -sin(angle*toRadian);
				rotation[2][2] = cos(angle*toRadian);
				rotation[3][3] = 1;
			break;
			case 'z':
				rotation[0][0] = cos(angle*toRadian);
				rotation[0][1] = -sin(angle*toRadian);
				rotation[1][0] = sin(angle*toRadian);
				rotation[1][1] = cos(angle*toRadian);
				rotation[2][2] = 1;
				rotation[3][3] = 1;
			break;
		}
		if (i == 0) {
			this->trans = this->trans*rotation; 	
			angle = -angle;
		} 
		else {
			this->invtrans = rotation*this->invtrans; 
		}	
	}
}

void SceneNode::translate(Vector3D trans) {
	Matrix4x4 translation;
	
	translation[0][3] = trans[0];
	translation[1][3] = trans[1];
	translation[2][3] = trans[2];
	this->trans = this->trans*translation; 	
	translation[0][3] = -trans[0];
	translation[1][3] = -trans[1];
	translation[2][3] = -trans[2];
	this->invtrans = translation*this->invtrans; 
}

void SceneNode::scale(Point3D origin, double factor[3] ) {
	Matrix4x4 scale;
	
	scale[0][0] = factor[0];
	scale[0][3] = origin[0] - factor[0] * origin[0];
	scale[1][1] = factor[1];
	scale[1][3] = origin[1] - factor[1] * origin[1];
	scale[2][2] = factor[2];
	scale[2][3] = origin[2] - factor[2] * origin[2];
	this->trans = this->trans*scale; 	
	scale[0][0] = 1/factor[0];
	scale[0][3] = origin[0] - 1/factor[0] * origin[0];
	scale[1][1] = 1/factor[1];
	scale[1][3] = origin[1] - 1/factor[1] * origin[1];
	scale[2][2] = 1/factor[2];
	scale[2][3] = origin[2] - 1/factor[2] * origin[2];
	this->invtrans = scale*this->invtrans; 
}


