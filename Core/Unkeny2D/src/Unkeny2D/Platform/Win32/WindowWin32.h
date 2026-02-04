// -----------------------------------------------------------------------------
// FICHIER: Core/Unkeny2D/src/Unkeny2D/Platform/Win32/WindowWin32.h
// DESCRIPTION: Déclaration de la classe WindowWin32 (implémentation Win32).
//              Header conditionnel pour la plateforme Windows.
// AUTEUR: Rihen
// DATE: 2026
// -----------------------------------------------------------------------------

#pragma once

#include "Unkeny2D/Window/Window.h"
#include "Nkentseu/Config/Platform.h"

// Compilation conditionnelle pour Windows uniquement
#ifdef NK_PLATFORM_WINDOWS

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>

// -----------------------------------------------------------------------------
// NAMESPACE: nkentseu
// -----------------------------------------------------------------------------
namespace nkentseu {

    // -------------------------------------------------------------------------
    // CLASSE: WindowWin32
    // DESCRIPTION: Implémentation Win32 de l'interface Window
    // -------------------------------------------------------------------------
    class WindowWin32 : public Window {
    public:
        // ---------------------------------------------------------------------
        // CONSTRUCTEUR ET DESTRUCTEUR
        // ---------------------------------------------------------------------
        
        /**
         * @brief Constructeur de fenêtre Win32
         * @param title Titre de la fenêtre
         * @param width Largeur initiale
         * @param height Hauteur initiale
         */
        WindowWin32(const char* title, uint32 width, uint32 height);
        
        /**
         * @brief Destructeur de fenêtre Win32
         */
        ~WindowWin32() override;
        
        // ---------------------------------------------------------------------
        // IMPLÉMENTATION DE L'INTERFACE Window
        // ---------------------------------------------------------------------
        
        /**
         * @brief Initialise la fenêtre Win32
         * @return true si réussite, false sinon
         */
        bool Initialize() override;
        
        /**
         * @brief Libère les ressources de la fenêtre Win32
         */
        void Shutdown() override;
        
        /**
         * @brief Affiche la fenêtre Win32
         */
        void Show() override;
        
        /**
         * @brief Cache la fenêtre Win32
         */
        void Hide() override;
        
        /**
         * @brief Vérifie si la fenêtre est ouverte
         * @return État d'ouverture de la fenêtre
         */
        bool IsOpen() const override { return m_IsOpen; }
        
        /**
         * @brief Traite les messages Windows
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
         * @return "Windows"
         */
        const char* GetPlatformName() const override { return "Windows"; }

    private:
        // ---------------------------------------------------------------------
        // MÉTHODES STATIQUES PRIVÉES
        // ---------------------------------------------------------------------
        
        /**
         * @brief Procédure de fenêtre Win32 (callback système)
         * @param hwnd Handle de fenêtre
         * @param msg Message Windows
         * @param wParam Paramètre W
         * @param lParam Paramètre L
         * @return Résultat du traitement
         */
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
        
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
        
        /// Handle de fenêtre Win32
        HWND m_Hwnd;
        
        /// Contexte de périphérique Win32
        HDC m_Hdc;
        
        /// Instance d'application Win32
        HINSTANCE m_Hinstance;
    };

} // namespace nkentseu

#endif // NK_PLATFORM_WINDOWS