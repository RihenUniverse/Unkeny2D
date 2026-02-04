// -----------------------------------------------------------------------------
// FICHIER: Core/Unkeny2D/src/Unkeny2D/Config/Platform.h
// DESCRIPTION: Détection de la plateforme d'exécution. Définit les macros
//              d'identification de plateforme (Windows, Linux, macOS, etc.)
// AUTEUR: Rihen
// DATE: 2026
// -----------------------------------------------------------------------------

#pragma once

// -----------------------------------------------------------------------------
// MACROS DE DÉTECTION DE PLATEFORME
// -----------------------------------------------------------------------------

// Plateforme Windows
#if defined(_WIN32) || defined(_WIN64)
    #define NK_PLATFORM_WINDOWS 1
#endif

// Plateforme Linux (non Android)
#if defined(__linux__) && !defined(__ANDROID__)
    #define NK_PLATFORM_LINUX 1
#endif

// Plateforme macOS
#if defined(__APPLE__) && defined(__MACH__)
    #include <TargetConditionals.h>
    #if TARGET_OS_MAC && !TARGET_OS_IPHONE
        #define NK_PLATFORM_MACOS 1
    #endif
#endif

// Plateforme iOS
#if defined(__APPLE__) && defined(__MACH__)
    #include <TargetConditionals.h>
    #if TARGET_OS_IPHONE
        #define NK_PLATFORM_IOS 1
    #endif
#endif

// Plateforme Android
#if defined(__ANDROID__)
    #define NK_PLATFORM_ANDROID 1
#endif

// Plateforme Emscripten (WebAssembly)
#if defined(__EMSCRIPTEN__)
    #define NK_PLATFORM_EMSCRIPTEN 1
#endif

// -----------------------------------------------------------------------------
// MACROS DE CATÉGORIE DE PLATEFORME
// -----------------------------------------------------------------------------

// Plateformes Desktop
#if defined(NK_PLATFORM_WINDOWS) || defined(NK_PLATFORM_LINUX) || defined(NK_PLATFORM_MACOS)
    #define NK_PLATFORM_DESKTOP 1
#endif

// Plateformes Mobile
#if defined(NK_PLATFORM_ANDROID) || defined(NK_PLATFORM_IOS)
    #define NK_PLATFORM_MOBILE 1
#endif

// -----------------------------------------------------------------------------
// NAMESPACE: nkentseu
// -----------------------------------------------------------------------------
namespace nkentseu {

    /**
     * @brief Obtient le nom de la plateforme courante
     * @return Chaîne de caractères décrivant la plateforme
     */
    inline const char* GetPlatformName() {
        #if defined(NK_PLATFORM_WINDOWS)
            return "Windows";
        #elif defined(NK_PLATFORM_LINUX)
            return "Linux";
        #elif defined(NK_PLATFORM_MACOS)
            return "macOS";
        #elif defined(NK_PLATFORM_IOS)
            return "iOS";
        #elif defined(NK_PLATFORM_ANDROID)
            return "Android";
        #elif defined(NK_PLATFORM_EMSCRIPTEN)
            return "Emscripten";
        #else
            return "Unknown";
        #endif
    }

} // namespace nkentseu