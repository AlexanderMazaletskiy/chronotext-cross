/*
 * THE NEW CHRONOTEXT TOOLKIT: https://github.com/arielm/new-chronotext-toolkit
 * COPYRIGHT (C) 2012-2015, ARIEL MALKA ALL RIGHTS RESERVED.
 *
 * THE FOLLOWING SOURCE-CODE IS DISTRIBUTED UNDER THE SIMPLIFIED BSD LICENSE:
 * https://github.com/arielm/new-chronotext-toolkit/blob/master/LICENSE.md
 */

#pragma once

#include "Platform.h"
#include "Log.h"

#if defined(CHR_PLATFORM_IOS)
  #include "ios/system/SystemInfo.h"
#elif defined(CHR_PLATFORM_ANDROID)
  #include "android/system/SystemInfo.h"
#elif defined(CHR_PLATFORM_DESKTOP)
  #include "desktop/system/SystemInfo.h"
#elif defined(CHR_PLATFORM_EMSCRIPTEN)
  #include "emscripten/system/SystemInfo.h"
#endif

namespace chr
{
  typedef system::Info SystemInfo;
}
