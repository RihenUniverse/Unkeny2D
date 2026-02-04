// -----------------------------------------------------------------------------
// FICHIER: Core/Unkeny2D/src/Unkeny2D/Platform/Emscripten/WindowEmscripten.cpp
// DESCRIPTION: Implémentation Emscripten (WebAssembly) de l'interface Window.
//              Utilise les APIs HTML5 Canvas pour l'affichage web.
// AUTEUR: Rihen
// DATE: 2026
// -----------------------------------------------------------------------------

#include "WindowEmscripten.h"

// Compilation conditionnelle pour Emscripten uniquement
#ifdef NK_PLATFORM_EMSCRIPTEN

#include "Unkeny2D/Events/EventManager.h"
#include "Unkeny2D/Window/WindowManager.h"
#include <emscripten.h>
#include <emscripten/html5.h>

// -----------------------------------------------------------------------------
// NAMESPACE: nkentseu
// -----------------------------------------------------------------------------
namespace nkentseu {

    // -------------------------------------------------------------------------
    // VARIABLE GLOBALE PRIVÉE
    // -------------------------------------------------------------------------
    
    /// Compteur pour générer des IDs uniques de fenêtres Emscripten
    static uint32 g_NextWindowID = 1;

    // -------------------------------------------------------------------------
    // IMPLÉMENTATION DE WindowEmscripten
    // -------------------------------------------------------------------------
    
    /**
     * @brief Constructeur de fenêtre Emscripten
     * @param title Titre de la fenêtre
     * @param width Largeur initiale
     * @param height Hauteur initiale
     */
    WindowEmscripten::WindowEmscripten(const char* title, uint32 width, uint32 height)
        : m_ID(g_NextWindowID++)
        , m_Title(title)
        , m_Width(width)
        , m_Height(height)
        , m_IsOpen(false)
    {
    }
    
    /**
     * @brief Destructeur de fenêtre Emscripten
     */
    WindowEmscripten::~WindowEmscripten() {
        Shutdown();
    }
    
    /**
     * @brief Initialise la fenêtre Emscripten
     * @return true si réussite, false sinon
     */
    bool WindowEmscripten::Initialize() {
        // Configuration du canvas HTML5
        emscripten_set_canvas_element_size("#canvas", m_Width, m_Height);
        
        m_IsOpen = true;
        WindowManager::RegisterWindow(this);
        return true;
    }
    
    /**
     * @brief Libère les ressources de la fenêtre Emscripten
     */
    void WindowEmscripten::Shutdown() {
        m_IsOpen = false;
        WindowManager::UnregisterWindow(this);
    }
    
    /**
     * @brief Traite les événements (gérés par HTML5 sur Emscripten)
     */
    void WindowEmscripten::ProcessEvents() {
        // Les événements sont gérés via les callbacks HTML5
    }
    
    /**
     * @brief Efface la fenêtre avec une couleur (stub pour Emscripten)
     * @param color Couleur de fond
     */
    void WindowEmscripten::Clear(const Color& color) {
        // TODO: Implémenter le rendu Canvas 2D pour Emscripten
    }
    
    /**
     * @brief Échange les buffers (automatique avec le navigateur)
     */
    void WindowEmscripten::SwapBuffers() {
        // Automatique avec le navigateur
    }

} // namespace nkentseu

#endif // NK_PLATFORM_EMSCRIPTEN