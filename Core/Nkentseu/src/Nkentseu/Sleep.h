// -----------------------------------------------------------------------------
// FICHIER: Core/Unkeny2D/src/Unkeny2D/Core/Sleep.h
// DESCRIPTION: Fonctions de mise en veille (sleep) multiplateforme avec
//              différentes unités de temps (nanosecondes, microsecondes, etc.)
// AUTEUR: Rihen
// DATE: 2026
// -----------------------------------------------------------------------------

#pragma once

#include "Nkentseu/Config/Export.h"
#include "Types.h"

// -----------------------------------------------------------------------------
// NAMESPACE: nkentseu
// -----------------------------------------------------------------------------
namespace nkentseu {

    /**
     * @brief Met le thread en veille pour une durée spécifiée en nanosecondes
     * @param nanoseconds Durée en nanosecondes
     */
    NK_API void SleepNano(uint64 nanoseconds);

    /**
     * @brief Met le thread en veille pour une durée spécifiée en microsecondes
     * @param microseconds Durée en microsecondes
     */
    inline void SleepMicro(uint64 microseconds) {
        SleepNano(microseconds * 1000);
    }

    /**
     * @brief Met le thread en veille pour une durée spécifiée en millisecondes
     * @param milliseconds Durée en millisecondes
     */
    inline void SleepMilli(uint64 milliseconds) {
        SleepNano(milliseconds * 1000000);
    }

    /**
     * @brief Met le thread en veille pour une durée spécifiée en secondes
     * @param seconds Durée en secondes
     */
    inline void Sleep(uint64 seconds) {
        SleepNano(seconds * 1000000000);
    }

} // namespace nkentseu