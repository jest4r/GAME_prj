#include "TileLayer.h"
#include "TextureManager.h"
TileLayer::TileLayer(int tilesize, int colcount, int rowcount, TileMap tilemap, TilesetList tilesets):
     m_Tilesize(tilesize), m_ColCount(colcount), m_RowCount(rowcount),  m_Tilemap(tilemap), m_Tilesets(tilesets)
{
    for (unsigned int i = 0; i < m_Tilesets.size(); i++)
    {
        TextureManager::GetInstance()->Load(m_Tilesets[i].Name, "assets/maps/" + m_Tilesets[i].Source);
    }
}

void TileLayer::Render()
{
    for (unsigned int i = 0; i < m_RowCount; i++){
        for (unsigned int j = 0; j < m_ColCount; j++){

            int tileID = m_Tilemap[i][j];

            if (tileID == 0)
                continue;
            else {
                int index = 0;
                if (m_Tilesets.size() > 1){
                    for (unsigned int k = 1; k < m_Tilesets.size(); k++){
                        if (tileID >= m_Tilesets[k].FirstID && tileID <= m_Tilesets[k].LastID){
                            tileID = tileID + m_Tilesets[k].TileCount - m_Tilesets[k].LastID;
                            index = k;
                            break;
                        }
                    }
                }
            Tileset ts = m_Tilesets[index];
            int tilerow = tileID/ts.ColCount;
            int tilecol = tileID - tilerow*ts.ColCount-1;

            if (tileID % ts.ColCount == 0){
                tilerow--;
                tilecol = ts.ColCount - 1;
            }
                TextureManager::GetInstance()->DrawTile(ts.Name, ts.TileSize, j*ts.TileSize, i*ts.TileSize, tilerow, tilecol);
            }
       }
    }
}

void TileLayer::Update()
{

}
