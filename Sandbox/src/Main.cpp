#include <Unkeny2D/Window/Window.h>
#include <Unkeny2D/Events/EventManager.h>
#include <Nkentseu/Sleep.h>
#include <Nkentseu/Config/Platform.h>
#include <Nkentseu/Config/Compiler.h>
#include <Nkentseu/Config/Architecture.h>
#include <Unkeny2D/Unkeny.h>
#include <Logger/Log.h>  // Inclure Defaultlog
#include <Logger/Sinks/ConsoleSink.h>
#include <Logger/Sinks/FileSink.h>
#include <iostream>
#include <cmath>

using namespace nkentseu;
using namespace nkentseu::logger;

/**
 * @brief Fonction principale de l'application
 */
int nkmain(int argc, char* argv[]) {
    // -------------------------------------------------------------------------
    // INITIALISATION DU LOGGING
    // -------------------------------------------------------------------------
    
    // Initialiser le log par défaut avec configuration personnalisée
    NkentseuLogger::Initialize("SandboxApp", "[%Y-%m-%d %H:%M:%S.%e] [%L] [%n] [%s] [%#] [%F] -> %v", LogLevel::Trace);
    
    // OU utiliser l'API fluide pour configurer
    // Defaultlog::Instance()
    //     .Named("SandboxApp")
    //     .Pattern("[%Y-%m-%d %H:%M:%S.%e] [%L] [%n] [%s:%#] %v")
    //     .Level(LogLevel::Debug);
    
    // -------------------------------------------------------------------------
    // LOGGING DE DÉBUT (avec la macro 'log' qui capture file/line/function)
    // -------------------------------------------------------------------------
    
    logs.Info("======================================");
    logs.Info("  Unkeny2D - Cross-Platform Window");
    logs.Info("  Platform: %s", GetPlatformName());
    logs.Info("  Architecture: %s", GetArchitectureName());
    logs.Info("  Compiler: %s", GetCompilerName());
    logs.Info("======================================");
    
    // -------------------------------------------------------------------------
    // CRÉATION DE LA FENÊTRE
    // -------------------------------------------------------------------------
    
    logs.Debug("Creating window...");
    Window* window = Window::Create("Unkeny2D Demo", 1280, 720);
    
    if (!window || !window->Initialize()) {
        logs.Error("Failed to create window");
        logs.Critical("Application initialization failed");
        return 1;
    }
    
    window->Show();
    logs.Info("Window created successfully (ID: %u)", window->GetID());
    
    // -------------------------------------------------------------------------
    // VARIABLES DE BOUCLE PRINCIPALE
    // -------------------------------------------------------------------------
    
    bool running = true;
    uint64 frameCount = 0;
    float clearColorR = 0.2f;
    
    // -------------------------------------------------------------------------
    // BOUCLE PRINCIPALE
    // -------------------------------------------------------------------------
    
    logs.Info("Entering main loop...");
    
    while (running) {
        // ---------------------------------------------------------------------
        // TRAITEMENT DES ÉVÉNEMENTS
        // ---------------------------------------------------------------------
        
        while (auto event = EventManager::PollEvent()) {
            if (const auto* closed = event->GetIf<WindowClosedEvent>()) {
                if (closed->GetWindowID() == window->GetID()) {
                    logs.Info("Window closed event received");
                    running = false;
                }
            }
            
            if (const auto* keyPressed = event->GetIf<KeyPressedEvent>()) {
                if (keyPressed->GetKeyCode() == KeyCode::Escape) {
                    logs.Warn("Escape key pressed - hiding window");
                    window->Hide();
                } else if (keyPressed->GetKeyCode() == KeyCode::F1) {
                    logs.Trace("F1 pressed - toggling trace logging");
                    // Changer le niveau de log
                    logs.Level(logs.GetLevel() == LogLevel::Trace ? 
                        LogLevel::Info : LogLevel::Trace
                    );
                }
            }
            
            else if (const auto* resized = event->GetIf<WindowResizedEvent>()) {
                logs.Info("Window resized to %ux%u", 
                          resized->GetWidth(), resized->GetHeight());
            }
            
            else if (const auto* mouseMoved = event->GetIf<MouseMovedEvent>()) {
                logs.Trace("Mouse moved to (%.1f, %.1f)", 
                           mouseMoved->GetX(), mouseMoved->GetY());
            }
        }
        
        // ---------------------------------------------------------------------
        // MISE À JOUR
        // ---------------------------------------------------------------------
        
        frameCount++;
        
        // Animation simple de couleur
        clearColorR = 0.2f + 0.1f * std::sin(static_cast<float>(frameCount) * 0.01f);
        
        if (frameCount % 100 == 0) {
            // logs.Debug("Frame %llu, color R: %.3f", frameCount, clearColorR);
        }
        
        // ---------------------------------------------------------------------
        // RENDU
        // ---------------------------------------------------------------------
        
        Color clearColor(clearColorR, 0.3f, 0.4f, 1.0f);
        window->Clear(clearColor);
        window->SwapBuffers();
        
        // ---------------------------------------------------------------------
        // PAUSE
        // ---------------------------------------------------------------------
        
        SleepMilli(1);
    }
    
    // -------------------------------------------------------------------------
    // FINALISATION
    // -------------------------------------------------------------------------
    
    logs.Info("Exiting main loop");
    logs.Info("Total frames rendered: %llu", frameCount);
    
    delete window;
    
    logs.Info("Application shutdown complete");
    logs.Info("======================================");
    
    // Flush final des logs
    logs.Flush();
    
    return 0;
}