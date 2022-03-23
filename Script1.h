#pragma once

#include "main.h"

class Script1 : public CScript
{
private:
	
	//dirty background animation stuff
	float scaleW, scaleH;
	bool bUpscale = true;
	float bgX, bgY, bgAngle;
public:
	void Load() override;
	void Unload() override;
	void Update() override;
	void Render() override;
};