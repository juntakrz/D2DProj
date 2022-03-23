#include "pch.h"
#include "Script1.h"

static D2DUI& CtlI = D2DUI::Get();

void Script1::Load()
{
	CtlI.ClearBitmaps();
	CtlI.AddBitmap(IDB_LOGORA2);
	CtlI.AddBitmap(IDB_LOGOYR);
	CtlI.AddBitmap(IDB_PNG2);
	CtlI.AddBitmap(IDB_SCRN_L);
	CtlI.AddBitmap(IDB_SCRN_T);
	CtlI.AddBitmap(IDB_SCRN_R);
	CtlI.AddBitmap(IDB_SCRN_B);

	CtlI.ClearControls();
	CtlI.Create(0, D2DUI::TYPE_BUTTON, IDB_LOGORA2, 100.0f, 80.0f, 340.0f, 140.0f);
	CtlI.Create(1, D2DUI::TYPE_BUTTON, IDB_LOGOYR, 340.0f, 220.0f);
	CtlI.SetAnimation(0, D2DUI::STATE_CREATE, D2DUI::ANIM_ALPHASCALEMOVE_TO, { 40.f, 15.f, 0.f, 1.35f, -30.f, -15.f });
	CtlI.SetAnimation(1, D2DUI::STATE_CREATE, D2DUI::ANIM_ALPHASCALEMOVE_TO, { 40.f, 30.f, 0.f, 1.35f, 30.f, 15.f });

	CtlI.EnableMouseTracking();

	//background variables
	scaleW = 1.1f;
	scaleH = 1.1f;
	bgX = 0.0f;
	bgY = 0.0f;
	bgAngle = 10.0f;
}

void Script1::Unload()
{
	//do I need it?
	Script1::~Script1();
}

void Script1::Update()
{
	//dirty background animation stuff
	if (bUpscale)
	{
		scaleW += 0.00012f;
		scaleH += 0.00012f;
		if (scaleW > 1.25f)
			bUpscale = false;
	}
	else
	{
		scaleW -= 0.00012f;
		scaleH -= 0.00012f;
		if (scaleW < 1.1f)
			bUpscale = true;
	}


	/* Orbital math
	angle += orbit_speed * delta_time;
	x = center_x + radius * cos(angle);
	y = center_y + radius * sin(angle);
	*/

	bgAngle += 0.004f;

	CtlI.Update();

}

void Script1::Render()
{
	CD2DCore::Get().BeginDraw();
	CD2DCore::Get().ClearScreen();

	//formula per 2D coordinate to keep scaled image centered and rotating: pos - ((size * scale) + (radius * sin(angle)) / 2		//'cos' for vertical motion
	CD2DBitmap::Get().DrawBitmap(IDB_PNG2, 0.0f-((784.0f*(scaleW - 1.0f) + 20.0f * sin(bgAngle)) / 2.0f), 0.0f - ((561.0f * (scaleH - 1.0f) + 20.0f * cos(bgAngle)) / 2.0f),
		784.f * scaleW, 561.f * scaleH);

	CtlI.Render();

	//test window title bar concept
	CD2DBasic::Get().FillRect(0.0f, 0.0f, APP_MAINRESX, 45.0f, 0.0f, 0.0f, 0.0f, 0.5f);
	CD2DBasic::Get().DrawLine(30.0f, 40.0f, 680.0f, 40.0f, 0.8f, 0.0f, 0.0f, 1.0f, 1.0f);

	//test minimize button concept
	CD2DBasic::Get().FillRect(695.0f, 10.0f, 40.0f, 30.0f, 1.0f, 1.0f, 1.0f);
	CD2DBasic::Get().DrawLine(710.0f, 30.0f, 720.0f, 30.0f, 0.8f, 0.0f, 0.0f, 1.0f, 2.0f);

	//test close button concept
	CD2DBasic::Get().FillRect(735.0f, 10.0f, 40.0f, 30.0f, 0.8f, 0.0f, 0.0f);
	CD2DBasic::Get().DrawLine(750.0f, 30.0f, 760.0f, 20.0f, 0.8f, 0.8f, 0.0f, 1.0f, 2.0f);
	CD2DBasic::Get().DrawLine(760.0f, 30.0f, 750.0f, 20.0f, 0.8f, 0.8f, 0.0f, 1.0f, 2.0f);

	//D2DBasic->DrawRect(0.0f, 0.0f, APP_MAINRESX, APP_MAINRESY, 0.8f, 0.0f, 0.0f, 1.0f, 2.0f);

	//Draw screen frame overlay
	CD2DBitmap::Get().DrawBitmap(IDB_SCRN_L, 0.f, 0.f, 20.f, 600.f);
	CD2DBitmap::Get().DrawBitmap(IDB_SCRN_T, 20.f, 0.f, 760.f, 20.f);
	CD2DBitmap::Get().DrawBitmap(IDB_SCRN_R, 780.f, 0.f, 20.f, 600.f);
	CD2DBitmap::Get().DrawBitmap(IDB_SCRN_B, 20.f, 580.f, 760.f, 20.f);

	CD2DCore::Get().EndDraw();
}