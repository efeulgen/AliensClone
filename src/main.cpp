
#include <iostream>
#include "AliensClone/AliensCloneGame.h"

int main()
{
      AliensCloneGame aliensGame;
      aliensGame.Init();
      aliensGame.SetupGame();
      aliensGame.Display();
      aliensGame.Destroy();
      return 0;
}
