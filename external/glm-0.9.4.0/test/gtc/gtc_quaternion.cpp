///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2012 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-09-16
// Updated : 2011-05-25
// Licence : This source is under MIT licence
// File    : test/gtc/quaternion.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/epsilon.hpp>

int test_quat_angle()
{
    int Error = 0;
    
    {
        glm::quat Q = glm::angleAxis(45.0f, glm::vec3(0, 0, 1));
        glm::quat N = glm::normalize(Q);
        float L = glm::length(N);
        Error += glm::epsilonEqual(L, 1.0f, 0.01f) ? 0 : 1;
        float A = glm::angle(N);
        Error += glm::epsilonEqual(A, 45.0f, 0.01f) ? 0 : 1;
    }
    {
        glm::quat Q = glm::angleAxis(45.0f, glm::normalize(glm::vec3(0, 1, 1)));
        glm::quat N = glm::normalize(Q);
        float L = glm::length(N);
        Error += glm::epsilonEqual(L, 1.0f, 0.01f) ? 0 : 1;
        float A = glm::angle(N);
        Error += glm::epsilonEqual(A, 45.0f, 0.01f) ? 0 : 1;
    }
    {
        glm::quat Q = glm::angleAxis(45.0f, glm::normalize(glm::vec3(1, 2, 3)));
        glm::quat N = glm::normalize(Q);
        float L = glm::length(N);
        Error += glm::epsilonEqual(L, 1.0f, 0.01f) ? 0 : 1;
        float A = glm::angle(N);
        Error += glm::epsilonEqual(A, 45.0f, 0.01f) ? 0 : 1;
    }
    
    return Error;
}

int test_quat_angleAxis()
{
	int Error = 0;

	glm::quat A = glm::angleAxis(0.0f, glm::vec3(0, 0, 1));
	glm::quat B = glm::angleAxis(90.0f, glm::vec3(0, 0, 1));
    glm::quat C = glm::mix(A, B, 0.5f);
    glm::quat D = glm::angleAxis(45.0f, glm::vec3(0, 0, 1));

    Error += glm::epsilonEqual(C.x, D.x, 0.01f) ? 0 : 1;
	Error += glm::epsilonEqual(C.y, D.y, 0.01f) ? 0 : 1;
	Error += glm::epsilonEqual(C.z, D.z, 0.01f) ? 0 : 1;
	Error += glm::epsilonEqual(C.w, D.w, 0.01f) ? 0 : 1;

	return Error;
}

int test_quat_mix()
{
	int Error = 0;
    
	glm::quat A = glm::angleAxis(0.0f, glm::vec3(0, 0, 1));
	glm::quat B = glm::angleAxis(90.0f, glm::vec3(0, 0, 1));
    glm::quat C = glm::mix(A, B, 0.5f);
    glm::quat D = glm::angleAxis(45.0f, glm::vec3(0, 0, 1));
    
    Error += glm::epsilonEqual(C.x, D.x, 0.01f) ? 0 : 1;
	Error += glm::epsilonEqual(C.y, D.y, 0.01f) ? 0 : 1;
	Error += glm::epsilonEqual(C.z, D.z, 0.01f) ? 0 : 1;
	Error += glm::epsilonEqual(C.w, D.w, 0.01f) ? 0 : 1;
    
	return Error;
}

int test_quat_precision()
{
	int Error = 0;

	Error += sizeof(glm::lowp_quat) <= sizeof(glm::mediump_quat) ? 0 : 1;
	Error += sizeof(glm::mediump_quat) <= sizeof(glm::highp_quat) ? 0 : 1;
    
    return Error;
}

int test_quat_normalize()
{
    int Error = 0;
 
    {
        glm::quat Q = glm::angleAxis(45.0f, glm::vec3(0, 0, 1));
        glm::quat N = glm::normalize(Q);
        float L = glm::length(N);
        Error += glm::epsilonEqual(L, 1.0f, 0.000001f) ? 0 : 1;
    }
    {
        glm::quat Q = glm::angleAxis(45.0f, glm::vec3(0, 0, 2));
        glm::quat N = glm::normalize(Q);
        float L = glm::length(N);
        Error += glm::epsilonEqual(L, 1.0f, 0.000001f) ? 0 : 1;
    }
    {
        glm::quat Q = glm::angleAxis(45.0f, glm::vec3(1, 2, 3));
        glm::quat N = glm::normalize(Q);
        float L = glm::length(N);
        Error += glm::epsilonEqual(L, 1.0f, 0.000001f) ? 0 : 1;
    }

    return Error;
}

int test_quat_type()
{
    glm::quat A;
    glm::dquat B;
    
    return 0;
}

int main()
{
	int Error = 0;
    
	Error += test_quat_precision();
    Error += test_quat_type();
    Error += test_quat_angle();
	Error += test_quat_angleAxis();
	Error += test_quat_mix();
	Error += test_quat_normalize();

	return Error;
}
