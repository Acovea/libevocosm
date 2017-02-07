//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//
//  Utilities for Mutating and Breeding IEC 60559/IEEE 754 single- and
//  double-precision floating-point number.
//
//  evoreal.cpp
//---------------------------------------------------------------------
//
//  Copyright 1996, 1999, 2002, 2003, 2004, 2005 Scott Robert Ladd
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the
//      Free Software Foundation, Inc.
//      59 Temple Place - Suite 330
//      Boston, MA 02111-1307, USA.
//
//-----------------------------------------------------------------------
//
//  For more information on this software package, please visit
//  Scott's web site, Coyote Gulch Productions, at:
//
//      http://www.coyotegulch.com
//  
//-----------------------------------------------------------------------

#include <cfloat>
#include <cstring>

#include "evoreal.h"

using namespace libevocosm;

// fix for older, broken Microsoft compilers
#if defined(_MSC_VER) && (_MSC_VER < 1300)
const long evoreal::FLT_EXP_BITS = 0x7F800000L;
const long evoreal::DBL_EXP_BITS = 0x7FF00000UL;
#endif

evoreal::evoreal(float a_sign_weight, float a_exponent_weight, float a_mantissa_weight)
    : m_total_weight(a_sign_weight + a_exponent_weight + a_mantissa_weight),
      m_sign_weight(a_sign_weight),
      m_exp_weight(a_exponent_weight)
{
    // intentionally blank
}

float evoreal::mutate(float a_f)
{
    // mask for exponent bits
    long x, n, mask;
    
    // choose section to mutate
    float mpick = static_cast<float>(g_random.get_rand_real2() * m_total_weight);
    
    // copy float to long for manipulation
    memcpy(&x,&a_f,sizeof(long));
    
    // if all exponent bits on (invalid #), return original
    if ((x & FLT_EXP_BITS) == FLT_EXP_BITS)
        return a_f;
    
    // mutate
    if (mpick < m_sign_weight)
    {
        // flip sign
        mask = 0x80000000L;
        
        if (x & mask)
            x &= ~mask;
        else
            x |= mask;
    }
    else
    {
        mpick -= m_sign_weight;
        
        if (mpick < m_exp_weight)
        {
            // mutate exponent while number is valid
            do  {
                n    = x;
                mask = 0x00800000L << int(g_random.get_rand_real2() * 8.0F);
                
                if (n & mask)
                    n &= ~mask;
                else
                    n |= mask;
            }
            while ((n & FLT_EXP_BITS) == FLT_EXP_BITS);
            
            x = n;
        }
        else
        {
            // flip bit in mantissa
            mask = 1L << int(g_random.get_rand_real2() * 23.0F);
            
            if (x & mask)
                x &= ~mask;
            else
                x |= mask;
        }
    }
    
    // done!
    float res;
    memcpy(&res,&x,sizeof(float));
    return res;
}

double evoreal::mutate(double a_d)
{
    // working storage
    long x[2], n, mask, bit;
    
    // choose section to mutate
    double mpick = g_random.get_rand_real2() * m_total_weight;
    
    // copy double to pair of longs for manipulation
    memcpy(x,&a_d,2 * sizeof(long));
    
    // choose what to change
    if (mpick < m_sign_weight)
    {
        // flip sign
        mask = 0x80000000L;
        
        if (x[1] & mask)
            x[1] &= ~mask;
        else
            x[1] |= mask;
    }
    else
    {
        mpick -= m_sign_weight;
        
        if (mpick < m_exp_weight)
        {
            // mutate exponent while number is valid
            do  {
                n = x[1];
                mask = 0x00100000L << int(g_random.get_rand_real2() * 11.0F);
                
                if (n & mask)
                    n &= ~mask;
                else
                    n |= mask;
            }
            while ((n & DBL_EXP_BITS) == DBL_EXP_BITS);
            
            x[1] = n;
        }
        else
        {
            bit = long(g_random.get_rand_real2() * 52.0F);
            
            if (bit > 31L)
            {
                bit -= 32L;
                mask = 1L << (int)bit;
                
                if (x[1] & mask)
                    x[1] &= ~mask;
                else
                    x[1] |= mask;
            }
            else
            {
                // flip bit in mantissa
                mask = 1L << (int)bit;
                
                if (x[0] & mask)
                    x[0] &= ~mask;
                else
                    x[0] |= mask;
            }
        }
    }
    
    // done
    double res;
    memcpy(&res,x,sizeof(double));
    return res;
}

// crossover
float evoreal::crossover(float a_f1, float a_f2)
{
    // working storage
    long  l1, l2, lcross, mask;
    float fcross;
    
    // store values in longs
    memcpy(&l1,&a_f1,sizeof(long));
    memcpy(&l2,&a_f2,sizeof(long));
    
    do  {
        // create mask
        mask   = 0xFFFFFFFFL << size_t(g_random.get_rand_real2() * 32.0F);
        
        // generate offspring
        lcross = (l1 & mask) | (l2 & (~mask));
    }
    while ((lcross & FLT_EXP_BITS) == FLT_EXP_BITS);
    
    // copy result to float and return
    memcpy(&fcross,&lcross,sizeof(float));
    
    return fcross;
}

double evoreal::crossover(double a_d1, double a_d2)
{
    // working storage    
    long   l1[2], l2[2], lcross[2], mask, bit;
    double fcross;
    
    // store values in longs
    memcpy(l1,&a_d1,sizeof(double));
    memcpy(l2,&a_d2,sizeof(double));
    
    do  {
        // calculate bit position for flip
        bit = size_t(g_random.get_rand_real2() * 64.0F);
        
        if (bit > 31) // if flip in high-order word
        {
            // create mask
            mask   = 0xFFFFFFFFL << int(bit - 32L);
            
            // duplicate low-order word of first parent
            lcross[0] = l1[0];
            
            // crossover in high-order word
            lcross[1] = (l1[1] & mask) | (l2[1] & (~mask));
        }
        else
        {
            // create mask
            mask   = 0xFFFFFFFFL << int(bit);
            
            // crossover in low-order word
            lcross[0] = (l1[0] & mask) | (l2[0] & (~mask));
            
            // duplicate high-order word of first parent
            lcross[1] = l1[1];
        }
    }
    while ((lcross[1] & DBL_EXP_BITS) == DBL_EXP_BITS);
    
    // copy and return
    memcpy(&fcross,lcross,sizeof(double));
    return fcross;
}

