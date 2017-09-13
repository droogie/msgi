#pragma once

#include "MgsFunction.hpp"

void ScriptCpp_ForceLink();
void CC Script_BindInits_452610();

struct GCL_Proc_Arguments
{
    WORD mNumArgs;
    WORD mPadding;
    DWORD* mPArgs;
};
MGS_ASSERT_SIZEOF(GCL_Proc_Arguments, 8);

signed int CC Script_Run(BYTE* pScriptBytes, GCL_Proc_Arguments* pArgs);
int CC Script_RunProc(BYTE* pScript);
BYTE* CC Script_GCL_Execute(BYTE* pScript, BYTE** ppScript, DWORD* pRet);
signed int CC Script_ProcCancelOrRun(WORD id, GCL_Proc_Arguments* pArgs);
DWORD CC Script_ParamExists(char paramId);
DWORD CC Script_get_int();
BYTE* CC Script_GetReturnAddress();
void CC ScriptEngineInit_4090A7();

EXTERN_MGS_FUNC_NOT_IMPL(0x409924, DWORD CC(BYTE *pScript), Script_Unknown8);

MGS_VAR_EXTERN(DWORD, dword_7227A4);
MGS_VAR_EXTERN(DWORD, script_cancel_non_zero_dword_7227A0);

enum GCLOperators
{
    eNegate = 1,
    eIsZero = 2,
    eComplement = 3,
    eAdd = 4,
    eSubtract = 5,
    eMultiply = 6,
    eDivide = 7,
    eModulus = 8,
    eEquals = 9,
    eNotEquals = 10,
    eLessThan = 11,
    eLessThanOrEqual = 12,
    eGreaterThan = 13,
    eGreaterThanOrEqual = 14,
    eBitWiseOR = 15,
    eBitWiseAND = 16,
    eBitWiseXOR = 17,
    eOr = 18,
    eAnd = 19,
};

void DoScriptTests();
