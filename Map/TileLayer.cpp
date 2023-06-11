#include "TileLayer.h"
#include "Texture.h"
#include <iostream>

TileLayer::TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets)
//:m_Tilesize(tilesize), m_RowCount(rowcount), m_ColCount(colcount), m_Tilemap(tilemap), m_Tilesets(tilesets)
{
    m_Tilesize = tilesize;
    m_RowCount = rowcount;
    m_ColCount = colcount;
    m_Tilemap  = tilemap;
    m_Tilesets = tilesets;

    for(unsigned int i=0; i < m_Tilesets.size(); i++)
    {
        Texture::GetInstance()->Load(m_Tilesets[i].Name, "assets/maps/" + m_Tilesets[i].Source);
    }
}

void TileLayer::Render()
{
    for( int i=0; i < m_RowCount; i++)
    {
        for( int j=0; j < m_ColCount; j++)
        {
            int tileID = m_Tilemap[i][j];

            if(tileID == 0)
                continue;
            else
            {
                int index = 0;
                if (m_Tilesets.size() > 1 )
                {
                    for(unsigned int k = 1; k < m_Tilesets.size(); k++)
                    {
                        if(tileID > m_Tilesets[k].FirstID && tileID < m_Tilesets[k].LastID)
                        {
                            tileID = tileID + m_Tilesets[k].TileCount - m_Tilesets[k].LastID;
                            index = k;
                            break;
                        }
                    }
                }

                Tileset ts = m_Tilesets[index];
                int tileRow = tileID / ts.ColCount;
                int tileCol = tileID - tileRow*ts.ColCount-1;

                // if tile is on last column
                if(tileID % ts.ColCount == 0)
                {
                    tileRow --;
                    tileCol = ts.ColCount -1;
                }
                Texture::GetInstance()->DrawTile(ts.Name, ts.TileSize, j*ts.TileSize, i*ts.TileSize, tileRow, tileCol);
            }
        }
    }
}

void TileLayer::Update()
{

}
