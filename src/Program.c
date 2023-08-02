// Copyright (c) 2023 Federico Polidoro. All Rights Reserved.
#include <raylib.h>
#include <stdio.h>

#define MAX_FILEPATH_RECORDED   4096
#define MAX_FILEPATH_SIZE       2048

int main (int argc, char *argv[]) {

  if (argc<2) {
    printf("%s%s%s%s",
           "     FMP - Fede Music Player\n",
           "//=================================// \n",
           "//  ./music [cancion1][cancion2].. // \n",
           "//=================================// \n\n");
    return 0;
  }
  
  int selector = 1;
  bool pause;
  float timePlayed = 0.1f, lastTime = 0.0f;
  
  InitWindow(400,200,"FMP - Fede Music Player");
  SetTargetFPS(60);

  char *filePaths[MAX_FILEPATH_RECORDED] = { 0 };

  for (int i = 0; i < MAX_FILEPATH_RECORDED; i++) {
    filePaths[i] = (char*)RL_CALLOC(MAX_FILEPATH_SIZE, 1);
  }

  InitAudioDevice();
  Music music = LoadMusicStream(argv[selector]);
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
        music = LoadMusicStream(argv[selector]);
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
        if(selector !=1){
          --selector;  // mov ax, [mem] => dec ax => mov [mem], ax 
          lastTime = 0.0f;
          music = LoadMusicStream(argv[selector]);
          PlayMusicStream(music);
        }
      }

      if (IsKeyReleased(KEY_RIGHT)) {
        if(selector != argc-1){
          ++selector;
          lastTime = 0.0f;
          music = LoadMusicStream(argv[selector]);
          PlayMusicStream(music);
        }
      }
     
      if (IsFileDropped()) {
        FilePathList droppedFiles = LoadDroppedFiles();
        
        music = LoadMusicStream(droppedFiles.paths[0]);
        PlayMusicStream(music);
        
        UnloadDroppedFiles(droppedFiles);
      }

      BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("q = salir\np = pause/resume\nr = reset song\n<-/-> = change song", 20, 48, 20, DARKPURPLE);
        DrawText(argv[selector], 20, 180, 8, BLUE);
        DrawRectangle(20, 20, 360, 12, LIGHTGRAY);
        DrawRectangle(20, 20, (int)(timePlayed*360.0f), 12, MAROON);
        
      EndDrawing();
    }
    
  UnloadMusicStream(music);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}
