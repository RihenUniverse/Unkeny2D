// -----------------------------------------------------------------------------
// FICHIER: Core/Unkeny2D/src/Unkeny2D/Events/Event.h
// DESCRIPTION: Système complet d'événements avec hiérarchie de classes.
//              Définit tous les types d'événements supportés (fenêtre,
//              clavier, souris, tactile).
// AUTEUR: Rihen
// DATE: 2026
// -----------------------------------------------------------------------------

#pragma once

#include "Nkentseu/Config/Export.h"
#include "Nkentseu/Types.h"
#include <type_traits>
#include <functional>

// -----------------------------------------------------------------------------
// NAMESPACE: nkentseu
// -----------------------------------------------------------------------------
namespace nkentseu {

    // -------------------------------------------------------------------------
    // ÉNUMÉRATION: EventType
    // DESCRIPTION: Identifiants de tous les types d'événements supportés
    // -------------------------------------------------------------------------
    enum class EventType {
        None = 0,
        WindowClosed, WindowResized, WindowFocused, WindowUnfocused,
        KeyPressed, KeyReleased,
        MouseMoved, MouseButtonPressed, MouseButtonReleased, MouseScrolled,
        TouchBegan, TouchMoved, TouchEnded
    };

    // -------------------------------------------------------------------------
    // ÉNUMÉRATION: KeyCode
    // DESCRIPTION: Codes des touches du clavier supportées
    // -------------------------------------------------------------------------
    enum class KeyCode {
        Unknown = 0,
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
        Escape, Enter, Tab, Backspace, Delete, Space,
        Left, Right, Up, Down
    };

    // -------------------------------------------------------------------------
    // ÉNUMÉRATION: MouseButton
    // DESCRIPTION: Boutons de souris supportés
    // -------------------------------------------------------------------------
    enum class MouseButton { Left = 0, Right, Middle };

    // -------------------------------------------------------------------------
    // CLASSE: Event
    // DESCRIPTION: Classe de base abstraite pour tous les événements du système
    // -------------------------------------------------------------------------
    class NK_API Event {
        public:
            /**
             * @brief Constructeur d'événement
             * @param type Type de l'événement
             * @param windowID Identifiant de la fenêtre associée (optionnel)
             */
            Event(EventType type, uint32 windowID = 0) 
                : m_Type(type), m_WindowID(windowID), m_Handled(false) {}
            
            virtual ~Event() = default;
            
            /**
             * @brief Obtient le type de l'événement
             * @return Type de l'événement
             */
            EventType GetType() const { return m_Type; }
            
            /**
             * @brief Obtient l'identifiant de la fenêtre associée
             * @return Identifiant de fenêtre
             */
            uint32 GetWindowID() const { return m_WindowID; }
            
            /**
             * @brief Vérifie si l'événement a été traité
             * @return true si traité, false sinon
             */
            bool IsHandled() const { return m_Handled; }
            
            /**
             * @brief Marque l'événement comme traité
             * @param h État de traitement (true par défaut)
             */
            void SetHandled(bool h = true) { m_Handled = h; }
            
            /**
             * @brief Vérifie si l'événement est d'un type spécifique
             * @tparam T Type d'événement à vérifier
             * @return true si l'événement est du type T, false sinon
             */
            template<typename T>
            bool IsType() const { return m_Type == T::GetStaticType(); }
            
            /**
             * @brief Conversion sécurisée vers un type d'événement spécifique
             * @tparam T Type d'événement cible
             * @return Référence à l'événement converti
             */
            template<typename T>
            T& As() { return *static_cast<T*>(this); }
            
            /**
             * @brief Conversion sécurisée vers un type d'événement spécifique (const)
             * @tparam T Type d'événement cible
             * @return Référence constante à l'événement converti
             */
            template<typename T>
            const T& As() const { return *static_cast<const T*>(this); }
            
            /**
             * @brief Obtient un pointeur vers l'événement s'il est du type spécifié
             * @tparam T Type d'événement cible
             * @return Pointeur vers l'événement ou nullptr si type incorrect
             */
            template<typename T>
            const T* GetIf() const {
                if (IsType<T>()) {
                    return &As<T>();
                }
                return nullptr;
            }
            
            /**
             * @brief Obtient un pointeur vers l'événement s'il est du type spécifié
             * @tparam T Type d'événement cible
             * @return Pointeur vers l'événement ou nullptr si type incorrect
             */
            template<typename T>
            T* GetIf() {
                if (IsType<T>()) {
                    return &As<T>();
                }
                return nullptr;
            }

        protected:
            /// Type de l'événement
            EventType m_Type;
            
            /// Identifiant de la fenêtre associée
            uint32 m_WindowID;
            
            /// Indicateur de traitement
            bool m_Handled;
    };

