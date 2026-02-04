// -----------------------------------------------------------------------------
// FICHIER: Core/Unkeny2D/src/Unkeny2D/Window/WindowManager.h
// DESCRIPTION: Gestionnaire centralisé des fenêtres. Permet d'enregistrer,
//              suivre et traiter toutes les fenêtres créées dans l'application.
// AUTEUR: Rihen
// DATE: 2026
// -----------------------------------------------------------------------------

#pragma once

#include "Nkentseu/Config/Export.h"
#include "Window.h"
#include <vector>
#include <mutex>

// -----------------------------------------------------------------------------
// NAMESPACE: nkentseu
// -----------------------------------------------------------------------------
namespace nkentseu {

    // -------------------------------------------------------------------------
    // CLASSE: WindowManager
    // DESCRIPTION: Singleton pour la gestion centralisée des fenêtres
    // -------------------------------------------------------------------------
    class NK_API WindowManager {
    public:
        // ---------------------------------------------------------------------
        // MÉTHODES STATIQUES PUBLIQUES
        // ---------------------------------------------------------------------
        
        /**
         * @brief Enregistre une nouvelle fenêtre dans le gestionnaire
         * @param window Pointeur vers la fenêtre à enregistrer
         */
        static void RegisterWindow(Window* window);
        
        /**
         * @brief Désenregistre une fenêtre du gestionnaire
         * @param window Pointeur vers la fenêtre à désenregistrer
         */
        static void UnregisterWindow(Window* window);
        
        /**
         * @brief Recherche une fenêtre par son identifiant
         * @param id Identifiant de la fenêtre recherchée
         * @return Pointeur vers la fenêtre ou nullptr si non trouvée
         */
        static Window* GetWindow(uint32 id);
        
        /**
         * @brief Traite les événements de toutes les fenêtres enregistrées
         */
        static void ProcessAllEvents();

    private:
        // ---------------------------------------------------------------------
        // VARIABLES STATIQUES PRIVÉES
        // ---------------------------------------------------------------------
        
        /// Liste de toutes les fenêtres enregistrées
        static std::vector<Window*> s_Windows;
        
        /// Mutex pour la synchronisation thread-safe
        static std::mutex s_Mutex;
        
        /// Compteur pour générer des identifiants uniques
        static uint32 s_NextID;
    };

} // namespace nkentseu