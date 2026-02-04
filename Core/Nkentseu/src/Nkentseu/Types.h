// -----------------------------------------------------------------------------
// FICHIER: Core/Unkeny2D/src/Unkeny2D/Core/Types.h
// DESCRIPTION: Définition des types de base du framework avec des alias
//              standardisés pour une portabilité optimale.
// AUTEUR: Rihen
// DATE: 2026
// -----------------------------------------------------------------------------

#pragma once

#include <cstdint>
#include <cstddef>

// -----------------------------------------------------------------------------
// NAMESPACE: nkentseu
// -----------------------------------------------------------------------------
namespace nkentseu {

    // -------------------------------------------------------------------------
    // TYPES ENTIERS SIGNÉS
    // -------------------------------------------------------------------------
    
    /// Type entier 8-bit signé
    using int8   = std::int8_t;
    
    /// Type entier 16-bit signé
    using int16  = std::int16_t;
    
    /// Type entier 32-bit signé
    using int32  = std::int32_t;
    
    /// Type entier 64-bit signé
    using int64  = std::int64_t;

    // -------------------------------------------------------------------------
    // TYPES ENTIERS NON SIGNÉS
    // -------------------------------------------------------------------------
    
    /// Type entier 8-bit non signé
    using uint8  = std::uint8_t;
    
    /// Type entier 16-bit non signé
    using uint16 = std::uint16_t;
    
    /// Type entier 32-bit non signé
    using uint32 = std::uint32_t;
    
    /// Type entier 64-bit non signé
    using uint64 = std::uint64_t;

    // -------------------------------------------------------------------------
    // TYPES FLOTTANTS
    // -------------------------------------------------------------------------
    
    /// Type flottant 32-bit (simple précision)
    using float32 = float;
    
    /// Type flottant 64-bit (double précision)
    using float64 = double;

} // namespace nkentseu