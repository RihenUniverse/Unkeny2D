// -----------------------------------------------------------------------------
// FICHIER: Core/Unkeny2D/src/Unkeny2D/Config/Compiler.h
// DESCRIPTION: Détection du compilateur. Définit les macros d'identification
//              de compilateur (MSVC, GCC, Clang, Emscripten).
// AUTEUR: Rihen
// DATE: 2026
// -----------------------------------------------------------------------------

#pragma once

// -----------------------------------------------------------------------------
// MACROS DE DÉTECTION DE COMPILATEUR
// -----------------------------------------------------------------------------

// Compilateur Microsoft Visual C++
#if defined(_MSC_VER)
    #define NK_COMPILER_MSVC 1
#endif

// Compilateur GCC (non Clang)
#if defined(__GNUC__) && !defined(__clang__)
    #define NK_COMPILER_GCC 1
#endif

// Compilateur Clang
#if defined(__clang__)
    #define NK_COMPILER_CLANG 1
#endif

// Compilateur Emscripten
#if defined(__EMSCRIPTEN__)
    #define NK_COMPILER_EMSCRIPTEN 1
#endif

// -----------------------------------------------------------------------------
// NAMESPACE: nkentseu
// -----------------------------------------------------------------------------
namespace nkentseu {

    /**
     * @brief Obtient le nom du compilateur courant
     * @return Chaîne de caractères décrivant le compilateur
     */
    inline const char* GetCompilerName() {
        #if defined(NK_COMPILER_MSVC)
            return "MSVC";
        #elif defined(NK_COMPILER_CLANG)
            return "Clang";
        #elif defined(NK_COMPILER_GCC)
            return "GCC";
        #elif defined(NK_COMPILER_EMSCRIPTEN)
            return "Emscripten";
        #else
            return "Unknown";
        #endif
    }

} // namespace nkentseu