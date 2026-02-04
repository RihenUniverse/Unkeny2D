# 🎮 Unkeny2D Framework

## Vue d'ensemble

Unkeny2D est un framework C++ moderne et multiplateforme pour le développement de jeux et d'applications graphiques 2D/3D. Conçu avec une architecture modulaire et extensible, il fournit une base solide pour créer des applications performantes sur Windows, Linux, macOS, Android, iOS et le Web (via Emscripten).

## 🏗️ Architecture du Système

Le framework est organisé en plusieurs bibliothèques indépendantes et réutilisables :

```
┌─────────────────────────────────────────────────────────────┐
│                        Sandbox                               │
│              (Application d'exemple/test)                    │
└──────────────────────┬──────────────────────────────────────┘
                       │
┌──────────────────────▼──────────────────────────────────────┐
│                      Unkeny2D                                │
│          (Moteur principal - Window, Events)                 │
└──────────────────────┬──────────────────────────────────────┘
                       │
        ┌──────────────┼──────────────┐
        │              │               │
┌───────▼──────┐ ┌────▼─────┐ ┌──────▼──────┐
│    Logger    │ │ Nkentseu │ │   MathLib   │
│   (Logging)  │ │  (Core)  │ │   (Math)    │
└──────────────┘ └──────────┘ └─────────────┘
```

### 📦 Composants Principaux

#### 1. **Nkentseu** (Bibliothèque Core)
La bibliothèque de base fournissant les types et utilitaires fondamentaux :

- **Types.h** : Types entiers portables (int8, uint32, float64, etc.)
- **Platform.h** : Détection de plateforme (Windows, Linux, macOS, etc.)
- **Export.h** : Macros d'export pour DLL/SO
- **Architecture.h** : Détection d'architecture (x86, x64, ARM, etc.)
- **Compiler.h** : Détection de compilateur (MSVC, GCC, Clang)
- **Sleep.h/cpp** : Fonctions de pause multiplateforme

**Namespace :** `nkentseu`

#### 2. **Logger** (Système de Logging)
Système de journalisation robuste et performant :

##### Features principales :
- ✅ Multiples niveaux de log (TRACE, DEBUG, INFO, WARN, ERROR, FATAL)
- ✅ Formatage personnalisable des messages
- ✅ Sinks multiples (Console, Fichier, Rotating, Daily, etc.)
- ✅ Thread-safe et asynchrone
- ✅ Macros pratiques (LOG_INFO, LOG_ERROR, etc.)
- ✅ Registry globale pour gérer plusieurs loggers

##### Sinks disponibles :
- **ConsoleSink** : Sortie vers stdout/stderr avec couleurs
- **FileSink** : Écriture dans un fichier
- **RotatingFileSink** : Rotation automatique basée sur la taille
- **DailyFileSink** : Rotation quotidienne
- **DistributingSink** : Distribution vers plusieurs sinks
- **AsyncSink** : Logging asynchrone avec file d'attente
- **NullSink** : Sink no-op pour désactiver le logging

##### Exemple d'utilisation :
```cpp
#include <Logger/Logger.h>

using namespace nkentseu::logger;

int main() {
    // Créer un logger avec sink console
    auto logger = std::make_shared<Logger>("App");
    logger->AddSink(std::make_shared<ConsoleSink>());
    
    // Enregistrer dans la registry globale
    LoggerRegistry::Register("App", logger);
    
    // Utiliser les macros
    LOG_INFO("Application démarrée");
    LOG_ERROR("Une erreur s'est produite");
    
    return 0;
}
```

#### 3. **Unkeny2D** (Système de Fenêtrage et Événements)
Le cœur du moteur fournissant la gestion des fenêtres et des événements :

##### Système de Fenêtrage (Window)
API unifiée et multiplateforme pour créer et gérer des fenêtres :

```cpp
#include <Unkeny2D/Window.h>

using namespace nkentseu::unkeny2d;

// Créer une fenêtre
WindowSettings settings;
settings.title = "Ma Fenêtre";
settings.width = 1280;
settings.height = 720;
settings.vsync = true;

auto window = Window::Create(settings);

// Boucle principale
while (window->IsOpen()) {
    window->PollEvents();
    
    // Rendu ici...
    
    window->Display();
}
```

