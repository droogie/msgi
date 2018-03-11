#include "stdafx.h"
#include "Actor_Debug.hpp"
#include "ResourceNameHash.hpp"
#include "LibDG.hpp"
#include "Menu.hpp"
#include "WinMain.hpp"
#include "Actor_GameD.hpp"

union PolyTag2
{
    struct
    {
        WORD LowPart;
        WORD HighPart;
    };
    DWORD WordPart;
};

void SetDepth(POLY_F4* p, u16 depth)
{
    PolyTag2* pTag = (PolyTag2*)&p->tag;
    //pTag->LowPart = depth;
    pTag->HighPart = 0x0900;
}

static std::string ButtonFlagsToString(DWORD flags)
{
    std::string buttons;

    if (flags & PsxButtonBits::eCircle)
    {
        buttons += "O ";
    }

    if (flags & PsxButtonBits::eCross)
    {
        buttons += "X ";
    }

    if (flags & PsxButtonBits::eDPadDown)
    {
        buttons += "D ";
    }

    if (flags & PsxButtonBits::eDPadLeft)
    {
        buttons += "L ";
    }

    if (flags & PsxButtonBits::eDPadRight)
    {
        buttons += "R ";
    }

    if (flags & PsxButtonBits::eDPadUp)
    {
        buttons += "U ";
    }

    if (flags & PsxButtonBits::eL1)
    {
        buttons += "L1 ";
    }

    if (flags & PsxButtonBits::eL2)
    {
        buttons += "L2 ";
    }

    if (flags & PsxButtonBits::eR1)
    {
        buttons += "R1 ";
    }

    if (flags & PsxButtonBits::eR2)
    {
        buttons += "R2 ";
    }

    if (flags & PsxButtonBits::eSelect)
    {
        buttons += "Select ";
    }

    if (flags & PsxButtonBits::eSquare)
    {
        buttons += "Square ";
    }

    if (flags & PsxButtonBits::eStart)
    {
        buttons += "Start ";
    }

    if (flags & PsxButtonBits::eTriangle)
    {
        buttons += "Triangle ";
    }

    return buttons;
}

static std::string LimitTo64Chars(const std::string& s)
{
    if (s.size() > 64)
    {
        return s.substr(0, 60) + "...";
    }
    return s;
}

Actor *__cdecl Res_strctrl_create_45803B(int scriptVar_s_vox_code, unsigned int scriptVar_p, int b24Or30fps)
{
    return nullptr;
}
MGS_FUNC_IMPLEX(0x45803B, Res_strctrl_create_45803B, false);

