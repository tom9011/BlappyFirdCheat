#pragma once
#include "defs.h"

#define M_PI 3.14159265358979323846

namespace util
{
    template <typename T>
    static int sgn( T val )
    {
        return ( T( 0 ) < val ) - ( val < T( 0 ) );
    }

    static UnityEngine_Vector3_o quaternion_to_euler( UnityEngine_Quaternion_o* quaternion )
    {
        UnityEngine_Vector3_o res;

        double sinr_cosp = +2.f * ( quaternion->fields.w * quaternion->fields.x + quaternion->fields.y * quaternion->fields.z );
        double cosr_cosp = +1.f - 2.f * ( quaternion->fields.x * quaternion->fields.x + quaternion->fields.y * quaternion->fields.y );
        res.fields.x = atan2( sinr_cosp, cosr_cosp );

        double sinp = +2.f * ( quaternion->fields.w * quaternion->fields.y - quaternion->fields.z * quaternion->fields.x );
        if ( abs( sinp ) >= 1 )
            res.fields.y = M_PI / 2.f * sgn( sinp );
        else
            res.fields.y = asin( sinp );

        double siny_cosp = +2.f * ( quaternion->fields.w * quaternion->fields.z + quaternion->fields.x * quaternion->fields.y );
        double cosy_cosp = +1.f - 2.f * ( quaternion->fields.y * quaternion->fields.y + quaternion->fields.z * quaternion->fields.z );
        res.fields.z = atan2( siny_cosp, cosy_cosp );

        return res;
    }
}