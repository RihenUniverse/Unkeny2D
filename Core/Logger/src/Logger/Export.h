// -----------------------------------------------------------------------------
// FICHIER: Core/Logger/src/Logger/Export.h
// DESCRIPTION: Configuration d'exportation de symboles pour le module Logger.
// AUTEUR: Rihen
// DATE: 2026
// -----------------------------------------------------------------------------

#pragma once

#include <Nkentseu/Config/Export.h>
#include <Nkentseu/Config/Compiler.h>

// -----------------------------------------------------------------------------
// MACROS D'EXPORTATION/IMPORTATION POUR LOGGER
// -----------------------------------------------------------------------------

#if defined(NK_PLATFORM_WINDOWS)
    #if defined(LOGGER_BUILD_SHARED)
        #define LOGGER_API __declspec(dllexport)
    #elif defined(LOGGER_USE_SHARED)
        #define LOGGER_API __declspec(dllimport)
    #else
        #define LOGGER_API
    #endif

#elif defined(NK_COMPILER_GCC) || defined(NK_COMPILER_CLANG)
    #if defined(LOGGER_BUILD_SHARED)
        #define LOGGER_API __attribute__((visibility("default")))
    #else
        #define LOGGER_API
    #endif

#else
    #define LOGGER_API
#endif

// -----------------------------------------------------------------------------
// MACROS D'INLINING POUR LOGGER
// -----------------------------------------------------------------------------

#if defined(NK_COMPILER_MSVC)
    #define LOGGER_FORCE_INLINE __forceinline
    #define LOGGER_NO_INLINE __declspec(noinline)

#elif defined(NK_COMPILER_GCC) || defined(NK_COMPILER_CLANG)
    #define LOGGER_FORCE_INLINE __attribute__((always_inline)) inline
    #define LOGGER_NO_INLINE __attribute__((noinline))

#else
    #define LOGGER_FORCE_INLINE inline
    #define LOGGER_NO_INLINE
#endif

// Macro d'inlining standard pour Logger
#define LOGGER_INLINE inline