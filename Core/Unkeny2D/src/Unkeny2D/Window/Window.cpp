// -----------------------------------------------------------------------------
// FICHIER: Core/Unkeny2D/src/Unkeny2D/Window/Window.cpp
// DESCRIPTION: Factory pour la création de fenêtres adaptées à la plateforme.
//              Sélectionne automatiquement l'implémentation appropriée.
// AUTEUR: Rihen
// DATE: 2026
// -----------------------------------------------------------------------------

#include "Unkeny2D/Window/Window.h"
#include "Nkentseu/Config/Platform.h"

// -----------------------------------------------------------------------------
// INCLUDES SPÉCIFIQUES À LA PLATEFORME
// -----------------------------------------------------------------------------

#if defined(NK_PLATFORM_WINDOWS)
    #include "Unkeny2D/Platform/Win32/WindowWin32.h"
    
#elif defined(NK_PLATFORM_LINUX)
    #include "Unkeny2D/Platform/Linux/WindowXCB.h"
    
#elif defined(NK_PLATFORM_MACOS)
    #include "Unkeny2D/Platform/macOS/WindowMacOS.h"
    
#elif defined(NK_PLATFORM_ANDROID)
    #include "Unkeny2D/Platform/Android/WindowAndroid.h"
    
#elif defined(NK_PLATFORM_IOS)
    #include "Unkeny2D/Platform/iOS/WindowIOS.h"
    
#elif defined(NK_PLATFORM_EMSCRIPTEN)
    #include "Unkeny2D/Platform/Emscripten/WindowEmscripten.h"
#endif

// -----------------------------------------------------------------------------
// NAMESPACE: nkentseu
// -----------------------------------------------------------------------------
namespace nkentseu {

    // -------------------------------------------------------------------------
    // FONCTION: Window::Create
    // DESCRIPTION: Factory method pour créer une fenêtre adaptée à la plateforme
    // -------------------------------------------------------------------------
    Window* Window::Create(const char* title, uint32 width, uint32 height) {
        #if defined(NK_PLATFORM_WINDOWS)
            return new WindowWin32(title, width, height);
            
        #elif defined(NK_PLATFORM_LINUX)
            return new WindowXCB(title, width, height);
            
        #elif defined(NK_PLATFORM_MACOS)
            return new WindowMacOS(title, width, height);
            
        #elif defined(NK_PLATFORM_ANDROID)
            return new WindowAndroid(title, width, height);
            
        #elif defined(NK_PLATFORM_IOS)
            return new WindowIOS(title, width, height);
            
        #elif defined(NK_PLATFORM_EMSCRIPTEN)
            return new WindowEmscripten(title, width, height);
            
        #else
            #error "Platform not supported"
            return nullptr;
        #endif
    }

} // namespace nkentseu