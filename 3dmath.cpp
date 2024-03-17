#include "irrlicht/irrlicht.h"
#include <string>
#pragma hdrstop

using namespace irr;

/*int _RTLENTRY _EXPFUNC _matherr(struct _exception* e)
{
        e->retval=1.0;
        return 1;
} */
f32 MakeDegreeNormal(f32 deg);
f32 Betrag(f32 &pValue);

const f32 GRAD_PI=180.0 / 3.14159265;
const f32 BOG=3.14159265 / 180.0f;
const f32 PI=3.14159265f;

core::vector3df getHorizontalAngle(core::vector3df vec)
{
        core::vector3df angle;

        angle.Y = (f32)atan2(vec.X, vec.Z);
        angle.Y *= (f32)GRAD_PI;
			    
        if (angle.Y < 0.0f) angle.Y += 360.0f;
        if (angle.Y >= 360.0f) angle.Y -= 360.0f;

        f32 z1;
        z1 = (f32)sqrt(vec.X*vec.X + vec.Z*vec.Z);

        angle.X = (f32)atan2(z1,vec.Y);
        angle.X *= (f32)GRAD_PI;
        angle.X -= 90.0f;

/*        angle.X=atan(vec.Y/(sqrt(vec.X*vec.X+vec.Z*vec.Z)) )*GRAD_PI;
        angle.X-=90.0f;*/

        if (angle.X < 0.0f) angle.X += 360.0f;
        if (angle.X >= 360) angle.X -= 360.0f;

        return angle;
}

core::vector3df getRotationToTarget(core::vector3df position, core::vector3df target)
{
        if(position!=target)
        {
                core::vector3df RelativeRotation=core::vector3df(0,0,0);
                core::vector3df vect = target - position;
	        vect = getHorizontalAngle(vect);
	        RelativeRotation.X = vect.X;
	        RelativeRotation.Y = vect.Y;
                return RelativeRotation;
        }
        else
                return core::vector3df(0,0,0);
}

core::vector3df getHorizontalAngle2(core::vector3df vec)
{
        core::vector3df angle;

        f32 x=Betrag(vec.X);
        f32 z=Betrag(vec.Z);

        if( x!=0 )
                angle.Y = (f32)atan(z/x);
        else
                angle.Y=0;
        angle.Y *= (f32)GRAD_PI;

        f32 z1;
        z1 = (f32)sqrt(vec.X*vec.X + vec.Z*vec.Z);

        if(z1!=0 )
                angle.X = (f32)atan(vec.Y/z1);
        else
                angle.X=0;

        angle.X *= (f32)GRAD_PI;

        if( vec.Y<=0 && vec.X >0)
                angle.X =(360.0f-angle.X);
        else if( vec.Y>=0 && vec.X<0 )
                angle.X=(180-angle.X)+180;
        else if( vec.Y<=0 && vec.X<0 )
                angle.X=180+angle.X;
        else if( vec.X==0 && vec.Z>0)
                angle.X=360-angle.X;
        else if( vec.X==0 && vec.Z<0 )
                angle.X-=180;
        else if( vec.Y>0 && vec.X>0 )
                angle.X+=180;

        if( angle.X<90 || angle.X>270 )
        {
                if( vec.Z>0 && vec.X>0 )
                        angle.Y=90-angle.Y;
                else if( vec.Z>0 && vec.X<0 )
                        angle.Y=270+angle.Y;
                else if( vec.Z<0 && vec.X<0)
                        angle.Y=270-angle.Y;
                else if( vec.Z<0 && vec.X>0)
                        angle.Y=90+angle.Y;
        }
        else
        {
                if( vec.Z>0 && vec.X>0 )
                        angle.Y=270-angle.Y;
                else if( vec.Z>0 && vec.X<0 )
                        angle.Y=90+angle.Y;
                else if( vec.Z<0 && vec.X<0)
                        angle.Y=90-angle.Y;
                else if( vec.Z<0 && vec.X>0)
                        angle.Y=270+angle.Y;
        }

        angle.Y=MakeDegreeNormal(angle.Y);
        angle.X=MakeDegreeNormal(angle.X);

        return angle;
}

core::vector3df getRotationToTarget2(core::vector3df position, core::vector3df target)
{
        if(position!=target)
        {
                core::vector3df RelativeRotation=core::vector3df(0,0,0);
                core::vector3df vect = target - position;


                core::vector3df rot = getHorizontalAngle2(vect);

	        RelativeRotation.X = rot.X;
	        RelativeRotation.Y = rot.Y;
                return RelativeRotation;
        }
        else
                return core::vector3df(0,0,0);
}

core::vector3df getTarget(core::vector3df pos,core::vector3df rot,f32 distance)
{
	core::vector3df target(0,0,1);
	core::matrix4 mat;

	mat.setRotationDegrees(core::vector3df(rot.X,rot.Y,0));
	mat.transformVect(target);
	target.normalize();

	core::vector3df end=pos+target*distance;

	return end;
}

core::vector3df getTargetDistance(core::vector3df position, core::vector3df target, f32 distance)
{
        core::line3d<f32> line(position, target);
        core::vector3df vect=target-position;
        vect.normalize();
        vect*=distance;
        return position+vect;
        /*core::vector3df rot=getRotationToTarget(position,target);
        return getTarget(position, rot, distance);*/
}

core::vector3df getTarget2(core::vector3df pos,core::vector3df rot,f32 distance)
{
        rot.X*=BOG;
        core::vector3df target;
        target.X=cos(rot.X);
        target.Z=sin(rot.X);
        target.Y=0;

        core::matrix4 mat;
        mat.setRotationRadians(core::vector3df(0,rot.Y,0));
        mat.transformVect(target);
        target.normalize();

        return pos+target*distance;
}

f32 MakeDegreeNormal(f32 deg)
{
	if(deg>0)
	{
		while(deg-360>0)
		{
			deg=deg-360;
		}
	}
	if(deg<0)
	{
		while(deg+360<0)
		{
			deg=deg+360;
		}
		deg=360+deg;
	}
	return deg;
}

f32 Betrag(f32 &pValue)
{
        if( pValue>0 )
                return pValue;
        else
                return -1*pValue;
}