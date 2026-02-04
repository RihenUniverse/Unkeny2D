// -----------------------------------------------------------------------------
// FICHIER: Core/Unkeny2D/src/Unkeny2D/Platform/Linux/WindowXCB.h
// DESCRIPTION: Déclaration de la classe WindowXCB (implémentation Linux XCB).
//              Header conditionnel pour la plateforme Linux.
// AUTEUR: Rihen
// DATE: 2026
// -----------------------------------------------------------------------------

#pragma once

#include "Unkeny2D/Window/Window.h"
#include "Nkentseu/Config/Platform.h"

// Compilation conditionnelle pour Linux uniquement
#ifdef NK_PLATFORM_LINUX

#include <xcb/xcb.h>
#include <string>

// -----------------------------------------------------------------------------
// NAMESPACE: nkentseu
// -----------------------------------------------------------------------------
namespace nkentseu {

    // -------------------------------------------------------------------------
    // CLASSE: WindowXCB
    // DESCRIPTION: Implémentation Linux XCB de l'interface Window
    // -------------------------------------------------------------------------
    class WindowXCB : public Window {
    public:
        // ---------------------------------------------------------------------
        // CONSTRUCTEUR ET DESTRUCTEUR
        // ---------------------------------------------------------------------
        
        /**
         * @brief Constructeur de fenêtre XCB
         * @param title Titre de la fenêtre
         * @param width Largeur initiale
         * @param height Hauteur initiale
         */
        WindowXCB(const char* title, uint32 width, uint32 height);
        
        /**
         * @brief Destructeur de fenêtre XCB
         */
        ~WindowXCB() override;
        
        // ---------------------------------------------------------------------
        // IMPLÉMENTATION DE L'INTERFACE Window
        // ---------------------------------------------------------------------
        
        /**
         * @brief Initialise la fenêtre XCB
         * @return true si réussite, false sinon
         */
        bool Initialize() override;
        
        /**
         * @brief Libère les ressources de la fenêtre XCB
         */
        void Shutdown() override;
        
        /**
         * @brief Affiche la fenêtre XCB
         */
        void Show() override;
        
        /**
         * @brief Cache la fenêtre XCB
         */
        void Hide() override;
        
        /**
         * @brief Vérifie si la fenêtre est ouverte
         * @return État d'ouverture de la fenêtre
         */
        bool IsOpen() const override { return m_IsOpen; }
        
        /**
         * @brief Traite les événements XCB
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
         * @return "Linux"
         */
        const char* GetPlatformName() const override { return "Linux"; }

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
        
        /// Connexion XCB
        xcb_connection_t* m_Connection;
        
        /// Fenêtre XCB
        xcb_window_t m_Window;
        
        /// Écran XCB
        xcb_screen_t* m_Screen;
        
        /// Contexte graphique XCB
        xcb_gcontext_t m_GC;
    };

} // namespace nkentseu

#endif // NK_PLATFORM_LINUX