    // -------------------------------------------------------------------------
    // ÉVÉNEMENTS DE FENÊTRE
    // -------------------------------------------------------------------------

    /// Événement de fermeture de fenêtre
    class NK_API WindowClosedEvent : public Event {
        public:
            /**
             * @brief Constructeur d'événement de fermeture de fenêtre
             * @param id Identifiant de la fenêtre fermée
             */
            WindowClosedEvent(uint32 id) : Event(EventType::WindowClosed, id) {}
            
            /**
             * @brief Obtient le type statique de l'événement
             * @return Type d'événement WindowClosed
             */
            static EventType GetStaticType() { return EventType::WindowClosed; }
    };

    /// Événement de redimensionnement de fenêtre
    class NK_API WindowResizedEvent : public Event {
        public:
            /**
             * @brief Constructeur d'événement de redimensionnement de fenêtre
             * @param id Identifiant de la fenêtre
             * @param w Nouvelle largeur
             * @param h Nouvelle hauteur
             */
            WindowResizedEvent(uint32 id, uint32 w, uint32 h)
                : Event(EventType::WindowResized, id), width(w), height(h) {}
            
            /**
             * @brief Obtient la nouvelle largeur de la fenêtre
             * @return Largeur en pixels
             */
            uint32 GetWidth() const { return width; }
            
            /**
             * @brief Obtient la nouvelle hauteur de la fenêtre
             * @return Hauteur en pixels
             */
            uint32 GetHeight() const { return height; }
            
            /**
             * @brief Obtient le type statique de l'événement
             * @return Type d'événement WindowResized
             */
            static EventType GetStaticType() { return EventType::WindowResized; }
            
        private:
            /// Nouvelle largeur de la fenêtre
            uint32 width;
            
            /// Nouvelle hauteur de la fenêtre
            uint32 height;
    };

    /// Événement de focus sur une fenêtre
    class NK_API WindowFocusedEvent : public Event {
        public:
            /**
             * @brief Constructeur d'événement de focus de fenêtre
             * @param id Identifiant de la fenêtre ayant reçu le focus
             */
            WindowFocusedEvent(uint32 id) : Event(EventType::WindowFocused, id) {}
            
            /**
             * @brief Obtient le type statique de l'événement
             * @return Type d'événement WindowFocused
             */
            static EventType GetStaticType() { return EventType::WindowFocused; }
    };

    /// Événement de perte de focus d'une fenêtre
    class NK_API WindowUnfocusedEvent : public Event {
        public:
            /**
             * @brief Constructeur d'événement de perte de focus de fenêtre
             * @param id Identifiant de la fenêtre ayant perdu le focus
             */
            WindowUnfocusedEvent(uint32 id) : Event(EventType::WindowUnfocused, id) {}
            
            /**
             * @brief Obtient le type statique de l'événement
             * @return Type d'événement WindowUnfocused
             */
            static EventType GetStaticType() { return EventType::WindowUnfocused; }
    };

    // -------------------------------------------------------------------------
    // ÉVÉNEMENTS CLAVIER
    // -------------------------------------------------------------------------

    /// Événement d'appui sur une touche
    class NK_API KeyPressedEvent : public Event {
        public:
            /**
             * @brief Constructeur d'événement d'appui sur touche
             * @param id Identifiant de la fenêtre
             * @param key Code de la touche appuyée
             * @param repeated Indique si l'appui est une répétition (auto-repeat)
             */
            KeyPressedEvent(uint32 id, KeyCode key, bool repeated = false)
                : Event(EventType::KeyPressed, id), keyCode(key), repeated(repeated) {}
            
            /**
             * @brief Obtient le code de la touche appuyée
             * @return Code de touche
             */
            KeyCode GetKeyCode() const { return keyCode; }
            
            /**
             * @brief Vérifie si l'appui est une répétition automatique
             * @return true si répétition, false sinon
             */
            bool IsRepeated() const { return repeated; }
            
            /**
             * @brief Obtient le type statique de l'événement
             * @return Type d'événement KeyPressed
             */
            static EventType GetStaticType() { return EventType::KeyPressed; }
            
        private:
            /// Code de la touche appuyée
            KeyCode keyCode;
            
            /// Indicateur de répétition automatique
            bool repeated;
    };

    /// Événement de relâchement d'une touche
    class NK_API KeyReleasedEvent : public Event {
        public:
            /**
             * @brief Constructeur d'événement de relâchement de touche
             * @param id Identifiant de la fenêtre
             * @param key Code de la touche relâchée
             */
            KeyReleasedEvent(uint32 id, KeyCode key)
                : Event(EventType::KeyReleased, id), keyCode(key) {}
            
            /**
             * @brief Obtient le code de la touche relâchée
             * @return Code de touche
             */
            KeyCode GetKeyCode() const { return keyCode; }
            
