#pragma once

#include "NativeImport.hpp"

namespace pawn_natives {
#ifdef PAWN_NATIVES_HAS_FUNC
std::list<NativeFuncBase*>*
    NativeFuncBase::all_
    = 0;
#endif

int AmxLoad(AMX* amx)
{
    int
        ret
        = 0;
#ifdef PAWN_NATIVES_HAS_FUNC
    if (NativeFuncBase::all_) {
        // Need a sentinel because of:
        //
        //   https://github.com/Zeex/sampgdk/issues/188
        //
        // Otherwise we could do:
        //
        //   curNative.name = curFunc->name_;
        //   curNative.func = curFunc->native_;
        //   ret = amx_Register(amx, &curNative, 1);
        //
        AMX_NATIVE_INFO
        curNative[2] = { { 0, 0 }, { 0, 0 } };
        for (NativeFuncBase* curFunc : *NativeFuncBase::all_) {
            LOG_NATIVE_INFO("Registering native %s", curFunc->name_);
            curNative[0].name = curFunc->name_;
            curNative[0].func = curFunc->native_;
            ret = amx_Register(amx, curNative, -1);
        }
    }
#endif
    return ret;
}
}
