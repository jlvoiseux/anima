#pragma once

class Game 
{
private:
    
    Game(const Game&);
    Game& operator=(const Game&);
    
public:
    
    inline Game() { }
    inline virtual ~Game() { }
    inline virtual void Initialize() { }
    inline virtual void ImGUI() { }
    inline virtual void Update(float inDeltaTime) { }
    inline virtual void Render(float inAspectRatio) { }
    inline virtual void Shutdown() { }
};