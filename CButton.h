#pragma once

#include <array>
#include <math.h>
#include <string>

#include "CAnimProc.h"
#include "D2DUI.h"

class CButton : public ICtl
{
private:
	uint16_t m_CtlID, m_CtlResID;
	uint8_t m_CtlState, m_CtlAnim;
	bool m_isAnimDelayed, m_isTrackingActive;
	uint16_t m_AnimDelayFrames, m_AnimFramesLeft, m_AnimFramesPassed;
	std::array<float, 5> m_BaseXYWHA;		//base x, y, width, height, alpha
	std::array<float, 5> m_RenderXYWHA;		//processed x, y, w, h, a used by the render methods
	std::array<std::array<float, 8>, 5> m_AnimParams;	//animation parameters received from CtlAPI 
	std::array<float, 8> m_AnimVariableBuffer;	//processed animation data / additional variable storage

	void ActivateTracking();				//activate control for mouse tracking
public:
	CButton(uint8_t ctlID, uint16_t resID, float ctlX, float ctlY, float ctlW = 1.0f, float ctlH = 1.0f, float ctlA = 1.0f);
	void SetAnimData(const uint8_t& CtlAnim, const uint8_t& CtlState, const std::array<float, 8>& AnimVec8f, bool& doAnimBlend);

	void OnHover() override;
	void OnLeave() override;
	void OnClick() override;
	void Update() override;
	void Render() override;
	void Delete() override;

	std::array<float, 5>* GetBaseArray() override;
	std::array<float, 5>* GetRenderArray() override;
	std::array<float, 8>* GetAnimParamArray(const uint8_t& ctlState) override;
	std::array<float, 8>* GetAnimBufferArray() override;
};