
/*
*   Copyright © 2017 Luxon Jean-Pierre
*   https://gumichan01.github.io/
*
*   LunatiX is a free, SDL2-based library.
*   It can be used for open-source or commercial games thanks to the zlib/libpng license.
*
*   Luxon Jean-Pierre (Gumichan01)
*   luxon.jean.pierre@gmail.com
*/

#ifndef LX_RANDOM_HPP_INCLUDED
#define LX_RANDOM_HPP_INCLUDED

/**
*   @file LX_Random.hpp
*   @brief The Random Number Generator library
*   @author Luxon Jean-Pierre(Gumichan01)
*   @version 0.10
*/

#include <cstdint>

/**
*   @ingroup System
*   @namespace LX_Random
*   @brief The Random Number Generator (RNG) namespace
*
*   This random number generator can be used using the Xorshift* generator,
*   or the standard C generator.
*/
namespace LX_Random
{

/**
*   @fn void initRand()
*   Initializes the random number generator
*   setting a seed
*/
void initRand();

/**
*   @fn uint64_t xorshiftRand()
*   Returns a pseudorandom number between 0 and (2^64 - 1)
*   @return An integer value between 0 and 2^64 - 1
*
*   @note This function uses the Xorshift* generator
*/
uint64_t xorshiftRand();

/**
*   @fn int crand()
*   Returns a pseudorandom number between 0 and RAND_MAX (at least 32767)
*   @return An integer value between 0 and RAND_MAX
*
*   @note This function uses the standard C generator
*/
int crand();

/**
*   @fn uint64_t xorshiftRand100()
*   Xorshift random value between 0 and 100
*   @return A random value generated by the Xorshift* RNG
*/
inline uint64_t xorshiftRand100()
{
    return LX_Random::xorshiftRand()%100;
}

/**
*   @fn inline int crand100()
*   C random value between 0 and 100
*   @return A random value generated by the standard C RNG
*/
inline int crand100()
{
    return LX_Random::crand()%100;
}

}

#endif // LX_RANDOM_HPP_INCLUDED
