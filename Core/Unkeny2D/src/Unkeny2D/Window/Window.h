// -----------------------------------------------------------------------------
// FICHIER: Core/Unkeny2D/src/Unkeny2D/Window/Window.h
// DESCRIPTION: Interface principale abstraite pour les fenêtres multiplateforme.
//              Définit l'API commune à toutes les implémentations de fenêtres.
// AUTEUR: Rihen
// DATE: 2026
// -----------------------------------------------------------------------------

#pragma once

#include "Nkentseu/Config/Export.h"
#include "Nkentseu/Types.h"
#include <string>

// -----------------------------------------------------------------------------
// NAMESPACE: nkentseu
// -----------------------------------------------------------------------------
namespace nkentseu {

    // -------------------------------------------------------------------------
    // STRUCTURE: Color
    // DESCRIPTION: Représentation d'une couleur RGBA avec composantes flottantes
    // -------------------------------------------------------------------------
    struct Color {
        /// Composante rouge (0.0 à 1.0)
        float r;
        
        /// Composante verte (0.0 à 1.0)
        float g;
        
        /// Composante bleue (0.0 à 1.0)
        float b;
        
        /// Composante alpha (0.0 à 1.0)
        float a;
        
        /**
         * @brief Constructeur de couleur
         * @param red Composante rouge (défaut: 0.0)
         * @param green Composante verte (défaut: 0.0)
         * @param blue Composante bleue (défaut: 0.0)
         * @param alpha Composante alpha (défaut: 1.0)
         */
        Color(float red = 0, float green = 0, float blue = 0, float alpha = 1)
            : r(red), g(green), b(blue), a(alpha) {}
    };

    // -------------------------------------------------------------------------
    // CLASSE: Window
    // DESCRIPTION: Interface abstraite pour les fenêtres multiplateforme
    // -------------------------------------------------------------------------
    class NK_API Window {
        public:
            virtual ~Window() = default;
            
            // ---------------------------------------------------------------------
            // MÉTHODES STATIQUES
            // ---------------------------------------------------------------------
            
            /**
             * @brief Factory method pour créer une fenêtre adaptée à la plateforme
             * @param title Titre de la fenêtre
             * @param width Largeur initiale en pixels
             * @param height Hauteur initiale en pixels
             * @return Pointeur vers la fenêtre créée (à détruire avec delete)
             */
            static Window* Create(const char* title, uint32 width, uint32 height);
            
            // ---------------------------------------------------------------------
            // MÉTHODES VIRTUELLES PURES (INTERFACE)
            // ---------------------------------------------------------------------
            
            /**
             * @brief Initialise la fenêtre et ses ressources
             * @return true si l'initialisation réussit, false sinon
             */
            virtual bool Initialize() = 0;
            
            /**
             * @brief Libère les ressources de la fenêtre
             */
            virtual void Shutdown() = 0;
            
            /**
             * @brief Affiche la fenêtre
             */
            virtual void Show() = 0;
            
            /**
             * @brief Cache la fenêtre
             */
            virtual void Hide() = 0;
            
            /**
             * @brief Vérifie si la fenêtre est ouverte
             * @return true si la fenêtre est ouverte, false sinon
             */
            virtual bool IsOpen() const = 0;
            
            /**
             * @brief Traite les événements en attente de la fenêtre
             */
            virtual void ProcessEvents() = 0;
            
            /**
             * @brief Efface le contenu de la fenêtre avec une couleur
             * @param color Couleur de fond
             */
            virtual void Clear(const Color& color) = 0;
            
            /**
             * @brief Échange les buffers d'affichage (double buffering)
             */
            virtual void SwapBuffers() = 0;
            
            // ---------------------------------------------------------------------
            // MÉTHODES D'ACCÈS (GETTERS)
            // ---------------------------------------------------------------------
            
            /**
             * @brief Obtient l'identifiant unique de la fenêtre
             * @return Identifiant de fenêtre
             */
            virtual uint32 GetID() const = 0;
            
            /**
             * @brief Obtient la largeur courante de la fenêtre
             * @return Largeur en pixels
             */
            virtual uint32 GetWidth() const = 0;
            
            /**
             * @brief Obtient la hauteur courante de la fenêtre
             * @return Hauteur en pixels
             */
            virtual uint32 GetHeight() const = 0;
            
            /**
             * @brief Obtient le titre de la fenêtre
             * @return Titre sous forme de chaîne C
             */
            virtual const char* GetTitle() const = 0;
            
            /**
             * @brief Obtient le nom de la plateforme d'implémentation
             * @return Nom de la plateforme
             */
            virtual const char* GetPlatformName() const = 0;
    };

} // namespace nkentseu