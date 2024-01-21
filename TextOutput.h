
#pragma once
#include "ECS.h"
#include "SDL_ttf.h"
#include "Components.h"

static int d = 4;
template <typename T>
class TextOutput : public Component{
public:
    
    //t = this->entity;
    void Write(std::string message, int x, int y, int size, int r = 202, int g = 69, int b = 255)
    {
        int width, heigth;

        TTF_Font* Sans = TTF_OpenFont("assets/bitcell_memesbruh03.ttf", size);
        SDL_Color White = { (Uint8)r, (Uint8)g, (Uint8)b };
        SDL_Surface* surfaceMessage = TTF_RenderUTF8_Solid(Sans, message.c_str(), White);
        SDL_Texture* Message = SDL_CreateTextureFromSurface(m_Renderer, surfaceMessage);
        SDL_QueryTexture(Message, NULL, NULL, &width, &heigth);
        SDL_Rect Message_rect = { x,y,width,heigth };
        SDL_RenderCopy(m_Renderer, Message, NULL, &Message_rect);
        SDL_DestroyTexture(Message);
        SDL_FreeSurface(surfaceMessage);
        TTF_CloseFont(Sans);

    }
    std::string Read(int x, int y, std::string& in) {
        
        SDL_StartTextInput();
        bool running = true;
        t->Render();
        while (running) {
            SDL_Event ev;
            while (SDL_PollEvent(&ev)) {
                if (ev.type == SDL_TEXTINPUT)
                {
                    char* a = ev.text.text;
                    if (*a < 0 && d < 7)
                    {
                        in += ev.text.text;
                        d++;
                    }
                }
                else if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE && in.size()) {
                    if (in.length() == 1)
                        in.pop_back(); // Удаление последнего символа из строки ввода
                    else
                    {
                        d--;
                        in.pop_back(); // Удаление последнего символа из строки ввода
                        in.pop_back();
                        t->Render();
                    }
                    if (ev.type == SDL_MOUSEBUTTONDOWN)
                    {
                        switch (ev.button.button)
                        {
                        case SDL_BUTTON_LEFT:
                            ;
                            break;
                        case SDL_BUTTON_RIGHT:
                            ;
                            break;
                        }
                        break;
                    }
                    if (ev.type == SDL_MOUSEBUTTONUP)
                    {
                        switch (ev.button.button)
                        {
                        case SDL_BUTTON_LEFT:
                            ;
                            break;
                        case SDL_BUTTON_RIGHT:
                            ;
                            break;
                        }
                        break;
                    }
                }
                else if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_RETURN && in.size()) {
                    SDL_Event events[100];
                    SDL_PeepEvents(events, 100, SDL_GETEVENT, -1, 100);
                    running = false;

                }
                Write(in, x, y, 60);
                SDL_RenderPresent(m_Renderer);
            }
        }
        return in;
    }
    TextOutput(T *t) {
        if (TTF_Init())
            SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        this->t = t;
        m_Window = t->GetWindow();
        m_Renderer = t->GetRenderer();
    }
private:
    T* t;
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    static TextOutput* s_Instance;
};





