// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_MATHS_GEOVECTOR2_C_H
#define NOVELRT_MATHS_GEOVECTOR2_C_H

#ifdef __cplusplus
extern "C" {
#endif

struct GeoVector2;
typedef struct GeoVector2 GeoVector2_t;

GeoVector2_t *GeoVector2_create(float x, float y);

float GeoVector2_getX(GeoVector2_t *gv);
//void GeoVector2_setX(float value);
float GeoVector2_getY(GeoVector2_t *gv);
//void GeoVector2_setY(float value);

//GeoVector2_t GeoVector2_getNormalized();
//float GeoVector2_getMagnitude();
//float GeoVector2_getLength();


#ifdef __cplusplus
}
#endif

#endif //NOVELRT_MATHS_CGEOVECTOR2_H
