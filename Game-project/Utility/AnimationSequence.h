#include <vector>
#include <SDL.h>

class AnimationSequence
{
    public:
        AnimationSequence(std::vector<SDL_Texture*> _textures)
        {
            textures = _textures;
            index    = 0;   
        }
        
        void reset()
        {
            // Reset the animation sequence
            index = 0;
        }
        
		SDL_Texture* getTexture()
        {
            // Return the current texture and then increment the index
            // if index is already at the end of the loop, go back to 0
            int tmp = index;
            if(tmp == (int)textures.size()-1)
            {
                // An animation sequence has finished, so trigger event
                // triggerEvent(...);
                index = 0;
            }else{
				// Move onto next image in the sequence
                index++; 
            }

            return textures[tmp];
        }
    
    private:
        int index; // The current index of the animation sequence
        std::vector<SDL_Texture*> textures; // All the textures in order for the animation sequence
};
