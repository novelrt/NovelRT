// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_MATHS_GEOVECTOR2F_H
#define NOVELRT_MATHS_GEOVECTOR2F_H

#ifdef __cplusplus
extern "C" {
#endif

 struct GeoVector2F {
   float x;
   float y;
 };

 typedef struct GeoVector2F GeoVector2F_t;

//GeoVector2F GeoVector2F_create(float x, float y);

float GeoVector2F_getX(GeoVector2F_t gv);
void GeoVector2F_setX(GeoVector2F_t gv, float value);
float GeoVector2F_getY(GeoVector2F_t gv);
void GeoVector2F_setY(GeoVector2F_t gv, float value);

//GeoVector2_t GeoVector2_getNormalized();
//float GeoVector2_getMagnitude();
float GeoVector2F_getLength(GeoVector2F_t gv);


#ifdef __cplusplus
}
#endif

#endif //NOVELRT_MATHS_GEOVECTOR2F_H
