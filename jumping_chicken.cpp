#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <cstdlib>
#include <ctime>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int CHICKEN_WIDTH = 64;
const int CHICKEN_HEIGHT = 64;
const int EGG_WIDTH = 32;
const int EGG_HEIGHT = 32;
const int JUMP_HEIGHT = 150;
const int GROUND_Y = SCREEN_HEIGHT / 2;

// Struktur, um die Position eines Eis zu speichern
struct Egg {
    int x, y;
};

// Lade ein PNG-Bild und wandle es in eine Textur um
SDL_Texture* LoadTexture(const char* path, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        printf("Failed to load image: %s, SDL_image Error: %s\n", path, IMG_GetError());
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void RenderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int w, int h) {
    SDL_Rect destRect = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}

int main(int argc, char* args[]) {
    // SDL und SDL_Image initialisieren
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    srand(static_cast<unsigned int>(time(nullptr)));

    SDL_Window* window = SDL_CreateWindow("Jumping Chicken", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Lade die PNG-Bilder für das Huhn und das Ei
    SDL_Texture* chickenTexture = LoadTexture("chicken.png", renderer);
    SDL_Texture* eggTexture = LoadTexture("egg.png", renderer);

    if (!chickenTexture || !eggTexture) {
        // Falls die Texturen nicht geladen werden konnten, Programm beenden
        printf("Failed to load textures.\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    SDL_Event event;

    int chickenX = (SCREEN_WIDTH - CHICKEN_WIDTH) / 2;
    int chickenY = GROUND_Y;

    bool isJumping = false;
    int jumpOffset = 0;
    int jumpDirection = -1;

    // Vektor, der alle Eier speichert
    std::vector<Egg> eggs;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE && !isJumping) {
                isJumping = true;

                // Füge ein neues Ei an einer zufälligen Position hinzu
                Egg newEgg = {rand() % (SCREEN_WIDTH - EGG_WIDTH), rand() % (SCREEN_HEIGHT - EGG_HEIGHT)};
                eggs.push_back(newEgg);
            }
        }

        if (isJumping) {
            jumpOffset += jumpDirection * 10;
            if (jumpOffset <= -JUMP_HEIGHT || jumpOffset >= 0) {
                jumpDirection *= -1;
            }
            if (jumpOffset == 0) {
                isJumping = false;
            }
        }

        // Bildschirm leeren
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // Huhn rendern
        RenderTexture(chickenTexture, renderer, chickenX, chickenY + jumpOffset, CHICKEN_WIDTH, CHICKEN_HEIGHT);

        // Alle Eier rendern
        for (const Egg& egg : eggs) {
            RenderTexture(eggTexture, renderer, egg.x, egg.y, EGG_WIDTH, EGG_HEIGHT);
        }

        // Aktualisieren des Bildschirms
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ca. 60 FPS
    }

    // Speicher freigeben
    SDL_DestroyTexture(chickenTexture);
    SDL_DestroyTexture(eggTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // SDL_Image und SDL beenden
    IMG_Quit();
    SDL_Quit();

    return 0;
}
