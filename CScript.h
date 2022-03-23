#pragma once

class CScript {						//abstract class for loading and unloading scripts
public:
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};