static void CC Debug_Update(Actor_Debug* pDebug)
{
   
    TextSetXYFlags_459B0B(30, 100, 0);
    TextSetRGB_459B27(0x80, 0x80, 0x80);
    Menu_DrawText_459B63 ("A textual test");

    TextSetXYFlags_459B0B(20, 120, 0x20);
    TextSetRGB_459B27(255, 0, 255);
    Menu_DrawText_459B63("A textual test !()_");

   
    TextSetXYFlags_459B0B(50, 140, 0x20);
    TextSetRGB_459B27(55, 255, 100);
    TextSetXYFlags_459B0B(50, 140, 0x10);
    Menu_DrawText_459B63("A textual test !$%^&*()_");

    POLY_F4 * pDst = (POLY_F4  *)pDebug->mPrimData->field_40_pDataStart[gActiveBuffer_dword_791A08];

    POLY_F4 * pSrc = &pDebug->mPolyF4;

    memcpy(pDst, pSrc, sizeof(POLY_F4));
    SetDepth(pDst, 0x0900);

    //SetDepth(&pDst[i], pRank->field_41C_16_prim_dst[i]);

    TextSetXYFlags_459B0B(60, 40, 0x0);
    TextSetRGB_459B27(255, 255, 0);
    const std::string buttonsStatus = "Button status = " + ButtonFlagsToString(gButtonsArray4_7919C0[0].field_0_button_status);
    Menu_DrawText_459B63(LimitTo64Chars(buttonsStatus).c_str());

    TextSetXYFlags_459B0B(60, 50, 0x0);
    const std::string buttonsPressed = "Button pressed = " + ButtonFlagsToString(gButtonsArray4_7919C0[0].field_2_button_pressed);
    Menu_DrawText_459B63(LimitTo64Chars(buttonsPressed).c_str());

    TextSetXYFlags_459B0B(60, 60, 0x0);
    const std::string buttonsReleased = "Button released = " + ButtonFlagsToString(gButtonsArray4_7919C0[0].field_4_button_release);
    Menu_DrawText_459B63(LimitTo64Chars(buttonsReleased).c_str());

    TextSetXYFlags_459B0B(60, 70, 0x0);
    const std::string buttonsQuick = "Button quick = " + ButtonFlagsToString(gButtonsArray4_7919C0[0].field_6_button_quick);
    Menu_DrawText_459B63(LimitTo64Chars(buttonsQuick).c_str());

    if (gButtonsArray4_7919C0[0].field_2_button_pressed & PsxButtonBits::eDPadUp)
    {
        Res_strctrl_create_45803B(0xfc308022, 0, 0);
    }

    if (gGameStates_78E7E0.gSnakeCurrentHealth_78E7F6 < gGameStates_78E7E0.gSnakeMaxHealth_78E7F8)
    {
        gGameStates_78E7E0.gSnakeCurrentHealth_78E7F6++;
        if (gGameStates_78E7E0.gSnakeCurrentHealth_78E7F6 >= gGameStates_78E7E0.gSnakeMaxHealth_78E7F8)
        {
            gGameStates_78E7E0.gSnakeCurrentHealth_78E7F6 = 0;
        }
    }

  //  memcpy((pDebug->mPrimData /*+ gActiveBuffer_dword_791A08*/)->field_40_pDataStart, &pDebug->mPolyF4, sizeof(POLY_FT4));
   // pDebug->mPrimData->mBase.field_0_ptr = 3;

}

static void CC Debug_Shutdown(Actor_Debug*)
{

}
MGS_VAR_EXTERN(u32, dword_9942A0);

static int CC Debug_Loader(Actor_Debug* pDebug)
{
    pDebug->mPolyF4 = {};

    int numPrims = 1;
    Prim_unknown_0x54* pPrim16Data = PrimAlloc_405050(2066, numPrims, 0, 0, 0);
    if (pPrim16Data)
    {
        PrimAdd_401805(pPrim16Data);
        pPrim16Data->field_28_flags_or_type = (signed __int16)dword_9942A0;
    }
    pDebug->mPrimData = pPrim16Data;

    //const WORD resHash = ResourceNameHash("back_l");
    //Res_rank_prim_related_4767CE(nullptr, resHash, &pDebug->mPolyF4, -160, -112, 0, 112, 0, 0);
  
    pDebug->mPolyF4.tag = 0x9000000;
    pDebug->mPolyF4.code = 2;

    pDebug->mPolyF4.r0 = 255;
    pDebug->mPolyF4.g0 = 255;
    pDebug->mPolyF4.b0 = 255;
    
    pDebug->mPolyF4.x0 = 0;
    pDebug->mPolyF4.y0 = 0;

    pDebug->mPolyF4.x1 = 0;
    pDebug->mPolyF4.y1 = 1000;

    pDebug->mPolyF4.x2 = 1000;
    pDebug->mPolyF4.y2 = 1000;

    pDebug->mPolyF4.x3= 0;
    pDebug->mPolyF4.y3 = 1000;

    // TODO: Hacks because these don't get set correctly in standalone exe yet
    game_state_dword_72279C.flags = 0x00440000;
    gGameStates_78E7E0.gSnakeCurrentHealth_78E7F6 = 1024-256;
    gGameStates_78E7E0.gSnakeMaxHealth_78E7F8 = 1024;
    gSnakeCurrentO2_995348 = 512;

    return 0;
}

Actor_Debug* AddDebugActor()
{
    Actor_Debug* pDebug = Actor_ResourceAllocT<Actor_Debug>(1);
    if (pDebug)
    {
        Actor_Init_40A347(&pDebug->mBase,
            reinterpret_cast<TActorFunction>(Debug_Update),
            reinterpret_cast<TActorFunction>(Debug_Shutdown),
            __FILE__);

        if (Debug_Loader(pDebug) < 0)
        {
            Actor_DestroyOnNextUpdate_40A3ED(&pDebug->mBase);
        }
    }
    return pDebug;
}
