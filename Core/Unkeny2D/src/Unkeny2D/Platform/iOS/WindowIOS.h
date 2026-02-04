// -----------------------------------------------------------------------------
// FICHIER: Core/Unkeny2D/src/Unkeny2D/Platform/iOS/WindowIOS.h
// DESCRIPTION: Stub d'implémentation iOS de l'interface Window.
//              À compléter avec les APIs iOS natives (UIKit).
// AUTEUR: Rihen
// DATE: 2026
// -----------------------------------------------------------------------------

#pragma once

#include "Unkeny2D/Window/Window.h"
#include "Nkentseu/Config/Platform.h"

// Compilation conditionnelle pour iOS uniquement
#ifdef NK_PLATFORM_IOS

#include <string>

// -----------------------------------------------------------------------------
// NAMESPACE: nkentseu
// -----------------------------------------------------------------------------
namespace nkentseu {

    // -------------------------------------------------------------------------
    // CLASSE: WindowIOS
    // DESCRIPTION: Implémentation iOS (stub) de l'interface Window
    // -------------------------------------------------------------------------
    class WindowIOS : public Window {
    public:
        // ---------------------------------------------------------------------
        // CONSTRUCTEUR ET DESTRUCTEUR
        // ---------------------------------------------------------------------
        
        /**
         * @brief Constructeur de fenêtre iOS (stub)
         * @param title Titre de la fenêtre
         * @param width Largeur initiale
         * @param height Hauteur initiale
         */
        WindowIOS(const char* title, uint32 width, uint32 height) {}
        
        /**
         * @brief Destructeur de fenêtre iOS (stub)
         */
        ~WindowIOS() override {}
        
        // ---------------------------------------------------------------------
        // IMPLÉMENTATION DE L'INTERFACE Window (STUBS)
        // ---------------------------------------------------------------------
        
        /**
         * @brief Initialise la fenêtre iOS (stub)
         * @return false (non implémenté)
         */
        bool Initialize() override { return false; }
        
        /**
         * @brief Libère les ressources de la fenêtre iOS (stub)
         */
        void Shutdown() override {}
        
        /**
         * @brief Affiche la fenêtre (stub)
         */
        void Show() override {}
        
        /**
         * @brief Cache la fenêtre (stub)
         */
        void Hide() override {}
        
        /**
         * @brief Vérifie si la fenêtre est ouverte (stub)
         * @return false (non implémenté)
         */
        bool IsOpen() const override { return false; }
        
        /**
         * @brief Traite les événements iOS (stub)
         */
        void ProcessEvents() override {}
        
        /**
         * @brief Efface la fenêtre avec une couleur (stub)
         * @param color Couleur de fond
         */
        void Clear(const Color& color) override {}
        
        /**
         * @brief Échange les buffers d'affichage (stub)
         */
        void SwapBuffers() override {}
        
        // ---------------------------------------------------------------------
        // GETTERS (STUBS)
        // ---------------------------------------------------------------------
        
        /**
         * @brief Obtient l'identifiant de la fenêtre (stub)
         * @return 0 (non implémenté)
         */
        uint32 GetID() const override { return 0; }
        
        /**
         * @brief Obtient la largeur courante de la fenêtre (stub)
         * @return 0 (non implémenté)
         */
        uint32 GetWidth() const override { return 0; }
        
        /**
         * @brief Obtient la hauteur courante de la fenêtre (stub)
         * @return 0 (non implémenté)
         */
        uint32 GetHeight() const override { return 0; }
        
        /**
         * @brief Obtient le titre de la fenêtre (stub)
         * @return Chaîne vide (non implémenté)
         */
        const char* GetTitle() const override { return ""; }
        
        /**
         * @brief Obtient le nom de la plateforme
         * @return "iOS"
         */
        const char* GetPlatformName() const override { return "iOS"; }
    };

} // namespace nkentseu

#endif // NK_PLATFORM_IOS