            /**
             * @brief Obtient le type statique de l'événement
             * @return Type d'événement KeyReleased
             */
            static EventType GetStaticType() { return EventType::KeyReleased; }
            
        private:
            /// Code de la touche relâchée
            KeyCode keyCode;
    };

    // -------------------------------------------------------------------------
    // ÉVÉNEMENTS SOURIS
    // -------------------------------------------------------------------------

    /// Événement de mouvement de souris
    class NK_API MouseMovedEvent : public Event {
        public:
            /**
             * @brief Constructeur d'événement de mouvement de souris
             * @param id Identifiant de la fenêtre
             * @param x Position X du curseur
             * @param y Position Y du curseur
             */
            MouseMovedEvent(uint32 id, float x, float y)
                : Event(EventType::MouseMoved, id), posX(x), posY(y) {}
            
            /**
             * @brief Obtient la position X du curseur
             * @return Position X en pixels
             */
            float GetX() const { return posX; }
            
            /**
             * @brief Obtient la position Y du curseur
             * @return Position Y en pixels
             */
            float GetY() const { return posY; }
            
            /**
             * @brief Obtient le type statique de l'événement
             * @return Type d'événement MouseMoved
             */
            static EventType GetStaticType() { return EventType::MouseMoved; }
            
        private:
            /// Position X du curseur
            float posX;
            
            /// Position Y du curseur
            float posY;
    };

    /// Événement d'appui sur un bouton de souris
    class NK_API MouseButtonPressedEvent : public Event {
        public:
            /**
             * @brief Constructeur d'événement d'appui sur bouton de souris
             * @param id Identifiant de la fenêtre
             * @param button Bouton de souris appuyé
             * @param x Position X du curseur
             * @param y Position Y du curseur
             */
            MouseButtonPressedEvent(uint32 id, MouseButton button, float x, float y)
                : Event(EventType::MouseButtonPressed, id), button(button), posX(x), posY(y) {}
            
            /**
             * @brief Obtient le bouton de souris appuyé
             * @return Bouton de souris
             */
            MouseButton GetButton() const { return button; }
            
            /**
             * @brief Obtient la position X du curseur
             * @return Position X en pixels
             */
            float GetX() const { return posX; }
            
            /**
             * @brief Obtient la position Y du curseur
             * @return Position Y en pixels
             */
            float GetY() const { return posY; }
            
            /**
             * @brief Obtient le type statique de l'événement
             * @return Type d'événement MouseButtonPressed
             */
            static EventType GetStaticType() { return EventType::MouseButtonPressed; }
            
        private:
            /// Bouton de souris appuyé
            MouseButton button;
            
            /// Position X du curseur
            float posX;
            
            /// Position Y du curseur
            float posY;
    };

    /// Événement de relâchement d'un bouton de souris
    class NK_API MouseButtonReleasedEvent : public Event {
        public:
            /**
             * @brief Constructeur d'événement de relâchement de bouton de souris
             * @param id Identifiant de la fenêtre
             * @param button Bouton de souris relâché
             * @param x Position X du curseur
             * @param y Position Y du curseur
             */
            MouseButtonReleasedEvent(uint32 id, MouseButton button, float x, float y)
                : Event(EventType::MouseButtonReleased, id), button(button), posX(x), posY(y) {}
            
            /**
             * @brief Obtient le bouton de souris relâché
             * @return Bouton de souris
             */
            MouseButton GetButton() const { return button; }
            
            /**
             * @brief Obtient la position X du curseur
             * @return Position X en pixels
             */
            float GetX() const { return posX; }
            
            /**
             * @brief Obtient la position Y du curseur
             * @return Position Y en pixels
             */
            float GetY() const { return posY; }
            
            /**
             * @brief Obtient le type statique de l'événement
             * @return Type d'événement MouseButtonReleased
             */
            static EventType GetStaticType() { return EventType::MouseButtonReleased; }
            
        private:
            /// Bouton de souris relâché
            MouseButton button;
            
            /// Position X du curseur
            float posX;
            
            /// Position Y du curseur
            float posY;
    };

    /// Événement de défilement de molette de souris
    class NK_API MouseScrolledEvent : public Event {
        public:
            /**
             * @brief Constructeur d'événement de défilement de molette
             * @param id Identifiant de la fenêtre
             * @param deltaX Déplacement horizontal de la molette
             * @param deltaY Déplacement vertical de la molette
             */
            MouseScrolledEvent(uint32 id, float deltaX, float deltaY)
                : Event(EventType::MouseScrolled, id), deltaX(deltaX), deltaY(deltaY) {}
            
            /**
             * @brief Obtient le déplacement horizontal de la molette
             * @return Delta X
             */
            float GetDeltaX() const { return deltaX; }
            
            /**
             * @brief Obtient le déplacement vertical de la molette
             * @return Delta Y
             */
            float GetDeltaY() const { return deltaY; }
            
