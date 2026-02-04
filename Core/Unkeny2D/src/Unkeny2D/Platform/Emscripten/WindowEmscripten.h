// -----------------------------------------------------------------------------
// FICHIER: Core/Unkeny2D/src/Unkeny2D/Platform/Emscripten/WindowEmscripten.h
// DESCRIPTION: Déclaration de la classe WindowEmscripten.
//              Header conditionnel pour la plateforme Emscripten.
// AUTEUR: Rihen
// DATE: 2026
// -----------------------------------------------------------------------------

#pragma once

#include "Unkeny2D/Window/Window.h"
#include "Nkentseu/Config/Platform.h"

// Compilation conditionnelle pour Emscripten uniquement
#ifdef NK_PLATFORM_EMSCRIPTEN

#include <string>

// -----------------------------------------------------------------------------
// NAMESPACE: nkentseu
// -----------------------------------------------------------------------------
namespace nkentseu {

    // -------------------------------------------------------------------------
    // CLASSE: WindowEmscripten
    // DESCRIPTION: Implémentation Emscripten de l'interface Window
    // -------------------------------------------------------------------------
    class WindowEmscripten : public Window {
    public:
        // ---------------------------------------------------------------------
        // CONSTRUCTEUR ET DESTRUCTEUR
        // ---------------------------------------------------------------------
        
        /**
         * @brief Constructeur de fenêtre Emscripten
         * @param title Titre de la fenêtre
         * @param width Largeur initiale
         * @param height Hauteur initiale
         */
        WindowEmscripten(const char* title, uint32 width, uint32 height);
        
        /**
         * @brief Destructeur de fenêtre Emscripten
         */
        ~WindowEmscripten() override;
        
        // ---------------------------------------------------------------------
        // IMPLÉMENTATION DE L'INTERFACE Window
        // ---------------------------------------------------------------------
        
        /**
         * @brief Initialise la fenêtre Emscripten
         * @return true si réussite, false sinon
         */
        bool Initialize() override;
        
        /**
         * @brief Libère les ressources de la fenêtre Emscripten
         */
        void Shutdown() override;
        
        /**
         * @brief Affiche la fenêtre (no-op sur Emscripten)
         */
        void Show() override {}
        
        /**
         * @brief Cache la fenêtre (no-op sur Emscripten)
         */
        void Hide() override {}
        
        /**
         * @brief Vérifie si la fenêtre est ouverte
         * @return État d'ouverture de la fenêtre
         */
        bool IsOpen() const override { return m_IsOpen; }
        
        /**
         * @brief Traite les événements (gérés par HTML5)
         */
        void ProcessEvents() override;
        
        /**
         * @brief Efface la fenêtre avec une couleur
         * @param color Couleur de fond
         */
        void Clear(const Color& color) override;
        
        /**
         * @brief Échange les buffers d'affichage
         */
        void SwapBuffers() override;
        
        // ---------------------------------------------------------------------
        // GETTERS
        // ---------------------------------------------------------------------
        
        /**
         * @brief Obtient l'identifiant de la fenêtre
         * @return ID unique de la fenêtre
         */
        uint32 GetID() const override { return m_ID; }
        
        /**
         * @brief Obtient la largeur courante de la fenêtre
         * @return Largeur en pixels
         */
        uint32 GetWidth() const override { return m_Width; }
        
        /**
         * @brief Obtient la hauteur courante de la fenêtre
         * @return Hauteur en pixels
         */
        uint32 GetHeight() const override { return m_Height; }
        
        /**
         * @brief Obtient le titre de la fenêtre
         * @return Titre sous forme de chaîne C
         */
        const char* GetTitle() const override { return m_Title.c_str(); }
        
        /**
         * @brief Obtient le nom de la plateforme
         * @return "Emscripten"
         */
        const char* GetPlatformName() const override { return "Emscripten"; }

    private:
        // ---------------------------------------------------------------------
        // VARIABLES MEMBRE PRIVÉES
        // ---------------------------------------------------------------------
        
        /// Identifiant unique de la fenêtre
        uint32 m_ID;
        
        /// Titre de la fenêtre
        std::string m_Title;
        
        /// Largeur de la fenêtre
        uint32 m_Width;
        
        /// Hauteur de la fenêtre
        uint32 m_Height;
        
        /// État d'ouverture de la fenêtre
        bool m_IsOpen;
    };

} // namespace nkentseu

#endif // NK_PLATFORM_EMSCRIPTEN