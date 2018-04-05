/***********************************************************
	
	Starter code for Assignment 3

	Implements light_source.h

***********************************************************/

#include <cmath>
#include "light_source.h"

void PointLight::shade(Ray3D& ray) {
	// TODO: implement this function to fill in values for ray.col 
	// using phong shading.  Make sure your vectors are normalized, and
	// clamp colour values to 1.0.
	//
	// It is assumed at this point that the intersection information in ray 
	// is available.  So be sure that traverseScene() is called on the ray 
	// before this function.  
	Vector3D normal = ray.intersection.normal;
	Point3D point = ray.intersection.point;
	Vector3D viewVec = -1.0 * ray.dir;

	Color ambient = ray.intersection.mat->ambient * col_ambient;
	Color diffuse = fmax(0.0, 1.dot(n)) * ray.intersection.mat->diffuse * col_diffuse;
	Color specular = pow(fmax(0.0, r.dot(v)), ray.intersection.mat->specular_exp) * ray.intersection.mat->specular * col_specular;

	Point3D lightPos = get_position();

	//Ambient 
	ray.col = ambient + diffuse + specular;

	ray.color.clamp();

}

