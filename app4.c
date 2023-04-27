#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include"ap.h"

#define MAX_QUESTIONS 3
#define MAX_ANSWERS 3

/*typedef struct {
    char question[100];
    char answers[MAX_ANSWERS][50];
    int correct_answer;
} Riddle;*/

/*void render_text(SDL_Surface *screen, TTF_Font *font, char *text, int x, int y, SDL_Color color) {
    SDL_Surface *text_surface;
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    text_surface = TTF_RenderText_Solid(font, text, color);
    SDL_BlitSurface(text_surface, NULL, screen, &rect);
    SDL_FreeSurface(text_surface);
}









void animate(SDL_Surface *screen) {
    SDL_Surface *image1, *image2, *image3;
    image1 = SDL_LoadBMP("frame0.bmp");
    image2 = SDL_LoadBMP("frame1.bmp");
    image3 = SDL_LoadBMP("frame2.bmp");
    SDL_Rect rect;
    rect.x = 300;
    rect.y = 300;
    SDL_BlitSurface(image1, NULL, screen, &rect);
    SDL_Flip(screen);
    SDL_Delay(80);
    SDL_BlitSurface(image2, NULL, screen, &rect);
    SDL_Flip(screen);
    SDL_Delay(80);
    SDL_BlitSurface(image3, NULL, screen, &rect);
    SDL_Flip(screen);
    SDL_BlitSurface(image1, NULL, screen, &rect);
    SDL_Flip(screen);
    SDL_Delay(80);
    SDL_BlitSurface(image2, NULL, screen, &rect);
    SDL_Flip(screen);
    SDL_Delay(80);
    SDL_BlitSurface(image3, NULL, screen, &rect);
    SDL_Flip(screen);
    SDL_Delay(80);
    SDL_BlitSurface(image1, NULL, screen, &rect);
    SDL_Flip(screen);
    SDL_Delay(80);
    SDL_BlitSurface(image2, NULL, screen, &rect);
    SDL_Flip(screen);
    SDL_Delay(80);
    SDL_BlitSurface(image3, NULL, screen, &rect);
    SDL_Flip(screen);
    SDL_BlitSurface(image1, NULL, screen, &rect);
    SDL_Flip(screen);
    SDL_Delay(80);
    SDL_BlitSurface(image2, NULL, screen, &rect);
    SDL_Flip(screen);
    SDL_Delay(80);
    SDL_BlitSurface(image3, NULL, screen, &rect);
    SDL_Flip(screen);
    SDL_FreeSurface(image1);
    SDL_FreeSurface(image2);
    SDL_FreeSurface(image3);
}
*/







int main() {
    SDL_Surface *screen;
    TTF_Font *font;
    SDL_Event event;
    int running = 1;
    int current_question = 0;
    char line[150];
    FILE *file;
    Riddle riddles[MAX_QUESTIONS];
    int i, j;
    int selected_answer = -1;
    int correct_answers = 0;
    SDL_Color text_color = {255, 255, 255};
    SDL_Color selected_color = {255, 0, 0};
    SDL_Color correct_color = {0, 255, 0};
    SDL_Color incorrect_color = {255, 0, 0};
    
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
    // Set up the screen and font
    screen = SDL_SetVideoMode(840, 600, 32, SDL_SWSURFACE);
    font = TTF_OpenFont("font/Ani.ttf", 24);
    
    // Load the riddles from the text file
    file = fopen("riddles.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    for (i = 0; i < MAX_QUESTIONS; i++) {
        fgets(line, sizeof(line), file);
        strcpy(riddles[i].question, line);
        for (j = 0; j < MAX_ANSWERS; j++) {
            fgets(line, sizeof(line), file);
            strcpy(riddles[i].answers[j], line);
        }
        fgets(line, sizeof(line), file);
        riddles[i].correct_answer = atoi(line);
    }
    fclose(file);

    
    // Loop until the user quits
    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_a:
                            selected_answer = 0;
                            animate(screen);

                            break;
                        case SDLK_b:
                            selected_answer = 1;
                            animate(screen);

                            break;
                        case SDLK_c:
                            selected_answer = 2;
                            animate(screen);
                            break;
                        case SDLK_RETURN:
                            if (selected_answer == riddles[current_question].correct_answer) {
                                correct_answers++;
                                animate(screen);
                            }
                            current_question++;
                            selected_answer = -1;
                            break;
                    }
                    break;
            }
        }
        
        // Clear the screen
        SDL_FillRect(screen, NULL, 0);
        
        // Render the current question and answers
       render_text(screen, font, riddles[current_question].question, 50, 50, text_color);
       
             for (i = 0; i < MAX_ANSWERS; i++) {
            if (selected_answer == i) {
                render_text(screen, font, riddles[current_question].answers[i], 50, 150 + i * 50, selected_color);
            } else if (selected_answer != -1 && i == riddles[current_question].correct_answer) {
                render_text(screen, font, riddles[current_question].answers[i], 50, 150 + i * 50, correct_color);
            } else {
                render_text(screen, font, riddles[current_question].answers[i], 50, 150 + i * 50, text_color);
            }
        }
        
        // Render the score
        char score_text[50];
        sprintf(score_text, "Score: %d / %d", correct_answers, MAX_QUESTIONS);
        render_text(screen, font, score_text, 50, 400, text_color);
        
        // Update the screen
        SDL_Flip(screen);
        
        // End the game if all questions have been answered
        if (current_question == MAX_QUESTIONS) {
            running = 0;
        }
    }
    
    // Clean up
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    
    return 0;
}
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