            /**
             * @brief Obtient le type statique de l'événement
             * @return Type d'événement MouseScrolled
             */
            static EventType GetStaticType() { return EventType::MouseScrolled; }
            
        private:
            /// Déplacement horizontal de la molette
            float deltaX;
            
            /// Déplacement vertical de la molette
            float deltaY;
    };

    // -------------------------------------------------------------------------
    // ÉVÉNEMENTS TACTILES
    // -------------------------------------------------------------------------

    /// Événement de début de contact tactile
    class NK_API TouchBeganEvent : public Event {
        public:
            /**
             * @brief Constructeur d'événement de début de contact tactile
             * @param id Identifiant de la fenêtre
             * @param tid Identifiant unique du contact tactile
             * @param x Position X du contact
             * @param y Position Y du contact
             */
            TouchBeganEvent(uint32 id, int32 tid, float x, float y)
                : Event(EventType::TouchBegan, id), touchID(tid), posX(x), posY(y) {}
            
            /**
             * @brief Obtient l'identifiant unique du contact tactile
             * @return Identifiant de contact
             */
            int32 GetTouchID() const { return touchID; }
            
            /**
             * @brief Obtient la position X du contact
             * @return Position X en pixels
             */
            float GetX() const { return posX; }
            
            /**
             * @brief Obtient la position Y du contact
             * @return Position Y en pixels
             */
            float GetY() const { return posY; }
            
            /**
             * @brief Obtient le type statique de l'événement
             * @return Type d'événement TouchBegan
             */
            static EventType GetStaticType() { return EventType::TouchBegan; }
            
        private:
            /// Identifiant unique du contact tactile
            int32 touchID;
            
            /// Position X du contact
            float posX;
            
            /// Position Y du contact
            float posY;
    };

    /// Événement de mouvement de contact tactile
    class NK_API TouchMovedEvent : public Event {
        public:
            /**
             * @brief Constructeur d'événement de mouvement de contact tactile
             * @param id Identifiant de la fenêtre
             * @param tid Identifiant unique du contact tactile
             * @param x Position X du contact
             * @param y Position Y du contact
             */
            TouchMovedEvent(uint32 id, int32 tid, float x, float y)
                : Event(EventType::TouchMoved, id), touchID(tid), posX(x), posY(y) {}
            
            /**
             * @brief Obtient l'identifiant unique du contact tactile
             * @return Identifiant de contact
             */
            int32 GetTouchID() const { return touchID; }
            
            /**
             * @brief Obtient la position X du contact
             * @return Position X en pixels
             */
            float GetX() const { return posX; }
            
            /**
             * @brief Obtient la position Y du contact
             * @return Position Y en pixels
             */
            float GetY() const { return posY; }
            
            /**
             * @brief Obtient le type statique de l'événement
             * @return Type d'événement TouchMoved
             */
            static EventType GetStaticType() { return EventType::TouchMoved; }
            
        private:
            /// Identifiant unique du contact tactile
            int32 touchID;
            
            /// Position X du contact
            float posX;
            
            /// Position Y du contact
            float posY;
    };

    /// Événement de fin de contact tactile
    class NK_API TouchEndedEvent : public Event {
        public:
            /**
             * @brief Constructeur d'événement de fin de contact tactile
             * @param id Identifiant de la fenêtre
             * @param tid Identifiant unique du contact tactile
             * @param x Position X du contact
             * @param y Position Y du contact
             */
            TouchEndedEvent(uint32 id, int32 tid, float x, float y)
                : Event(EventType::TouchEnded, id), touchID(tid), posX(x), posY(y) {}
            
            /**
             * @brief Obtient l'identifiant unique du contact tactile
             * @return Identifiant de contact
             */
            int32 GetTouchID() const { return touchID; }
            
            /**
             * @brief Obtient la position X du contact
             * @return Position X en pixels
             */
            float GetX() const { return posX; }
            
            /**
             * @brief Obtient la position Y du contact
             * @return Position Y en pixels
             */
            float GetY() const { return posY; }
            
            /**
             * @brief Obtient le type statique de l'événement
             * @return Type d'événement TouchEnded
             */
            static EventType GetStaticType() { return EventType::TouchEnded; }
            
        private:
            /// Identifiant unique du contact tactile
            int32 touchID;
            
            /// Position X du contact
            float posX;
            
            /// Position Y du contact
            float posY;
    };

    // -------------------------------------------------------------------------
    // ALIAS DE TYPE POUR LES CALLBACKS D'ÉVÉNEMENTS
    // -------------------------------------------------------------------------
    
    /**
     * @brief Type de callback pour les événements
     * @tparam EventType Type d'événement spécifique
     */
    template<typename EventType>
    using EventCallback = std::function<void(const EventType&)>;

} // namespace nkentseu