///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-24
// Updated : 2008-10-07
// Licence : This source is under MIT License
// File    : glm/gtx/unsigned_int.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace unsigned_int{

inline uint pow(uint x, uint y)
{
    uint result = x;
    for(uint i = 1; i < y; ++i)
        result *= x;
    return result;
}

inline uint sqrt(uint x)
{
    if(x <= 1) return x;

    uint NextTrial = x >> 1;
    uint CurrentAnswer;

    do
    {
        CurrentAnswer = NextTrial;
        NextTrial = (NextTrial + x / NextTrial) >> 1;
    } while(NextTrial < CurrentAnswer);

    return CurrentAnswer;
}

inline uint mod(uint x, uint y)
{
	return x - y * (x / y);
}

}//namespace unsigned_int
}//namespace gtx
}//namespace glm
