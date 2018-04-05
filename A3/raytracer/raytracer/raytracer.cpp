/***********************************************************
	
	Starter code for Assignment 3

	Implementations of functions in raytracer.h, 
	and the main function which specifies the scene to be rendered.	

***********************************************************/


#include "raytracer.h"
#include <cmath>
#include <iostream>
#include <cstdlib>

void Raytracer::traverseScene(Scene& scene, Ray3D& ray)  {
	for (size_t i = 0; i < scene.size(); ++i) {
		SceneNode* node = scene[i];

		if (node->obj->intersect(ray, node->worldToModel, node->modelToWorld)) {
			ray.intersection.mat = node->mat;
		}
	}
}

void Raytracer::computeTransforms(Scene& scene) {
	// right now this method might seem redundant. But if you decide to implement 
	// scene graph this is where you would propagate transformations to child nodes
		
	for (size_t i = 0; i < scene.size(); ++i) {
		SceneNode* node = scene[i];

		node->modelToWorld = node->trans;
		node->worldToModel = node->invtrans; 
	}
}

void Raytracer::computeShading(Ray3D& ray, LightList& light_list) {
	for (size_t  i = 0; i < light_list.size(); ++i) {
		LightSource* light = light_list[i];
		
		// Each lightSource provides its own shading function.
		// Implement shadows here if needed.
		light->shade(ray);        
	}
}

Color Raytracer::shadeRay(Ray3D& ray, Scene& scene, LightList& light_list, int bounce = 0) {
	Color col(0.0, 0.0, 0.0); 
	traverseScene(scene, ray); 

	// Don't bother shading if the ray didn't hit 
	// anything.
	if (!ray.intersection.none) {
		computeShading(ray, light_list); 
		col = ray.col;  
	}

	// You'll want to call shadeRay recursively (with a different ray, 
	// of course) here to implement reflection/refraction effects.  

	if (!ray.intersection.none){
		if(bounce < 3){
			//get reflection vector
			Vector3D normal = ray.intersection.normal;
			Vector3D incident = ray.dir;
			if (ray.intersection.mat->reflective){
				Vector3D reflect = (ray.dir * ray.intersection.mat->index_of_refraction) - (normal.dot(incident) + (ray.intersection.mat->index_of_refraction * normal.dot(incident))) * normal;
			} else {
				Vector3D reflect = ray.dir - (2 * (ray.intersection.normal.dot(ray.dir)) * ray.intersection.normal);
			}
			reflect.normalize();
			Ray3D final;
			final.dir = reflect;
			final.origin = ray.intersection.point + 0.01 * final.dir;

			if (ray.intersection.mat->reflective){
				Color colour = col + shadeRay(final, scene, light_list, bounce + 1);
			} else {
				Color colour = col + 0.2 * shadeRay(final, scene, light_list, bounce + 1);
			}
			return colour;
		}
	}

	return col; 
}	

void Raytracer::render(Camera& camera, Scene& scene, LightList& light_list, Image& image) {
	computeTransforms(scene);

	Matrix4x4 viewToWorld;
	double factor = (double(image.height)/2)/tan(camera.fov*M_PI/360.0);

	viewToWorld = camera.initInvViewMatrix();

	// Construct a ray for each pixel.
	for (int i = 0; i < image.height; i++) {
		for (int j = 0; j < image.width; j++) {
			// Sets up ray origin and direction in view space, 
			// image plane is at z = -1.
			Point3D origin(0, 0, 0);
			Point3D imagePlane;
			imagePlane[0] = (-double(image.width)/2 + 0.5 + j)/factor;
			imagePlane[1] = (-double(image.height)/2 + 0.5 + i)/factor;
			imagePlane[2] = -1;
			
			Ray3D ray;
			// TODO: Convert ray to world space  
			Point3D world_origin = viewToWorld * imagePlane;
			Vector3D world_dir = world_origin - camera.eye;
			world_dir.normalize();
			Ray3D ray(world_origin, world_dir);
			
			Color col = shadeRay(ray, scene, light_list); 
			image.setColorAtPixel(i, j, col);		
		}
	}
}

