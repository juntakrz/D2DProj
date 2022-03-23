#include "CButton.h"

CButton::CButton(uint8_t ctlID, uint16_t resID, float ctlX, float ctlY, float ctlW, float ctlH, float ctlA)
{
	m_CtlID = ctlID;
	m_CtlResID = resID;
	m_CtlState = D2DUI::STATE_CREATE;
	m_CtlAnim = D2DUI::ANIM_IDLE;
	m_BaseXYWHA[0] = ctlX, m_BaseXYWHA[1] = ctlY, m_BaseXYWHA[4] = ctlA;

	if (ctlW == 0 && ctlH == 0)		//if no width or height is provided - retrieve it from the default bitmap size
	{
		CD2DBitmap::Get().GetBitmapSize(resID, m_BaseXYWHA[2], m_BaseXYWHA[3]);
	}
	else
	{
		m_BaseXYWHA[2] = ctlW;
		m_BaseXYWHA[3] = ctlH;
	}
	m_isAnimDelayed = false, m_isTrackingActive = false;
	m_AnimDelayFrames = 0, m_AnimFramesLeft = 0, m_AnimFramesPassed = 0;
}

void CButton::ActivateTracking()
{
	if (!m_isTrackingActive)
	{
		RECT ctlArea{ m_BaseXYWHA[0], m_BaseXYWHA[1], m_BaseXYWHA[0] + m_BaseXYWHA[2], m_BaseXYWHA[1] + m_BaseXYWHA[3] };
		D2DUI::Get().GetCtlAreaVector()->emplace_back(std::make_pair(m_CtlID, ctlArea));
		m_isTrackingActive = true;
	}
}

void CButton::SetAnimData(const uint8_t& CtlAnim, const uint8_t& CtlState, const std::array<float, 8>& AnimVec8f, bool& doAnimBlend)
{
	m_CtlAnim = CtlAnim;
	m_AnimParams[CtlState] = AnimVec8f;
	if (m_AnimParams[CtlState][1])
	{
		m_AnimDelayFrames = m_AnimParams[CtlState][1];
		m_isAnimDelayed = true;
	}
	m_AnimFramesLeft = m_AnimParams[CtlState][0];
}

void CButton::OnHover()
{

}

void CButton::OnLeave()
{

}

void CButton::OnClick()
{

}

void CButton::Update()
{

	switch (m_isAnimDelayed)
	{
	case true:
	{
		//if 'delay' frames are skipped - preprocess animation variables
		switch (m_AnimDelayFrames)
		{
		case 0 :
		{
			D2DUIAnimate::Frame(this, m_CtlState, m_CtlAnim, true);
			m_isAnimDelayed = false;
			break;
		}
		//if not - subtract one delay frame
		default :
		{
			m_AnimDelayFrames--;
			break;
		}
		}
		break;
	}
	case false:
	{
		switch (m_AnimFramesLeft)	//animate if any animation frames are left
		{
		case 0:
		{
			if (m_CtlState == D2DUI::STATE_CREATE)
			{
				//activate control if it was animate on creation
				m_CtlState = D2DUI::STATE_IDLE;
				ActivateTracking();
			}
			m_CtlAnim = D2DUI::ANIM_IDLE;
			break;
		}
		default:
		{
			D2DUIAnimate::Frame(this, m_CtlState, m_CtlAnim);
			//one less frame to go
			m_AnimFramesLeft--;
			break;
		}
		}
		break;
	}
	}
}

void CButton::Render()
{
	switch (m_CtlState)
	{
		case (D2DUI::STATE_IDLE):
		{
			CD2DBitmap::Get().DrawBitmap(m_CtlResID, m_BaseXYWHA[0], m_BaseXYWHA[1], m_BaseXYWHA[2], m_BaseXYWHA[3], m_BaseXYWHA[4]);
			break;
		}
		default:
		{
			CD2DBitmap::Get().DrawBitmap(m_CtlResID, m_RenderXYWHA[0], m_RenderXYWHA[1], m_RenderXYWHA[2], m_RenderXYWHA[3], m_RenderXYWHA[4]);
			break;
		}
	}
}

void CButton::Delete()
{

}

std::array<float, 5>* CButton::GetBaseArray()
{
	return &m_BaseXYWHA;
}

std::array<float, 5>* CButton::GetRenderArray()
{
	return &m_RenderXYWHA;
}

std::array<float, 8>* CButton::GetAnimParamArray(const uint8_t& ctlState)
{
	return &m_AnimParams[ctlState];
}

std::array<float, 8>* CButton::GetAnimBufferArray()
{
	return &m_AnimVariableBuffer;
}