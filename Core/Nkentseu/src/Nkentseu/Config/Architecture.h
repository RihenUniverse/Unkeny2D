// -----------------------------------------------------------------------------
// FICHIER: Core/Unkeny2D/src/Unkeny2D/Config/Architecture.h
// DESCRIPTION: Détection de l'architecture processeur. Définit les macros
//              d'identification d'architecture (x86, x64, ARM, WASM).
// AUTEUR: Rihen
// DATE: 2026
// -----------------------------------------------------------------------------

#pragma once

// -----------------------------------------------------------------------------
// MACROS DE DÉTECTION D'ARCHITECTURE
// -----------------------------------------------------------------------------

// Architecture x64 (64-bit)
#if defined(__x86_64__) || defined(_M_X64)
    #define NK_ARCH_X64 1
    #define NK_ARCH_64BIT 1

// Architecture x86 (32-bit)
#elif defined(__i386__) || defined(_M_IX86)
    #define NK_ARCH_X86 1
    #define NK_ARCH_32BIT 1
#endif

// Architecture ARM64 (64-bit)
#if defined(__aarch64__) || defined(_M_ARM64)
    #define NK_ARCH_ARM64 1
    #define NK_ARCH_64BIT 1

// Architecture ARM (32-bit)
#elif defined(__arm__) || defined(_M_ARM)
    #define NK_ARCH_ARM 1
    #define NK_ARCH_32BIT 1
#endif

// Architecture WebAssembly (WASM)
#if defined(__wasm__)
    #define NK_ARCH_WASM 1
#endif

// -----------------------------------------------------------------------------
// NAMESPACE: nkentseu
// DESCRIPTION: Espace de noms principal du framework
// -----------------------------------------------------------------------------
namespace nkentseu {

    /**
     * @brief Obtient le nom de l'architecture courante
     * @return Chaîne de caractères décrivant l'architecture
     */
    inline const char* GetArchitectureName() {
        #if defined(NK_ARCH_X64)
            return "x86_64";
        #elif defined(NK_ARCH_X86)
            return "x86";
        #elif defined(NK_ARCH_ARM64)
            return "ARM64";
        #elif defined(NK_ARCH_ARM)
            return "ARM";
        #elif defined(NK_ARCH_WASM)
            return "WebAssembly";
        #else
            return "Unknown";
        #endif
    }

} // namespace nkentseu