##### Implémentations Plateforme :
- **Win32Window** : Windows natif (Win32 API)
- **XCBWindow** : Linux (XCB/X11)
- **AndroidWindow** : Android (ANativeWindow)
- **EmscriptenWindow** : Web (HTML5 Canvas)
- **IOSWindow** : iOS (UIKit) - En développement
- **MacOSWindow** : macOS (Cocoa) - En développement

##### Système d'Événements (EventManager)
Gestion centralisée des événements avec pattern observer :

**Types d'événements supportés :**
- Fenêtre : Close, Resize, Focus, Blur, Move
- Clavier : KeyPress, KeyRelease, KeyRepeat
- Souris : MouseMove, MouseButton, MouseWheel
- Touch : TouchBegin, TouchMove, TouchEnd (mobile)

```cpp
#include <Unkeny2D/EventManager.h>

using namespace nkentseu::unkeny2d;

auto& eventMgr = EventManager::Instance();

// S'abonner aux événements
eventMgr.Subscribe(EventType::WindowClose, [](const Event& e) {
    std::cout << "Fenêtre fermée!" << std::endl;
});

eventMgr.Subscribe(EventType::KeyPress, [](const Event& e) {
    auto& keyEvent = static_cast<const KeyEvent&>(e);
    std::cout << "Touche pressée : " << keyEvent.key << std::endl;
});
```

#### 4. **MathLib** (Bibliothèque Mathématique)
Bibliothèque mathématique complète pour les graphiques 2D/3D :

##### Classes disponibles :
- **Vector2<T>** : Vecteur 2D avec toutes les opérations
- **Vector3<T>** : Vecteur 3D avec produit vectoriel
- **Matrix4x4<T>** : Matrice 4x4 pour transformations 3D

##### Alias de types :
```cpp
using Vec2 = Vector2<float>;
using Vec3 = Vector3<float>;
using Mat4 = Matrix4x4<float>;
```

##### Exemple d'utilisation :
```cpp
#include <Math/Vector3.h>
#include <Math/Matrix4x4.h>

using namespace nkentseu::math;

// Vecteurs
Vec3 position(1.0f, 2.0f, 3.0f);
Vec3 direction = Vec3::Forward;
float distance = position.Distance(Vec3::Zero);

// Transformations
Mat4 translation = Mat4::Translation(10.0f, 0.0f, 0.0f);
Mat4 rotation = Mat4::RotationY(M_PI / 2.0f);
Mat4 scale = Mat4::Scale(2.0f, 2.0f, 2.0f);
Mat4 transform = translation * rotation * scale;

Vec3 transformedPoint = transform * position;
```

#### 5. **Sandbox** (Application de Test)
Application d'exemple démontrant l'utilisation du framework :

```cpp
#include <Unkeny2D/Window.h>
#include <Unkeny2D/EventManager.h>
#include <Logger/Logger.h>

int main() {
    // Initialiser le logger
    auto logger = std::make_shared<nkentseu::logger::Logger>("Sandbox");
    logger->AddSink(std::make_shared<nkentseu::logger::ConsoleSink>());
    nkentseu::logger::LoggerRegistry::Register("Sandbox", logger);
    
    LOG_INFO("Démarrage de Sandbox");
    
    // Créer la fenêtre
    nkentseu::unkeny2d::WindowSettings settings;
    settings.title = "Unkeny2D Sandbox";
    settings.width = 1280;
    settings.height = 720;
    
    auto window = nkentseu::unkeny2d::Window::Create(settings);
    
    // Configurer les événements
    auto& eventMgr = nkentseu::unkeny2d::EventManager::Instance();
    eventMgr.Subscribe(nkentseu::unkeny2d::EventType::WindowClose, [&](auto& e) {
        window->Close();
    });
    
    // Boucle principale
    while (window->IsOpen()) {
        window->PollEvents();
        
        // Logique de jeu ici...
        
        window->Display();
    }
    
    LOG_INFO("Arrêt de Sandbox");
    return 0;
}
```

## 🔧 Système de Build : Jenga

Le projet utilise **Jenga**, un système de build personnalisé écrit en Lua, similaire à Premake/CMake mais plus flexible.

### Structure des Fichiers Jenga

