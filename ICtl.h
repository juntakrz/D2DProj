#pragma once

struct ICtl
{
	virtual void OnHover() = 0;
	virtual void OnLeave() = 0;
	virtual void OnClick() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Delete() = 0;

	virtual std::array<float, 5>* GetBaseArray() = 0;
	virtual std::array<float, 5>* GetRenderArray() = 0;
	virtual std::array<float, 8>* GetAnimParamArray(const uint8_t& ctlState) = 0;
	virtual std::array<float, 8>* GetAnimBufferArray() = 0;
};