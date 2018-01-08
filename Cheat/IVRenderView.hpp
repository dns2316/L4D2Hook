#pragma once

class IVRenderView
{
public:
	inline void SetColorModulation(float r, float g, float b)
	{
		float color[3] = { r, g, b };
		return GetFunction<void( __thiscall* )(IVRenderView*, float[])>( this, 7 )(this, color);
	}
};