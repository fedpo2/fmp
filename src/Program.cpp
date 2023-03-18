#include <raylib.h>
#include <iostream>

//=================================//
//  ./music [cancion1][cancion2].. //
//=================================//
//
//  pause function needs to be reworked
//  


using std::string;

void passSong(int *selector, Music *music, char **argv[]) {
  *selector--;
  *music = LoadMusicStream(*argv[*selector]);
  PlayMusicStream(*music);
}

int main (int argc, char *argv[]) {

  int selector = 0;
  bool pause;
  float timePlayed = 0.0f;
  
  if (argc<2) {
    std::cout << "      FMP - Fede Music Player\n"
              << "//=================================// \n" 
              << "//  ./music [cancion1][cancion2].. // \n"
              << "//=================================// \n\n"; 
    return 0;
  }

  InitWindow(400,200,"fede");
  SetTargetFPS(60);

  InitAudioDevice();
  selector++;
  Music music = LoadMusicStream(argv[selector]);
  PlayMusicStream(music);

    while (!IsKeyReleased(KEY_Q)) {
      
      UpdateMusicStream(music);

      if (IsKeyReleased(KEY_P)) {
        pause = !pause;
        if (pause) {
          PauseMusicStream(music);
        } else {
          ResumeMusicStream(music);
        }
      }
      
      if (IsKeyReleased(KEY_R)) {
        StopMusicStream(music);
        PlayMusicStream(music);
      }

      if (IsKeyReleased(KEY_LEFT)) {
        if(selector !=1){
          --selector;  // mov ax, [mem] => dec ax => mov [mem], ax 
          music = LoadMusicStream(argv[selector]);
          PlayMusicStream(music);
        }
      }

      if (IsKeyReleased(KEY_RIGHT)) {
        if(selector != argc-1){
          ++selector;
          music = LoadMusicStream(argv[selector]);
          PlayMusicStream(music);
        }
      }
      
      timePlayed = GetMusicTimePlayed(music)/GetMusicTimeLength(music);

      //chequea que el tiempo de reproduccion de la musica no sea más larga que la cancion 
      if (timePlayed > 1.0f) {
        timePlayed = 1.0f;
        
        if (selector != argc-1) {
          passSong(&selector, &music, &argv);
        }
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
//by fede






/*
char[] <- campo 


next()
prvius()
*/
