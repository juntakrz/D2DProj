#include "CAnimProc.h"

void D2DUIAnimate::Frame(ICtl* pCtl, const uint8_t& ctlState, const uint8_t& animID, const bool initFirstFrame)
{
	enum arrayAlias
	{
		X = 0, Y, W, H, A
	};

	std::array<float, 5>* baseXYWHA = pCtl->GetBaseArray();
	std::array<float, 5>* renderXYWHA = pCtl->GetRenderArray();
	std::array<float, 8>* animBuffer = pCtl->GetAnimBufferArray();

	switch (animID)
	{
	case D2DUI::ANIM_ALPHASCALEMOVE_TO:
	{
		switch (initFirstFrame)
		{
		case true :
		{
			//PREPROCESSING ANIMATION DATA
			//'final' values are object's base values
			std::array<float, 8>* animParams = pCtl->GetAnimParamArray(ctlState);

			//increment a = (final a - initial a) / frames
			renderXYWHA->at(A) = animParams->at(2);
			animBuffer->at(0) = (baseXYWHA->at(A) - animParams->at(2)) / animParams->at(0);

			//initial w|h = base w|h * scale
			renderXYWHA->at(W) = baseXYWHA->at(W) * animParams->at(3);
			renderXYWHA->at(H) = baseXYWHA->at(H) * animParams->at(3);

			//increment w|h = (base w|h - initial w|h) / frames
			animBuffer->at(1) = (baseXYWHA->at(W) - renderXYWHA->at(W)) / animParams->at(0);
			animBuffer->at(2) = (baseXYWHA->at(H) - renderXYWHA->at(H)) / animParams->at(0);

			//increment x|y = -(displacement x|y / frames)		//a sign reversed to increment/decrement correctly
			animBuffer->at(3) = -(animParams->at(4) / animParams->at(0));
			animBuffer->at(4) = -(animParams->at(5) / animParams->at(0));

			//store temporary x|y displacement
			animBuffer->at(5) = animParams->at(4);
			animBuffer->at(6) = animParams->at(5);

			break;
		}
		case false :
		{
			//incrementing alpha
			renderXYWHA->at(A) += animBuffer->at(0);

			//scaling width/height
			renderXYWHA->at(W) += animBuffer->at(1);
			renderXYWHA->at(H) += animBuffer->at(2);

			//caculating x/y with displacement
			renderXYWHA->at(X) = (baseXYWHA->at(X) -
				(renderXYWHA->at(W) - baseXYWHA->at(W)) / 2) + (animBuffer->at(5) += animBuffer->at(3));
			renderXYWHA->at(Y) = (baseXYWHA->at(Y) -
				(renderXYWHA->at(H) - baseXYWHA->at(H)) / 2) + (animBuffer->at(6) += animBuffer->at(4));

			break;
		}
		}
		break;
	}

	case D2DUI::ANIM_ALPHASCALEMOVE_FROM :
	{
		switch (initFirstFrame)
		{
		case true:
		{
			//PREPROCESSING ANIMATION DATA
			//'final' values are object's base values
			std::array<float, 8>* animParams = pCtl->GetAnimParamArray(ctlState);

			//increment a = (final a - initial a) / frames
			renderXYWHA->at(A) = baseXYWHA->at(A);
			animBuffer->at(0) = (baseXYWHA->at(A) - animParams->at(2)) / animParams->at(0);

			//initial w|h = base w|h * scale
			renderXYWHA->at(W) = baseXYWHA->at(W) * animParams->at(3);
			renderXYWHA->at(H) = baseXYWHA->at(H) * animParams->at(3);

			//increment w|h = (base w|h - initial w|h) / frames
			animBuffer->at(1) = (baseXYWHA->at(W) - renderXYWHA->at(W)) / animParams->at(0);
			animBuffer->at(2) = (baseXYWHA->at(H) - renderXYWHA->at(H)) / animParams->at(0);

			//increment x|y = -(displacement x|y / frames)		//a sign reversed to increment/decrement correctly
			animBuffer->at(3) = -(animParams->at(4) / animParams->at(0));
			animBuffer->at(4) = -(animParams->at(5) / animParams->at(0));

			//store temporary x|y displacement
			animBuffer->at(5) = animParams->at(4);
			animBuffer->at(6) = animParams->at(5);

			break;
		}
		case false:
		{
			//decrementing alpha
			renderXYWHA->at(A) -= animBuffer->at(0);

			//scaling width/height
			renderXYWHA->at(W) -= animBuffer->at(1);
			renderXYWHA->at(H) -= animBuffer->at(2);

			//caculating x/y with displacement
			renderXYWHA->at(X) = (baseXYWHA->at(X) -
				(renderXYWHA->at(W) - baseXYWHA->at(W)) / 2) + (animBuffer->at(5) += animBuffer->at(3));
			renderXYWHA->at(Y) = (baseXYWHA->at(Y) -
				(renderXYWHA->at(H) - baseXYWHA->at(H)) / 2) + (animBuffer->at(6) += animBuffer->at(4));

			break;
		}
		}
		break;
	}

	}
}