#### workspace.jenga (Racine)
```lua
workspace "Unkeny2D"
    configurations { "Debug", "Release" }
    platforms { "x64", "x86", "ARM" }
    toolchains { "msvc", "gcc", "clang" }
    
    -- Inclure les projets
    include "Core/Nkentseu"
    include "Core/Logger"
    include "Core/Math"
    include "Unkeny2D"
    include "Sandbox"
```

#### Exemple de Projet (Nkentseu.jenga)
```lua
project "Nkentseu"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    
    targetdir "bin/%{cfg.buildcfg}/%{cfg.platform}"
    objdir "obj/%{cfg.buildcfg}/%{cfg.platform}"
    
    files {
        "src/**.h",
        "src/**.cpp"
    }
    
    includedirs {
        "src"
    }
    
    filter "configurations:Debug"
        defines { "NKENTSEU_DEBUG" }
        symbols "On"
    
    filter "configurations:Release"
        defines { "NKENTSEU_RELEASE" }
        optimize "Speed"
```

### Commandes Jenga

```bash
# Générer les projets
jenga generate

# Compiler
jenga build

# Nettoyer
jenga clean

# Rebuild complet
jenga rebuild

# Spécifier une configuration
jenga build --config=Release --platform=x64 --toolchain=msvc
```

## 🚀 Démarrage Rapide

### 1. Prérequis
- **Compilateur C++17** : MSVC 2019+, GCC 9+, Clang 10+
- **Jenga** : Système de build (fourni)
- **Git** : Pour cloner le dépôt

### 2. Cloner le Projet
```bash
git clone https://github.com/votre-repo/Unkeny2D.git
cd Unkeny2D
```

### 3. Générer et Compiler
```bash
# Générer les fichiers de projet
jenga generate

# Compiler en mode Debug
jenga build --config=Debug

# Compiler en mode Release
jenga build --config=Release
```

### 4. Lancer Sandbox
```bash
# Windows
bin/Debug/x64/Sandbox.exe

# Linux/macOS
./bin/Debug/x64/Sandbox
```

## 📚 Documentation Supplémentaire

- **Logger README** : Voir `Core/Logger/README.md`
- **MathLib README** : Voir `Core/Math/README.md`
- **API Documentation** : Génération Doxygen en cours
- **Exemples** : Dossier `Examples/`

## 🎯 Roadmap

### Version 1.0 (Actuel)
- [x] Système de fenêtrage multiplateforme
- [x] Gestion des événements
- [x] Système de logging robuste
- [x] Bibliothèque mathématique de base
- [ ] Tests unitaires complets
- [ ] Documentation API

### Version 1.1 (Prochaine)
- [ ] Renderer 2D de base
- [ ] Gestion des textures
- [ ] Sprite system
- [ ] Animation 2D
- [ ] Audio system

### Version 2.0 (Future)
- [ ] Renderer 3D (OpenGL/Vulkan)
- [ ] Physics engine integration
- [ ] Scene management
- [ ] Entity Component System (ECS)
- [ ] Scripting (Lua/Python)

## 🤝 Contribution

Les contributions sont les bienvenues ! Pour contribuer :

1. Forkez le projet
2. Créez une branche (`git checkout -b feature/NouvelleFonctionnalité`)
3. Commitez vos changements (`git commit -m 'Ajout de...'`)
4. Pushez vers la branche (`git push origin feature/NouvelleFonctionnalité`)
5. Ouvrez une Pull Request

### Guidelines
- Suivre le style de code existant
- Ajouter des tests unitaires pour les nouvelles fonctionnalités
- Documenter le code avec Doxygen
- Tester sur plusieurs plateformes si possible

## 📄 Licence

Ce projet est sous licence MIT. Voir le fichier `LICENSE` pour plus de détails.

## 👥 Auteurs

- **Rihen** - Développeur principal - [GitHub](https://github.com/rihen)

## 🙏 Remerciements

- Inspiré par SFML, SDL, et d'autres frameworks de jeu
- Merci à tous les contributeurs et testeurs

## 📞 Support

- **Issues** : Utilisez le tracker GitHub
- **Email** : support@unkeny2d.com
- **Discord** : [Serveur Unkeny2D](https://discord.gg/unkeny2d)

---

**Version** : 1.0.0  
**Date** : 2026  
**Copyright** : © 2026 Rihen - Tous droits réservés
