// -----------------------------------------------------------------------------
// FICHIER: Core/Unkeny2D/src/Unkeny2D/Config/Export.h
// DESCRIPTION: Configuration d'exportation de symboles (DLL/Shared Library).
//              Définit les macros pour l'export/import et l'inlining.
// AUTEUR: Rihen
// DATE: 2026
// -----------------------------------------------------------------------------

#pragma once

#include "Platform.h"
#include "Compiler.h"

// -----------------------------------------------------------------------------
// MACROS D'EXPORTATION/IMPORTATION (DLL/SHARED LIBRARY)
// -----------------------------------------------------------------------------

#if defined(NK_PLATFORM_WINDOWS)
    #if defined(NK_BUILD_SHARED)
        #define NK_API __declspec(dllexport)
    #elif defined(NK_USE_SHARED)
        #define NK_API __declspec(dllimport)
    #else
        #define NK_API
    #endif

#elif defined(NK_COMPILER_GCC) || defined(NK_COMPILER_CLANG)
    #if defined(NK_BUILD_SHARED)
        #define NK_API __attribute__((visibility("default")))
    #else
        #define NK_API
    #endif

#else
    #define NK_API
#endif

// -----------------------------------------------------------------------------
// MACROS D'INLINING
// -----------------------------------------------------------------------------

#if defined(NK_COMPILER_MSVC)
    #define NK_FORCE_INLINE __forceinline
    #define NK_NO_INLINE __declspec(noinline)

#elif defined(NK_COMPILER_GCC) || defined(NK_COMPILER_CLANG)
    #define NK_FORCE_INLINE __attribute__((always_inline)) inline
    #define NK_NO_INLINE __attribute__((noinline))

#else
    #define NK_FORCE_INLINE inline
    #define NK_NO_INLINE
#endif

// Macro d'inlining standard
#define NK_INLINE inline