// Copyright (c) 2023 Federico Polidoro. All Rights Reserved.
#include <raylib.h>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"

#define HELP_EXIT() show_help_message(); return 0

void load_paths(struct linked_node** p, char** str, int cant){
  for (int i = cant-1; i>0; i--) {
    top_push(p,str[i]);
  }
}

void unload_paths(struct linked_node** p, int ind){
  for (int i = ind; i!=0; i--){
    top_pop(p);
  }
}


void show_help_message() {
    printf("     FMP - Fede Music Player\n"
           "//=================================// \n"
           "//  ./music [cancion1][cancion2].. // \n"
           "//=================================// \n\n");
}

int main (int argc, char *argv[]) {

  if (argc<2) { HELP_EXIT(); }
  if (strcmp("-h",argv[1]) == 0) { HELP_EXIT(); }
  if (strcmp("--help",argv[1]) == 0) { HELP_EXIT(); }
  
  int selector = 0;
  bool pause;
  float timePlayed = 0.1f, lastTime = 0.0f;
  
  SetTraceLogLevel(LOG_ERROR);
  InitWindow(400,200,"FMP - Fede Music Player");
  SetTargetFPS(60);


  struct linked_node* path = NULL;

  load_paths(&path, argv, argc);
  int ind = argc;

  //NOTE: this is for debugging
  print_list(path);
  //


  InitAudioDevice();
  Music music = LoadMusicStream(get_value(path, selector));
  PlayMusicStream(music);

    while (!IsKeyReleased(KEY_Q)) {

      timePlayed = GetMusicTimePlayed(music)/GetMusicTimeLength(music);

      //chequea que el tiempo de reproduccion de la musica no sea más larga que la cancion 
      if (timePlayed > 1.0f) {
        timePlayed = 1.0f;
      }

      if (timePlayed < lastTime) {
        if (selector != argc-1) {
          selector++;
        } else {
          selector = 1; 
        }
        lastTime = 0.0f;
        music = LoadMusicStream(get_value(path, selector));
        PlayMusicStream(music);
      }
     
      lastTime = timePlayed;
      UpdateMusicStream(music);

      if (IsKeyReleased(KEY_P)) {
        pause = !pause;
        if (pause == true) {
          PauseMusicStream(music);
        } else {
          ResumeMusicStream(music);
        }
      }
      
      if (IsKeyReleased(KEY_R)) {
        StopMusicStream(music);
        PlayMusicStream(music);
        lastTime = 0.0f;
      }

      if (IsKeyReleased(KEY_LEFT)) {
        if(selector > 0){
          --selector;
          lastTime = 0.0f;
          music = LoadMusicStream(get_value(path, selector));
          PlayMusicStream(music);
        }
      }

      if (IsKeyReleased(KEY_RIGHT)) {
        if(selector < ind-1){
          ++selector;
          lastTime = 0.0f;
          music = LoadMusicStream(get_value(path, selector));
          PlayMusicStream(music);
        }
      }
     
      if (IsFileDropped()) {
        FilePathList droppedFiles = LoadDroppedFiles();

        end_push(&path, droppedFiles.paths[0]);
        selector = ++ind;
        music = LoadMusicStream(get_value(path, selector));
        PlayMusicStream(music);
        
        UnloadDroppedFiles(droppedFiles);
      }

      BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("q = salir\np = pause/resume\nr = reset song\n<-/-> = change song", 20, 48, 20, DARKPURPLE);
        DrawText(get_value(path, selector), 20, 180, 8, BLUE);
        DrawRectangle(20, 20, 360, 12, LIGHTGRAY);
        DrawRectangle(20, 20, (int)(timePlayed*360.0f), 12, MAROON);
        
      EndDrawing();
    }

  unload_paths(&path, ind);

  UnloadMusicStream(music);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}
