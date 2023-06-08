#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>
#include "Layer.h"

class GameMap
{
    public:
        void Render(){
            for (unsigned int i=0; i <m_Maplayers.size(); i++)
                m_Maplayers[i]->Render();
        }
        void Update(){
            for (unsigned int i=0; i <m_Maplayers.size(); i++)
                m_Maplayers[i]->Update();
        }
        std::vector<Layer*> GetMaplayers() {return m_Maplayers;}

    private:
        friend class MapParser;
        std::vector<Layer*> m_Maplayers;
};

#endif // GAMEMAP_H
