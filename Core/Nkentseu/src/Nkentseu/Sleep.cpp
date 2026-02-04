// -----------------------------------------------------------------------------
// FICHIER: Core/Unkeny2D/src/Unkeny2D/Core/Sleep.cpp
// DESCRIPTION: Implémentation multiplateforme des fonctions de mise en veille.
//              Supporte Windows, Linux, Android, macOS et Emscripten.
// AUTEUR: Rihen
// DATE: 2026
// -----------------------------------------------------------------------------

#include "Nkentseu/Sleep.h"
#include "Nkentseu/Config/Platform.h"

// -----------------------------------------------------------------------------
// INCLUDES SPÉCIFIQUES À LA PLATEFORME
// -----------------------------------------------------------------------------

#if defined(NK_PLATFORM_WINDOWS)
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
    
#elif defined(NK_PLATFORM_DESKTOP) || defined(NK_PLATFORM_ANDROID)
    #include <time.h>
    #include <errno.h>
    
#elif defined(NK_PLATFORM_EMSCRIPTEN)
    #include <emscripten.h>
#endif

// -----------------------------------------------------------------------------
// NAMESPACE: nkentseu
// -----------------------------------------------------------------------------
namespace nkentseu {

    // -------------------------------------------------------------------------
    // FONCTION: SleepNano
    // DESCRIPTION: Met le thread en veille avec précision nanoseconde
    // -------------------------------------------------------------------------
    void SleepNano(uint64 nanoseconds) {
        if (nanoseconds == 0) return;

        // ---------------------------------------------------------------------
        // IMPLÉMENTATION WINDOWS (QueryPerformanceCounter)
        // ---------------------------------------------------------------------
        #if defined(NK_PLATFORM_WINDOWS)
            LARGE_INTEGER freq, start, end;
            QueryPerformanceFrequency(&freq);
            QueryPerformanceCounter(&start);
            
            uint64 target = start.QuadPart + (nanoseconds * freq.QuadPart) / 1000000000ULL;
            
            // Pour les délais > 2ms, utiliser Sleep() pour économiser le CPU
            if (nanoseconds > 2000000) {
                ::Sleep(static_cast<DWORD>(nanoseconds / 1000000) - 1);
            }
            
            // Boucle d'attente active pour la précision
            do {
                QueryPerformanceCounter(&end);
            } while (end.QuadPart < target);

        // ---------------------------------------------------------------------
        // IMPLÉMENTATION POSIX (Linux, macOS, Android)
        // ---------------------------------------------------------------------
        #elif defined(NK_PLATFORM_DESKTOP) || defined(NK_PLATFORM_ANDROID)
            struct timespec req, rem;
            req.tv_sec = nanoseconds / 1000000000ULL;
            req.tv_nsec = nanoseconds % 1000000000ULL;
            
            // Gestion des interruptions (EINTR)
            while (nanosleep(&req, &rem) == -1 && errno == EINTR) {
                req = rem;
            }

        // ---------------------------------------------------------------------
        // IMPLÉMENTATION EMSCRIPTEN (WebAssembly)
        // ---------------------------------------------------------------------
        #elif defined(NK_PLATFORM_EMSCRIPTEN)
            emscripten_sleep(nanoseconds / 1000000);
        #endif
    }

} // namespace nkentseu