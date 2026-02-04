// -----------------------------------------------------------------------------
// FICHIER: Core/Unkeny2D/src/Unkeny2D/Window/WindowManager.cpp
// DESCRIPTION: Implémentation du gestionnaire centralisé des fenêtres.
//              Fournit des services d'enregistrement, recherche et traitement
//              pour toutes les fenêtres de l'application.
// AUTEUR: Rihen
// DATE: 2026
// -----------------------------------------------------------------------------

#include "Unkeny2D/Window/WindowManager.h"
#include <algorithm>
#include <iostream>

// -----------------------------------------------------------------------------
// NAMESPACE: nkentseu
// -----------------------------------------------------------------------------
namespace nkentseu {

    // -------------------------------------------------------------------------
    // INITIALISATION DES VARIABLES STATIQUES
    // -------------------------------------------------------------------------
    
    /// Liste de toutes les fenêtres enregistrées
    std::vector<Window*> WindowManager::s_Windows;
    
    /// Mutex pour la synchronisation thread-safe
    std::mutex WindowManager::s_Mutex;
    
    /// Compteur pour générer des identifiants uniques
    uint32 WindowManager::s_NextID = 1;

    // -------------------------------------------------------------------------
    // IMPLÉMENTATION DES MÉTHODES PUBLIQUES
    // -------------------------------------------------------------------------
    
    /**
     * @brief Enregistre une nouvelle fenêtre dans le gestionnaire
     * @param window Pointeur vers la fenêtre à enregistrer
     */
    void WindowManager::RegisterWindow(Window* window) {
        std::lock_guard<std::mutex> lock(s_Mutex);
        s_Windows.push_back(window);
    }
    
    /**
     * @brief Désenregistre une fenêtre du gestionnaire
     * @param window Pointeur vers la fenêtre à désenregistrer
     */
    void WindowManager::UnregisterWindow(Window* window) {
        std::lock_guard<std::mutex> lock(s_Mutex);
        auto it = std::find(s_Windows.begin(), s_Windows.end(), window);
        if (it != s_Windows.end()) {
            s_Windows.erase(it);
        }
    }
    
    /**
     * @brief Recherche une fenêtre par son identifiant
     * @param id Identifiant de la fenêtre recherchée
     * @return Pointeur vers la fenêtre ou nullptr si non trouvée
     */
    Window* WindowManager::GetWindow(uint32 id) {
        std::lock_guard<std::mutex> lock(s_Mutex);
        for (auto* win : s_Windows) {
            if (win->GetID() == id) {
                return win;
            }
        }
        return nullptr;
    }
    
    /**
     * @brief Traite les événements de toutes les fenêtres enregistrées
     */
    void WindowManager::ProcessAllEvents() {
        std::lock_guard<std::mutex> lock(s_Mutex);
        for (auto* win : s_Windows) {
            if (win->IsOpen()) {
                win->ProcessEvents();
            }
        }
    }

} // namespace nkentseu