// -----------------------------------------------------------------------------
// FICHIER: Core/Unkeny2D/src/Unkeny2D/Platform/Android/WindowAndroid.h
// DESCRIPTION: Déclaration de la classe WindowAndroid (implémentation Android).
//              Header conditionnel pour la plateforme Android.
// AUTEUR: Rihen
// DATE: 2026
// -----------------------------------------------------------------------------

#pragma once

#include "Unkeny2D/Window/Window.h"
#include "Nkentseu/Config/Platform.h"

// Compilation conditionnelle pour Android uniquement
#ifdef NK_PLATFORM_ANDROID

#include <android_native_app_glue.h>
#include <string>

// -----------------------------------------------------------------------------
// NAMESPACE: nkentseu
// -----------------------------------------------------------------------------
namespace nkentseu {

    // -------------------------------------------------------------------------
    // CLASSE: WindowAndroid
    // DESCRIPTION: Implémentation Android de l'interface Window
    // -------------------------------------------------------------------------
    class WindowAndroid : public Window {
    public:
        // ---------------------------------------------------------------------
        // CONSTRUCTEUR ET DESTRUCTEUR
        // ---------------------------------------------------------------------
        
        /**
         * @brief Constructeur de fenêtre Android
         * @param title Titre de la fenêtre
         * @param width Largeur initiale
         * @param height Hauteur initiale
         */
        WindowAndroid(const char* title, uint32 width, uint32 height);
        
        /**
         * @brief Destructeur de fenêtre Android
         */
        ~WindowAndroid() override;
        
        // ---------------------------------------------------------------------
        // IMPLÉMENTATION DE L'INTERFACE Window
        // ---------------------------------------------------------------------
        
        /**
         * @brief Initialise la fenêtre Android
         * @return true si réussite, false sinon
         */
        bool Initialize() override;
        
        /**
         * @brief Libère les ressources de la fenêtre Android
         */
        void Shutdown() override;
        
        /**
         * @brief Affiche la fenêtre (no-op sur Android)
         */
        void Show() override {}
        
        /**
         * @brief Cache la fenêtre (no-op sur Android)
         */
        void Hide() override {}
        
        /**
         * @brief Vérifie si la fenêtre est ouverte
         * @return État d'ouverture de la fenêtre
         */
        bool IsOpen() const override { return m_IsOpen; }
        
        /**
         * @brief Traite les événements Android
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
         * @return "Android"
         */
        const char* GetPlatformName() const override { return "Android"; }
        
        // ---------------------------------------------------------------------
        // MÉTHODES SPÉCIFIQUES ANDROID
        // ---------------------------------------------------------------------
        
        /**
         * @brief Configure l'application Android associée
         * @param app Structure d'application Android
         */
        void SetAndroidApp(struct android_app* app) { m_App = app; }

    private:
        // ---------------------------------------------------------------------
        // MÉTHODES STATIQUES PRIVÉES (CALLBACKS ANDROID)
        // ---------------------------------------------------------------------
        
        /**
         * @brief Callback de commande Android
         * @param app Structure d'application
         * @param cmd Commande reçue
         */
        static void HandleCmd(struct android_app* app, int32_t cmd);
        
        /**
         * @brief Callback d'entrée Android
         * @param app Structure d'application
         * @param event Événement d'entrée
         * @return 1 si traité, 0 sinon
         */
        static int32_t HandleInput(struct android_app* app, AInputEvent* event);
        
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
        
        /// Pointeur vers la structure d'application Android
        struct android_app* m_App;
    };

} // namespace nkentseu

#endif // NK_PLATFORM_ANDROID